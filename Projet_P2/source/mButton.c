/*
 * mButton.c
 *
 *  Created on: 23 août 2021
 *      Author: luc.froideva
 */


#include "iDio.h"
#include "mButton.h"

void mButton_Setup()
	{
	iDio_EnablePortClk();

	iDio_PinConfig(kPortB, kPin0, kAlternate1);
	iDio_PinConfig(kPortB, kPin1, kAlternate1);
	iDio_PinConfig(kPortB, kPin2, kAlternate1);
	iDio_PinConfig(kPortB, kPin3, kAlternate1);

	iDio_SetPortDirection(kPortB, kMaskIo0+kMaskIo1+kMaskIo2+kMaskIo3, kIoInput);
	}


bool mButton_Read(ButtonMaskEnum aButton)
	{
	bool aState = false;

	switch (aButton) {
		case kMaskButton0:
			aState = iDio_GetPort(kPortB, kMaskIo0);
			break;
		case kMaskButton1:
			aState = iDio_GetPort(kPortB, kMaskIo1);
			break;
		case kMaskButton2:
			aState = iDio_GetPort(kPortB, kMaskIo2);
			break;
		case kMaskButton3:
			aState = iDio_GetPort(kPortB, kMaskIo3);
			break;
	}
	return aState;
	}
