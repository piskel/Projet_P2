/*
 * mUI.c
 *
 *  Created on: 26 août 2021
 *      Author: luc.froideva
 */


#include <Modules/mUI.h>

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
			const UIActionFocusPage * uiActionFocusPage = (UIActionFocusPage*)uiAction;
			mUI_ActionFocusPage(uiActionFocusPage->idPage);
			break;

		case kUIActionFocusElement:;
			const UIActionFocusElement * uiActionFocusElement = (UIActionFocusElement*)uiAction;
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


