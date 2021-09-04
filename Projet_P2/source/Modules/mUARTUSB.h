/*
 * mUARTUSB.h
 *
 *  Created on: 4 sept. 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MUARTUSB_H_
#define MODULES_MUARTUSB_H_

void mUARTUSB_Setup();

void mUARTUSB_Start();
void mUARTUSB_Stop();
void mUARTUSB_WriteChar(char data);
void mUARTUSB_WriteString(char* data);
void mUARTUSB_WriteData(char* data, int size);
char* mUARTUSB_ReadData();
void mUARTUSB_ClearBuffer();

#endif /* MODULES_MUARTUSB_H_ */
