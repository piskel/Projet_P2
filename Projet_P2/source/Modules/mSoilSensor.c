/*
 * SoilSensor.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */


#include "mSoilSensor.h"
#include <string.h>
#include "iI2C.h"


#define SOIL_SENSOR_ADDR 0x36

#define SOIL_SENSOR_TEMP_BASE_REG 0x00
#define SOIL_SENSOR_TEMP_FUNC_REG 0x04

#define SOIL_SENSOR_MOISTURE_BASE_REG 0x0F
#define SOIL_SENSOR_MOISTURE_FUNC_REG 0x10

#define SOIL_SENSOR_WRITE_BIT 0x00
#define SOIL_SENSOR_READ_BIT 0x01

static char sensorData[2];

void mSoilSensor_Setup()
	{
	iI2C0_Config();

	}


// TODO: Adapt for temp values

void mSoilSensor_RequestValues()
	{
	iI2C0_Enable();
	if(!iI2C0_StartCom()){return;}
	if(!iI2C0_SendSlaveAdd(SOIL_SENSOR_ADDR << 1 | SOIL_SENSOR_WRITE_BIT)){return;}
	if(!iI2C0_SendByte(SOIL_SENSOR_MOISTURE_BASE_REG)){return;}
	if(!iI2C0_SendByte(SOIL_SENSOR_MOISTURE_FUNC_REG)){return;}
	iI2C0_SetStopState();
	iI2C0_Disable();

	}

bool mSoilSensor_ReadValues()
	{
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

	return !fail;

	}


float mSoilSensor_GetHumidity()
	{
	int value = sensorData[0] << 8 | sensorData[1];
	float result = (float)(value-200)/1800*100;
//	float result = value;
	return result;
	}

