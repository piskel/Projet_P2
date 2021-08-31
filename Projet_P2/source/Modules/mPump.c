/*
 * mPump.c
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */

#include "mPump.h"

#include "iDio.h"

void mPump_Setup()
	{
	iDio_EnablePortClk();
	iDio_PinConfig(kPortE, kPin6, kAlternate1);
	iDio_SetPortDirection(kPortE, kMaskIo6, kIoOutput);
	}


void mPump_Enable()
	{
	iDio_SetPort(kPortE, kMaskIo6, kIoOn);
	}

void mPump_Disable()
	{
	iDio_SetPort(kPortE, kMaskIo6, kIoOff);
	}
