#include "VibrationMonitoring.h"
#include "main.h"
#include "app_mems.h"
#include "MotionSP.h"
#include "sensor_def.h"
#include "custom_motion_sensors.h"
#include "custom_motion_sensors_ex.h"



#define LSM6DSL_HP_DISABLE        0xFBU  /* Disable HP filter */
#define LSM6DSL_HP_ENABLE_DIV400  0x34U  /* Enable HP filter, DIV/400 */
#define LSM6DSL_DEFAULT_ODR       417.0f /* Default output/batch data rate */
//#define LSM6DSL_DEFAULT_ODR       3333.0f /* Default output/batch data rate */
#define LSM6DSL_DEFAULT_FS        2      /* Default full scale */

#define TMsg_EOF                0xF0
#define TMsg_BS                 0xF1
#define TMsg_BS_EOF             0xF2
#define CMD_SF_Data                    0x7D

#define DEV_ADDR                        50U

/* Private function prototypes -----------------------------------------------*/

static void HP_DC_Changer(void);
static uint8_t Enable_DRDY(void);
static uint8_t Disable_DRDY(void);

uint8_t Init_Demo(void);
static uint8_t Meas_Odr(void);
static uint8_t Disable_FIFO(void);
uint8_t Restart_FIFO(void);
static uint8_t Enable_FIFO(void);
uint8_t Collect_Data(void);
void Init_Sensors(void);
int ByteStuffCopyByte(uint8_t *Dest, uint8_t Source);
void UART_SendMsg(TMsg *Msg);
void INIT_STREAMING_HEADER(TMsg *Msg);
void Get_Msg(TMsg *Msg, ACTIVE_AXIS_t AxisActive);
void CHK_ComputeAndAdd(TMsg *Msg);
/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t AccIntReceived = 0;
gui_settings_t GuiSettings = {.hp_filter = 0, .switch_HP_to_DC_null = 0};
static volatile uint32_t IntCurrentTime1 = 0;
static volatile uint32_t IntCurrentTime2 = 0;
static uint8_t RestartFlag = 1;
static uint32_t StartTick = 0;
static volatile uint8_t DataStreamingDest = 1;
static volatile uint8_t UartTxBuffer[TMsg_MaxLen * 2];

UART_HandleTypeDef UartHandle;


extern sAxesMagBuff_t AccAxesAvgMagBuff;


/**
 * @brief  Serial message structure definition
 */


uint8_t Init_Demo(void)
{
  uint8_t data;

  /* Disable HP filter if needed */
  if (SensorSetting.hp_filter_available == 1)
  {
    if (CUSTOM_MOTION_SENSOR_Read_Register(CUSTOM_LSM6DSL_0, LSM6DSL_CTRL8_XL, &data) != BSP_ERROR_NONE)
    {
      return 0;
    }

    data &= LSM6DSL_HP_DISABLE;

    if (CUSTOM_MOTION_SENSOR_Write_Register(CUSTOM_LSM6DSL_0, LSM6DSL_CTRL8_XL, data) != BSP_ERROR_NONE)
    {
      return 0;
    }
  }

  /* Turn-on time delay */
  HAL_Delay(40);

  if (Enable_DRDY() == 0)
  {
    return 0;
  }

  GuiSettings.switch_HP_to_DC_null = 0;
  GuiSettings.hp_filter = 0;
  fftIsEnabled = 0;

  /* Set parameters for MotionSP library */
  MotionSP_Parameters.FftSize = FFT_SIZE_DEFAULT;
  MotionSP_Parameters.tau = TAU_DEFAULT;
  MotionSP_Parameters.window = WINDOW_DEFAULT;
  MotionSP_Parameters.td_type = TD_DEFAULT;
  MotionSP_Parameters.tacq = TACQ_DEFAULT;

  /* Create circular buffer and initialize result variables */
  AccCircBuffer.Size = MotionSP_Parameters.FftSize;
  AccCircBuffer.IdPos = 0;
  AccCircBuffer.Ovf = 0;

  SpeedCircBuffer.Size = MotionSP_Parameters.FftSize;
  SpeedCircBuffer.IdPos = 0;
  SpeedCircBuffer.Ovf=0;

  magSize = MotionSP_Parameters.FftSize / 2;

  /* Reset circular buffer for storing accelerometer values */
  memset(AccCircBuffer.Data.AXIS_X, 0x00, (AccCircBuffer.Size) * (sizeof(float)));
  memset(AccCircBuffer.Data.AXIS_Y, 0x00, (AccCircBuffer.Size) * (sizeof(float)));
  memset(AccCircBuffer.Data.AXIS_Z, 0x00, (AccCircBuffer.Size) * (sizeof(float)));

  /* Reset circular buffer for storing accelerometer values */
  memset(SpeedCircBuffer.Data.AXIS_X, 0x00, (SpeedCircBuffer.Size) * (sizeof(float)));
  memset(SpeedCircBuffer.Data.AXIS_Y, 0x00, (SpeedCircBuffer.Size) * (sizeof(float)));
  memset(SpeedCircBuffer.Data.AXIS_Z, 0x00, (SpeedCircBuffer.Size) * (sizeof(float)));

  /* Reset the TimeDomain parameter values */
  sTimeDomain.AccRms.AXIS_X = 0.0f;
  sTimeDomain.AccRms.AXIS_Y = 0.0f;
  sTimeDomain.AccRms.AXIS_Z = 0.0f;
  sTimeDomain.AccPeak.AXIS_X = 0.0f;
  sTimeDomain.AccPeak.AXIS_Y = 0.0f;
  sTimeDomain.AccPeak.AXIS_Z = 0.0f;
  sTimeDomain.SpeedRms.AXIS_X = 0.0f;
  sTimeDomain.SpeedRms.AXIS_Y = 0.0f;
  sTimeDomain.SpeedRms.AXIS_Z = 0.0f;

  /* Reset the counters of the number of sums about the calculation of the average */
  AccSumCnt.AXIS_X = 0;
  AccSumCnt.AXIS_Y = 0;
  AccSumCnt.AXIS_Z = 0;

  MotionSP_SetWindFiltArray(Filter_Params, MotionSP_Parameters.FftSize, (Filt_Type_t)MotionSP_Parameters.window);

  /* Reset the flag to enable FFT computation */
  fftIsEnabled = 0;

  arm_rfft_fast_init_f32(&fftS, MotionSP_Parameters.FftSize);

  accCircBuffIndexForFft = MotionSP_Parameters.FftSize - 1; /* It is the minimum value to do the first FFT */

  /* Enable AXL data to FIFO with no decimation */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_Decimation(CUSTOM_LSM6DSL_0, MOTION_ACCELERO, LSM6DSL_FIFO_XL_NO_DEC) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* Set FIFO ODR to highest value */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_ODR_Value(CUSTOM_LSM6DSL_0, 6660.0f) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* Set FIFO watermark level */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_Watermark_Level(CUSTOM_LSM6DSL_0, (MotionSP_Parameters.FftSize + 1) * 3) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* Set FIFO to stop on FIFO threshold */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_Stop_On_Fth(CUSTOM_LSM6DSL_0, PROPERTY_ENABLE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  if (SensorSetting.hp_filter_available == 0)
  {
    HP_DC_Changer();
  }

  /* Measure and calculate ODR */
  if (Meas_Odr() == 0)
  {
    return 0;
  }

  return 1;
}
/**
 * @brief  Measure accelerometer real ODR
 * @param  None
 * @retval 1 in case of success 0 otherwise
 */
static uint8_t Meas_Odr(void)
{
  uint8_t  odr_meas_enable = 1;
  uint16_t odr_meas_iter = 0;
  uint16_t odr_meas_start_time = 0;
  uint16_t odr_meas_stop_time = 0;
  uint16_t odr_meas_samples = 150; /* number of measured samples for calculating ODR */
  uint32_t start = 0;

  if (!Disable_FIFO())
  {
    return 0;
  }

  /* Set DRDY pulsed mode */
  if (CUSTOM_MOTION_SENSOR_DRDY_Set_Mode(CUSTOM_LSM6DSL_0, LSM6DSL_DRDY_PULSED) != BSP_ERROR_NONE)
  {
    return 0;
  }

  if (!Enable_DRDY())
  {
    return 0;
  }

  start = HAL_GetTick();

  while (odr_meas_enable)
  {
    if (((HAL_GetTick() - start) > 1000))
    {
      return 0;
    }

    if (AccIntReceived)
    {
      AccIntReceived = 0;

      /* Get start time */
      if (odr_meas_iter == 0)
      {
        IntCurrentTime1 = HAL_GetTick();
        odr_meas_start_time = IntCurrentTime1;
      }

      /* Get stop time */
      if (odr_meas_iter == odr_meas_samples - 1)
      {
        IntCurrentTime2 = HAL_GetTick();
        odr_meas_stop_time = IntCurrentTime2;
        odr_meas_enable = 0;
      }

      /* Stop after measuring "odr_meas_samples" values */
      if (odr_meas_iter < odr_meas_samples)
      {
        odr_meas_iter++;
      }
    }
  }

  /* Calculate measured ODR */
  AcceleroODR.Frequency = ((float)(1000 * odr_meas_samples) / (odr_meas_stop_time - odr_meas_start_time));

  if (AcceleroODR.Frequency != 0)
  {
    AcceleroODR.Period = 1 / AcceleroODR.Frequency;
  }

  AcceleroODR.Tau = exp(-(float)(1000 * AcceleroODR.Period) / MotionSP_Parameters.tau);

  /* Disable accelerometer to avoid interrupt conflicts on highest ODRs */
  if (CUSTOM_MOTION_SENSOR_Disable(CUSTOM_LSM6DSL_0, MOTION_ACCELERO) != BSP_ERROR_NONE)
  {
    return 0;
  }

  if (!Disable_DRDY())
  {
    return 0;
  }

  /* Set DRDY latched mode */
  if (CUSTOM_MOTION_SENSOR_DRDY_Set_Mode(CUSTOM_LSM6DSL_0, LSM6DSL_DRDY_LATCHED) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* Enable accelerometer */
  if (CUSTOM_MOTION_SENSOR_Enable(CUSTOM_LSM6DSL_0, MOTION_ACCELERO) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* Enable FIFO full flag interrupt */
  if (!Enable_FIFO())
  {
    return 0;
  }

  if (!Restart_FIFO())
  {
    return 0;
  }

  return 1;
}

/**
  * @brief  Restart FIFO
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
uint8_t Restart_FIFO(void)
{
  AccIntReceived = 0;

  /* FIFO Bypass Mode */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(CUSTOM_LSM6DSL_0, LSM6DSL_BYPASS_MODE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* FIFO Mode*/
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(CUSTOM_LSM6DSL_0, LSM6DSL_FIFO_MODE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  return 1;
}
/**
  * @brief  Collect data from accelerometer
  * @param  None
  * @retval 1 in case of success
  * @retval 0 otherwise
  */
uint8_t Collect_Data(void)
{
  uint16_t pattern;
  uint16_t samples_in_fifo = 0;
  int32_t acceleration;
  uint32_t start = HAL_GetTick();
  SensorVal_f_t single_data;
  SensorVal_f_t single_data_no_dc;
  uint8_t exit_cond = 0;
  //printf("FinishAvgFlag = %d, fftIsEnabled = %d, AccIntReceived = %d\n",FinishAvgFlag, fftIsEnabled, AccIntReceived);
  if (FinishAvgFlag == 0 && fftIsEnabled == 0 && AccIntReceived == 1)
  {
    AccIntReceived = 0;

    CUSTOM_MOTION_SENSOR_FIFO_Get_Num_Samples(CUSTOM_LSM6DSL_0, &samples_in_fifo);

    if ((samples_in_fifo / 3U) < MotionSP_Parameters.FftSize)
    {
      Restart_FIFO();
      return 0;
    }

    while (fftIsEnabled == 0)
    {
      if (((HAL_GetTick() - start) > 6000))
      {
        Restart_FIFO();
        return 0;
      }

      CUSTOM_MOTION_SENSOR_FIFO_Get_Pattern(CUSTOM_LSM6DSL_0, &pattern);
      CUSTOM_MOTION_SENSOR_FIFO_Get_Axis(CUSTOM_LSM6DSL_0, MOTION_ACCELERO, &acceleration);
      //printf("pattern: %d\n",pattern);
      switch (pattern)
      {
        case X_AXIS:
          single_data.AXIS_X = (float)acceleration;
          break;

        case Y_AXIS:
          single_data.AXIS_Y = (float)acceleration;
          break;

        case Z_AXIS:
          single_data.AXIS_Z = (float)acceleration;

          /* Remove DC offset */
          MotionSP_accDelOffset(&single_data_no_dc, &single_data, DC_SMOOTH, RestartFlag);

          /* Fill the accelero circular buffer */
          MotionSP_CreateAccCircBuffer(&AccCircBuffer, single_data_no_dc);

          /* TIME DOMAIN ANALYSIS: Speed RMS Moving AVERAGE */
         MotionSP_evalSpeedFromAccelero(&SpeedTimeDomain, &AccCircBuffer, RestartFlag);
              // Delete the Speed DC components
         MotionSP_speedDelOffset(&SpeedTimeDomain_noDC, &SpeedTimeDomain, DC_SMOOTH, RestartFlag);

          MotionSP_CreateAccCircBuffer(&SpeedCircBuffer, SpeedTimeDomain);

          if (AccCircBuffer.Ovf == 1)
          {
            fftIsEnabled = 1;
            AccCircBuffer.Ovf = 0;
          }

          MotionSP_TimeDomainProcess(&sTimeDomain, (Td_Type_t)MotionSP_Parameters.td_type, RestartFlag);
//          MotionSP_FillSpeedCircBuffer();
          RestartFlag = 0;
          break;

        default:
          exit_cond = 1;
          break;
      }

      if (exit_cond)
      {
        return 0;
      }
    }

    if (!Restart_FIFO())
    {
      return 0;
    }
  }

  return 1;
}
/**
  * @brief  Enable FIFO measuring
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
static uint8_t Enable_FIFO(void)
{
  /* Enable FIFO full flag interrupt */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_INT1_FIFO_Full(CUSTOM_LSM6DSL_0, PROPERTY_ENABLE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  return 1;
}
/**
  * @brief  Disable FIFO measuring
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
static uint8_t Disable_FIFO(void)
{
  /* Set FIFO to bypass mode */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(CUSTOM_LSM6DSL_0, LSM6DSL_BYPASS_MODE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* Disable FIFO full flag interrupt */
  if (CUSTOM_MOTION_SENSOR_FIFO_Set_INT1_FIFO_Full(CUSTOM_LSM6DSL_0, PROPERTY_DISABLE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  return 1;
}

/**
 * @brief  Changes HP to DCnull and vice versa in main menu options
 * @param  None
 * @retval void
 */
static void HP_DC_Changer(void)
{
  uint8_t ret_err = 0;
  uint8_t data;

  if (GuiSettings.switch_HP_to_DC_null)
  {
    GuiSettings.switch_HP_to_DC_null = 0;
    GuiSettings.hp_filter = 0;
  }
  else
  {
    /* Disable HP filter */
    if (SensorSetting.hp_filter_available)
    {
      if (CUSTOM_MOTION_SENSOR_Read_Register(CUSTOM_LSM6DSL_0, LSM6DSL_CTRL8_XL, &data) != BSP_ERROR_NONE)
      {
        ret_err = 1;
      }

      data &= LSM6DSL_HP_DISABLE;

      if (CUSTOM_MOTION_SENSOR_Write_Register(CUSTOM_LSM6DSL_0, LSM6DSL_CTRL8_XL, data) != BSP_ERROR_NONE)
      {
        ret_err = 1;
      }
    }

    if (ret_err == 0)
    {
      GuiSettings.switch_HP_to_DC_null = 1;
      GuiSettings.hp_filter = 0;
      fftIsEnabled = 0;
    }
  }
}
/**
  * @brief  Enable DRDY
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
static uint8_t Enable_DRDY(void)
{
  CUSTOM_MOTION_SENSOR_AxesRaw_t axes;

  AccIntReceived = 0;

  /* Enable DRDY */

  if ( CUSTOM_MOTION_SENSOR_Set_INT1_DRDY(CUSTOM_LSM6DSL_0, ENABLE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  /* Clear DRDY */
  if (CUSTOM_MOTION_SENSOR_GetAxesRaw(CUSTOM_LSM6DSL_0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE)
  {
    return 0;
  }

  return 1;
}

/**
  * @brief  Disable DRDY
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
static uint8_t Disable_DRDY(void)
{
  /* Disable DRDY */
  if (CUSTOM_MOTION_SENSOR_Set_INT1_DRDY(CUSTOM_LSM6DSL_0, DISABLE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  return 1;
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Initialize all sensors
 * @param  None
 * @retval None
 */
void Init_Sensors(void)
{
  (void)CUSTOM_MOTION_SENSOR_Init(CUSTOM_LSM6DSL_0, MOTION_ACCELERO);

  /* Set accelerometer:
   *   - ODR >= 416Hz
   *   - FS   = <-2g, 2g>
   */
  (void)CUSTOM_MOTION_SENSOR_SetOutputDataRate(CUSTOM_LSM6DSL_0, MOTION_ACCELERO, LSM6DSL_DEFAULT_ODR);
  (void)CUSTOM_MOTION_SENSOR_SetFullScale(CUSTOM_LSM6DSL_0, MOTION_ACCELERO, LSM6DSL_DEFAULT_FS);
  set_mems_int_pin_a_exti();
}

/* Set EXTI settings for Interrupt A */


/**
 * @brief  Initialize the streaming header
 * @param  Msg the pointer to the header to be initialized
 * @retval None
 */
void INIT_STREAMING_HEADER(TMsg *Msg)
{
  Msg->Data[0] = DataStreamingDest;
  Msg->Data[1] = DEV_ADDR;
  Msg->Data[2] = CMD_SF_Data;
  Msg->Len = 3;
}

/**
  * @brief  Get message
  * @param  Msg the pointer to the message to be handled
  * @param  AxisActive currently active axis index
  * @retval None
  */
void Get_Msg(TMsg *Msg, ACTIVE_AXIS_t AxisActive)
{
  uint32_t k = 0;
  float err = -1.0f;
  float temp;

  memcpy(&Msg->Data[3], (void *) &AcceleroODR.Frequency, sizeof(float));
  Msg->Len = 3 + sizeof(float);

  /* Store FFT values to Msg */
  /* Store TimeDomain parameter values to Msg */
  switch (AxisActive)
  {
    case X_AXIS:
      for (k = 0; k < MotionSP_Parameters.FftSize / 2; k++)
      {
        temp = AccAxesAvgMagBuff.AXIS_X[k] * 1000; // * 1000 for Unicleo-GUI
        memcpy(&Msg->Data[Msg->Len + k * sizeof(float)], (void *) &temp, sizeof(float));
      }
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.AccRms.AXIS_X, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.AccPeak.AXIS_X, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.SpeedRms.AXIS_X, sizeof(float));
      break;

    case Y_AXIS:
      for (k = 0; k < MotionSP_Parameters.FftSize / 2; k++)
      {
        temp = AccAxesAvgMagBuff.AXIS_Y[k] * 1000; // * 1000 for Unicleo-GUI
        memcpy(&Msg->Data[Msg->Len + k * sizeof(float)], (void *) &temp, sizeof(float));
      }
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.AccRms.AXIS_Y, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.AccPeak.AXIS_Y, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.SpeedRms.AXIS_Y, sizeof(float));
      break;

    case Z_AXIS:
      for (k = 0; k < MotionSP_Parameters.FftSize / 2; k++)
      {
        temp = AccAxesAvgMagBuff.AXIS_Z[k] * 1000; // * 1000 for Unicleo-GUI
        memcpy(&Msg->Data[Msg->Len + k * sizeof(float)], (void *) &temp, sizeof(float));
      }
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.AccRms.AXIS_Z, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.AccPeak.AXIS_Z, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &sTimeDomain.SpeedRms.AXIS_Z, sizeof(float));
      break;

    default:
      /* Store -1 to Msg to indicate error */
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &err, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &err, sizeof(float));
      memcpy(&Msg->Data[Msg->Len + k++ * sizeof(float)], (void *) &err, sizeof(float));
      break;
  }
  Msg->Len += k * sizeof(float);

  /* Store active axis index to Msg */
  Msg->Data[Msg->Len] = (uint8_t)AxisActive;
  Msg->Len += sizeof(uint8_t);
}

/**
 * @brief  Send a message via UART
 * @param  Msg the pointer to the message to be sent
 * @retval None
 */
void UART_SendMsg(TMsg *Msg)
{
  uint16_t count_out;

  CHK_ComputeAndAdd(Msg);

  /* MISRA C-2012 rule 11.8 violation for purpose */
  count_out = (uint16_t)ByteStuffCopy((uint8_t *)UartTxBuffer, Msg);

  /* MISRA C-2012 rule 11.8 violation for purpose */
  //(void)HAL_UART_Transmit(&UartHandle, (uint8_t *)UartTxBuffer, count_out, 5000);
  //printf("%d\n",(uint8_t *)UartTxBuffer);
//  printf("Dados coletados:\n");
  for (int i=0;i<count_out;i++){
	  printf("%d, %d\n",i,UartTxBuffer[i]);

  }

//  for (int i=0;i<AccCircBuffer.Size;i++){
// 	  printf("%d, %f\n",i, AccCircBuffer.Data.AXIS_X[i]);
//
//  }

  //(void)HAL_UART_Transmit(&huart1, (uint8_t *)UartTxBuffer, count_out, 5000);
}

/**
 * @brief  Compute and add checksum
 * @param  Msg pointer to the message
 * @retval None
 */
void CHK_ComputeAndAdd(TMsg *Msg)
{
  uint8_t chk = 0;
  uint32_t i;

  for (i = 0; i < Msg->Len; i++)
  {
    chk -= Msg->Data[i];
  }

  Msg->Data[i] = chk;
  Msg->Len++;
}

/**
 * @brief  Byte stuffing process for a Msg
 * @param  Dest destination
 * @param  Source source
 * @retval Total number of bytes processed
 */
int ByteStuffCopy(uint8_t *Dest, TMsg *Source)
{
  uint32_t i;
  int32_t count = 0;

  for (i = 0; i < Source->Len; i++)
  {
    count += ByteStuffCopyByte(&Dest[count], Source->Data[i]);
  }

  Dest[count] = TMsg_EOF;
  count++;
  return count;
}
/**
 * @brief  Byte stuffing process for one byte
 * @param  Dest destination
 * @param  Source source
 * @retval Total number of bytes processed
 */
int ByteStuffCopyByte(uint8_t *Dest, uint8_t Source)
{
  int ret = 2;

  switch (Source)
  {
    case TMsg_EOF:
      Dest[0] = TMsg_BS;
      Dest[1] = TMsg_BS_EOF;
      break;

    case TMsg_BS:
      Dest[0] = TMsg_BS;
      Dest[1] = TMsg_BS;
      break;

    default:
      Dest[0] = Source;
      ret = 1;
      break;
  }

  return ret;
}
