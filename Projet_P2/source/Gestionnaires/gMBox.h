/*
 * gMBox.h
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */

#ifndef GMBOX_H_
#define GMBOX_H_

#include "def.h"

typedef struct
	{
	bool buttonStateTab[4];
	bool buttonJustPressedTab[4];
	}InputStruct;

typedef struct
	{
//	char bleData[32];
//	bool bleRunning;
//	bool uartRunning;

	}COMStruct;

typedef struct
	{
	unsigned char waterLevel;
	float soilHumidity;
	unsigned int visibleLight;
	unsigned int ir;
	int temperature;
	int pressure;
	unsigned char humidity;
	}SensorsStruct;

typedef struct
	{
	char* currentPageName;
	char* currentElementName;
	}GUIStruct;

typedef struct
	{

	}ComputeStruct;

typedef struct
	{
	bool enablePump;
	}OutputStruct;

extern InputStruct gInput;
extern COMStruct gCOM;
extern SensorsStruct gSensors;
extern GUIStruct gGUI;
extern ComputeStruct gCompute;
extern OutputStruct gOutput;

#endif /* GMBOX_H_ */
