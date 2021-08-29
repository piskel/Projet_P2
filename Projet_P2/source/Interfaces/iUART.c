/*
 * iUART.c
 *
 *  Created on: 29 août 2021
 *      Author: luc.froideva
 */

#include "iUART.h"

#include "MKL46Z4.h"
#include "iDio.h"

void iUART_Config()
	{
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;

	iDio_PinConfig(kPortE, kPin20, kAlternate4); // UART0_TX
	iDio_PinConfig(kPortE, kPin21, kAlternate4); // UART0_RX

	}

