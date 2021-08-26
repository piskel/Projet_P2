/*
 * mDisplay.c
 *
 *  Created on: 24 août 2021
 *      Author: luc.froideva
 */

#include <math.h>
#include "mDisplay.h"
#include "iSpi.h"
#include "iDio.h"

void mDisplay_Setup()
	{


	iSpi_Setup();
	iSpi_Enable();

	iDio_EnablePortClk();
	iDio_PinConfig(kPortB, kPin17, kAlternate1); // DC
	iDio_PinConfig(kPortB, kPin18, kAlternate1); // RES_n
	iDio_SetPortDirection(kPortB, kMaskIo17, kIoOutput);
	iDio_SetPortDirection(kPortB, kMaskIo18, kIoOutput);

	iDio_SetPort(kPortB, kMaskIo18, kIoOn);


	mDisplay_SendCommand(0x40); //Set Display start line
	mDisplay_SendCommand(0xA0); //Bottom View no Segment remap
	mDisplay_SendCommand(0xC0); //Bottom View COM scan direction normal
	mDisplay_SendCommand(0x2E); //StartColumnAddress
	mDisplay_SendCommand(0x8D); mDisplay_SendCommand(0x14); //Switch Charge Pump (RESET)

	mDisplay_SendCommand(0x20); mDisplay_SendCommand(0x02); //Set Memory AddressMode

	mDisplay_SendCommand(0x81); mDisplay_SendCommand(0xFF); //Set Brightness
	mDisplay_SendCommand(0xD5); mDisplay_SendCommand(0x40); //Set Display Clock Divide
	mDisplay_SendCommand(0xD9); mDisplay_SendCommand(0xF1); //Set Precharge Periode
	mDisplay_SendCommand(0xAD); mDisplay_SendCommand(0x30); //Set Internal Ref
	mDisplay_SendCommand(0x21); mDisplay_SendCommand(0x0D); mDisplay_SendCommand(0x72); //Set ColumnAddress
	mDisplay_SendCommand(0x22); mDisplay_SendCommand(0x00); mDisplay_SendCommand(0x3F); //Set PageAddress
	mDisplay_SendCommand(0xAF);

	}

void mDisplay_SendData(char data)
	{
	iDio_SetPort(kPortB, kMaskIo17, kIoOn);
	iSpi_SendData(data);

	}

void mDisplay_SendCommand(char command)
	{
	iDio_SetPort(kPortB, kMaskIo17, kIoOff);
	iSpi_SendData(command);
	}


void mDisplay_OnOff(bool mode)
	{
	mDisplay_SendCommand(mode?0xAF:0xAE);
	}


void mDisplay_SetContrast(char contrast)
	{
	mDisplay_SendCommand(0x81);
	mDisplay_SendCommand(contrast);
	}



/**
 * Buffer size : 102 * 64 = 6528
 */
void mDisplay_SendBuffer(bool *buffer)
	{

	int posX, posY = 0;

	// TODO Rename buffer size constant
	for(int i = DISPLAY_MEM_SIZE-1; i >=0 ; i--)
		{
		posX = i%102;
		posY = i/102;

		char line = 0x00;

		for(int j = 0; j < 8; j++)
			{
			 line |= buffer[posX+102*(posY*8+7-j)] << j;
			}

		mDisplay_SendCommand(0xb0+7-posY);
		mDisplay_SendData(line);
		}

	}


void mDisplay_Clear()
	{

	for (int i = 0; i  < 102*8; i++)
		{
		mDisplay_SendCommand(0xb0+i/102);
		mDisplay_SendData(0x00);
		}

	}

