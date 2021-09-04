/*
 * gCOM.c
 *
 *  Created on: 2 sept. 2021
 *      Author: luc.froideva
 */

#include "gCOM.h"
#include "string.h"

#include "gMBox.h"

#include "mBLE.h"
#include "mUARTUSB.h"

//#define COM_QUERY_GET_DATA 0x20

//static char gComBleBuffer[32];
//static char gComUARTBuffer[32];


void gCOM_Setup()
	{
	mBLE_Setup();
	mUARTUSB_Setup();



	mBLE_Start();
	mUARTUSB_Start();


	}

void gCOM_Execute()
	{
	gCOM_BLEHandler();


	}

void gCOM_BLEHandler()
	{
	char bluetoothData[32];
	char uartUsbData[32];

	strcpy(bluetoothData, mBLE_ReadData());
	strcpy(uartUsbData, mUARTUSB_ReadData());
	mBLE_ClearBuffer();
	mUARTUSB_ClearBuffer();

	mUARTUSB_WriteString(uartUsbData);

	switch ((COMQuery)bluetoothData[0])
		{
		case kCOMQueryGetData:;

			gCOM_QueryGetData();
			break;
		default:
			break;
		}
	}


void gCOM_QueryGetData()
	{
	int structSize = sizeof(gSensors);
	char dataPacket[structSize];

	memcpy(dataPacket, &gSensors, structSize);

	mBLE_WriteData(dataPacket, structSize);
	}

