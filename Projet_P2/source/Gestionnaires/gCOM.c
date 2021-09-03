/*
 * gCOM.c
 *
 *  Created on: 2 sept. 2021
 *      Author: luc.froideva
 */

#include "gCOM.h"
#include "gMBox.h"

#include "mBLE.h"

#define COM_QUERY_GET_DATA 0x20

static char gComBleBuffer[32];
//static char gComUARTBuffer[32];


void gCOM_Setup()
	{
	mBLE_Setup();

//	mBLE_RenameDevice("Test123");

	mBLE_Start();
	mBLE_WriteString("AT+ADDR?");
	char* test = mBLE_ReadData();
//	strcpy(test, mBLE_ReadData());



	}

void gCOM_Execute()
	{


	mBLE_ReadData();


	char* test = mBLE_ReadData();

//	mBLE_Start();
//	gCOM.bleData = mBLE_ReadData();
//	mBLE_Stop();
	}
