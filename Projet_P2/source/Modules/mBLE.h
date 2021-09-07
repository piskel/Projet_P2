/*
 * mBLE.h
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MBLE_H_
#define MODULES_MBLE_H_

#include "def.h"

void mBLE_Setup();

void mBLE_Start();
void mBLE_Stop();

void mBLE_WriteChar(char data);
void mBLE_WriteString(char* data);
void mBLE_WriteData(char* data, int size);

char* mBLE_ReadData();
void mBLE_ClearBuffer();

#endif /* MODULES_MBLE_H_ */
