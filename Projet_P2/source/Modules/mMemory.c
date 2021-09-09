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
#define MEM_ADDR_BASE 0b01010000
#define MEM_ADDR_A0 1
#define MEM_ADDR_A1 1
#define MEM_ADDR_A2 1
#define MEM_ADDR (MEM_ADDR_BASE | MEM_ADDR_A2 << 2 | MEM_ADDR_A1 << 1 | MEM_ADDR_A0)

static int mMemoryErrorCounter = 0;


void mMemory_Setup()
	{
	mMemoryErrorCounter = 0;

	iI2C1_Config();
	mDelay_Setup();

	iDio_EnablePortClk();

	iDio_PinConfig(kPortC, kPin12, kAlternate1); // MEM_A0
	iDio_PinConfig(kPortC, kPin13, kAlternate1); // MEM_A1
	iDio_PinConfig(kPortC, kPin16, kAlternate1); // MEM_A2
	iDio_PinConfig(kPortC, kPin17, kAlternate1); // MEM_WP

	iDio_SetPortDirection(kPortC, kMaskIo12, kIoOutput);
	iDio_SetPortDirection(kPortC, kMaskIo13, kIoOutput);
	iDio_SetPortDirection(kPortC, kMaskIo16, kIoOutput);
	iDio_SetPortDirection(kPortC, kMaskIo17, kIoOutput);

	iDio_SetPort(kPortC, kMaskIo12, MEM_ADDR_A0 == 1 ? kIoOn : kIoOff);
	iDio_SetPort(kPortC, kMaskIo13, MEM_ADDR_A1 == 1 ? kIoOn : kIoOff);
	iDio_SetPort(kPortC, kMaskIo16, MEM_ADDR_A2 == 1 ? kIoOn : kIoOff);

	iDio_SetPort(kPortC, kMaskIo17, kIoOn); // Write protection ON

	}

void mMemory_ReadData(unsigned int address, char* aData, int size)
	{
	iI2C1_SetSpeed(0x00);
	iDio_SetPort(kPortC, kMaskIo17, kIoOff); // Write protection OFF
	iI2C1_Enable();
	if(!iI2C1_StartCom()){mMemoryErrorCounter++;return;}
	if(!iI2C1_SendSlaveAdd(MEM_ADDR << 1 | MEM_WRITE_BIT)){mMemoryErrorCounter++;return;}
	if(!iI2C1_SendByte((address >> 8) & 0xFF)){mMemoryErrorCounter++;return;}
	if(!iI2C1_SendByte(address & 0xFF)){mMemoryErrorCounter++;return;}
	iI2C1_SetRepeatedStartSate();
	if(!iI2C1_SendSlaveAdd(MEM_ADDR << 1 | MEM_READ_BIT)){mMemoryErrorCounter++;return;}
	if (!iI2C1_ReadBytesAndStopCom(aData, size)){mMemoryErrorCounter++;return;}
	iI2C1_Disable();
	iDio_SetPort(kPortC, kMaskIo17, kIoOn); // Write protection ON
	}

void mMemory_WriteData(unsigned int address, char* aData, int size)
	{
	for(int i = 0; i < size; i++)
		{
		mMemory_WriteByte(address+i, aData[i]);
		}
	}


void mMemory_WriteByte(unsigned int address, char data)
	{
	iI2C1_SetSpeed(0x00);
	iDio_SetPort(kPortC, kMaskIo17, kIoOff); // Write protection OFF
	iI2C1_Enable();
	if(!iI2C1_StartCom()){mMemoryErrorCounter++;return;}
	if(!iI2C1_SendSlaveAdd(MEM_ADDR << 1 | MEM_WRITE_BIT)){mMemoryErrorCounter++;return;}
	if(!iI2C1_SendByte((address >> 8) & 0xFF)){mMemoryErrorCounter++;return;}
	if(!iI2C1_SendByte(address & 0xFF)){mMemoryErrorCounter++;return;}
	if(!iI2C1_SendByte(data)){mMemoryErrorCounter++;return;}
	iI2C1_StopCom();
	iI2C1_Disable();
	iDio_SetPort(kPortC, kMaskIo17, kIoOn); // Write protection ON

	int tmpDelay = mDelay_GetDelay(5);
	while(!mDelay_IsDelayDone(tmpDelay));
	mDelay_DelayRelease(tmpDelay);
	}

