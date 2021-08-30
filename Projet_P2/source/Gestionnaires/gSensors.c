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

#define SOIL_SENSOR_DELAY_MS 50

void gSensors_Setup()
	{
	mWLSensor_Setup();
	mDelay_Setup();

	mDelay_GetDelay(SOIL_SENSOR_DELAY_MS);
	}

void gSensors_Execute()
	{


	gSensors.waterLevel = mWLSensor_GetWaterLevel();


	}
