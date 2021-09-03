/*
 * gCOM.c
 *
 *  Created on: 2 sept. 2021
 *      Author: luc.froideva
 */

#include "gCOM.h"
#include "gMBox.h"

#include "mBLE.h"

//#define COM_QUERY_GET_DATA 0x20

//static char gComBleBuffer[32];
//static char gComUARTBuffer[32];


void gCOM_Setup()
	{
	mBLE_Setup();


	mBLE_Start();


	}

void gCOM_Execute()
	{
	gCOM_BLEHandler();


	}

void gCOM_BLEHandler()
	{
	char bluetoothData[32];

	strcpy(bluetoothData, mBLE_ReadData());
	mBLE_ClearBuffer();

	switch ((COMQuery)bluetoothData[0])
		{
		case kCOMQueryGetData:;
			mBLE_WriteString(gSensors.visibleLight);
			break;
		default:
			break;
		}

	}


