//Arvuivo com as funções que faltam no arquivo "custom_motion_sensors_ex.c"
//se essas funções forem colocadas no próprio arquivo, elas são excluídas ao
//gerar um códgo novo pelo Cube.

#include "custom_motion_sensors_ex.h"



extern void *MotionCompObj[CUSTOM_MOTION_INSTANCES_NBR];
/**
 * @brief  Set DRDY mode (available only for LSM6DSL, ISM330DLC sensor)
 * @param  Instance the device instance
 * @param  Status of DRDY mode
 * @retval BSP status
 */
int32_t CUSTOM_MOTION_SENSOR_DRDY_Set_Mode(uint32_t Instance, uint8_t Status)
{
  int32_t ret;

  switch (Instance)
  {
    case CUSTOM_LSM6DSL_0:
      if (LSM6DSL_Set_DRDY_Mode(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;



    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Set DRDY interrupt on INT1 pin (available only for ISM330DLC sensor)
 * @param  Instance the device instance
 * @param  Status DRDY interrupt on INT1 pin
 * @retval BSP status
 */
int32_t CUSTOM_MOTION_SENSOR_Set_INT1_DRDY(uint32_t Instance, uint8_t Status)
{
  int32_t ret;

  switch (Instance)
  {

    case CUSTOM_LSM6DSL_0:
      if (LSM6DSL_ACC_Set_INT1_DRDY(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;




    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}
