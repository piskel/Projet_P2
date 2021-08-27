/*
 * mUI.h
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */

#ifndef MUI_H_
#define MUI_H_

#include "def.h"
#include "mGraphics.h"

// Navigation des éléments dans l'ordre d'ajout à la page !!!!


// https://stackoverflow.com/questions/18422002/best-approach-for-struct-polymorphism-in-c


typedef enum UIActionType
	{
		kUIActionFocusPage,
		kUIActionFocusElement
	} UIActionType;


///////////////////////////////////////////////////////////////
// UI ACTIONS /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

typedef struct UIAction
	{
		UIActionType aUIActionType;
	} UIAction;

typedef struct UIActionFocusPage
	{
		UIAction super;
		char* uiPageName;

	} UIActionFocusPage;

typedef struct UIActionFocusElement
	{
		UIAction super;
		char* uiPageName;
		char* uiElementName;

	} UIActionFocusElement;




///////////////////////////////////////////////////////////////
// UI ELEMENTS ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

typedef enum UIElementType
	{
		kUILabel,
		kUIButton
	} UIElementType;

typedef struct UIElement
	{
		char* name;
		UIElementType aUIElementType;
		point pos;
	} UIElement;

typedef struct UILabel
	{
		UIElement super;
		char* text;

	} UILabel;

typedef struct UIButton
	{
		UIElement super;
		char* text;
		UIAction* aUIAction;

	} UIButton;


typedef struct UIPage
	{
		char* name;
		char** tabUIElementName;
		int nbUIElements;

	} UIPage;

typedef struct UIContext
	{
		char* uiPageName;
		char* uiElementName;
	} UIContext;


void mUI_Setup();

void mUI_CreatePage(const char* uiPageName);
void mUI_DeletePage(const char* uiPageName);
UIPage* mUI_GetPage(const char* uiPageName);

//void mUI_CreateElement(char* uiElementName, point pos);
void mUI_CreateLabel(const char* uiElementName, point pos, const char* text);
void mUI_CreateButton(const char* uiElementName, point pos, const char* text, UIAction* pUIAction);
void mUI_DeleteElement(const char* uiElementName);
UIElement* mUI_GetElement(const char* uiElementName);

void mUI_AddElementToPage(const char* uiElementName, const char* uiPageName);

// TODO MAKE SURE TO DELETE ALL ACTIONS LINKED TO ELEMENTS !!!

void mUI_HandleElement(const char* uiElementName);
void mUI_HandleAction(const UIAction* uiAction);

void mUI_ActionFocusPage(const char* uiPageName);
void mUI_ActionFocusElement(const char* uiPageName, const char* uiElementName);

void mUI_PrintPage(const char* uiPageId);
void mUI_PrintElement(const char* uiElementName, bool* buffer);
void mUI_PrintLabel(const UILabel* uiLabel, bool* buffer);
void mUI_PrintButton(const UIButton* uiButton, bool* buffer);

#endif /* MUI_H_ */
