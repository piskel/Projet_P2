/*
 * mLightSensor.h
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MLIGHTSENSOR_H_
#define MODULES_MLIGHTSENSOR_H_

void mLightSensor_Setup();
void mLightSensor_SingleWrite(char address, char data);
char mLightSensor_SingleRead(char address);
void mLightSensor_SendCommand(char command);

unsigned int mLightSensor_GetVisibleLight();
unsigned int mLightSensor_GetIR();


#endif /* MODULES_MLIGHTSENSOR_H_ */
