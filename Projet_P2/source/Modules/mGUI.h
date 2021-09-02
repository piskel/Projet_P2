/*
 * mGUI.h
 *
 *  Created on: 29 août 2021
 *      Author: luc.froideva
 */

#ifndef MODULES_MGUI_H_
#define MODULES_MGUI_H_

#include "def.h"

typedef enum UIElementType
	{
	kUIText,
	kUIImage
	} UIElementType;

typedef struct UIElement
	{
	char* name;
	point position;
	UIElementType uiElementType;
	bool interactive;
	bool selected;
	char* linkedPage;
	}UIElement;

typedef struct UIText
	{
	UIElement super;
	char* text;
	} UIText;

typedef struct UIImage
	{
	UIElement super;
	bool* image;
	point imageSize;
	} UIImage;


typedef struct UIPage
	{
	char* name;
	char** uiElementNameTab;
	int nbUIElement;
	}UIPage;

// When pressing a button, we look at the context to know which action to perform
typedef struct UIContext
	{
	char* uiPageName;
	int cursor;
	} UIContext;

void mGUI_Setup();

void mGUI_CreatePage(const char* name);

void mGUI_CreateText(const char* name, point position, bool interactive, const char* linkedPage, const char* text);
void mGUI_CreateImage(const char* name, point position, bool interactive, const char* linkedPage, bool* image, point imageSize);

UIPage* mGUI_GetPageFromName(const char* name);
UIElement* mGUI_GetElementFromName(const char* name);

void mGUI_AddElementToPage(const char* uiElementName, const char* uiPageName);

void mGUI_PrintPage(const char* name);
void mGUI_PrintElement(const char* name);
void mGUI_PrintText(UIText* pUIText);
void mGUI_PrintImage(UIImage* pUIImage);

void mGUI_SetInitContext(const char* uiPageName);
void mGUI_SetCurrentPage(const char* uiPageName);
void mGUI_PrintCurrentPage();
void mGUI_NavigateInteractive(bool direction);

char* mGUI_GetCurrentPageName();
char* mGUI_GetCurrentElementName();

void mGUI_GoToLinkedPage();

void mGUI_CopyString(const char* source, char* target);

#endif /* MODULES_MGUI_H_ */
