/*
 * mMemory.h
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MMEMORY_H_
#define MODULES_MMEMORY_H_

void mMemory_Setup();

void mMemory_Read(unsigned int address);
void mMemory_Write(unsigned int address, char data);


#endif /* MODULES_MMEMORY_H_ */
