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
		kCOMQueryGetData = 0x20,
		kCOMQuerySetData = 0x21
	} COMQuery;


void gCOM_Setup();
void gCOM_Execute();

void gCOM_BLEHandler();
void gCOM_QueryGetData();


#endif /* GESTIONNAIRES_GCOM_H_ */
