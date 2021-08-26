/*
 * pixelFont.h
 *
 *  Created on: 25 août 2021
 *      Author: luc.froideva
 */

#ifndef PIXELFONT_H_
#define PIXELFONT_H_

#include "def.h"

typedef struct Font
	{
	char width;
	char height;
	unsigned long charList[128];
	} font;

#define PIXEL_FONT_WIDTH 4
#define PIXEL_FONT_HEIGHT 5


#endif /* PIXELFONT_H_ */
