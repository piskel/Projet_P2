/*
 * gCOM.h
 *
 *  Created on: 2 sept. 2021
 *      Author: luc.froideva
 */

#ifndef GESTIONNAIRES_GCOM_H_
#define GESTIONNAIRES_GCOM_H_

typedef enum
	{
		kCOMQueryGetWL = 0x10,
		kCOMQueryGetSoilHum = 0x11,
		kCOMQueryGetVisLight = 0x12,
		kCOMQueryGetIR = 0x13,
		kCOMQueryGetTemp = 0x14,
		kCOMQueryGetPress = 0x15,
		kCOMQueryGetHum = 0x16,
		kCOMQueryEnablePump = 0x30,
		kCOMQueryDisablePump = 0x31,
		kCOMQueryGetSettings = 0x32,
		kCOMQuerySetSettings = 0x33,
	} COMQuery;


void gCOM_Setup();
void gCOM_Execute();

void gCOM_BLEHandler();
void gCOM_UARTUSBHandler();


void gCOM_QueryGetData();

void gCOM_HandleQuery(const char* query, char* response, int* size);




#endif /* GESTIONNAIRES_GCOM_H_ */
