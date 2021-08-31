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
	float waterLevel;
	float soilHumidity;
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
	}OutputStruct;

extern InputStruct gInput;
extern SensorsStruct gSensors;
extern GUIStruct gGUI;
extern ComputeStruct gCompute;
extern OutputStruct gOutput;

#endif /* GMBOX_H_ */
