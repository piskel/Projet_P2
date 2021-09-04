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
	gCOM_UARTUSBHandler();

	}

void gCOM_BLEHandler()
	{
	char bluetoothData[32];

	strcpy(bluetoothData, mBLE_ReadData());
	mBLE_ClearBuffer();

	switch ((COMQuery)bluetoothData[0])
		{
		case kCOMQueryGetData:;

			gCOM_QueryGetData();
			break;
		default:
			break;
		}
	}


void gCOM_UARTUSBHandler()
	{
	char uartUsbData[32];

	for(int i = 0; i < 32; i++)
		{
		uartUsbData[i] = 0;
		}

	strcpy(uartUsbData, mUARTUSB_ReadData());
	mUARTUSB_ClearBuffer();

//	for(int i = 0; i < strlen(uartUsbData); i++)
//		{
//		if(uartUsbData[i] == 13)
//			{
//			mUARTUSB_WriteString("\n");
//			}
//		else
//			{
//			mUARTUSB_WriteString(uartUsbData[i]);
//			}
//		}
	mUARTUSB_WriteString(uartUsbData);




//	switch ((COMQuery)uartUsbData[0])
//		{
//		case kCOMQueryGetData:;
//
//			gCOM_QueryGetData();
//			break;
//		default:
//			break;
//		}



	}

void gCOM_QueryGetData()
	{
	int structSize = sizeof(gSensors);
	char dataPacket[structSize];

	memcpy(dataPacket, &gSensors, structSize);

	mBLE_WriteData(dataPacket, structSize);
	mUARTUSB_WriteData(dataPacket, structSize);
	}

