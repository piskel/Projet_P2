/*
 * mUI.c
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */


#include <Modules/mUI.h>
#include <def.h>

#include "pixelFont.h"

#define UI_MAX_PAGES 64
#define UI_MAX_ELEMENTS 512

static bool buffer[DISPLAY_HEIGHT*DISPLAY_WIDTH];

static UIContext uiContext;

static UIPage* uiPageTab[UI_MAX_PAGES];
static UIElement* uiElementTab[UI_MAX_ELEMENTS];

extern const font pixelFont4x5;


void mUI_Setup()
	{

	}

void mUI_AddPage(char* pageName)
	{

	}

void mUI_AddElement(UIElement* uiElement, char* pageName)
	{

	}

void mUI_AddLabel(UILabel* uiLabel, char* pageName)
	{

	}

void mUI_AddButton(UIButton* uiButton, char* pageName)
	{

	}

void mUI_HandleElement(const UIElement* uiElement)
	{
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
			mUI_ActionFocusPage(uiActionFocusPage->idPage);
			break;

		case kUIActionFocusElement:;
			const UIActionFocusElement* uiActionFocusElement = (UIActionFocusElement*)uiAction;
			mUI_ActionFocusElement(uiActionFocusElement->idElement);
			break;
		}
	}

void mUI_ActionFocusPage(int idPage)
	{

	}

void mUI_ActionFocusElement(int idElement)
	{

	}



void mUI_PrintPage(const UIPage uiPage)
	{
	mGraphics_FillBuffer(buffer, false);

	for(int i = 0; i < uiPage.nbUIElements; i++)
		{
		UIElement *uiElement = uiPage.pUIElementTab[i];
		mUI_PrintElement(uiElement, buffer);
		}
	mGraphics_Print(buffer);
	return;
	}

void mUI_PrintElement(const UIElement* uiElement, bool* buffer)
	{

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

