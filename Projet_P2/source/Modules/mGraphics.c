/*
 * mGraphics.c
 *
 *  Created on: 25 août 2021
 *      Author: luc.froideva
 */

#include <math.h>
#include <Modules/mDisplay.h>
#include <Modules/mGraphics.h>

void mGraphics_Setup()
	{
	mDisplay_Setup();
	}

// TODO Rename white variable to something else
void mGraphics_FillBuffer(bool *buffer, bool white)
	{
	for(int i = 0; i < DISPLAY_BUFFER_SIZE; i++)
		{
		buffer[i] = white;
		}
	}


void mGraphics_DrawLine(bool *buffer, point startPos, point endPos, bool white, int thickness)
	{

	int dx = abs(endPos.x - startPos.x);
	int sx = startPos.x < endPos.x ? 1 : -1;
	int dy = -abs(endPos.y - startPos.y);
	int sy = startPos.y < endPos.y ? 1 : -1;
	int err = dx + dy, e2;

	for (;;)
		{
		mGraphics_DrawPixel(buffer, startPos, white);

		if (startPos.x == endPos.x && startPos.y == endPos.y) break;
		e2 = 2 * err;
		if (e2 >= dy)
			{
			err += dy;
			startPos.x += sx;
			}
		if (e2 <= dx)
			{
			err += dx;
			startPos.y += sy;
			}
		}
	}


// TODO Handle reverse start and end coordinates
// TODO Handle fill
// TODO Handle thickness
void mGraphics_DrawBox(bool *buffer, point startPos, point endPos, bool white, int thickness, bool fill)
	{
	for(int posY = 0; posY <= (endPos.y-startPos.y); posY++)
		{
		for(int posX = 0; posX <= (endPos.x-startPos.x); posX++)
			{
			point drawPoint = {x:startPos.x+posX, y:startPos.y+posY};

			mGraphics_DrawPixel(buffer, drawPoint, white);
			}
		}
	}

void mGraphics_DrawCircle(bool *buffer, point startPos, point endPos, bool white, int thickness, bool fill)
	{

	}


void mGraphics_DrawPixel(bool *buffer, point pos, bool white)
	{
	if(mGraphics_IsPointInRange(pos))
		{
		buffer[pos.x+pos.y*DISPLAY_WIDTH] = white;
		}
	}

void mGraphics_DrawPixelNew(char* buffer, point pos, bool enable)
	{
	if(mGraphics_IsPointInRange(pos))
		{

		}
	}

void mGraphics_DrawImage(bool *buffer, const bool *image, point imageSize, point pos, bool inverseColor)
	{

	int totalImgPixel = imageSize.x*imageSize.y;

	for(int i = 0; i < totalImgPixel; i++)
		{
		point imgDrawPos = {i%imageSize.x, (i/imageSize.x)}; // Drawing position in image
		point displayDrawPos = {imgDrawPos.x+pos.x, imgDrawPos.y+pos.y}; // Drawing position on screen

		mGraphics_DrawPixel(buffer, displayDrawPos, image[(imgDrawPos.x+(imgDrawPos.y)*imageSize.x)] == !inverseColor);
		}
	}

void mGraphics_DrawText(bool *buffer, char *text, font f, point pos, bool inverseColor)
	{

	for(int i = 0; i < strlen(text); i++)
		{

		bool bmpChar[f.width*f.height];

		for(int j = 0; j < f.width*f.height; j++)
			{
				bmpChar[j] = (f.charList[text[i]] >> j) & 0x01;
			}

		mGraphics_DrawImage(
				buffer,
				bmpChar,
				(point){f.width, f.height},
				(point){pos.x+i*(f.width+1), pos.y},
				inverseColor);
		}
	}

point mGraphics_GetTextSize(char* text, font f)
	{
	return (point){strlen(text)*(f.width+1)-1, f.height};
	}

void mGraphics_Print(bool *buffer)
	{
	mDisplay_SendBuffer(buffer);
	}

bool mGraphics_IsPointInRange(point p)
	{
	return p.x >= 0 && p.x < DISPLAY_WIDTH && p.y >= 0 && p.y < DISPLAY_HEIGHT;
	}

point mGraphics_TrimPoint(point p)
	{
	point newPoint;
	newPoint.x = p.x < 0 ? 0 : p.x >= DISPLAY_WIDTH ? DISPLAY_WIDTH : p.x;
	newPoint.y = p.y < 0 ? 0 : p.y >= DISPLAY_HEIGHT ? DISPLAY_HEIGHT : p.y;
	return newPoint;
	}

