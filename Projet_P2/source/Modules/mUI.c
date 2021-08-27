/*
 * mUI.c
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */


#include <Modules/mUI.h>
#include <def.h>
#include <stdlib.h>
#include <string.h>

#include "pixelFont.h"

// TODO Make it dynamically allocated
#define UI_MAX_PAGES 64
#define UI_MAX_ELEMENTS 512
#define UI_MAX_ACTIONS 256
#define UI_MAX_TEXT_SIZE 32
#define UI_MAX_ELEMENT_PER_PAGE 32

static bool buffer[DISPLAY_HEIGHT*DISPLAY_WIDTH];
static UIPage* uiPageTab[UI_MAX_PAGES]; // TODO: Page zero should be the error page
static UIElement* uiElementTab[UI_MAX_ELEMENTS];

static UIContext uiContext = {uiPageName: "", uiElementName: ""};


static int nbUIPage = 0;
static int nbUIElement = 0;

extern const font pixelFont4x5;

void mUI_Setup()
	{
	mUI_CreatePage("error_page");
	mUI_CreateLabel("error_label", (point){0, 0}, "ERROR");

//	mUI_CreateButton("error_button", (point){0, 0}, "ERROR", pUIAction);
	mUI_AddElementToPage("error_label", "error_page");
	}

void mUI_CreatePage(const char* uiPageName)
	{
	uiPageTab[nbUIPage] = (UIPage*) malloc(sizeof(UIPage));

	uiPageTab[nbUIPage]->nbUIElements = 0;
	uiPageTab[nbUIPage]->tabUIElementName = (char**) calloc(UI_MAX_ELEMENT_PER_PAGE, sizeof(char*));

	uiPageTab[nbUIPage]->name = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));
	strcpy(uiPageTab[nbUIPage]->name, uiPageName);

	nbUIPage++;
	}

void mUI_DeletePage(const char* uiPageName)
	{

	}

UIPage* mUI_GetPage(const char* uiPageName)
	{
	for(int i = 0; i < UI_MAX_PAGES; i++)
		{
		if (strcmp(uiPageTab[i]->name, uiPageName) == 0) return uiPageTab[i];
		}
	return uiPageTab[0];
	}

//void mUI_CreateElement(char* uiElementName, point pos)
//	{
//
//	}

void mUI_CreateLabel(const char* uiElementName, point pos, const char* text)
	{
	uiElementTab[nbUIElement] = (UIElement*) malloc(sizeof(UILabel));
	UILabel* pUILabel = ((UILabel*)uiElementTab[nbUIElement]);

	pUILabel->super.name = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));
	pUILabel->text = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));

	pUILabel->super.aUIElementType = kUILabel;

	pUILabel->super.name = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));
	pUILabel->text = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));

	pUILabel->super.pos = pos;

	strcpy(pUILabel->super.name, uiElementName);
	strcpy(pUILabel->text, text);
//	pUILabel->super.name = uiElementName;
//	pUILabel->text = text;
	nbUIElement++;
	}

void mUI_CreateButton(const char* uiElementName, point pos, const char* text, UIAction* pUIAction)
	{
	uiElementTab[nbUIElement] = (UIElement*) malloc(sizeof(UIButton));
	UIButton* pUIButton = ((UIButton*)uiElementTab[nbUIElement]);

	pUIButton->super.name = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));
	pUIButton->text = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));

	pUIButton->super.aUIElementType = kUIButton;
	pUIButton->super.pos = pos;

	strcpy(pUIButton->super.name, uiElementName);
	strcpy(pUIButton->text, text);

	pUIButton->aUIAction = pUIAction;


//	pUIButton->super.name = uiElementName;
//	pUIButton->text = text;

	nbUIElement++;
	}

void mUI_DeleteElement(const char* uiElementName) {}

UIElement* mUI_GetElement(const char* uiElementName)
	{
	for(int i = 0; i < UI_MAX_ELEMENTS; i++)
		{
		const char* uiElementNameTest = uiElementTab[i]->name;
		if (strcmp(uiElementNameTest, uiElementName) == 0)
			{
			return uiElementTab[i];
			}
		}
	return uiElementTab[0];
	}

void mUI_AddElementToPage(const char* uiElementName, const char* uiPageName)
	{
	UIPage* uiPage = mUI_GetPage(uiPageName);

	// Sets the element to the error_label if the one specified does not exist

//	strcpy(uiPage->tabUIElementName[uiPage->nbUIElements], mUI_GetElement(uiElementName)->name);
	uiPage->tabUIElementName[uiPage->nbUIElements] = mUI_GetElement(uiElementName)->name;

	uiPage->nbUIElements++;
	}


void mUI_HandleElement(const char* uiElementName)
	{
	UIElement* uiElement = mUI_GetElement(uiElementName);
	switch (uiElement->aUIElementType) {
		case kUILabel:;
//			const UILabel * uiLabel = (UILabel*)uiElement;
			break;

		case kUIButton:;
			const UIButton * uiButton = (UIButton*)uiElement;
			mUI_HandleAction(uiButton->aUIAction);
			break;
		}
	}


void mUI_HandleAction(const UIAction* uiAction)
	{
	switch (uiAction->aUIActionType) {
		case kUIActionFocusPage:;
			const UIActionFocusPage* uiActionFocusPage = (UIActionFocusPage*)uiAction;
			mUI_ActionFocusPage(uiActionFocusPage->uiPageName);
			break;

		case kUIActionFocusElement:;
			const UIActionFocusElement* uiActionFocusElement = (UIActionFocusElement*)uiAction;
			mUI_ActionFocusElement(uiActionFocusElement->uiPageName, uiActionFocusElement->uiElementName);
			break;
		}
	}

void mUI_ActionFocusPage(const char* uiPageName)
	{
	uiContext.uiPageName = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));
	strcpy(uiContext.uiPageName, uiPageName);
	}

void mUI_ActionFocusElement(const char* uiPageName, const char* uiElementName)
	{
	uiContext.uiPageName = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));
	uiContext.uiElementName = (char*) calloc(UI_MAX_TEXT_SIZE, sizeof(char));
	strcpy(uiContext.uiPageName, uiPageName);
	strcpy(uiContext.uiElementName, uiElementName);
	}



void mUI_PrintPage(const char* uiPageName)
	{
	UIPage* uiPage = mUI_GetPage(uiPageName);

	mGraphics_FillBuffer(buffer, false);

	for(int i = 0; i < uiPage->nbUIElements; i++)
		{
		mUI_PrintElement(uiPage->tabUIElementName[i], buffer);
		}
	mGraphics_Print(buffer);
	return;
	}

void mUI_PrintElement(const char* uiElementName, bool* buffer)
	{

	UIElement* uiElement = mUI_GetElement(uiElementName);

	switch (uiElement->aUIElementType)
		{
		case kUILabel:;
			const UILabel* uiLabel = (UILabel*)uiElement;
			mUI_PrintLabel(uiLabel, buffer);
			break;

		case kUIButton:;
			const UIButton* uiButton = (UIButton*)uiElement;
			mUI_PrintButton(uiButton, buffer);
			break;
		}
	}


void mUI_PrintLabel(const UILabel* uiLabel, bool* buffer)
	{
	mGraphics_DrawText(buffer, uiLabel->text, pixelFont4x5, uiLabel->super.pos, false);
	}

void mUI_PrintButton(const UIButton* uiButton, bool* buffer)
	{
	// TODO Ability to change the font
	point textSize = mGraphics_GetTextSize(uiButton->text, pixelFont4x5);
	point buttonStartPos = uiButton->super.pos;

	int thickness = 1;

	point buttonEndPos = {
			x: buttonStartPos.x+textSize.x + 2*thickness-1,
			y: buttonStartPos.y+textSize.y + 2*thickness-1
	};
	mGraphics_DrawBox(buffer, buttonStartPos, buttonEndPos, true, 1, true);
	mGraphics_DrawText(buffer, uiButton->text, pixelFont4x5, (point){buttonStartPos.x+1, buttonStartPos.y+1}, true);
	}

void mUI_ContextMoveElement(int shift)
	{
	UIPage* uiPage = mUI_GetPage(uiContext.uiPageName);

	int elementPosition = 0;

	for(int i = 0; i < uiPage->nbUIElements; i++)
		{
		UIElement* cursorUIElement = mUI_GetElement(uiPage->tabUIElementName[i]);
		if(strcmp(cursorUIElement->name, uiContext.uiElementName)) elementPosition = i;
		}
	elementPosition = (elementPosition + shift)%uiPage->nbUIElements;

	uiContext.uiElementName = mUI_GetElement(uiPage->tabUIElementName[elementPosition])->name;

	}

void mUI_TriggerAction()
	{

	}

