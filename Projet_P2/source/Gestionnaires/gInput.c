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
	gInput.buttonStateTab[0] = false;
	gInput.buttonStateTab[1] = false;
	gInput.buttonStateTab[2] = false;
	gInput.buttonStateTab[3] = false;
	}

void gInput_Execute()
	{

	gInput.buttonJustPressedTab[0] = (mButton_Read(kMaskButton0) != gInput.buttonStateTab[0]) && mButton_Read(kMaskButton0) == true;
	gInput.buttonJustPressedTab[1] = (mButton_Read(kMaskButton1) != gInput.buttonStateTab[1]) && mButton_Read(kMaskButton1) == true;
	gInput.buttonJustPressedTab[2] = (mButton_Read(kMaskButton2) != gInput.buttonStateTab[2]) && mButton_Read(kMaskButton2) == true;
	gInput.buttonJustPressedTab[3] = (mButton_Read(kMaskButton3) != gInput.buttonStateTab[3]) && mButton_Read(kMaskButton3) == true;

	gInput.buttonStateTab[0] = mButton_Read(kMaskButton0);
	gInput.buttonStateTab[1] = mButton_Read(kMaskButton1);
	gInput.buttonStateTab[2] = mButton_Read(kMaskButton2);
	gInput.buttonStateTab[3] = mButton_Read(kMaskButton3);

	}

