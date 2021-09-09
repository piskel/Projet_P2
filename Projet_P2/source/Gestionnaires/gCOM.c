/*
 * gCOM.c
 *
 *  Created on: 2 sept. 2021
 *      Author: luc.froideva
 */

#include "gCOM.h"
#include "def.h"
#include "string.h"

#include "gMBox.h"

#include "mBLE.h"
#include "mUARTUSB.h"
#include "mMemory.h"

//#define COM_QUERY_GET_DATA 0x20

//static char gComBleBuffer[32];
//static char gComUARTBuffer[32];

#define BLE_MAX_PACKET_SIZE 20

//static int gCOMTestDelay;

void gCOM_Setup()
	{
	mBLE_Setup();
	mUARTUSB_Setup();


	mBLE_Start();
	mUARTUSB_Start();

	memcpy((char*)&(gCOM.settings), &gSettings, sizeof(SettingsStruct));

//	char test = mBLE_ReadData();
	}

void gCOM_Execute()
	{
	// Checking if the settings were applied in the memory
	if(memcmp(&(gCOM.settings), &gSettings, sizeof(SettingsStruct)) == true)
		{
		gCOM.saveSettings = false;
		}


	gCOM_BLEHandler();
	gCOM_UARTUSBHandler();
	}

void gCOM_BLEHandler()
	{
	char bluetoothData[32];

	strcpy(bluetoothData, mBLE_ReadData());
	mBLE_ClearBuffer();

	char response[32];
	int size = 0;

	gCOM_HandleQuery(bluetoothData, response, &size);

	if(size > 0)
		{
		mBLE_WriteData(response, size);
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
	mUARTUSB_WriteString(uartUsbData);


	}

void gCOM_QueryGetData()
	{
	int structSize = sizeof(gSensors);
	char dataPacket[structSize];

	memcpy(dataPacket, &gSensors, structSize);

	mBLE_WriteData(dataPacket, structSize);
	mUARTUSB_WriteData(dataPacket, structSize);
	}


void gCOM_HandleQuery(const char* query, char* response, int* size)
	{
	// Emptying response buffer
	for(int i = 0; i < 32; i++)
		{
		response[i] = 0;
		}


	response[0] = query[0];
	*size = 1;

	switch ((COMQuery)query[0])
		{
		case kCOMQueryGetWL:;
			response[1] = gSensors.waterLevel;
			*size += sizeof(gSensors.waterLevel);
			break;

		case kCOMQueryGetSoilHum:;
			response[1] = gSensors.soilHumidity;
			*size += sizeof(gSensors.soilHumidity);
			break;

		case kCOMQueryGetVisLight:;
			response[1] = gSensors.visibleLight;
			*size += sizeof(gSensors.visibleLight);
			break;

		case kCOMQueryGetIR:;
			response[1] = gSensors.ir;
			*size += sizeof(gSensors.ir);
			break;

		case kCOMQueryGetTemp:;
			response[1] = gSensors.temperature;
			*size += sizeof(gSensors.temperature);
			break;

		case kCOMQueryGetPress:;
			response[1] = gSensors.pressure;
			*size += sizeof(gSensors.pressure);
			break;

		case kCOMQueryGetHum:;
			response[1] = gSensors.humidity;
			*size += sizeof(gSensors.humidity);
			break;

		case kCOMQueryEnablePump:;
			gCOM.enablePump = true;
			*size = 0;
			break;

		case kCOMQueryDisablePump:;
			gCOM.enablePump = false;
			*size = 0;
			break;

		case kCOMQueryGetSettings:;
			memcpy(&(response[1]), &gSettings, sizeof(SettingsStruct));
			break;

		case kCOMQuerySetSettings:;

			memcpy((char*)&(gCOM.settings), &(query[1]), sizeof(SettingsStruct));
			gCOM.saveSettings = true;

			break;

		default:;
			*size = 0;
			break;

		}
	}

