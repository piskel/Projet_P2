/*
 * mUARTUSB.c
 *
 *  Created on: 4 sept. 2021
 *      Author: luc.froideva
 */


#include "mUARTUSB.h"

#include "iUART.h"
#include "def.h"
#include "string.h"

#define UARTUSB_BUFFER_MAX_SIZE 32
static char mUARTUSBBuffer[UARTUSB_BUFFER_MAX_SIZE];

void mUARTUSB_Setup()
	{
	iUART_Config();
	iUART_SetParity(kUART0, false);
	iUART_SetFrameType(kUART0, false);
	}

void mUARTUSB_Start()
	{
	iUART_SetTX(kUART0, true);
	iUART_SetRX(kUART0, true);
	}

void mUARTUSB_Stop()
	{
	iUART_SetTX(kUART0, false);
	iUART_SetRX(kUART0, false);
	}


void mUARTUSB_WriteChar(char data)
	{
	iUART_SetRTS(kUART0, true);
	while(!iUART_GetFlag(kUART0, kUARTFlagTC) || !iUART_ReceptionDone(kUART0));
	iUART_SetData(kUART0, data);
	iUART_SetRTS(kUART0, false);
	}

void mUARTUSB_WriteString(char* data)
	{
	for(int i = 0; i < strlen(data); i++)
		{
		mUARTUSB_WriteChar(data[i]);
		}
	}
void mUARTUSB_WriteData(char* data, int size)
	{
	for(int i = 0; i < size; i++)
		{
		mUARTUSB_WriteChar(data[i]);
		}
	}


char* mUARTUSB_ReadData()
	{

	bool isUARTBufferEmpty = false;
	int index = 0;
	do
		{
		if(index >= UARTUSB_BUFFER_MAX_SIZE-1) break;
		isUARTBufferEmpty = iUART_GetCharFromBuffer(kUART0, &(mUARTUSBBuffer[index]));
		index++;
		}
	while(!isUARTBufferEmpty || !iUART_ReceptionDone(kUART0));
	return mUARTUSBBuffer;
	}

void mUARTUSB_ClearBuffer()
	{
	for(int i = 0; i < UARTUSB_BUFFER_MAX_SIZE; i++)
		{
		mUARTUSBBuffer[i] = 0;
		}

	}
