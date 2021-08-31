/*
 * SoilSensor.h
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MSOILSENSOR_H_
#define MODULES_MSOILSENSOR_H_

#include "def.h"

void mSoilSensor_Setup();
void mSoilSensor_RequestValues();
bool mSoilSensor_ReadValues();
float mSoilSensor_GetHumidity();



#endif /* MODULES_MSOILSENSOR_H_ */
