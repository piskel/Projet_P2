/*
 * mLightSensor.c
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */


#include "mLightSensor.h"

#include "iI2C.h"
#include "iDio.h"

#define LIGHT_SENSOR_ADDR 0x60 // Slave address
#define LIGHT_SENSOR_WRITE_BIT 0x00
#define LIGHT_SENSOR_READ_BIT 0x01
#define LIGHT_SENSOR_ADDR_AUTO_INC 0x40

#define LIGHT_SENSOR_INT_CFG_REGISTER 0x03
#define LIGHT_SENSOR_IRQ_ENABLE_REGISTER 0x04
#define LIGHT_SENSOR_COMMAND_REGISTER 0x18
#define LIGHT_SENSOR_PARAM_WR_REGISTER 0x17
#define LIGHT_SENSOR_PARAM_RD_REGISTER 0x2E
#define LIGHT_SENSOR_RESPONSE_REGISTER 0x20
#define LIGHT_SENSOR_MEAS_0_REGISTER 0x08
#define LIGHT_SENSOR_MEAS_1_REGISTER 0x09
#define LIGHT_SENSOR_PARAM_QUERY_REGISTER 0b10000000
#define LIGHT_SENSOR_PARAM_SET_REGISTER 0b10100000
#define LIGHT_SENSOR_CHLIST_RAM_REGISTER 0x01
#define LIGHT_SENSOR_PSALS_AUTO_COMMAND 0b00001111


static int mLightSensorErrorCounter = 0;

void mLightSensor_Setup()
	{
	mLightSensorErrorCounter = 0;
	iI2C1_Config();
	iDio_EnablePortClk();

	iDio_PinConfig(kPortC, kPin0, kAlternate1);
	iDio_SetPortDirection(kPortC, kMaskIo0, kIoInput);

	mLightSensor_SendCommand(0x00, 0x00);


	mLightSensor_SingleWrite(LIGHT_SENSOR_MEAS_0_REGISTER, 0x01);
	mLightSensor_SingleWrite(LIGHT_SENSOR_MEAS_1_REGISTER, 0x10);

	char result = mLightSensor_SendCommand(LIGHT_SENSOR_PARAM_SET_REGISTER|LIGHT_SENSOR_CHLIST_RAM_REGISTER, 0b11110000);

	mLightSensor_SendCommand(LIGHT_SENSOR_PSALS_AUTO_COMMAND, 0x00);

	}

void mLightSensor_SingleWrite(char address, char data)
	{
	iI2C1_Enable();
	if(!iI2C1_StartCom()){mLightSensorErrorCounter++;return;}
	if(!iI2C1_SendSlaveAdd(LIGHT_SENSOR_ADDR << 1 | LIGHT_SENSOR_WRITE_BIT)){mLightSensorErrorCounter++;return;}
	if(!iI2C1_SendByte((address & 0x3F)| LIGHT_SENSOR_ADDR_AUTO_INC)){mLightSensorErrorCounter++;return;}
	if(!iI2C1_SendByte(data)){mLightSensorErrorCounter++;return;}
	iI2C1_StopCom();
	iI2C1_Disable();
	}

 char mLightSensor_SingleRead(char address)
	{
	char data;
	iI2C1_Enable();
	if(!iI2C1_StartCom()){mLightSensorErrorCounter++;return 0x00;}
	if(!iI2C1_SendSlaveAdd(LIGHT_SENSOR_ADDR << 1 | LIGHT_SENSOR_WRITE_BIT)){mLightSensorErrorCounter++;return 0x00;}
	if(!iI2C1_SendByte(address)){mLightSensorErrorCounter++;return 0x00;}
	iI2C1_SetRepeatedStartSate();
	if(!iI2C1_SendSlaveAdd(LIGHT_SENSOR_ADDR << 1 | LIGHT_SENSOR_READ_BIT)){mLightSensorErrorCounter++;return 0x00;}
	if (!iI2C1_ReadBytesAndStopCom(&data, 1)){mLightSensorErrorCounter++;return 0x00;}
	iI2C1_Disable();
	return data;
	}

 char mLightSensor_SendCommand(char command, char param_wr)
 	 {
	 mLightSensor_SingleWrite(LIGHT_SENSOR_PARAM_WR_REGISTER, param_wr);
	 mLightSensor_SingleWrite(LIGHT_SENSOR_COMMAND_REGISTER, command);
	 return mLightSensor_SingleRead(LIGHT_SENSOR_RESPONSE_REGISTER);
 	 }

 unsigned int mLightSensor_GetVisibleLight()
 	 {

	 char vis[2] = {0x00, 0x00};
	 vis[0] = mLightSensor_SingleRead(0x22);
	 vis[1] = mLightSensor_SingleRead(0x23);

	 return vis[0] | vis[1] << 8;
 	 }

 unsigned int mLightSensor_GetIR()
 	 {

	 char vis[2] = {0x00, 0x00};
	 vis[0] = mLightSensor_SingleRead(0x24);
	 vis[1] = mLightSensor_SingleRead(0x25);

	 return vis[0] | vis[1] << 8;
 	 }

 // UV not working
 unsigned int mLightSensor_GetUV()
 	 {
	 char vis[2] = {0x00, 0x00};
	 vis[0] = mLightSensor_SingleRead(0x2C);
	 vis[1] = mLightSensor_SingleRead(0x2D);

	 return vis[0] | vis[1] << 8;
 	 }
