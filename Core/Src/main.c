/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dfsdm.h"
#include "tim.h"
#include "gpio.h"
#include "app_mems.h"

#define LSM6DSL_HP_DISABLE        0xFBU  /* Disable HP filter */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MotionSP.h"
#include "sensor_def.h"
/* USER CODE END Includes */
#define EOF -1
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
static UART_HandleTypeDef console_uart;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//extern uint8_t fftIsEnabled;
//extern uint8_t FinishAvgFlag;
static uint32_t StartTick = 0;
static uint8_t RestartFlag = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

static void Console_UART_Init(void);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//extern void BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *huart);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	ACTIVE_AXIS_t axis_active;
	TMsg msg_dat;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DFSDM1_Init();
  MX_TIM6_Init();
  //MX_MEMS_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  /* UART console init */
   Console_UART_Init();
   Init_Sensors();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  HAL_TIM_Base_Start_IT(&htim6);
  printf("Hello\n");
  printf("Inicializando a placa\n");
  if ( Init_Demo() !=0)
  {
	  printf("Placa inicializada com sucesso.\n");

  }
  else
  {
	  printf("Problema na inicialização da placa.\n");
  }

  while (1)
  {

	//HAL_UART_Transmit(&huart1, "Hello", 5, 3000);
    /* USER CODE END WHILE */

  //MX_MEMS_Process();
    /* USER CODE BEGIN 3 */



	  //Init_Demo();
     if (Collect_Data())
     {
    	 printf("\n\nSOF\n", EOF);
    	 printf("Dados de aquisicao,Fr,%f,Pr,%f,Tau,%f,Amostras,%d,FFT_fr_res,%f\n",
    			 AcceleroODR.Frequency, AcceleroODR.Period, AcceleroODR.Tau, AccCircBuffer.Size,
				 AcceleroODR.Frequency / ((float)(MotionSP_Parameters.FftSize)));
    	 printf("RMS-ACC,ACC_rms_x,%f,ACC_rms_y,%f,ACC_rms_z,%f\n",sTimeDomain.AccRms.AXIS_X,
    			 	 	 	 	 	 	 	 	 	 	 	     sTimeDomain.AccRms.AXIS_Y,
																 sTimeDomain.AccRms.AXIS_Z);
    	 printf("RMS-Speed,Speed_rms_x,%f,Speed_rms_y,%f,Speed_rms_z,%f\n",sTimeDomain.SpeedRms.AXIS_X/100,
    	     			 	 	 	 	 	 	 	 	 	 	 	     sTimeDomain.SpeedRms.AXIS_Y/100,
    	 																 sTimeDomain.SpeedRms.AXIS_Z/100);
    	 printf("Pico-ACC,Pico_acc_x,%f,Pico_acc_y,%f,Pico_acc_z,%f\n",sTimeDomain.AccPeak.AXIS_X,
    			 	 	 	 	 	 	 	 	 	 	 	 	 	 sTimeDomain.AccPeak.AXIS_Y,
    	 														     sTimeDomain.AccPeak.AXIS_Z);
    	 /* Perform Frequency Domain analysis if buffer is full */

        if (fftIsEnabled == 1)
        {
          fftIsEnabled = 0;

          if ((HAL_GetTick() - StartTick) >= MotionSP_Parameters.tacq)
          {
            FinishAvgFlag = 1;
            StartTick = HAL_GetTick();
          }

          MotionSP_FrequencyDomainProcess();
        }
        /* Send data to GUI if total acquisition time is reached */
              if (FinishAvgFlag == 1)
              {
                FinishAvgFlag = 0;

                /* Send all 3 axes data to Unicleo-GUI */
//                for (axis_active = X_AXIS; axis_active < NUM_AXES; axis_active++)
//                {
//                  INIT_STREAMING_HEADER(&msg_dat);
//                  Get_Msg(&msg_dat, axis_active);
////                  if (axis_active == X_AXIS)
////                  {
////                	  printf("\n\n\n\n\n\n\n\nEixoX:\n");
////                  } else if (axis_active == Y_AXIS)
////                  {
////                	  printf("EixoY:\n");
////                  } else if (axis_active == Z_AXIS)
////                  {
////                	  printf("EixoZ:\n");
////                  }
////                  UART_SendMsg(&msg_dat);
//                }
                printf("\n\n\n ACC:\n");
                for (int i=0;i<AccCircBuffer.Size;i++){
                	printf("t_a,%d,x,%f,y,%f,z,%f\n",i, AccCircBuffer.Data.AXIS_X[i], AccCircBuffer.Data.AXIS_Y[i], AccCircBuffer.Data.AXIS_Z[i]);

                   }

                printf("\n\n\n Speed:\n");
				for (int i=0;i<AccCircBuffer.Size;i++){
					printf("t_s,%d,x,%f,y,%f,z,%f\n",i, SpeedCircBuffer.Data.AXIS_X[i], SpeedCircBuffer.Data.AXIS_Y[i], SpeedCircBuffer.Data.AXIS_Z[i]);

				   }
                RestartFlag = 1;
              }

              printf("EOF\n", EOF);
              printf("%d", EOF);
              HAL_Delay(100);
     }
  }
  /* USER CODE END 3 */

}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* EXTI9_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  /* EXTI15_10_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  /* TIM6_DAC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

/* USER CODE BEGIN 4 */
///**
//  * @brief  Retargets the C library scanf function to the USART.
//  * @param  None
//  * @retval None
//  */
//int __io_getchar(void)
//{
//  /* Place your implementation of fgetc here */
//  /* e.g. read a character on USART and loop until the end of read */
//  uint8_t ch = 0;
//  while (HAL_OK != HAL_UART_Receive(&console_uart, (uint8_t *)&ch, 1, 30000))
//  {
//    ;
//  }
//  return ch;
//}
///**
//  * @brief  Retargets the C library printf function to the USART.
//  * @param  None
//  * @retval None
//  */
//int __io_putchar(int ch)
//{
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART2 and Loop until the end of transmission */
//  while (HAL_OK != HAL_UART_Transmit(&console_uart, (uint8_t *) &ch, 1, 30000))
//  {
//    ;
//  }
//  return ch;
//}


/**
  * @brief UART console init function
  */
static void Console_UART_Init(void)
{
  console_uart.Instance = USART1;
  console_uart.Init.BaudRate = 115200;
  console_uart.Init.WordLength = UART_WORDLENGTH_8B;
  console_uart.Init.StopBits = UART_STOPBITS_1;
  console_uart.Init.Parity = UART_PARITY_NONE;
  console_uart.Init.Mode = UART_MODE_TX_RX;
  console_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  console_uart.Init.OverSampling = UART_OVERSAMPLING_16;
#ifdef UART_ONE_BIT_SAMPLE_DISABLE
  console_uart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  console_uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#endif
  BSP_COM_Init(COM1);//,&console_uart);
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
int i;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  i++;

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
}

///**
//  * @brief  Configures COM port.
//  * @param  COM: COM port to be configured.
//  *          This parameter can be one of the following values:
//  *            @arg  COM1
//  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
//  *                configuration information for the specified USART peripheral.
//  */
//void BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *huart)
//{
//  GPIO_InitTypeDef gpio_init_structure;
//
//  /* Enable GPIO clock */
//  DISCOVERY_COMx_TX_GPIO_CLK_ENABLE(COM);
//  DISCOVERY_COMx_RX_GPIO_CLK_ENABLE(COM);
//
//  /* Enable USART clock */
//  DISCOVERY_COMx_CLK_ENABLE(COM);
//
//  /* Configure USART Tx as alternate function */
//  gpio_init_structure.Pin = DISCOVERY_COM1_RX_PIN;//COM_TX_PIN[COM];
//  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
//  gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;
//  gpio_init_structure.Pull = GPIO_NOPULL;
//  gpio_init_structure.Alternate = DISCOVERY_COM1_TX_AF;//COM_TX_AF[COM];
//  HAL_GPIO_Init(DISCOVERY_COM1_RX_GPIO_PORT, &gpio_init_structure);// COM_TX_PORT[COM], &gpio_init_structure);
//
//  /* Configure USART Rx as alternate function */
//  gpio_init_structure.Pin = DISCOVERY_COM1_RX_PIN;//COM_RX_PIN[COM];
//  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
//  gpio_init_structure.Alternate = DISCOVERY_COM1_RX_AF;//COM_RX_AF[COM];
//  HAL_GPIO_Init(DISCOVERY_COM1_RX_GPIO_PORT, &gpio_init_structure);//COM_RX_PORT[COM], &gpio_init_structure);
//
//  //USART_TypeDef* COM_USART[COMn] = {DISCOVERY_COM1};
//
//  //GPIO_TypeDef* COM_TX_PORT[COMn] = {DISCOVERY_COM1_TX_GPIO_PORT};
//  //
//  //GPIO_TypeDef* COM_RX_PORT[COMn] = {DISCOVERY_COM1_RX_GPIO_PORT};
//  //
//  //const uint16_t COM_TX_PIN[COMn] = {DISCOVERY_COM1_TX_PIN};
//  //
//  //const uint16_t COM_RX_PIN[COMn] = {DISCOVERY_COM1_RX_PIN};
//  //
//  //const uint16_t COM_TX_AF[COMn] = {DISCOVERY_COM1_TX_AF};
//  ////
//  //const uint16_t COM_RX_AF[COMn] = {DISCOVERY_COM1_RX_AF};
//
//  /* USART configuration */
////  huart->Instance = COM_USART[COM];
//  huart->Instance = DISCOVERY_COM1;
//  HAL_UART_Init(huart);
//}
///**
//  * @brief  DeInit COM port.
//  * @param  COM: COM port to be configured.
//  *          This parameter can be one of the following values:
//  *            @arg  COM1
//  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
//  *                configuration information for the specified USART peripheral.
//  */
//void BSP_COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart)
//{
//  /* USART configuration */
////  huart->Instance = COM_USART[COM];
//  huart->Instance = DISCOVERY_COM1;
//  HAL_UART_DeInit(huart);
//
//  /* Enable USART clock */
//  DISCOVERY_COMx_CLK_DISABLE(COM);
//
//  /* DeInit GPIO pins can be done in the application
//     (by surcharging this __weak function) */
//
//  /* GPIO pins clock, FMC clock and DMA clock can be shut down in the application
//     by surcharging this __weak function */
//}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
