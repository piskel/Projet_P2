/*
 * mBME280.h
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MBME280_H_
#define MODULES_MBME280_H_


typedef struct BME280Data
	{
	unsigned int digT1;
	int digT2;
	int digT3;
	unsigned int digP1;
	int digP2;
	int digP3;
	int digP4;
	int digP5;
	int digP6;
	int digP7;
	int digP8;
	int digP9;
	unsigned char digH1;
	int digH2;
	unsigned char digH3;
	int digH4;
	int digH5;
	unsigned char digH6;
	long tFine;
	} BME280Data;


void mBME280_Setup();

void mBME280_WriteData(char address, char data);
char mBME280_ReadData(char address);
void mBME280_ReadMultData(char address, char* data, int size);

int mBME280_GetPressure();
int mBME280_GetTemperature();
int mBME280_GetHumidity();

double mBME280_CompensateTemperature(unsigned long temp, BME280Data *calib_data);
unsigned long mBME280_CompensatePressure(unsigned long press, BME280Data *calib_data);
unsigned long mBME280_CompensateHumidity(unsigned long humidity, BME280Data *calib_data);


#endif /* MODULES_MBME280_H_ */
