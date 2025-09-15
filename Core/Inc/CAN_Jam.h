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
 * CAN_Tap.h
 *
 *  Created on: Aug 29, 2025
 *      Author: karl.yamashita
 */

#ifndef INC_CAN_JAM_H_
#define INC_CAN_JAM_H_


#define CAN_JAM_SIZE 8 // how many filters to create

enum
{
	CAN1_JAM,
	CAN2_JAM
};

typedef struct
{
	uint32_t ArbID; // the id to match

	uint32_t index:8; // or key,  probably won't need

	uint32_t node:1; // which CANx to apply to, can1_mod = 0 or can2_mod = 1
	uint32_t jam:1;
	uint32_t :6; // reserved

	uint32_t :8; // reserved

	uint8_t byteToMod; // byte mask selection 0-7
	// 8 bytes to here

	uint8_t bitsToToggle[8]; // 8 bit mask for each byte.
	uint8_t bitsToHigh[8]; // 8 bit mask for each byte. Will override bitsToToggle
	uint8_t bitsToLow[8]; // 8 bit mask for each byte. Will override bitsToHigh and bitsToToggle
	uint8_t byteValue[8]; // Will override the above 3 bit type manipulation
}CAN_Jam_Status_t;

typedef struct
{
	union
	{
		uint8_t data[sizeof(CAN_Jam_Status_t)]; // 40 bytes?
		CAN_Jam_Status_t status;
	}Info[CAN_JAM_SIZE];
	uint32_t can_jam_size;
}CAN_Jam_t;

typedef struct
{
	uint32_t can1_relay_disabled;
	uint32_t can2_relay_disabled;
}CAN_Jam_Relay_t;


int CAN_Jam_Add(CAN_Jam_t *msg, uint8_t *data);
int CAN_Jam_Delete(CAN_Jam_t *msg,  uint8_t *data);

int CAN_Jam_IDE_Type(CAN_MsgStruct *msg, CAN_Jam_t *jam);
int CAN_Jam_STD_Parse(CAN_MsgStruct *msg, CAN_Jam_t *jam);
int CAN_Jam_EXT_Parse(CAN_MsgStruct *msg, CAN_Jam_t *jam);
int CAN_Jam_Manipulate(CAN_MsgStruct *msg, CAN_Jam_t *jam, int arrayPtr);
int CAN_Jam_ManipulateBytes(CAN_MsgStruct *msg, CAN_Jam_t *jam, int arrayPtr);
int CAN_Jam_ManipulateBits(CAN_MsgStruct *msg, CAN_Jam_t *jam, int arrayPtr);

int CAN_Jam_Relay_Msg(CAN_Jam_Relay_t *msg, uint8_t *data);


#endif /* INC_CAN_JAM_H_ */
