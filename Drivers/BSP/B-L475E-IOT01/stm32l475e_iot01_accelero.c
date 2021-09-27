/**
  ******************************************************************************
  * @file    stm32l475e_iot01_accelero.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the accelerometer sensor
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l475e_iot01_accelero.h"

#include "lsm6dsl.h"
#include "stm32l475e_iot01_accelero_ex.h"

//void *MotionCompObj[B_L475E_IOT01_MOTION_INSTANCES_NBR];

int32_t BSP_MOTION_SENSOR_Set_INT1_DRDY(uint32_t Instance, uint8_t Status);
static int32_t LSM6DSL_0_Probe(uint32_t Functions);


/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32L475E_IOT01
  * @{
  */

/** @defgroup STM32L475E_IOT01_ACCELERO ACCELERO
  * @{
  */

/** @defgroup STM32L475E_IOT01_ACCELERO_Private_Variables ACCELERO Private Variables 
  * @{
  */    
static ACCELERO_DrvTypeDef *AccelerometerDrv;  
/**
  * @}
  */


#define MOTION_ACCELERO         2U
/** @defgroup STM32L475E_IOT01_ACCELERO_Private_Functions ACCELERO Private Functions
  * @{
  */ 
/**
  * @brief  Initialize the ACCELERO.
  * @retval ACCELERO_OK or ACCELERO_ERROR
  */
ACCELERO_StatusTypeDef BSP_ACCELERO_Init(void)
{  
  ACCELERO_StatusTypeDef ret = ACCELERO_OK;
  
  if (LSM6DSL_0_Probe(MOTION_ACCELERO) != BSP_ERROR_NONE)
       {
//         return BSP_ERROR_NO_INIT;
       }

  return ret;
}

/**
 * @brief  Register Bus IOs for instance 0 if component ID is OK
 * @retval BSP status
 */
static int32_t LSM6DSL_0_Probe(uint32_t Functions)
{
  LSM6DSL_IO_t            io_ctx;
  uint8_t                 id;
  static LSM6DSL_Object_t lsm6dsl_obj_0;
  LSM6DSL_Capabilities_t  cap;
  int32_t ret = BSP_ERROR_NONE;

  /* Configure the accelero driver */
  io_ctx.BusType     = LSM6DSL_I2C_BUS; /* I2C */
  io_ctx.Address     = LSM6DSL_I2C_ADD_H;
  io_ctx.Init        = BSP_I2C1_Init;
  io_ctx.DeInit      = BSP_I2C1_DeInit;
  io_ctx.ReadReg     = BSP_I2C1_ReadReg;
  io_ctx.WriteReg    = BSP_I2C1_WriteReg;
  io_ctx.GetTick     = BSP_GetTick;
//


//  if (LSM6DSL_RegisterBusIO(&lsm6dsl_obj_0, &io_ctx) != LSM6DSL_OK)
//  {
//    ret = BSP_ERROR_UNKNOWN_COMPONENT;
//  }
//  else if (LSM6DSL_ReadID(&lsm6dsl_obj_0, &id) != LSM6DSL_OK)
//  {
//    ret = BSP_ERROR_UNKNOWN_COMPONENT;
//  }
//  else if (id != LSM6DSL_ID)
//  {
//    ret = BSP_ERROR_UNKNOWN_COMPONENT;
//  }
//  else
//  {
//    (void)LSM6DSL_GetCapabilities(&lsm6dsl_obj_0, &cap);
//    MotionCtx[IKS01A2_LSM6DSL_0].Functions = ((uint32_t)cap.Gyro) | ((uint32_t)cap.Acc << 1) | ((uint32_t)cap.Magneto << 2);
//
//    MotionCompObj[IKS01A2_LSM6DSL_0] = &lsm6dsl_obj_0;
//    /* The second cast (void *) is added to bypass Misra R11.3 rule */
//    MotionDrv[IKS01A2_LSM6DSL_0] = (MOTION_SENSOR_CommonDrv_t *)(void *)&LSM6DSL_COMMON_Driver;
//
//    if ((ret == BSP_ERROR_NONE) && ((Functions & MOTION_GYRO) == MOTION_GYRO) && (cap.Gyro == 1U))
//    {
//      /* The second cast (void *) is added to bypass Misra R11.3 rule */
//      MotionFuncDrv[IKS01A2_LSM6DSL_0][FunctionIndex[MOTION_GYRO]] = (MOTION_SENSOR_FuncDrv_t *)(void *)&LSM6DSL_GYRO_Driver;
//
//      if (MotionDrv[IKS01A2_LSM6DSL_0]->Init(MotionCompObj[IKS01A2_LSM6DSL_0]) != LSM6DSL_OK)
//      {
//        ret = BSP_ERROR_COMPONENT_FAILURE;
//      }
//      else
//      {
//        ret = BSP_ERROR_NONE;
//      }
//    }
//    if ((ret == BSP_ERROR_NONE) && ((Functions & MOTION_ACCELERO) == MOTION_ACCELERO) && (cap.Acc == 1U))
//    {
//      /* The second cast (void *) is added to bypass Misra R11.3 rule */
//      MotionFuncDrv[IKS01A2_LSM6DSL_0][FunctionIndex[MOTION_ACCELERO]] = (MOTION_SENSOR_FuncDrv_t *)(
//            void *)&LSM6DSL_ACC_Driver;
//
//      if (MotionDrv[IKS01A2_LSM6DSL_0]->Init(MotionCompObj[IKS01A2_LSM6DSL_0]) != LSM6DSL_OK)
//      {
//        ret = BSP_ERROR_COMPONENT_FAILURE;
//      }
//      else
//      {
//        ret = BSP_ERROR_NONE;
//      }
//    }
//    if ((ret == BSP_ERROR_NONE) && ((Functions & MOTION_MAGNETO) == MOTION_MAGNETO))
//    {
//      /* Return an error if the application try to initialize a function not supported by the component */
//      ret = BSP_ERROR_COMPONENT_FAILURE;
//    }
//  }
  return ret;
}

/**
  * @brief  Initialize ACCELEROMETER extended features.
  * @retval None.
  */
int32_t BSP_extended_init_accel (void){



	//disable Hi-Pass Filter

	//Enable DDRY() - Data Ready interruption pin
//	/* Enable DRDY */
	  if (BSP_MOTION_SENSOR_Set_INT1_DRDY(BSP_LSM6DSL_0, PROPERTY_ENABLE) != BSP_ERROR_NONE)
	  {
	    return 0;
	  }

}

/**
 * @brief  Set DRDY interrupt on INT1 pin (available only for ISM330DLC sensor)
 * @param  Instance the device instance
 * @param  Status DRDY interrupt on INT1 pin
 * @retval BSP status
 */

int32_t BSP_MOTION_SENSOR_Set_INT1_DRDY(uint32_t Instance, uint8_t Status)
{
	int32_t ret;
	  if (LSM6DSL_ACC_Set_INT1_DRDY(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
	  {
		ret = BSP_ERROR_COMPONENT_FAILURE;
	  }
	  else
	  {
		ret = BSP_ERROR_NONE;
	  }
	  return ret;
}

/**
  * @brief  DeInitialize the ACCELERO.
  * @retval None.
  */
void BSP_ACCELERO_DeInit(void)
{
  /* DeInitialize the accelerometer IO interfaces */
  if(AccelerometerDrv != NULL)
  {
    if(AccelerometerDrv->DeInit != NULL)
    {
      AccelerometerDrv->DeInit();
    }
  }
}

/**
  * @brief  Set/Unset the ACCELERO in low power mode.
  * @param  status 0 means disable Low Power Mode, otherwise Low Power Mode is enabled
  * @retval None
  */
void BSP_ACCELERO_LowPower(uint16_t status)
{
  /* Set/Unset the ACCELERO in low power mode */
  if(AccelerometerDrv != NULL)
  {
    if(AccelerometerDrv->LowPower != NULL)
    {
      AccelerometerDrv->LowPower(status);
    }
  }
}

/**
  * @brief  Get XYZ acceleration values.
  * @param  pDataXYZ Pointer on 3 angular accelerations table with  
  *                  pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  * @retval None
  */
void BSP_ACCELERO_AccGetXYZ(int16_t *pDataXYZ)
{
  if(AccelerometerDrv != NULL)
  {
    if(AccelerometerDrv->GetXYZ != NULL)
    {   
      AccelerometerDrv->GetXYZ(pDataXYZ);
    }
  }
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
