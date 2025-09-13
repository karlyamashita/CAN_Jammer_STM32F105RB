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


// Standard ASCII characters
#define CMD_ACK 0x06
#define CMD_NAK 0x15

// custom defines
#define CMD_CAN1_MESSAGE 0x80 // Send CAN1 message
#define CMD_CAN2_MESSAGE 0x81 // Send CAN2 message

#define CMD_CAN1_ADD_MOD 0x40 // Add modification
#define CMD_CAN2_ADD_MOD 0x41
#define CMD_CAN1_DEL_MOD 0x42 // delete modification
#define CMD_CAN2_DEL_MOD 0x43
#define CMD_CAN_JAM_RELAY 0x44

#define CMD_INFO 0x90 // N/A
#define CMD_CAN1_BTR 0x91 // send back the CAN BTC value to PC
#define CMD_VERSION 0x92 // send back version to PC
#define CMD_HARDWARE 0x93 // send back hardware type to PC
#define CMD_FREQUENCY 0x94 // send back the APB1 clock frequency to PC

#define CMD_CAN1_BAUD 0x95 // set baud
#define CMD_CAN2_BAUD 0x96 // set baud

#define CMD_CAN2_BTR 0x98 // send back the CAN BTC value to PC

#define CMD_UID 0xEF
