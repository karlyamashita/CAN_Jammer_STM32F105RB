/*
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Karl Yamashita
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
 */

/*
 * GPIO_Handler.c
 *
 *  Created on: Jul 30, 2025
 *      Author: karl.yamashita
 */


#include "main.h"

// TX
void LED_CAN1_Toggle(void)
{
	HAL_GPIO_TogglePin(LED_PA4_GPIO_Port, LED_PA4_Pin);
}

// RX
void LED_CAN2_Toggle(void)
{
	HAL_GPIO_TogglePin(LED_PA5_GPIO_Port, LED_PA5_Pin);
}

void LED_Status_Toggle(void)
{
	HAL_GPIO_TogglePin(LED_PB5_GPIO_Port, LED_PB5_Pin);
}

void LED_CAN1(bool state)
{
	if(state)
	{
		HAL_GPIO_WritePin(LED_PA4_GPIO_Port, LED_PA4_Pin, GPIO_PIN_RESET); // On
	}
	else
	{
		HAL_GPIO_WritePin(LED_PA4_GPIO_Port, LED_PA4_Pin, GPIO_PIN_SET); // Off
	}
}

void LED_CAN2(bool state)
{
	if(state)
	{
		HAL_GPIO_WritePin(LED_PA5_GPIO_Port, LED_PA5_Pin, GPIO_PIN_RESET); // On
	}
	else
	{
		HAL_GPIO_WritePin(LED_PA5_GPIO_Port, LED_PA5_Pin, GPIO_PIN_SET); // Off
	}
}

void LED_Status(bool state)
{
	if(state)
	{
		HAL_GPIO_WritePin(LED_PB5_GPIO_Port, LED_PB5_Pin, GPIO_PIN_RESET); // On
	}
	else
	{
		HAL_GPIO_WritePin(LED_PB5_GPIO_Port, LED_PB5_Pin, GPIO_PIN_SET); // Off
	}
}





