/*
 * mUI.h
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */

#ifndef MUI_H_
#define MUI_H_

#include "def.h"

// Navigation des éléments dans l'ordre d'ajout à la page !!!!


// https://stackoverflow.com/questions/18422002/best-approach-for-struct-polymorphism-in-c

typedef enum UIElementType
	{
		kUILabel,
		kUIButton
	} UIElementType;

typedef enum UIActionType
	{
		kUIActionFocusPage,
		kUIActionFocusElement
	} UIActionType;


typedef struct UIAction
	{
		UIActionType aUIActionType;
	} UIAction;

typedef struct UIActionFocusPage
	{
		UIAction super;
		int idPage;

	} UIActionFocusPage;

typedef struct UIActionFocusElement
	{
		UIAction super;
		int idElement;

	} UIActionFocusElement;

typedef struct UIContext
	{
		int pageId;
		int elementId;
	} UIContext;

typedef struct UIPage
	{
		int* idUIElements;
		int nbUIElements;

	} UIPage;


typedef struct UIElement
	{
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


void mUI_HandleElement(const UIElement* uiElement);
void mUI_HandleAction(const UIAction* uiAction);
void mUI_ActionFocusPage(int idPage);
void mUI_ActionFocusElement(int idElement);


#endif /* MUI_H_ */
