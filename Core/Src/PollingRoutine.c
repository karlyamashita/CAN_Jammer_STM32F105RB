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
 * PollingRoutine.c
 *
 *  Created on: Oct 24, 2023
 *      Author: karl.yamashita
 *
 *
 *      Template for projects.
 *
 *      The object of this PollingRoutine.c/h files is to not have to write code in main.c which already has a lot of generated code.
 *      It is cumbersome having to scroll through all the generated code for your own code and having to find a USER CODE section so your code is not erased when CubeMX re-generates code.
 *      
 *      Direction: Call PollingInit before the main while loop. Call PollingRoutine from within the main while loop
 * 
 *      Example;
        // USER CODE BEGIN WHILE
        PollingInit();
        while (1)
        {
            PollingRoutine();
            // USER CODE END WHILE

            // USER CODE BEGIN 3
        }
        // USER CODE END 3

 */


#include "main.h"


const char* Hardware = "USBCAN-2A";

const char* Version = "v1.0.0"; // FW version


#define CAN1_RX_QUEUE_SIZE 8
#define CAN1_TX_QUEUE_SIZE 8
CanRxMsgTypeDef can1RxQueue[CAN1_RX_QUEUE_SIZE] = {0};
CanTxMsgTypeDef can1TxQueue[CAN1_TX_QUEUE_SIZE] = {0};

CAN_MsgStruct can1_msg =
{
	.hcan = &hcan1,
	.rxQueue = can1RxQueue,
	.txQueue = can1TxQueue,
	.rxQueueSize = CAN1_RX_QUEUE_SIZE,
	.txQueueSize = CAN1_TX_QUEUE_SIZE,
	.rxPtr = {0},
	.txPtr = {0}
};

#define CAN2_RX_QUEUE_SIZE 8
#define CAN2_TX_QUEUE_SIZE 8
CanRxMsgTypeDef can2RxQueue[CAN2_RX_QUEUE_SIZE] = {0};
CanTxMsgTypeDef can2TxQueue[CAN2_TX_QUEUE_SIZE] = {0};

CAN_MsgStruct can2_msg =
{
	.hcan = &hcan2,
	.rxQueue = can2RxQueue,
	.txQueue = can2TxQueue,
	.rxQueueSize = CAN2_RX_QUEUE_SIZE,
	.txQueueSize = CAN2_TX_QUEUE_SIZE,
	.rxPtr = {0},
	.txPtr = {0}
};


CAN_Jam_t can1_mod =
{
	.can_jam_size = CAN_JAM_SIZE
};
CAN_Jam_t can2_mod =
{
	.can_jam_size = CAN_JAM_SIZE
};


#define USB_QUEUE_SIZE 16
USB_Data_t usbRxQueue[USB_QUEUE_SIZE] = {0};
USB_Data_t usbTxQueue[USB_QUEUE_SIZE] = {0};

USB_MsgStruct usb_msg =
{
	.rxQueue = usbRxQueue,
	.rxQueueSize = USB_QUEUE_SIZE,
	.txQueue = usbTxQueue,
	.txQueueSize = USB_QUEUE_SIZE
};


void PollingInit(void)
{
	CAN_SetFilter(&can1_msg);
	CAN_SetFilter(&can2_msg);

	TimerCallbackRegisterOnly(&timerCallback, LED_CAN1_Toggle);
	TimerCallbackRepetitionStart(&timerCallback, LED_CAN1_Toggle, 333, 6);

	TimerCallbackRegisterOnly(&timerCallback, LED_CAN2_Toggle);
	TimerCallbackRepetitionStart(&timerCallback, LED_CAN2_Toggle, 333, 6);

	TimerCallbackRegisterOnly(&timerCallback, LED_Status_Toggle);
	TimerCallbackTimerStart(&timerCallback, LED_Status_Toggle, 1000, true);
}

void PollingRoutine(void)
{
    TimerCallbackPoll(&timerCallback);

    USB_Parse(&usb_msg);

	CAN1_Parse(&can1_msg);
	CAN2_Parse(&can2_msg);

	USB_SendMessage(&usb_msg);
}

void USB_Parse(USB_MsgStruct *msg)
{
	int status = -1;
	USB_Data_t usbData = {0};
	char retStr[128] = {0};

	if(USB_DataAvailable(msg))
	{
		switch(msg->msgToParse->Status.id)
		{
		case CMD_CAN1_MESSAGE:
			USB_to_CAN_Send(&can1_msg, msg->msgToParse->Status.data);
			break;
		case CMD_CAN2_MESSAGE:
			USB_to_CAN_Send(&can2_msg, msg->msgToParse->Status.data);
			break;
		case CMD_CAN1_ADD_MOD:
			CAN_Jam_Add(&can1_mod, msg->msgToParse->Status.data);
			break;
		case CMD_CAN2_ADD_MOD:
			CAN_Jam_Add(&can2_mod, msg->msgToParse->Status.data);
			break;
		case CMD_CAN1_DEL_MOD:
			CAN_Jam_Delete(&can1_mod, msg->msgToParse->Status.data);
			break;
		case CMD_CAN2_DEL_MOD:
			CAN_Jam_Delete(&can2_mod, msg->msgToParse->Status.data);
			break;
		case CMD_CAN1_BAUD:
			status = CAN_BTR_Set(&can1_msg, msg->msgToParse->Status.data);
			break;
		case CMD_CAN2_BAUD:
			status = CAN_BTR_Set(&can2_msg, msg->msgToParse->Status.data);
			break;
		case CMD_INFO:
			SendStringInfo(CMD_HARDWARE, (char*)Hardware);
			SendStringInfo(CMD_VERSION, (char*)Version);
			APB1_Frequency_Get(retStr);
			SendStringInfo(CMD_FREQUENCY, retStr);
			CAN_BTR_Get(&can1_msg);
			break;
		case CMD_CAN1_BTR:
			CAN_BTR_Get(&can1_msg);
			break;
		case CMD_CAN2_BTR:
			CAN_BTR_Get(&can2_msg);
			break;
		case CMD_VERSION:
			SendStringInfo(CMD_VERSION, (char*)Version);
			break;
		case CMD_HARDWARE:
			SendStringInfo(CMD_HARDWARE, (char*)Hardware);
			break;
		case CMD_FREQUENCY:
			APB1_Frequency_Get(retStr);
			SendStringInfo(CMD_FREQUENCY, retStr);
			break;
		case CMD_UID:
			STM32_UID_Get(retStr);
			SendStringInfo(CMD_UID, retStr);
			break;
		default:
			status = 1;
			break;
		}

		if(status == -1) // do not ACK/NAK
		{
			return;
		}
		else if(status != 0)
		{
			usbData.Status.id = CMD_NAK; // NAK PC
			usbData.Status.size = 1;
		}
		else
		{
			usbData.Status.id = CMD_ACK; // ACK PC
			usbData.Status.size = 1;
		}

		USB_AddTxBuffer(&usb_msg, &usbData);
	}
}

void CAN_BTR_Get(CAN_MsgStruct *msg)
{
	USB_Data_t usb_data = {0};
	uint32_t btrValue = READ_REG(msg->hcan->Instance->BTR);

	if(msg->hcan == &hcan1)
	{
		usb_data.Status.id = CMD_CAN1_BTR;
	}
	else if(msg->hcan == &hcan2)
	{
		usb_data.Status.id = CMD_CAN2_BTR;
	}
	usb_data.Status.data[0] = btrValue >> 24 & 0xFF;
	usb_data.Status.data[1] = btrValue >> 16 & 0xFF;
	usb_data.Status.data[2] = btrValue >> 8 & 0xFF;
	usb_data.Status.data[3] = btrValue & 0xFF;

	usb_data.Status.size = 4;

	USB_AddTxBuffer(&usb_msg, &usb_data);
}

void APB1_Frequency_Get(char *retStr)
{
	uint32_t freq;

	freq = HAL_RCC_GetPCLK1Freq();

	sprintf(retStr, "%ld", freq);
}

int CAN_BTR_Set(CAN_MsgStruct *msg, uint8_t *data)
{
	HAL_StatusTypeDef hal_status;
	uint32_t btrValue = 0;

	btrValue = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]; // parse the BTR data

	// some of these snippets were copied from HAL_CAN_Init()
	HAL_CAN_DeInit(msg->hcan);

	if (msg->hcan->State == HAL_CAN_STATE_RESET)
	{
		/* Init the low level hardware: CLOCK, NVIC */
		HAL_CAN_MspInit(msg->hcan);
	}

	/* Set the bit timing register */
	WRITE_REG(msg->hcan->Instance->BTR, (uint32_t)(btrValue));

	/* Initialize the error code */
	msg->hcan->ErrorCode = HAL_CAN_ERROR_NONE;

	/* Initialize the CAN state */
	msg->hcan->State = HAL_CAN_STATE_READY;

	hal_status = HAL_CAN_Start(msg->hcan); // start the CAN module

	return hal_status;
}

void SendStringInfo(uint8_t cmd, char *msg)
{
	USB_Data_t usb_data = {0};

	sprintf((char*)usb_data.Status.data, "%s\r\n", msg);

	usb_data.Status.id = cmd;
	usb_data.Status.size = strlen((char*)usb_data.Status.data);

	USB_AddTxBuffer(&usb_msg, &usb_data);
}



