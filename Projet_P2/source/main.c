/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Laboratoire_1.c
 * @brief   Application entry point.
 */

#include <def.h>
#include <iDio.h>
#include <mButton.h>
#include <mCpu.h>
#include <mDisplay.h>
#include <mGpio.h>
#include <mGraphics.h>
#include "MKL46Z4.h"
//#include <mUI.h>
#include "mWLSensor.h"
#include "mDelay.h"
#include "stdlib.h"
#include "mGUI.h"
#include "mBLE.h"

/* TODO: insert other include files here. */
#include "math.h"


extern const font pixelFont4x5;

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

// System Integration Module, System Clock Gating Control Register 5
//unsigned int *gSimSCGC5Ptr=(unsigned int*)0x40048038;

// Port Control and Interrupts (crossbar)
//unsigned int *gPCRPtr;

#ifndef M_PI
#    define M_PI 3.1415926535897932
#endif

int main(void)
	{
	EnableInterrupts;
	mCpu_Setup();
//	iDio_EnablePortClk();

	mDelay_Setup();
	mButton_Setup();
	mGpio_Setup();
	mDisplay_Setup();
//	mUI_Setup();
	mWLSensor_Setup();
	mGUI_Setup();
	mBLE_Setup();

	mBLE_Start();

	bool buffer[DISPLAY_HEIGHT*DISPLAY_WIDTH];

	bool btn0Mem = false;
	bool btn1Mem = false;
	bool btn2Mem = false;
	bool btn3Mem = false;
	bool btn0 = false;
	bool btn1 = false;
	bool btn2 = false;
	bool btn3 = false;



//	mUI_CreatePage("splash_page");
//	mUI_CreateLabel("splash_label", (point){10, 10}, "Projet P2");
//
//	mUI_AddElementToPage("splash_label", "splash_page");
//
//
//	mUI_PrintPage("splash_page");



	mGUI_CreatePage("main_page");
	mGUI_CreateText("sensor_item_text", (point){0, 0}, true, "Sensors");
	mGUI_CreateText("settings_item_text", (point){0, 8}, true, "Settings");
	mGUI_CreateText("about_item_text", (point){0, 16}, true, "About");
	mGUI_CreateText("test_item_text", (point){30, 30}, true, "X");


	mGUI_CreateText("info_text", (point){10, 50}, false, "NaN");


	mGUI_AddElementToPage("sensor_item_text", "main_page");
	mGUI_AddElementToPage("settings_item_text", "main_page");
	mGUI_AddElementToPage("about_item_text", "main_page");
	mGUI_AddElementToPage("test_item_text", "main_page");
	mGUI_AddElementToPage("info_text", "main_page");



	mGUI_SetCurrentPage("main_page");


	UIText* pTestText = (UIText*) mGUI_GetElementFromName("test_item_text");

	int interval = 0;

	while(1)
		{
		btn0 = mButton_Read(kMaskButton0);
		btn1 = mButton_Read(kMaskButton1);
		btn2 = mButton_Read(kMaskButton2);
		btn3 = mButton_Read(kMaskButton3);

		if(btn0 != btn0Mem && btn0)
			{
			UIText* uiBLE = (UIText*) mGUI_GetElementFromName("test_item_text");
			mBLE_WriteString("AT+NAMEBOUP");

			uiBLE->text = mBLE_ReadData();

//			uiBLE->text = mBLE_ReadChar();
			}

		if(btn1 != btn1Mem && btn1)
			{
			mGUI_NavigateInteractive(false);
			}

		if(btn2 != btn2Mem && btn2)
			{

			mGUI_NavigateInteractive(true);
			}

		if(btn3 != btn3Mem && btn3)
			{
			UIText* pUIText = (UIText*) mGUI_GetElementFromName("info_text");
			pUIText->text = mGUI_GetCurrentElementName();

			}


		mGUI_PrintCurrentPage();


		pTestText->super.position = (point){(int)(cos((double)interval/50)*15)+30, (int)(sin((double)interval/50)*15)+30};

		interval = (interval+1)%1000000;

		btn0Mem = btn0;
		btn1Mem = btn1;
		btn2Mem = btn2;
		btn3Mem = btn3;

		}

	return 0;
	}
