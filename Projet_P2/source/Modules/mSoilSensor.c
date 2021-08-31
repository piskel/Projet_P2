/*
 * SoilSensor.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */


#include "mSoilSensor.h"
#include <string.h>
#include "iI2C.h"


static char sensorData[2];

void mSoilSensor_Setup()
	{
	iI2C0_Config();

	}




void mSoilSensor_RequestValues()
	{
	iI2C0_Enable();
	if(!iI2C0_StartCom()){return;}
	if(!iI2C0_SendSlaveAdd(SOIL_SENSOR_ADDR << 1 | 0)){return;}
	if(!iI2C0_SendByte(0x0F)){return;}
	if(!iI2C0_SendByte(0x10)){return;}
	iI2C0_SetStopState();
	iI2C0_Disable();
	}

bool mSoilSensor_ReadValues()
	{
	char tmpSensorData[2];
	bool fail = false;

	iI2C0_Enable();
	if (!fail && !iI2C0_StartCom()) fail = true;
	if (!fail && !iI2C0_SendSlaveAdd(SOIL_SENSOR_ADDR << 1 | 1)) fail = true;
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
	return result;
	}

