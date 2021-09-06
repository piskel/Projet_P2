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
//		kCOMQueryGetData = 0x20,
//		kCOMQuerySetData = 0x21
		kCOMQueryGetWL = 0x10,
		kCOMQueryGetSoilHum = 0x11,
		kCOMQueryGetVisLight = 0x12,
		kCOMQueryGetIR = 0x13,
		kCOMQueryGetTemp = 0x14,
		kCOMQueryGetHum= 0x15,
	} COMQuery;


void gCOM_Setup();
void gCOM_Execute();

void gCOM_BLEHandler();
void gCOM_UARTUSBHandler();


void gCOM_QueryGetData();

void gCOM_HandleQuery(const char* query, char* response, int* size);




#endif /* GESTIONNAIRES_GCOM_H_ */
