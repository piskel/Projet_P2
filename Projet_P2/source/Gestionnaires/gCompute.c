/*
 * gCompute.c
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */

#include "gCompute.h"

#include "gMBox.h"

#define LOW_SOIL_HUM_THRESHOLD 30
#define LOW_LIGHT_THRESHOLD 270

static bool guiPumpMem = false;
static bool comPumpMem = false;

void gCompute_Setup()
	{
	guiPumpMem = gGUI.enablePump;
	comPumpMem = gCOM.enablePump;

	}

void gCompute_Execute()
	{

	if(gGUI.enablePump != guiPumpMem)
		{
		gCompute.enablePump = gGUI.enablePump;
		}
	else if(gCOM.enablePump != comPumpMem)
		{
		gCompute.enablePump = gCOM.enablePump;
		}
	else
	{
//		gCompute.enablePump =gSensors.soilHumidity < LOW_SOIL_HUM_THRESHOLD && gSensors.visibleLight < LOW_LIGHT_THRESHOLD;
	}
	guiPumpMem = gGUI.enablePump;
	comPumpMem = gCOM.enablePump;

	}
