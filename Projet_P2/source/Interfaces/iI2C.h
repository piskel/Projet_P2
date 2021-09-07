/*
------------------------------------------------------------
Copyright 2003-20xx Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier : 	iI2C.h	
Auteur et Date :	Monnerat Serge 8.5.20xx

But : Interface du p�riph�rique I2C 

Modifications
Date		Faite	Ctrl		Description
------------------------------------------------------------
*/
#ifndef __I2C__
#define __I2C__

#include "def.h"


typedef enum
{
	kAckAuto,
	kNoAck
}I2CAckEnum;

typedef enum
{
	kTransferComplete=0x80,
	kInterruptFlag=0x2,
	kRxAK=0x1,
	kBUSY=0x20
}I2CStatusEnum;

typedef enum
{
	kTxMode,
	kRxMode
}I2CTransmiteModeEnum;



//------------------------------------------------------------
// I2C module config
//------------------------------------------------------------
void iI2C0_Config();
void iI2C1_Config();


void iI2C0_Reset(void);

void iI2C1_Reset(void);

//------------------------------------------------------------
// I2C interface enable
//------------------------------------------------------------
void iI2C0_Enable(void);
void iI2C1_Enable(void);

//------------------------------------------------------------
// I2C interface disable
//------------------------------------------------------------
void iI2C0_Disable(void);
void iI2C1_Disable(void);

//------------------------------------------------------------
// Set START state
//------------------------------------------------------------
void iI2C0_SetStartState(void);
void iI2C1_SetStartState(void);

//------------------------------------------------------------
// Set repeated START state
//------------------------------------------------------------
void iI2C0_SetRepeatedStartSate(void);
void iI2C1_SetRepeatedStartSate(void);

//------------------------------------------------------------
// Set STOP state
//------------------------------------------------------------
void iI2C0_SetStopState(void);
void iI2C1_SetStopState(void);

//------------------------------------------------------------
// Generate automatic ACK or not
//------------------------------------------------------------
void iI2C0_SetAckMode(I2CAckEnum aAck);
void iI2C1_SetAckMode(I2CAckEnum aAck);

//------------------------------------------------------------
// Select if we transmit or receive
//------------------------------------------------------------
void iI2C0_TxRxSelect(I2CTransmiteModeEnum aMode);
void iI2C1_TxRxSelect(I2CTransmiteModeEnum aMode);

//------------------------------------------------------------
// Send a data
//------------------------------------------------------------
void iI2C0_SendData(char aData);
void iI2C1_SendData(char aData);

//------------------------------------------------------------
// Wait End of transmit or receive
//------------------------------------------------------------
bool iI2C0_WaitEndOfRxOrTx(void);
bool iI2C1_WaitEndOfRxOrTx(void);

//------------------------------------------------------------
// Read received data, ! generate I2C clock if not in STOP mode
//------------------------------------------------------------
char iI2C0_ReadData(void);
char iI2C1_ReadData(void);

//------------------------------------------------------------
// Get I2C status flags
//------------------------------------------------------------
bool iI2C0_ReadStatus(I2CStatusEnum aStatus);
bool iI2C1_ReadStatus(I2CStatusEnum aStatus);


//------------------------------------------------------------
// Start communication
//------------------------------------------------------------
bool iI2C0_StartCom(void);
bool iI2C1_StartCom(void);

//------------------------------------------------------------
// Send Add slave
//------------------------------------------------------------
bool iI2C0_SendSlaveAdd(char aAdd);
bool iI2C1_SendSlaveAdd(char aAdd);

//------------------------------------------------------------
// Send a byte
//------------------------------------------------------------
bool iI2C0_SendByte(char aData);
bool iI2C1_SendByte(char aData);

//------------------------------------------------------------
// Read bytes
//------------------------------------------------------------
bool iI2C0_ReadBytes(char* aData, char aNbByte);
bool iI2C1_ReadBytes(char* aData, char aNbByte);

//------------------------------------------------------------
// Read last byte
//------------------------------------------------------------
bool iI2C0_ReadLastByte(char* aData, char aNbByte);
bool iI2C1_ReadLastByte(char* aData, char aNbByte);

//------------------------------------------------------------
// Stop communication
//------------------------------------------------------------
bool iI2C0_StopCom(void);
bool iI2C1_StopCom(void);

//------------------------------------------------------------
// Stop communication
//------------------------------------------------------------
bool iI2C0_ReadBytesAndStopCom(char* aData, char aNbByte);
bool iI2C1_ReadBytesAndStopCom(char* aData, char aNbByte);

void iI2C0_SetSpeed(char speed);
void iI2C1_SetSpeed(char speed);


#endif
