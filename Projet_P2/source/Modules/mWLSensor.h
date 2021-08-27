/*
 * mWaterLevelSensor.h
 *
 *  Created on: 27 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MWLSENSOR_H_
#define MODULES_MWLSENSOR_H_

#include "def.h"

#define WL_SENSOR_ADDR_L 0xEF
#define WL_SENSOR_ADDR_H 0xF1

void mWLSensor_Setup();

bool mWLSensor_ReadValues();

float mWLSensor_GetWaterLevel();


#endif /* MODULES_MWLSENSOR_H_ */
