/*
 * mBLE.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#include "mBLE.h"
#include "iUART.h"
// BLE Baud rate: 115200


void mBLE_Setup()
	{
	iUART_Config();
	iUART_SetParity(kUART1, false);
	iUART_SetFrameType(kUART1, false);
	}

void mBLE_Start()
	{
	iUART_SetTX(kUART1, true);
	iUART_SetRX(kUART1, true);
	}

void mBLE_Stop()
	{
	iUART_SetTX(kUART1, false);
	iUART_SetRX(kUART1, false);
	}


void mBLE_WriteChar(char data)
	{
	while(!iUART_GetFlag(kUART1, kUARTFlagTC));
	iUART_SetData(kUART1, data);
	}

void mBLE_WriteString(char* data)
	{
	for(int i = 0; i < strlen(data); i++)
		{
		mBLE_WriteChar(data[i]);
		}
	}


char* mBLE_ReadData()
	{
//	while(!iUART_GetFlag(kUART1, kUARTFlagRDRF));
	return iUART_GetData(kUART1);
	}

