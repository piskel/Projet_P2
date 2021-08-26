/*
 * gInput.c
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */

#include "gInput.h"
#include "gMBox.h"

#include "mButton.h"

void gInput_Setup()
	{
	mButton_Setup();
	}

void gInput_Execute()
	{
	gInput.buttonTab[0] = mButton_Read(kMaskButton0);
	gInput.buttonTab[1] = mButton_Read(kMaskButton1);
	gInput.buttonTab[2] = mButton_Read(kMaskButton2);
	gInput.buttonTab[3] = mButton_Read(kMaskButton3);
	}

