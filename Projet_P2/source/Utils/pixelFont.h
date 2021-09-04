/*
 * pixelFont.h
 *
 *  Created on: 25 août 2021
 *      Author: luc.froideva
 */

#ifndef PIXELFONT_H_
#define PIXELFONT_H_

typedef struct Font
	{
	char width;
	char height;
	unsigned long charList[255];
	} font;


#endif /* PIXELFONT_H_ */
