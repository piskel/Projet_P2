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

// UI Instantiation
UIPage* mGUI_CreatePage(char* name);
UIText* mGUI_CreateText(char* name, point position, bool interactive, char* linkedPage, char* text);
UIImage* mGUI_CreateImage(char* name, point position, bool interactive, char* linkedPage, const bool* image, point imageSize);

// UI Initialization
void mGUI_AddElementToPage(const char* uiPageName, char* uiElementName);
void mGUI_SetInitContext(const char* uiPageName);

// UI Getters
UIPage* mGUI_GetPageFromName(const char* name);
UIElement* mGUI_GetElementFromName(const char* name);
char* mGUI_GetCurrentPageName();
char* mGUI_GetCurrentElementName();
UIPage* mGUI_GetCurrentPage();
UIElement* mGUI_GetCurrentElement();
UIContext* mGUI_GetCurrentContext();

// UI Navigation
void mGUI_SetCurrentPage(const char* uiPageName);
void mGUI_PreviousContext();
void mGUI_NavigateInteractive(bool direction);
void mGUI_GoToLinkedPage();

// UI Printing
void mGUI_PrintPage(const char* name);
void mGUI_PrintElement(const char* name);
void mGUI_PrintText(UIText* pUIText);
void mGUI_PrintImage(UIImage* pUIImage);
void mGUI_PrintCurrentPage();




#endif /* MODULES_MGUI_H_ */
