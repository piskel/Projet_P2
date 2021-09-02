/*
 ------------------------------------------------------------
 Copyright 2003-20xx Haute �cole ARC Ing�ni�rie, Switzerland.
 All rights reserved.
 ------------------------------------------------------------
 Nom du fichier :	iI2C.c
 Auteur et Date :	Monnerat Serge 8.5.20xx

 Description dans le fichier iI2C.h
 ------------------------------------------------------------
 */

#include "iI2C.h"
#include <MKL46Z4.h>
#include "iDio.h"

#define I2C_WATCHDOG_SIZE 10000

static bool isI2C0Init = false;
static bool isI2C1Init = false;
//------------------------------------------------------------
// Configuration du module I2C
//------------------------------------------------------------

void iI2C0_Config()
	{
		if(isI2C0Init) return;

		void iI2C0_Reset();

		iDio_EnablePortClk();
		// I2C clock enable
		// System Clock Gating Control Register 4 (SIM_SCGC4)
		SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

		// Baud rate speed and I2C timing
		// I2C Frequency Divider register (I2Cx_F)
		// I2C clock rate=375 kHz (max 400kHz)
		// SDA Hold = 0.54us (max 0.9us)
		// SCL start Hold = 1.08us (min 0.6us)
		// SCL stop Hold = 1.38 us (min 0.6us
		I2C0->F = 0x5F;
		I2C0->F |= I2C_F_ICR(0x12) | I2C_F_MULT(0);


		iDio_PinConfig(kPortC, kPin8, kAlternate2); // SCL
		iDio_PinConfig(kPortC, kPin9, kAlternate2); // SDA

		isI2C0Init = true;
	}

void iI2C1_Config()
	{
		if(isI2C1Init) return;

		void iI2C1_Reset();
		iDio_EnablePortClk();
		// I2C clock enable
		// System Clock Gating Control Register 4 (SIM_SCGC4)
		SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;

		// Baud rate speed and I2C timing
		// I2C Frequency Divider register (I2Cx_F)
		// I2C clock rate=375 kHz (max 400kHz)
		// SDA Hold = 0.54us (max 0.9us)
		// SCL start Hold = 1.08us (min 0.6us)
		// SCL stop Hold = 1.38 us (min 0.6us
		I2C1->F = 0x5F;
		I2C1->F |= I2C_F_ICR(0x12) | I2C_F_MULT(0);


		iDio_PinConfig(kPortC, kPin10, kAlternate2); // SCL
		iDio_PinConfig(kPortC, kPin11, kAlternate2); // SDA

		isI2C1Init = true;
	}



void iI2C0_Reset(void)
    {
        I2C0->A1 = 0x00;
        I2C0->F = 0x00;
        I2C0->C1 = 0x00;
        I2C0->S = 0x80;
        I2C0->D = 0x00;
        I2C0->C2 = 0x00;
        I2C0->FLT = 0x00;
        I2C0->RA = 0x00;
        I2C0->SMB = 0x00;
        I2C0->A2 = 0xC2;
        I2C0->SLTH = 0x00;
        I2C0->SLTL = 0x00;
    }

void iI2C1_Reset(void)
    {
        I2C1->A1 = 0x00;
        I2C1->F = 0x00;
        I2C1->C1 = 0x00;
        I2C1->S = 0x80;
        I2C1->D = 0x00;
        I2C1->C2 = 0x00;
        I2C1->FLT = 0x00;
        I2C1->RA = 0x00;
        I2C1->SMB = 0x00;
        I2C1->A2 = 0xC2;
        I2C1->SLTH = 0x00;
        I2C1->SLTL = 0x00;
    }



//------------------------------------------------------------
// I2C interface enable
//------------------------------------------------------------

void iI2C0_Enable(void)
	{
		// I2C0 enable
		// I2C Control Register 1 (I2Cx_C1)
		I2C0->C1 |= I2C_C1_IICEN_MASK;
	}

void iI2C1_Enable(void)
	{
		// I2C0 enable
		// I2C Control Register 1 (I2Cx_C1)
		I2C1->C1 |= I2C_C1_IICEN_MASK;
	}

//------------------------------------------------------------
// I2C interface disable
//------------------------------------------------------------

void iI2C0_Disable(void)
	{
		// I2C0 disable
		// I2C Control Register 1 (I2Cx_C1)
		I2C0->C1 &= (~I2C_C1_IICEN_MASK);
	}

void iI2C1_Disable(void)
	{
		// I2C0 disable
		// I2C Control Register 1 (I2Cx_C1)
		I2C1->C1 &= (~I2C_C1_IICEN_MASK);
	}

//------------------------------------------------------------
// Set START state
//------------------------------------------------------------

void iI2C0_SetStartState(void)
	{
		// I2C Control Register 1 (I2Cx_C1)
		I2C0->C1 |= I2C_C1_MST_MASK;
	}

void iI2C1_SetStartState(void)
	{
		// I2C Control Register 1 (I2Cx_C1)
		I2C1->C1 |= I2C_C1_MST_MASK;
	}

//------------------------------------------------------------
// Set repeated START state
//------------------------------------------------------------

void iI2C0_SetRepeatedStartSate(void)
	{
		// I2C Control Register 1 (I2Cx_C1)
		I2C0->C1 |= I2C_C1_RSTA_MASK;
	}

void iI2C1_SetRepeatedStartSate(void)
	{
		// I2C Control Register 1 (I2Cx_C1)
		I2C1->C1 |= I2C_C1_RSTA_MASK;
	}

//------------------------------------------------------------
// Set STOP state
//------------------------------------------------------------

void iI2C0_SetStopState(void)
	{
		// I2C Control Register 1 (I2Cx_C1)
		I2C0->C1 &= (~I2C_C1_MST_MASK);
	}

void iI2C1_SetStopState(void)
	{
		// I2C Control Register 1 (I2Cx_C1)
		I2C1->C1 &= (~I2C_C1_MST_MASK);
	}

//------------------------------------------------------------
// Generate automatic ACK or not
//------------------------------------------------------------

void iI2C0_SetAckMode(I2CAckEnum aAck)
	{

		if (aAck == kAckAuto)
			{
				// I2C Control Register 1 (I2Cx_C1)
				I2C0->C1 &= (~I2C_C1_TXAK_MASK);
			}
		else if (aAck == kNoAck)
			{
				// I2C Control Register 1 (I2Cx_C1)
				I2C0->C1 |= I2C_C1_TXAK_MASK;
			}
	}

void iI2C1_SetAckMode(I2CAckEnum aAck)
	{

		if (aAck == kAckAuto)
			{
				// I2C Control Register 1 (I2Cx_C1)
				I2C1->C1 &= (~I2C_C1_TXAK_MASK);
			}
		else if (aAck == kNoAck)
			{
				// I2C Control Register 1 (I2Cx_C1)
				I2C1->C1 |= I2C_C1_TXAK_MASK;
			}
	}

//------------------------------------------------------------
// Select if we transmit or receive
//------------------------------------------------------------

void iI2C0_TxRxSelect(I2CTransmiteModeEnum aMode)
	{
		if (kTxMode == aMode)
			{
				// TX
				I2C0->C1 |= I2C_C1_TX_MASK;
			}
		else if (kRxMode == aMode)
			{
				// RX
				I2C0->C1 &= ~I2C_C1_TX_MASK;
			}
	}

void iI2C1_TxRxSelect(I2CTransmiteModeEnum aMode)
	{
		if (kTxMode == aMode)
			{
				// TX
				I2C1->C1 |= I2C_C1_TX_MASK;
			}
		else if (kRxMode == aMode)
			{
				// RX
				I2C1->C1 &= ~I2C_C1_TX_MASK;
			}
	}

//------------------------------------------------------------
// Send a data
//------------------------------------------------------------

void iI2C0_SendData(char aData)
	{
		// I2C Data I/O register (I2Cx_D)
		I2C0->D = aData;
	}

void iI2C1_SendData(char aData)
	{
		// I2C Data I/O register (I2Cx_D)
		I2C1->D = aData;
	}

//------------------------------------------------------------
// Wait End of transmit or receive
//------------------------------------------------------------

bool iI2C0_WaitEndOfRxOrTx(void)
	{
		// Wait for IICIF flag
		// I2C Status register (I2Cx_S)
		int wd = I2C_WATCHDOG_SIZE;
		while ((I2C0->S & I2C_S_IICIF_MASK) == 0)
		{
			if(wd <= 0) return false;
			wd--;
		};
		// Clear the IICIF flag
		I2C0->S |= I2C_S_IICIF_MASK;
		return true;
	}

bool iI2C1_WaitEndOfRxOrTx(void)
	{
		// Wait for IICIF flag
		// I2C Status register (I2Cx_S)

		int wd = I2C_WATCHDOG_SIZE;
		while ((I2C1->S & I2C_S_IICIF_MASK) == 0)
		{
			if(wd <= 0) return false;
			wd--;
		};
			;
		// Clear the IICIF flag
		I2C1->S |= I2C_S_IICIF_MASK;
		return true;
	}

//------------------------------------------------------------
// Read received data, ! generate I2C clock if not in STOP mode
//------------------------------------------------------------

char iI2C0_ReadData(void)
	{
		char aReturnData = 0;

		// I2C Data I/O register (I2Cx_D)
		aReturnData = I2C0->D;

		return aReturnData;
	}

char iI2C1_ReadData(void)
	{
		char aReturnData = 0;

		// I2C Data I/O register (I2Cx_D)
		aReturnData = I2C1->D;

		return aReturnData;
	}

//------------------------------------------------------------
// Get I2C status flags
//------------------------------------------------------------

bool iI2C0_ReadStatus(I2CStatusEnum aStatus)
	{
		return (bool) (((I2C0->S & aStatus) == aStatus));
	}

bool iI2C1_ReadStatus(I2CStatusEnum aStatus)
	{
		return (bool) (((I2C1->S & aStatus) == aStatus));
	}

//------------------------------------------------------------
// Start communication
//------------------------------------------------------------

bool iI2C0_StartCom(void)
	{
		// Disable transmit ACK
		iI2C0_SetAckMode(kNoAck);

		// Attend que le bus soit libre
		int wd = I2C_WATCHDOG_SIZE;
		while (true == iI2C0_ReadStatus(kBUSY))
		{
			wd--;
			if(wd <= 0) return false;
		};

		//-----------------------------------------------------------------------------
		// D'abords en WRITE afin de transmettre le registre
		// que l'on veut lire ainsi que l'adresse du slave
		//-----------------------------------------------------------------------------

		// Début de la transmission --> mode write et START condition
		iI2C0_TxRxSelect(kTxMode);
		iI2C0_SetStartState();

		return true;
	}

bool iI2C1_StartCom(void)
	{
		// Disable transmit ACK
		iI2C1_SetAckMode(kNoAck);

		// Attend que le bus soit libre
		int wd = I2C_WATCHDOG_SIZE;
		while (true == iI2C1_ReadStatus(kBUSY))
		{
			wd--;
			if(wd <= 0) return false;
		};

		//-----------------------------------------------------------------------------
		// D'abords en WRITE afin de transmettre le registre
		// que l'on veut lire ainsi que l'adresse du slave
		//-----------------------------------------------------------------------------

		// Début de la transmission --> mode write et START condition
		iI2C1_TxRxSelect(kTxMode);
		iI2C1_SetStartState();

		return true;
	}

//------------------------------------------------------------
// Send Add slave
//------------------------------------------------------------
bool iI2C0_SendSlaveAdd(char aAdd)
	{
		// Transmission de l'adresse en WRITE du slave dans le registre de données
		// --> obligatoire protocolle I2C, le slave doit d'abords répondre à son adresse
		iI2C0_SendData(aAdd);

		// Attend la fin de la transmission
		if(!iI2C0_WaitEndOfRxOrTx()) return false;

		if (iI2C0_ReadStatus(kRxAK))
			{
				// FIN de la lecture
				iI2C0_TxRxSelect(kTxMode);
				iI2C0_SetAckMode(kNoAck);
				iI2C0_SetStopState();
				return false;
			}
		return true;
	}

bool iI2C1_SendSlaveAdd(char aAdd)
	{
		// Transmission de l'adresse en WRITE du slave dans le registre de données
		// --> obligatoire protocolle I2C, le slave doit d'abords répondre à son adresse
		iI2C1_SendData(aAdd);

		// Attend la fin de la transmission
		if(!iI2C1_WaitEndOfRxOrTx()) return false;

		if (iI2C1_ReadStatus(kRxAK))
			{
				// FIN de la lecture
				iI2C1_TxRxSelect(kTxMode);
				iI2C1_SetAckMode(kNoAck);
				iI2C1_SetStopState();
				return false;
			}
		return true;
	}

//------------------------------------------------------------
// Send a byte
//------------------------------------------------------------
bool iI2C0_SendByte(char aData)
	{
		// Transmission de l'adresse du registre que l'on veut écrire
		iI2C0_SendData(aData);

		// Attend la fin de la transmission
		if(!iI2C0_WaitEndOfRxOrTx()) return false;

		if (iI2C0_ReadStatus(kRxAK))
			{
				// FIN de la lecture
				iI2C0_TxRxSelect(kTxMode);
				iI2C0_SetAckMode(kNoAck);
				iI2C0_SetStopState();
				return false;
			}
		return true;
	}

bool iI2C1_SendByte(char aData)
	{
		// Transmission de l'adresse du registre que l'on veut écrire
		iI2C1_SendData(aData);

		// Attend la fin de la transmission
		if(!iI2C1_WaitEndOfRxOrTx()) return false;

		if (iI2C1_ReadStatus(kRxAK))
			{
				// FIN de la lecture
				iI2C1_TxRxSelect(kTxMode);
				iI2C1_SetAckMode(kNoAck);
				iI2C1_SetStopState();
				return false;
			}
		return true;
	}

//------------------------------------------------------------
// Read bytes
//------------------------------------------------------------
bool iI2C0_ReadBytes(char *aData, char aNbByte)
	{
		iI2C0_TxRxSelect(kRxMode);

		if (aNbByte < 1)
			{
				return false;
			}
		else if (aNbByte == 1)
			{
				iI2C0_SetAckMode(kNoAck);
			}
		else
			{
				iI2C0_SetAckMode(kAckAuto);
			}

		iI2C0_ReadData();

		if(!iI2C0_WaitEndOfRxOrTx()) return false;

		for (int i = 0; i < aNbByte - 1; i++)
			{
				aData[i] = iI2C0_ReadData();
				if (i == aNbByte - 2)
					{
						iI2C0_SetAckMode(kNoAck);
					}
				if(!iI2C0_WaitEndOfRxOrTx()) return false;
			}

		return true;
	}

bool iI2C1_ReadBytes(char *aData, char aNbByte)
	{
		iI2C1_TxRxSelect(kRxMode);

		if (aNbByte < 1)
			{
				return false;
			}
		else if (aNbByte == 1)
			{
				iI2C1_SetAckMode(kNoAck);
			}
		else
			{
				iI2C1_SetAckMode(kAckAuto);
			}

		iI2C1_ReadData();
		if(!iI2C1_WaitEndOfRxOrTx()) return false;

		for (int i = 0; i < aNbByte - 1; i++)
			{
				aData[i] = iI2C1_ReadData();
				if (i == aNbByte - 2)
					{
						iI2C1_SetAckMode(kNoAck);
					}
				if(!iI2C1_WaitEndOfRxOrTx()) return false;
			}

		return true;
	}

//------------------------------------------------------------
// Read last byte
//------------------------------------------------------------
bool iI2C0_ReadLastByte(char *aData, char aNbByte)
	{
		aData[aNbByte - 1] = iI2C0_ReadData();
		return true;
	}

bool iI2C1_ReadLastByte(char *aData, char aNbByte)
	{
		aData[aNbByte - 1] = iI2C1_ReadData();
		return true;
	}

//------------------------------------------------------------
// Stop communication
//------------------------------------------------------------
bool iI2C0_StopCom(void)
	{
		iI2C0_TxRxSelect(kTxMode);
		iI2C0_SetAckMode(kNoAck);
		iI2C0_SetStopState();
		return true;
	}

bool iI2C1_StopCom(void)
	{
		iI2C1_TxRxSelect(kTxMode);
		iI2C1_SetAckMode(kNoAck);
		iI2C1_SetStopState();
		return true;
	}
//------------------------------------------------------------
// Stop communication
//------------------------------------------------------------
bool iI2C0_ReadBytesAndStopCom(char *aData, char aNbByte)
	{
		bool check = true;
		if(!iI2C0_ReadBytes(aData, aNbByte)) check = false;
		if(!iI2C0_StopCom()) check = false;
		if(!iI2C0_ReadLastByte(aData, aNbByte)) check = false;
		return check;
	}

bool iI2C1_ReadBytesAndStopCom(char *aData, char aNbByte)
	{
	bool check = true;
	if(!iI2C1_ReadBytes(aData, aNbByte)) check = false;
	if(!iI2C1_StopCom()) check = false;
	if(!iI2C1_ReadLastByte(aData, aNbByte)) check = false;
	return check;
	}
