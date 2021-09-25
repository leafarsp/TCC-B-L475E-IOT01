/**
 ******************************************************************************
 * @file    app_mems_int_pin_a_interface.c
 * @author  MEMS Application Team
 * @brief   This file contains the MEMS INT pin A interface
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

/* Includes ------------------------------------------------------------------*/
#include "app_mems_int_pin_a_interface.h"

EXTI_HandleTypeDef hexti11 = {.Line = EXTI_LINE_11};
extern volatile uint8_t MemsEventDetected;
extern volatile uint8_t AccIntReceived;


static void mems_int_pin_a_hardware_event_isr(void);

void set_mems_int_pin_a_exti(void)
{
  /* register event irq handler */
  HAL_EXTI_GetHandle(&hexti11, EXTI_LINE_11);
  HAL_EXTI_RegisterCallback(&hexti11, HAL_EXTI_COMMON_CB_ID, mems_int_pin_a_hardware_event_isr);
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

static void mems_int_pin_a_hardware_event_isr(void)
{
  MemsEventDetected = 1;
  AccIntReceived = 1;

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
