/*
 * gCompute.c
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */

#include "gCompute.h"

#include "gMBox.h"

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
	guiPumpMem = gGUI.enablePump;
	comPumpMem = gCOM.enablePump;

	}
