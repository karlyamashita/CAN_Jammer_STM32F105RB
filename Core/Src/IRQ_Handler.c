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
 * IRQ_Handler.c
 *
 *  Created on: Jul 30, 2025
 *      Author: karl.yamashita
 */


#include "main.h"


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_StatusTypeDef hal_status;
	CanRxMsgTypeDef *ptr;

	if(hcan == can1_msg.hcan)
	{
		ptr = &can1_msg.rxQueue[can1_msg.rxPtr.index_IN];
		hal_status = HAL_CAN_GetRxMessage(can1_msg.hcan, CAN_RX_FIFO0, &ptr->header, ptr->data);
		if(hal_status == HAL_OK)
		{
			RingBuff_Ptr_Input(&can1_msg.rxPtr, can1_msg.rxQueueSize);
			TimerCallbackRepetitionStart(&timerCallback, LED_CAN1_Toggle, 20, 2); // blip LED
			can1_msg.rxCounter += 1;
		}
	}
	else if(hcan == can2_msg.hcan)
	{
		ptr = &can2_msg.rxQueue[can2_msg.rxPtr.index_IN];
		hal_status = HAL_CAN_GetRxMessage(can2_msg.hcan, CAN_RX_FIFO0, &ptr->header, ptr->data);
		if(hal_status == HAL_OK)
		{
			RingBuff_Ptr_Input(&can2_msg.rxPtr, can2_msg.rxQueueSize);
			TimerCallbackRepetitionStart(&timerCallback, LED_CAN2_Toggle, 20, 2); // blip LED
			can2_msg.rxCounter += 1;
		}
	}
}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan == can1_msg.hcan)
	{
		TimerCallbackRepetitionStart(&timerCallback, LED_CAN1_Toggle, 20, 2); // blip LED
		CAN_SendMessage(&can1_msg);
	}
	else if(hcan == can2_msg.hcan)
	{
		TimerCallbackRepetitionStart(&timerCallback, LED_CAN2_Toggle, 20, 2); // blip LED
		CAN_SendMessage(&can2_msg);
	}
}

