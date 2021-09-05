/*
 * gGUI.h
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#ifndef GESTIONNAIRES_GGUI_H_
#define GESTIONNAIRES_GGUI_H_


void gGUI_Setup();

void gGUI_Execute();
void gGUI_RenderValues();
void gGUI_HandleActions();

void gGUI_FormatValue(int value, char* string, int pos, const char* unit);

#endif /* GESTIONNAIRES_GGUI_H_ */
