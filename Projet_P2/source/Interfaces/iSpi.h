/*
 * iSpi.h
 *
 *  Created on: 24 août 2021
 *      Author: luc.froideva
 */

#ifndef ISPI_H_
#define ISPI_H_

#include <def.h>

void iSpi_Setup();

void iSpi_Enable();
void iSpi_Disable();

bool iSpi_IsLastTickReceived();
bool iSpi_IsBufferEmpty();
bool iSpi_IsChipSelectLow();


void iSpi_SendData(char data);

#endif /* ISPI_H_ */
