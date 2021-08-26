/*
 * mGraphics.h
 *
 *  Created on: 25 août 2021
 *      Author: luc.froideva
 */

#ifndef MGRAPHICS_H_
#define MGRAPHICS_H_

#include <def.h>
#include <pixelFont.h>
#include "string.h"


void mGraphics_FillBuffer(bool *buffer, bool white);
void mGraphics_DrawLine(bool *buffer, point startPos, point endPos, bool white, int thickness);
void mGraphics_DrawBox(bool *buffer, point startPos, point endPos, bool white, int thickness, bool fill);
void mGraphics_DrawCircle(bool *buffer, point startPos, point endPos, bool white, int thickness, bool fill);
void mGraphics_DrawPixel(bool *buffer, point pos, bool white);
void mGraphics_DrawImage(bool *buffer, const bool *image, point imageSize, point pos, bool inverseColor);
void mGraphics_DrawText(bool *buffer, char *text, font f, point pos, bool inverseColor);
point mGraphics_GetTextSize(char* text);

void mGraphics_Print(bool *buffer);

bool mGraphics_IsPointInRange(point p);
point mGraphics_TrimPoint(point p);



#endif /* MGRAPHICS_H_ */
