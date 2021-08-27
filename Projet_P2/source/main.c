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
#include <mUI.h>
#include "mWLSensor.h"
#include "mDelay.h"

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
	mUI_Setup();
	mWLSensor_Setup();


	bool btn0Mem = false;
	bool btn1Mem = false;
	bool btn2Mem = false;
	bool btn3Mem = false;
	bool btn0 = false;
	bool btn1 = false;
	bool btn2 = false;
	bool btn3 = false;

	bool buffer[DISPLAY_BUFFER_SIZE];

	mGraphics_FillBuffer(buffer, false);
	mGraphics_Print(buffer);

	float waterLevel = 0;

	double interval = 0;


	while(1)
		{
		btn0 = mButton_Read(kMaskButton0);
		btn1 = mButton_Read(kMaskButton1);
		btn2 = mButton_Read(kMaskButton2);
		btn3 = mButton_Read(kMaskButton3);



		if(btn0 != btn0Mem && btn0)
			{
			mGraphics_FillBuffer(buffer, false);

			point a = {x:20+cos(interval/10)*20, 			y:20+sin(interval/10)*20};
			point b = {x:20+cos(interval/10 + 2*M_PI/3)*20, y:20+sin(interval/10 + 2*M_PI/3)*20};
			point c = {x:20+cos(interval/10 + 4*M_PI/3)*20, y:20+sin(interval/10 + 4*M_PI/3)*20};


			mGraphics_DrawLine(buffer, a, b, true, 1);
			mGraphics_DrawLine(buffer, b, c, true, 1);
			mGraphics_DrawLine(buffer, c, a, true, 1);


			mGraphics_Print(buffer);
			interval++;

			}

		if(btn1 != btn1Mem && btn1)
			{
			mGraphics_FillBuffer(buffer, false);

			mGraphics_DrawBox(buffer, (point){0, 0}, (point){101, 6}, true, 1, true);
			mGraphics_DrawText(buffer, "Hello world", pixelFont4x5, (point){1, 1}, true);


			mGraphics_Print(buffer);
			}

		if(btn2 != btn2Mem && btn2)
			{
			waterLevel = mWLSensor_GetWaterLevel();

			}

		if(btn3 != btn3Mem && btn3)
			{

			mUI_PrintPage("error_page");
			}

		btn0Mem = btn0;
		btn1Mem = btn1;
		btn2Mem = btn2;
		btn3Mem = btn3;

		}

	return 0;
	}
