/*
 * mDisplay.h
 *
 *  Created on: 24 août 2021
 *      Author: luc.froideva
 */

#ifndef MDISPLAY_H_
#define MDISPLAY_H_

#include <def.h>


// Ratio: 102x64


void mDisplay_Setup();

void mDisplay_SendData(char data);
void mDisplay_SendCommand(char command);
void mDisplay_OnOff(bool mode);
void mDisplay_SetContrast(char contrast);
void mDisplay_SendBuffer(bool* buffer);
void mDisplay_SendBufferNew(char* buffer);
void mDisplay_Clear();

#endif /* MDISPLAY_H_ */
