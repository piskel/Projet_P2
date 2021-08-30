/*
 * mWLSensor.c
 *
 *  Created on: 27 août 2021
 *      Author: luc.froideva
 */


#include "mWLSensor.h"
#include <string.h>

#include "iI2C.h"


static char sensorData[20];


void mWLSensor_Setup()
	{
	iI2C0_Config();
	}


bool mWLSensor_ReadValues()
	{

	iI2C0_Enable();

	char tmpSensorData[20];

	bool fail = false;

	if (!fail && !iI2C0_StartCom()) fail = true;
	if (!fail && !iI2C0_SendSlaveAdd(WL_SENSOR_ADDR_H)) fail = true;
	if (!fail && !iI2C0_ReadBytesAndStopCom(tmpSensorData, 12)) fail = true;

	if (!fail && !iI2C0_StartCom()) fail = true;
	if (!fail && !iI2C0_SendSlaveAdd(WL_SENSOR_ADDR_L)) fail = true;
	if (!fail && !iI2C0_ReadBytesAndStopCom(&tmpSensorData[12], 8)) fail = true;

	iI2C0_Disable();

	if(!fail)
		{
		memcpy(sensorData, tmpSensorData, sizeof(char)*20);
		}

	return !fail;
	}


float mWLSensor_GetWaterLevel()
	{
	if(!mWLSensor_ReadValues()) return 0;

	float waterLevel = 0;

	for(int i = 0; i < 20; i++)
	{
		waterLevel += sensorData[i];
	}
	waterLevel /= 20*255;

	return waterLevel;
	}
