/*
 * iSpi.c
 *
 *  Created on: 24 août 2021
 *      Author: luc.froideva
 */

#include <Interfaces/iDio.h>
#include <Interfaces/iSpi.h>
#include <MKL46Z4.h>

void iSpi_Setup()
	{
	// Enable SCGC4 for SPI1
	SIM->SCGC4 |= SIM_SCGC4_SPI1_MASK;

	iDio_EnablePortClk();
	iDio_PinConfig(kPortB, kPin10, kAlternate2); // SPI1_PCS0
	iDio_PinConfig(kPortB, kPin11, kAlternate2); // SPI1_SCK
	iDio_PinConfig(kPortB, kPin16, kAlternate2); // SPI1_MOSI

	// BaudRate Divisor = (SPPR+1) * 2(SPR+1)
	// BaudRate = SPI Clock Module (24Mhz) / BaudRate Divisor
	SPI1->BR &= ~SPI_BR_SPR_MASK;
	SPI1->BR &= ~SPI_BR_SPPR_MASK;
	SPI1->BR |= 0b00000001;

	SPI1->C1 |= SPI_C1_MSTR_MASK; // 1: Master mode
	SPI1->C1 &= ~SPI_C1_LSBFE_MASK; // 1: LSB, 0: MSB
	SPI1->C2 &= ~SPI_C2_SPIMODE_MASK; // 0: 8-bit transmission mode, 1: 16-bit transmission mode

	// HANDLES CHIP SELECT !!!!
	SPI1->C1 |= SPI_C1_SSOE_MASK;
	SPI1->C2 |= SPI_C2_MODFEN_MASK;

	// 4-Wire
	SPI1->C2 &= ~SPI_C2_SPC0_MASK;

	// Clock sampling
	SPI1->C1 &= ~SPI_C1_CPOL_MASK; // Sampling at rising edge
	SPI1->C1 &= ~SPI_C1_CPHA_MASK; // Clock resting state at low

	// No interruptions
	SPI1->C1 &= ~SPI_C1_SPIE_MASK;
	SPI1->C1 &= ~SPI_C1_SPTIE_MASK;

	}


void iSpi_Enable()
	{
	SPI1->C1 |= SPI_C1_SPE_MASK;
	}

void iSpi_Disable()
	{
	SPI1->C1 &= ~SPI_C1_SPE_MASK;
	}


bool iSpi_IsLastTickReceived()
	{
	return (SPI1->S & SPI_S_SPRF_MASK) == SPI_S_SPRF_MASK;
	}

bool iSpi_IsBufferEmpty()
	{
	return (SPI1->S & SPI_S_SPTEF_MASK) == SPI_S_SPTEF_MASK;
	}

bool iSpi_IsChipSelectLow()
	{
	return (SPI1->S & SPI_S_MODF_MASK) == SPI_S_MODF_MASK;
	}

void iSpi_SendData(char data)
	{
	// Waiting for buffer to empty
	while(!iSpi_IsBufferEmpty()){}

	SPI1->DH = 0;
	SPI1->DL = data;

	while(!iSpi_IsLastTickReceived()){}
//	char DH = SPI1->DH;
//	char DL = SPI1->DL;
	// TODO: Check if SPRF is 0

	}
