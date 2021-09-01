/*
 * mMemory.c
 *
 *  Created on: 31 août 2021
 *      Author: luc.froideva
 */


#include "mMemory.h"

#include "iI2C.h"
#include "iDio.h"

#define MEM_READ_BIT 0x01
#define MEM_WRITE_BIT 0x00
#define MEM_ADDR_BASE 0b10100000
#define MEM_ADDR_A0 1
#define MEM_ADDR_A1 1
#define MEM_ADDR_A2 1

void mMemory_Setup()
	{
	iI2C1_Config();

	iDio_EnablePortClk();

	iDio_PinConfig(kPortC, kPin12, kAlternate1); // MEM_A0
	iDio_PinConfig(kPortC, kPin13, kAlternate1); // MEM_A1
	iDio_PinConfig(kPortC, kPin16, kAlternate1); // MEM_A2
	iDio_PinConfig(kPortC, kPin17, kAlternate1); // MEM_WP

	iDio_SetPortDirection(kPortC, kMaskIo12, kIoOutput);
	iDio_SetPortDirection(kPortC, kMaskIo13, kIoOutput);
	iDio_SetPortDirection(kPortC, kMaskIo16, kIoOutput);
	iDio_SetPortDirection(kPortC, kMaskIo17, kIoOutput);

	iDio_SetPort(kPortC, kMaskIo12, MEM_ADDR_A0);
	iDio_SetPort(kPortC, kMaskIo13, MEM_ADDR_A1);
	iDio_SetPort(kPortC, kMaskIo16, MEM_ADDR_A2);

	}


