/*
 * gSettings.c
 *
 *  Created on: 7 sept. 2021
 *      Author: luc.froideva
 */

#include "gSettings.h"
#include "gMBox.h"

#include "mMemory.h"


#define SETTINGS_ADDR 0x0000


void gSettings_Setup()
	{
	mMemory_Setup();


//	mMemory_WriteByte(LIGHT_THRESHOLD, 260)
//	int lt = 270;
//	char data[4];
//	mMemory_WriteData(LIGHT_THRESHOLD, &lt, sizeof(int));
//	mMemory_ReadData(LIGHT_THRESHOLD, data, sizeof(int));

	mMemory_ReadData(SETTINGS_ADDR, (char*)&gSettings, sizeof(gSettings));

	}

void gSettings_Execute()
	{

	char test[sizeof(SettingsStruct)];
	if(gCOM.saveSettings == true)
		{
		mMemory_WriteData(SETTINGS_ADDR, (char*)&(gCOM.settings), sizeof(SettingsStruct));
		mMemory_ReadData(SETTINGS_ADDR, (char*)&(gSettings), sizeof(SettingsStruct));

		mMemory_ReadData(SETTINGS_ADDR, test, sizeof(SettingsStruct));

		}

	}
