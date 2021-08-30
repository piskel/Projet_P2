/*
 * iUART.h
 *
 *  Created on: 29 août 2021
 *      Author: luc.froideva
 */

#ifndef INTERFACES_IUART_H_
#define INTERFACES_IUART_H_

#include "def.h"
#include "MKL46Z4.h"

#define UART_BUFFER_SIZE 128

typedef struct UARTDataBuffer
	{
	char buffer[UART_BUFFER_SIZE];
	int index;
	}UARTDataBuffer;

typedef enum
	{
		kUART0,
		kUART1
	} UARTEnum;

typedef enum
	{
		kUARTIntTIE,
		kUARTIntTCIE,
		kUARTIntRIE,
		kUARTIntORIE,
		kUARTIntNEIE,
		kUARTIntFEIE,
		kUARTIntPEIE
	}UARTInterruptEnum;

typedef enum
	{
	kUARTFlagTDRE,
	kUARTFlagTC,
	kUARTFlagRDRF,
	kUARTFlagOR,
	kUARTFlagNF,
	kUARTFlagFE,
	kUARTFlagPF
	}UARTFlagEnum;

void iUART_Config();

void iUART_SetFrameType(UARTEnum aUART, bool data9bits);
void iUART_SetParity(UARTEnum aUART, bool enable);
void iUART_SetParityType(UARTEnum aUART, bool odd);
//void iUART_SetInterrupts(UARTEnum aUART, bool tie, bool tcie, bool rie);

void iUART_SetTX(UARTEnum aUART, bool enable);
void iUART_SetRX(UARTEnum aUART, bool enable);

bool iUART_GetFlag(UARTEnum aUART, UARTFlagEnum aUARTFlag);

char* iUART_GetData(UARTEnum aUART);
void iUART_SetData(UARTEnum aUART, char data);

void iUART_ClearBuffer(UARTEnum aUART);

#endif /* INTERFACES_IUART_H_ */
