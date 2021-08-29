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

	mCpu_Setup();
//	iDio_EnablePortClk();

	mDelay_Setup();
	mButton_Setup();
	mGpio_Setup();
	mDisplay_Setup();
//	mUI_Setup();
	mWLSensor_Setup();
	mGUI_Setup();

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

	int interval = 0;


	mGUI_CreatePage("main_page");
	mGUI_CreateText("sensor_item_text", (point){0, 0}, true, "Sensors");
	mGUI_CreateText("settings_item_text", (point){0, 8}, true, "Settings");
	mGUI_CreateText("about_item_text", (point){0, 16}, true, "About");

	mGUI_AddElementToPage("sensor_item_text", "main_page");
	mGUI_AddElementToPage("settings_item_text", "main_page");
	mGUI_AddElementToPage("about_item_text", "main_page");


	while(1)
		{
		btn0 = mButton_Read(kMaskButton0);
		btn1 = mButton_Read(kMaskButton1);
		btn2 = mButton_Read(kMaskButton2);
		btn3 = mButton_Read(kMaskButton3);



		if(btn0 != btn0Mem && btn0)
			{
			mGUI_SetCurrentPage("error_page");
			mGUI_PrintCurrentPage();
			}

		if(btn1 != btn1Mem && btn1)
			{

			mGUI_SetCurrentPage("main_page");
			mGUI_NavigateInteractive(false);
			mGUI_PrintCurrentPage();
			}

		if(btn2)
			{

			mGraphics_FillBuffer(buffer, false);
			for(int i = 0; i < DISPLAY_WIDTH; i++)
				{
				int py = (int)(cos((double)((double)i/10.0+(double)interval/5))*10.0)+30;
				mGraphics_DrawPixel(buffer, (point){i, py}, true);
				}

			mGraphics_Print(buffer);
			interval++;
			}

		if(btn3 != btn3Mem && btn3)
			{

			}

		btn0Mem = btn0;
		btn1Mem = btn1;
		btn2Mem = btn2;
		btn3Mem = btn3;

		}

	return 0;
	}
