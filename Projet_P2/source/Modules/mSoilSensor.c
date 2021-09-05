/*
 * SoilSensor.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */


#include "mSoilSensor.h"
#include <string.h>
#include "iI2C.h"
#include "mDelay.h"


#define SOIL_SENSOR_ADDR 0x36

#define SOIL_SENSOR_TEMP_BASE_REG 0x00
#define SOIL_SENSOR_TEMP_FUNC_REG 0x04

#define SOIL_SENSOR_MOISTURE_BASE_REG 0x0F
#define SOIL_SENSOR_MOISTURE_FUNC_REG 0x10

#define SOIL_SENSOR_WRITE_BIT 0x00
#define SOIL_SENSOR_READ_BIT 0x01

#define SOIL_SENSOR_READ_DELAY_MS 50

static char sensorData[2] = {0x00, 0x00};

static int mSoilSensorErrorCounter = 0;

static int mSoilSensorDelayId;
static bool mSoilSensorValueRead = false;

void mSoilSensor_Setup()
	{
	mSoilSensorErrorCounter = 0;
	iI2C0_Config();
	mDelay_Setup();

	mSoilSensorDelayId = mDelay_GetDelay(SOIL_SENSOR_READ_DELAY_MS);
	}

// TODO: Adapt for temp values

void mSoilSensor_RequestValues()
	{
	if(!mSoilSensorValueRead) return;

	iI2C0_Enable();
	if(!iI2C0_StartCom()){mSoilSensorErrorCounter++;return;}
	if(!iI2C0_SendSlaveAdd(SOIL_SENSOR_ADDR << 1 | SOIL_SENSOR_WRITE_BIT)){mSoilSensorErrorCounter++;return;}
	if(!iI2C0_SendByte(SOIL_SENSOR_MOISTURE_BASE_REG)){mSoilSensorErrorCounter++;return;}
	if(!iI2C0_SendByte(SOIL_SENSOR_MOISTURE_FUNC_REG)){mSoilSensorErrorCounter++;return;}
	iI2C0_StopCom();
	iI2C0_Disable();

	mSoilSensorValueRead = false;
	mSoilSensorDelayId = mDelay_GetDelay(SOIL_SENSOR_READ_DELAY_MS);

	}

bool mSoilSensor_ReadValues()
	{
	if(!mDelay_IsDelayDone(mSoilSensorDelayId)) return false;
	mDelay_DelayRelease(mSoilSensorDelayId);

	char tmpSensorData[2];
	bool fail = false;

	iI2C0_Enable();
	if (!fail && !iI2C0_StartCom()) fail = true;
	if (!fail && !iI2C0_SendSlaveAdd(SOIL_SENSOR_ADDR << 1 | SOIL_SENSOR_READ_BIT)) fail = true;
	if (!fail && !iI2C0_ReadBytesAndStopCom(tmpSensorData, 2)) fail = true;
	iI2C0_Disable();


	if(!fail)
		{
		memcpy(sensorData, tmpSensorData, sizeof(char)*2);
		}
	else
		{
		mSoilSensorErrorCounter++;
		}

	mSoilSensorValueRead = true;
	return !fail;

	}


int mSoilSensor_GetHumidity()
	{
	int value = sensorData[0] << 8 | sensorData[1];
	float result = (float)(value-200)/1800*100;
	return result;
	}

