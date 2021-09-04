/*
 * mWLSensor.c
 *
 *  Created on: 27 août 2021
 *      Author: luc.froideva
 */


#include "mWLSensor.h"
#include <string.h>

#include "iI2C.h"

#define WL_SENSOR_ADDR_L 0x77
#define WL_SENSOR_ADDR_H 0x78


static char sensorData[20];

static int mWLSensorErrorCounter = 0;


void mWLSensor_Setup()
	{
	mWLSensorErrorCounter = 0;
	iI2C0_Config();
	}


bool mWLSensor_ReadValues()
	{


	char tmpSensorData[20];

	bool fail = false;
	iI2C0_Enable();

	if (!fail && !iI2C0_StartCom()) fail = true;
	if (!fail && !iI2C0_SendSlaveAdd(WL_SENSOR_ADDR_H << 1 | 1)) fail = true;
	if (!fail && !iI2C0_ReadBytesAndStopCom(tmpSensorData, 12)) fail = true;

	if (!fail && !iI2C0_StartCom()) fail = true;
	if (!fail && !iI2C0_SendSlaveAdd(WL_SENSOR_ADDR_L << 1 | 1)) fail = true;
	if (!fail && !iI2C0_ReadBytesAndStopCom(&tmpSensorData[12], 8)) fail = true;


	if(!fail)
		{
		memcpy(sensorData, tmpSensorData, sizeof(char)*20);
		}
	else
		{
		mWLSensorErrorCounter++;
		}
	iI2C0_Disable();

	return !fail;
	}


unsigned char mWLSensor_GetWaterLevel()
	{
	if(!mWLSensor_ReadValues()) return 0;

	float waterLevel = 0;

	for(int i = 0; i < 20; i++)
	{
		waterLevel += sensorData[i];
	}
//	waterLevel /= 20*255;
	waterLevel /= 51;

	return (unsigned char)waterLevel;
	}
