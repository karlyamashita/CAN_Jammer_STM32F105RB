/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>
#define Nop() asm(" NOP ")

// most commonly used. Uncomment if needed.
#include "ErrorStatus.h"
#include "RingBuffer.h"

#include "CAN_Buffer.h"
#include "CAN_Filter.h"
#include "CAN_Jam.h"
#include "CAN_Parser.h"
#include "GPIO_Handler.h"
#include "ProtocolCommands.h"
#include "STM32_UID.h"
#include "TimerCallback.h"
#include "USB_Buffer.h"
#include "UsbAndCanConvert.h"

#include "PollingRoutine.h"


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

extern CAN_MsgStruct can1_msg;
extern CAN_MsgStruct can2_msg;
extern CAN_Jam_t can1_mod;
extern CAN_Jam_t can2_mod;
extern USB_MsgStruct usb_msg;
extern TimerCallbackStruct timerCallback;

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_PA4_Pin GPIO_PIN_4
#define LED_PA4_GPIO_Port GPIOA
#define LED_PA5_Pin GPIO_PIN_5
#define LED_PA5_GPIO_Port GPIOA
#define LED_PB5_Pin GPIO_PIN_5
#define LED_PB5_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
