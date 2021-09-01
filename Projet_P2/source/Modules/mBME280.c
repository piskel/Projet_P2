/*
 * mBME280.c
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */

#include "mBME280.h"
#include "iI2C.h"

#define BME280_ADDR 0x76
#define BME280_WRITE_BIT 0x00
#define BME280_READ_BIT 0x01

#define BME280_REG_DIG_T1 0x88
#define BME280_REG_DIG_T2 0x8A
#define BME280_REG_DIG_T3 0x8C
#define BME280_REG_DIG_P1 0x8E
#define BME280_REG_DIG_P2 0x90
#define BME280_REG_DIG_P3 0x92
#define BME280_REG_DIG_P4 0x94
#define BME280_REG_DIG_P5 0x96
#define BME280_REG_DIG_P6 0x98
#define BME280_REG_DIG_P7 0x9A
#define BME280_REG_DIG_P8 0x9C
#define BME280_REG_DIG_P9 0x9E
#define BME280_REG_DIG_H1 0xA1
#define BME280_REG_DIG_H2 0xE1
#define BME280_REG_DIG_H3 0xE3

#define BME280_REG_CALIB_00 0x88
#define BME280_REG_ID 0xD0
#define BME280_REG_RESET 0xE0
#define BME280_REG_CALIB_26 0xE1
#define BME280_REG_CTRL_HUM 0xF2
#define BME280_REG_STATUS 0xF3
#define BME280_REG_CTRL_MEAS 0xF4
#define BME280_REG_CONFIG 0xF5
#define BME280_REG_PRESS_MSB 0xF7
#define BME280_REG_PRESS_LSB 0xF8
#define BME280_REG_PRESS_XLSB 0xF9
#define BME280_REG_TEMP_MSB 0xFA
#define BME280_REG_TEMP_LSB 0xFB
#define BME280_REG_TEMP_xLSB 0xFC
#define BME280_REG_HUM_MSB 0xFD
#define BME280_REG_HUM_LSB 0xFE

static BME280Data bme280Data;

static bool BME280_I2C_Err_Flag = false;

void mBME280_Setup()
	{
	iI2C0_Config();

	char tabCalibData[33];


	mBME280_WriteData(BME280_REG_CONFIG, 0x30);
	mBME280_WriteData(BME280_REG_CTRL_HUM, 0x01);
	mBME280_WriteData(BME280_REG_CTRL_MEAS, 0x57);

	mBME280_ReadMultData(BME280_REG_DIG_T1, tabCalibData, 26);
	mBME280_ReadMultData(BME280_REG_DIG_H2, &tabCalibData[26], 7);

	bme280Data.digT1 = tabCalibData[0] | tabCalibData[1] << 8;
	bme280Data.digT2 = tabCalibData[2] | tabCalibData[3] << 8;
	bme280Data.digT3 = tabCalibData[4] | tabCalibData[5] << 8;

	bme280Data.digP1 = tabCalibData[6] | tabCalibData[7] << 8;
	bme280Data.digP2 = tabCalibData[8] | tabCalibData[9] << 8;
	bme280Data.digP3 = tabCalibData[10] | tabCalibData[11] << 8;
	bme280Data.digP4 = tabCalibData[12] | tabCalibData[13] << 8;
	bme280Data.digP5 = tabCalibData[14] | tabCalibData[15] << 8;
	bme280Data.digP6 = tabCalibData[16] | tabCalibData[17] << 8;
	bme280Data.digP7 = tabCalibData[18] | tabCalibData[19] << 8;
	bme280Data.digP8 = tabCalibData[20] | tabCalibData[21] << 8;
	bme280Data.digP9 = tabCalibData[22] | tabCalibData[23] << 8;

	bme280Data.digH1 = tabCalibData[25];
	bme280Data.digH2 = tabCalibData[26] | tabCalibData[27] << 8;
	bme280Data.digH3 = tabCalibData[28];
	bme280Data.digH4 = 0;
	bme280Data.digH4 = tabCalibData[29] << 4 | (tabCalibData[30] & 0x0F);
	bme280Data.digH5 = 0;
	bme280Data.digH5 = tabCalibData[30] >> 4 | tabCalibData[31] << 4;
	bme280Data.digH6 = tabCalibData[32];

	BME280_I2C_Err_Flag = true;
	}

void mBME280_WriteData(char address, char data)
	{

	iI2C0_Enable();
	if(!iI2C0_StartCom()){return;}
	if(!iI2C0_SendSlaveAdd(BME280_ADDR << 1 | BME280_WRITE_BIT)){return;}
	if(!iI2C0_SendByte(address)){return;}
	if(!iI2C0_SendByte(data)){return;}
	iI2C0_StopCom();
	iI2C0_Disable();
	}


char mBME280_ReadData(char address)
	{
	char data;
	iI2C0_Enable();
	if(!iI2C0_StartCom()){return 0x00;}
	if(!iI2C0_SendSlaveAdd(BME280_ADDR << 1 | BME280_WRITE_BIT)){return 0x00;}
	if(!iI2C0_SendByte(address)){return 0x00;}
	iI2C0_SetRepeatedStartSate();
	if(!iI2C0_SendSlaveAdd(BME280_ADDR << 1 | BME280_READ_BIT)){return 0x00;}
	if (!iI2C0_ReadBytesAndStopCom(&data, 1)){return 0x00;}
	iI2C0_Disable();
	return data;
	}

void mBME280_ReadMultData(char address, char* data, int size)
	{
	iI2C0_Enable();
	if(!iI2C0_StartCom()){return;}
	if(!iI2C0_SendSlaveAdd(BME280_ADDR << 1 | BME280_WRITE_BIT)){return;}
	if(!iI2C0_SendByte(address)){return;}
	iI2C0_SetRepeatedStartSate();
	if(!iI2C0_SendSlaveAdd(BME280_ADDR << 1 | BME280_READ_BIT)){return;}
	if (!iI2C0_ReadBytesAndStopCom(data, size)){return;}
	iI2C0_Disable();
	}


int mBME280_GetPressure()
	{
	char tabPressure[3];

	mBME280_ReadMultData(BME280_REG_PRESS_MSB, tabPressure, 3);

	unsigned long tmpPressure = tabPressure[0] << 12;
	tmpPressure |= tabPressure[1] << 4;
	tmpPressure |= (tabPressure[2]&0xF0) >> 4;
	unsigned long finalPressure = mBME280_CompensatePressure(tmpPressure, &bme280Data);


	return finalPressure;
	}

int mBME280_GetTemperature()
	{
	char tabTemperature[3];

	mBME280_ReadMultData(BME280_REG_TEMP_MSB, tabTemperature, 3);

	unsigned long tmpTemperature = tabTemperature[0]  << 12;
	tmpTemperature |= tabTemperature[1] << 4;
	tmpTemperature |= (tabTemperature[2] & 0xF0) >> 4;
	unsigned int finalTemperature = mBME280_CompensateTemperature(tmpTemperature, &bme280Data);
	return finalTemperature;
	}

int mBME280_GetHumidity()
	{
	char tabHumidity[2];

	mBME280_ReadMultData(BME280_REG_HUM_MSB, tabHumidity, 2);

	unsigned long tmpHumidity = tabHumidity[0] << 8;
	tmpHumidity |= tabHumidity[1];
	unsigned int finalHumidity = mBME280_CompensateHumidity(tmpHumidity, &bme280Data);

	return finalHumidity;
	}

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
// t_fine carries fine temperature as global value
double mBME280_CompensateTemperature(unsigned long temp, BME280Data *calib_data)
	{

		double var1, var2, T;
		var1 = ((((temp >> 3) - (calib_data->digT1 << 1))) * (calib_data->digT2))
				>> 11;
		var2 = (((((temp >> 4) - (calib_data->digT1))
				* ((temp >> 4) - (calib_data->digT1))) >> 12) * (calib_data->digT3))
				>> 14;
		calib_data->tFine = var1 + var2;
		T = (calib_data->tFine * 5 + 128) >> 8;
		return T / 100;

	}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
unsigned long mBME280_CompensatePressure(unsigned long press, BME280Data *calib_data)
	{
		unsigned long var1, var2;
		unsigned long p;
		var1 = ((calib_data->tFine) >> 1) - 64000;
		var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * (calib_data->digP6);
		var2 = var2 + ((var1 * (calib_data->digP5)) << 1);
		var2 = (var2 >> 2) + ((calib_data->digP4) << 16);
		var1 = (((calib_data->digP3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3)
				+ (((calib_data->digP2) * var1) >> 1)) >> 18;
		var1 = ((((32768 + var1)) * (calib_data->digP1)) >> 15);
		if (var1 == 0)
			{
				return 0; // avoid exception caused by division by zero
			}
		p = ((((1048576) - press) - (var2 >> 12))) * 3125;
		if (p < 0x80000000)
			{
				p = (p << 1) / (var1);
			}
		else
			{
				p = (p / var1) * 2;
			}
		var1 = ((calib_data->digP9) * ((((p >> 3) * (p >> 3)) >> 13))) >> 12;
		var2 = (((p >> 2)) * (calib_data->digP8)) >> 13;
		p = (p + ((var1 + var2 + calib_data->digP7) >> 4));
		return p / 100;

	}

// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
// Output value of “47445” represents 47445/1024 = 46.333 %RH
unsigned long mBME280_CompensateHumidity(unsigned long humidity, BME280Data *calib_data)
	{
		unsigned long v_x1_u32r;
		v_x1_u32r = (calib_data->tFine - (76800));
		v_x1_u32r = (((((humidity << 14) - ((calib_data->digH4) << 20)
				- ((calib_data->digH5) * v_x1_u32r)) + (16384)) >> 15)
				* (((((((v_x1_u32r * (calib_data->digH6)) >> 10)
						* (((v_x1_u32r * (calib_data->digH3)) >> 11) + (32768))) >> 10)
						+ (2097152)) * (calib_data->digH2) + 8192) >> 14));
		v_x1_u32r = (v_x1_u32r
				- (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7)
						* (calib_data->digH1)) >> 4));
		v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
		v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
		return (v_x1_u32r >> 12)/1024;
	}
