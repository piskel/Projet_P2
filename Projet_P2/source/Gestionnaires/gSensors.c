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
#include "mLightSensor.h"
#include "mBME280.h"

#define SENSOR_DELAY_MS 50

int gSensorsDelayId = 0;

void gSensors_Setup()
	{
	mWLSensor_Setup();
	mSoilSensor_Setup();
	mLightSensor_Setup();
	mBME280_Setup();

	mDelay_Setup();
	gSensorsDelayId = mDelay_GetDelay(SENSOR_DELAY_MS);
	}

void gSensors_Execute()
	{
	if(mDelay_IsDelayDone(gSensorsDelayId))
		{


		// Water level
		gSensors.waterLevel = mWLSensor_GetWaterLevel()*100;

		// Soil humidity
		mSoilSensor_ReadValues();
		gSensors.soilHumidity = mSoilSensor_GetHumidity();
		mSoilSensor_RequestValues();

		// Light
		gSensors.visibleLight = mLightSensor_GetVisibleLight();
		gSensors.ir = mLightSensor_GetIR();
		gSensors.uv = mLightSensor_GetUV();

		// BME280
		gSensors.temperature = mBME280_GetTemperature();
		gSensors.pressure = mBME280_GetPressure();
		gSensors.humidity = mBME280_GetHumidity();

//		mDelay_ResetFlag();
		mDelay_DelayRelease(gSensorsDelayId);
		gSensorsDelayId = mDelay_GetDelay(SENSOR_DELAY_MS);
		}

	}
