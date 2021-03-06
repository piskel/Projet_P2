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
