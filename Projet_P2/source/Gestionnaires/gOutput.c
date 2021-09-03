/*
 * gOutput.c
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */

#include "gOutput.h"

#include "gMBox.h"

#include "mPump.h"

void gOutput_Setup()
	{
	gOutput.enablePump = false;

	mPump_Setup();
	}
void gOutput_Execute()
	{
	if(gOutput.enablePump)
		{
		mPump_Enable();
		}
	else
		{
		mPump_Disable();
		}
	}
