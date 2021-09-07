/*
 * mBLE.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#include "mBLE.h"
#include "iUART.h"
#include "string.h"
#include "mDelay.h"
#include "iDio.h"
// BLE Baud rate: 115200

#define BLE_COM_RES "OK+Set:"
#define BLE_COM_RENAME "AT+NAME"
#define BLE_COM_SET_BAUD "AT+BAUD"
#define BLE_BUFFER_MAX_SIZE 32


static bool mBleRunning = false;

static char mBleBuffer[BLE_BUFFER_MAX_SIZE];



void mBLE_Setup()
	{
	iDio_EnablePortClk();
	mDelay_Setup();

	iDio_PinConfig(kPortE, kPin4, kAlternate1); // PIO0
	iDio_PinConfig(kPortE, kPin5, kAlternate1); // Reset_n

	iDio_SetPortDirection(kPortE, kMaskIo4, kIoOutput);
	iDio_SetPortDirection(kPortE, kMaskIo5, kIoOutput);

	iDio_SetPort(kPortE, kMaskIo4, kIoOff);
	iDio_SetPort(kPortE, kMaskIo5, kIoOff);

	int resetDelay;

	iDio_SetPort(kPortE, kMaskIo4, kIoOn);
	iDio_SetPort(kPortE, kMaskIo5, kIoOn);


	resetDelay = mDelay_GetDelay(200);
	while(!mDelay_IsDelayDone(resetDelay)){};
	mDelay_DelayRelease(resetDelay);

	mBLE_ClearBuffer();
	iUART_Config();
	iUART_SetParity(kUART1, false);
	iUART_SetFrameType(kUART1, false);

	mBLE_Start();

	resetDelay = mDelay_GetDelay(100);
	while(!mDelay_IsDelayDone(resetDelay)){};
	mDelay_DelayRelease(resetDelay);

	mBLE_WriteString("AT+NAMEP2_LUC");

	mBLE_Stop();


	}

void mBLE_Start()
	{
	iUART_SetTX(kUART1, true);
	iUART_SetRX(kUART1, true);
	mBleRunning = true;
	}

void mBLE_Stop()
	{
	iUART_SetTX(kUART1, false);
	iUART_SetRX(kUART1, false);
	mBleRunning = false;
	}


void mBLE_WriteChar(char data)
	{
	while(!iUART_GetFlag(kUART1, kUARTFlagTC) || !iUART_ReceptionDone(kUART1)){};

	iUART_SetData(kUART1, data);
	}

void mBLE_WriteString(char* data)
	{
	for(int i = 0; i < strlen(data); i++)
		{
		mBLE_WriteChar(data[i]);
		}
//	mBLE_WriteChar(0x00);
	}
void mBLE_WriteData(char* data, int size)
	{
	for(int i = 0; i < size; i++)
		{
		mBLE_WriteChar(data[i]);
		}
	}


char* mBLE_ReadData()
	{

	bool isUARTBufferEmpty = false;
	int index = 0;
	do
		{
		if(index >= BLE_BUFFER_MAX_SIZE-1) break;
		isUARTBufferEmpty = iUART_GetCharFromBuffer(kUART1, &(mBleBuffer[index]));
		index++;
		}
	while(!isUARTBufferEmpty || !iUART_ReceptionDone(kUART1));
	return mBleBuffer;
	}

void mBLE_ClearBuffer()
	{
	for(int i = 0; i < BLE_BUFFER_MAX_SIZE; i++)
		{
		mBleBuffer[i] = 0;
		}

	}
