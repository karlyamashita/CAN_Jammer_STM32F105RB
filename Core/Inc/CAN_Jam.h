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


#define CAN_JAM_SIZE 6 // how many filters to create

// modifyType
enum
{
	CAN_JAM_MOD_BYTE,
	CAN_JAM_MOD_BITS,
	CAN_JAM_MOD_BLOCK,
	CAN_JAM_MOD_PASS
};
// can_jam selection
enum
{
	CAN1_JAM,
	CAN2_JAM
};

typedef struct
{
	uint32_t id; // the id to match
	uint8_t node; // which CANx to use, can1_mod or can2_mod
	uint8_t index; // or key,  probably won't need
	uint8_t modifyType; // CAN_JAM_MOD_BYTE = 0, CAN_JAM_MOD_BITS = 1, CAN_JAM_MOD_BLOCK = 2, CAN_JAM_MOD_PASS = 3
	uint8_t byteToMod; // byte selection 0-7
	uint8_t byteValue[8]; //
	uint8_t bitsToToggle[8];
	uint8_t bitsToHigh[8]; // will override bitsToToggle
	uint8_t bitsToLow[8]; // will override bitsToHigh and bitsToToggle
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


int CAN_Jam_Add(CAN_Jam_t *msg, uint8_t *data);
int CAN_Jam_Delete(CAN_Jam_t *msg,  uint8_t *data);

int CAN_Jam_IDE_Type(CAN_MsgStruct *msg, CAN_Jam_t *jam);
int CAN_Jam_STD_Parse(CAN_MsgStruct *msg, CAN_Jam_t *jam);
int CAN_Jam_EXT_Parse(CAN_MsgStruct *msg, CAN_Jam_t *jam);
int CAN_Jam_Manipulate(CAN_MsgStruct *msg, CAN_Jam_t *jam, int arrayPtr);
int CAN_Jam_ManipulateBytes(CAN_MsgStruct *msg, CAN_Jam_t *jam, int arrayPtr);
int CAN_Jam_ManipulateBits(CAN_MsgStruct *msg, CAN_Jam_t *jam, int arrayPtr);

#endif /* INC_CAN_JAM_H_ */
