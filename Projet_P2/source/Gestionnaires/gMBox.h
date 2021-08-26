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
	bool buttonTab[3];
}InputStruct;

typedef struct
{

}ComputeStruct;

typedef struct
{

}OutputStruct;

extern InputStruct gInput;
extern OutputStruct gOutput;

#endif /* GMBOX_H_ */
