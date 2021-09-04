/*
 * mWaterLevelSensor.h
 *
 *  Created on: 27 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MWLSENSOR_H_
#define MODULES_MWLSENSOR_H_

#include "def.h"


void mWLSensor_Setup();

bool mWLSensor_ReadValues();

unsigned char mWLSensor_GetWaterLevel();


#endif /* MODULES_MWLSENSOR_H_ */
