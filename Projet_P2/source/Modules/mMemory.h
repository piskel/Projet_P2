/*
 * mMemory.h
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MMEMORY_H_
#define MODULES_MMEMORY_H_

void mMemory_Setup();

void mMemory_ReadData(unsigned int address, char* aData, int size);
void mMemory_WriteData(unsigned int address, char* aData, int size);


#endif /* MODULES_MMEMORY_H_ */
