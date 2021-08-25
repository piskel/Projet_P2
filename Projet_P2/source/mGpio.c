/*
 * mGpio.c
 *
 *  Created on: 23 août 2021
 *      Author: luc.froideva
 */


#include "mGpio.h"
#include "iDio.h"

void mGpio_Setup()
	{
	iDio_EnablePortClk();

	iDio_PinConfig(kPortA, kPin4, kAlternate1);
	iDio_PinConfig(kPortA, kPin5, kAlternate1);
	iDio_PinConfig(kPortA, kPin6, kAlternate1);
	iDio_PinConfig(kPortA, kPin7, kAlternate1);
	iDio_PinConfig(kPortA, kPin12, kAlternate1);
	iDio_PinConfig(kPortA, kPin13, kAlternate1);
	iDio_PinConfig(kPortA, kPin14, kAlternate1);
	iDio_PinConfig(kPortA, kPin15, kAlternate1);

	iDio_SetPortDirection(kPortA, kMaskIo4+kMaskIo5+kMaskIo6+kMaskIo7+kMaskIo12+kMaskIo13+kMaskIo14+kMaskIo15, kIoOutput);
	}

void mGpio_Enable(GpioMaskEnum aGpio)
	{
	switch (aGpio) {
		case kMaskGpio0:
			iDio_SetPort(kPortA, kMaskIo4, kIoOn);
			break;
		case kMaskGpio1:
			iDio_SetPort(kPortA, kMaskIo5, kIoOn);
			break;
		case kMaskGpio2:
			iDio_SetPort(kPortA, kMaskIo6, kIoOn);
			break;
		case kMaskGpio3:
			iDio_SetPort(kPortA, kMaskIo7, kIoOn);
			break;
		case kMaskGpio4:
			iDio_SetPort(kPortA, kMaskIo12, kIoOn);
			break;
		case kMaskGpio5:
			iDio_SetPort(kPortA, kMaskIo13, kIoOn);
			break;
		case kMaskGpio6:
			iDio_SetPort(kPortA, kMaskIo14, kIoOn);
			break;
		case kMaskGpio7:
			iDio_SetPort(kPortA, kMaskIo15, kIoOn);
			break;
		}
	}

void mGpio_Disable(GpioMaskEnum aGpio)
	{
	switch (aGpio) {
		case kMaskGpio0:
			iDio_SetPort(kPortA, kMaskIo4, kIoOff);
			break;
		case kMaskGpio1:
			iDio_SetPort(kPortA, kMaskIo5, kIoOff);
			break;
		case kMaskGpio2:
			iDio_SetPort(kPortA, kMaskIo6, kIoOff);
			break;
		case kMaskGpio3:
			iDio_SetPort(kPortA, kMaskIo7, kIoOff);
			break;
		case kMaskGpio4:
			iDio_SetPort(kPortA, kMaskIo12, kIoOff);
			break;
		case kMaskGpio5:
			iDio_SetPort(kPortA, kMaskIo13, kIoOff);
			break;
		case kMaskGpio6:
			iDio_SetPort(kPortA, kMaskIo14, kIoOff);
			break;
		case kMaskGpio7:
			iDio_SetPort(kPortA, kMaskIo15, kIoOff);
			break;
		}
	}
