/*
 * pixelImage.c
 *
 *  Created on: 10 sept. 2021
 *      Author: luc.froideva
 */


#include "pixelImage.h"


const bool bufferImSkull[7*7] = {
		0, 1, 1, 1, 1, 1, 0,
		1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 0,
		0, 1, 0, 1, 0, 1, 0
	};

const PixelImage imSkull =
	{
		size: (point){7, 7},
		image: (bool*)bufferImSkull
	};


static bool bufferImFlower[154] = {
		0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
		1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1,
		1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0
};

const PixelImage imFlower =
	{
	size: (point){11, 14},
	image: (bool*)bufferImFlower
	};
