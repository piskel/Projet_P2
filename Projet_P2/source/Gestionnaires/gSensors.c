/*
 * gSensors.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */


#include "gSensors.h"
#include "gMBox.h"
#include "mDelay.h"

#include "mWLSensor.h"
#include "mSoilSensor.h"

#define SENSOR_DELAY_MS 500

void gSensors_Setup()
	{
	mWLSensor_Setup();
	mSoilSensor_Setup();

	mDelay_Setup();
	mDelay_GetDelay(SENSOR_DELAY_MS);
	}

void gSensors_Execute()
	{
	if(mDelay_IsDelayDone(0))
		{

		gSensors.waterLevel = mWLSensor_GetWaterLevel();

		mSoilSensor_ReadValues();
		gSensors.soilHumidity = mSoilSensor_GetHumidity();
		mSoilSensor_RequestValues();


		mDelay_ResetFlag();
		mDelay_GetDelay(SENSOR_DELAY_MS);
		}

	}
