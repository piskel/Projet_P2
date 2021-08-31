/*
 * mLightSensor.c
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */


#include "mLightSensor.h"

#include "iI2C.h"


#define LIGHT_SENSOR_ADDR 0x60 // Slave address
#define LIGHT_SENSOR_WRITE_BIT 0x00
#define LIGHT_SENSOR_READ_BIT 0x01
#define LIGHT_SENSOR_ADDR_AUTO_INC 0x40
#define LIGHT_SENSOR


void mLightSensor_Setup()
	{
	iI2C1_Config();
	mLightSensor_SendCommand(0b000001111);
	}

void mLightSensor_SingleWrite(char address, char data)
	{
	iI2C1_Enable();
	if(!iI2C1_StartCom()){return;}
	if(!iI2C1_SendSlaveAdd(LIGHT_SENSOR_ADDR << 1 | LIGHT_SENSOR_WRITE_BIT)){return;}
	if(!iI2C1_SendByte((address & 0x3F) | LIGHT_SENSOR_ADDR_AUTO_INC)){return;}
	if(!iI2C1_SendByte(data)){return;}
	iI2C1_SetStopState();
	iI2C1_Disable();
	}

 char mLightSensor_SingleRead(char address)
	{
	char data = 0x00;
	iI2C1_Enable();
	if(!iI2C1_StartCom()){return 0x00;}
	if(!iI2C1_SendSlaveAdd(LIGHT_SENSOR_ADDR << 1 | LIGHT_SENSOR_READ_BIT)){return 0x00;}
	if (!iI2C1_ReadBytesAndStopCom(&data, 1)){return 0x00;}
	iI2C1_SetStopState();
	iI2C1_Disable();
	return data;
	}

 void mLightSensor_SendCommand(char command)
 	 {
	 mLightSensor_SingleWrite(0x18, command);
 	 }

 unsigned int mLightSensor_GetVisibleLight()
 	 {
	 char vis[2] = {0x00, 0x00};
	 vis[0] = mLightSensor_SingleRead(0x22);
	 vis[1] = mLightSensor_SingleRead(0x23);

	 int result = vis[0] | vis[1] << 8;
	 return result;
 	 }

 unsigned int mLightSensor_GetIR()
 	 {

 	 }

