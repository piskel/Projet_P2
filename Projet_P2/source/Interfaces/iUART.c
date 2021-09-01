/*
 * iUART.c
 *
 *  Created on: 29 août 2021
 *      Author: luc.froideva
 */

#include "iUART.h"

#include "MKL46Z4.h"
#include "iDio.h"
#include "core_cm0plus.h"

static UARTDataBuffer uart0DataBuffer;
static UARTDataBuffer uart1DataBuffer;

static bool isInit = false;

void iUART_Config()
	{
	if(isInit) return;

	iUART_ClearBuffer(kUART0);
	iUART_ClearBuffer(kUART1);


	EnableInterrupts;
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_EnableIRQ(UART1_IRQn);
	NVIC_SetPriority(UART1_IRQn, 1);


	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;

	SIM->SOPT2&=SIM_SOPT2_UART0SRC_MASK;
	SIM->SOPT2|=SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2|=SIM_SOPT2_PLLFLLSEL_MASK;

	iDio_PinConfig(kPortE, kPin20, kAlternate4); // UART0_TX
	iDio_PinConfig(kPortE, kPin21, kAlternate4); // UART0_RX
	iDio_PinConfig(kPortE, kPin22, kAlternate1); // UART0_CTS
	iDio_PinConfig(kPortE, kPin23, kAlternate1); // UART0_RTS

	iDio_SetPortDirection(kPortE, kMaskIo22, kIoOutput);
	iDio_SetPortDirection(kPortE, kMaskIo23, kIoOutput);

	iDio_PinConfig(kPortE, kPin0, kAlternate3); // UART1_TX
	iDio_PinConfig(kPortE, kPin1, kAlternate3); // UART1_RX
	iDio_PinConfig(kPortE, kPin2, kAlternate1); // UART1_CTS
	iDio_PinConfig(kPortE, kPin3, kAlternate1); // UART1_RTS

	iDio_SetPortDirection(kPortE, kMaskIo2, kIoOutput);
	iDio_SetPortDirection(kPortE, kMaskIo3, kIoOutput);

	// Baud rate : 115200
	// Baud rate = bus clock freq (24MHz)/(SBR[12:0]*16)
	// SBR[12:0] = bus clock freq (24MHz)/16 * 115200 = 13

	UART0->BDH &= ~UART_BDH_SBR_MASK;
	UART0->BDL &= ~UART_BDL_SBR_MASK;
	UART0->BDL = 13;

	UART1->BDH &= ~UART_BDH_SBR_MASK;
	UART1->BDL &= ~UART_BDL_SBR_MASK;
	UART1->BDL = 13;

	// Interrupts
	UART0->C2|=UART_C2_RIE_MASK;
	UART1->C2|=UART_C2_RIE_MASK;

	isInit = true;
	}

void iUART_SetFrameType(UARTEnum aUART, bool data9bits)
	{
	switch (aUART)
		{
		case kUART0:
			UART0->C1 &= ~UART_C1_M_MASK;
			UART0->C1 |= data9bits << UART_C1_M_SHIFT;
			break;

		case kUART1:
			UART1->C1 &= ~UART_C1_M_MASK;
			UART1->C1 |= data9bits << UART_C1_M_SHIFT;
			break;
		}
	}

void iUART_SetParity(UARTEnum aUART, bool enable)
	{
	switch (aUART)
		{
		case kUART0:
			UART0->C1 &= ~UART_C1_PE_MASK;
			UART0->C1 |= enable << UART_C1_PE_SHIFT;
			break;

		case kUART1:
			UART1->C1 &= ~UART_C1_PE_MASK;
			UART1->C1 |= enable << UART_C1_PE_SHIFT;
			break;
		}
	}

void iUART_SetParityType(UARTEnum aUART, bool odd)
	{
	switch (aUART)
		{
		case kUART0:
			UART0->C1 &= ~UART_C1_PT_MASK;
			UART0->C1 |= odd << UART_C1_PT_SHIFT;
			break;

		case kUART1:
			UART0->C1 &= ~UART_C1_PT_MASK;
			UART0->C1 |= odd << UART_C1_PT_SHIFT;
			break;
		}
	}

//
//void iUART_SetInterrupts(UARTEnum aUART, bool tie, bool tcie, bool rie)
//	{
//	switch (aUART)
//		{
//		case kUART0:
//			UART0->C2 &= ~UART_C2_TIE_MASK;
//			UART0->C2 |= tie << UART_C2_TIE_SHIFT;
//			UART0->C2 &= ~UART_C2_TCIE_MASK;
//			UART0->C2 |= tcie << UART_C2_TCIE_SHIFT;
//			UART0->C2 &= ~UART_C2_RIE_MASK;
//			UART0->C2 |= rie << UART_C2_RIE_SHIFT;
//			break;
//
//		case kUART1:
//			UART1->C2 &= ~UART_C2_TIE_MASK;
//			UART1->C2 |= tie << UART_C2_TIE_SHIFT;
//			UART1->C2 &= ~UART_C2_TCIE_MASK;
//			UART1->C2 |= tcie << UART_C2_TCIE_SHIFT;
//			UART1->C2 &= ~UART_C2_RIE_MASK;
//			UART1->C2 |= rie << UART_C2_RIE_SHIFT;
//			break;
//		}
//	}

void iUART_SetTX(UARTEnum aUART, bool enable)
	{
	switch (aUART)
		{
		case kUART0:
			UART0->C2 &= ~UART_C2_TE_MASK;
			UART0->C2 |= enable << UART_C2_TE_SHIFT;
			break;

		case kUART1:
			UART1->C2 &= ~UART_C2_TE_MASK;
			UART1->C2 |= enable << UART_C2_TE_SHIFT;
			break;
		}
	}

void iUART_SetRX(UARTEnum aUART, bool enable)
	{
	switch (aUART)
		{
		case kUART0:
			UART0->C2 &= ~UART_C2_RE_MASK;
			UART0->C2 |= enable << UART_C2_RE_SHIFT;
			break;

		case kUART1:
			UART1->C2 &= ~UART_C2_RE_MASK;
			UART1->C2 |= enable << UART_C2_RE_SHIFT;
			break;
		}
	}


bool iUART_GetFlag(UARTEnum aUART, UARTFlagEnum aUARTFlag)
	{
	uint8_t reg = UART0->S1;

	if(aUART==kUART1) reg = UART1->S1;

	switch (aUARTFlag) {
		case kUARTFlagTDRE:
			return (reg >> UART_S1_TDRE_SHIFT) & 1;
		case kUARTFlagTC:
			return (reg >> UART_S1_TC_SHIFT) & 1;
		case kUARTFlagRDRF:
			return (reg >> UART_S1_RDRF_SHIFT) & 1;
		case kUARTFlagOR:
			return (reg >> UART_S1_OR_SHIFT) & 1;
		case kUARTFlagNF:
			return (reg >> UART_S1_NF_SHIFT) & 1;
		case kUARTFlagFE:
			return (reg >> UART_S1_FE_SHIFT) & 1;
		case kUARTFlagPF:
			return (reg >> UART_S1_PF_SHIFT) & 1;
		default:
			return false;
		}
	}


char* iUART_GetData(UARTEnum aUART)
	{
	switch (aUART)
		{
		case kUART0:
			return uart0DataBuffer.buffer;

		case kUART1:
			return uart1DataBuffer.buffer;
		}
	return 0;
	}


// Les flags concernant la transmission sont remis à 0 en lisant le registre de statut et en
// écrivant une donnée dans le registre de donnée, les flags concernant la réception sont
// remis à 0 en lisant le registre de statut et en lisant le registre de donnée, tous les autres
// sont remis à 0 en les écrivant à 1.

void UART0_IRQHandler()
	{
	if(uart0DataBuffer.index >= UART_BUFFER_SIZE)
	{
		iUART_ClearBuffer(kUART0);
	}

	uart0DataBuffer.buffer[uart0DataBuffer.index] = UART0->D;
	uart0DataBuffer.index++;

	UART1->S1;
	char data = UART1->D;
	}

void UART1_IRQHandler()
	{
	if(uart1DataBuffer.index >= UART_BUFFER_SIZE)
	{
		iUART_ClearBuffer(kUART1);
	}

	uart1DataBuffer.buffer[uart1DataBuffer.index] = UART1->D;
	uart1DataBuffer.index++;

	UART1->S1;
	char data = UART1->D;

	}

void iUART_SetData(UARTEnum aUART, char data)
	{
	switch (aUART)
		{
		case kUART0:
			UART0->D = data;

		case kUART1:
			UART1->D = data;
		}
	}


void iUART_ClearBuffer(UARTEnum aUART)
	{
	switch (aUART)
		{
		case kUART0:
			uart0DataBuffer.index = 0;
			for(int i = 0; i < UART_BUFFER_SIZE; i++)
				{
				uart0DataBuffer.buffer[i] = 0;
				}

		case kUART1:
			uart1DataBuffer.index = 0;
			for(int i = 0; i < UART_BUFFER_SIZE; i++)
				{
				uart1DataBuffer.buffer[i] = 0;
				}
		}
	}

