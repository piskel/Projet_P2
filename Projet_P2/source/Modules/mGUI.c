/*
 * mGUI.c
 *
 *  Created on: 29 août 2021
 *      Author: luc.froideva
 */


#include "mGUI.h"

#include "stdlib.h"
#include "mGraphics.h"

#include "pixelFont.h"


extern const font pixelFont4x5;

static bool buffer[DISPLAY_HEIGHT*DISPLAY_WIDTH];

static UIPage** uiPageTab;
static UIElement** uiElementTab;
static UIContext uiContext;

static int nbUIPage = 0;
static int nbUIElement = 0;

void mGUI_Setup()
	{
	uiPageTab = (UIPage**) malloc(sizeof(UIPage*));
	uiElementTab = (UIElement**) malloc(sizeof(UIElement*));

	mGUI_CreatePage("error_page");
	mGUI_CreateText("error_text", (point){0, 0}, false, "ERROR");
	mGUI_AddElementToPage("error_text", "error_page");

	uiContext.uiPageName = "error_page";
	uiContext.cursor = -1;

	mGUI_SetCurrentPage("error_page");
	}

void mGUI_CreatePage(const char* name)
	{

	uiPageTab = (UIPage**) realloc(uiPageTab, (nbUIPage+1)*sizeof(UIPage*));
	uiPageTab[nbUIPage] = (UIPage*) malloc(sizeof(UIPage));

//	mGUI_CopyString(name, uiPageTab[nbUIPage]->name);
	uiPageTab[nbUIPage]->name = name;
	uiPageTab[nbUIPage]->nbUIElement = 0;
	uiPageTab[nbUIPage]->uiElementNameTab = (char**) malloc(sizeof(char*));


	nbUIPage++;
	}

void mGUI_CreateText(const char* name, point position, bool interactive, const char* text)
	{
	uiElementTab = (UIElement**) realloc(uiElementTab, (nbUIElement+1)*sizeof(UIElement*));
	uiElementTab[nbUIElement] = (UIElement*) malloc(sizeof(UIText));

	UIText* pUIText = (UIText*)uiElementTab[nbUIElement];

//	mGUI_CopyString(name, pUIText->super.name);
	pUIText->super.name = name;
	pUIText->super.position = position;
	pUIText->super.uiElementType = kUIText;
	pUIText->super.interactive = interactive;
	pUIText->super.selected = false;
//	mGUI_CopyString(text, pUIText->text);
	pUIText->text = text;

	nbUIElement++;
	}

void mGUI_CreateImage(const char* name, point position, bool interactive, bool* image, point imageSize)
	{
	uiElementTab = (UIElement**) realloc(uiElementTab, (nbUIElement+1)*sizeof(UIElement*));
	uiElementTab[nbUIElement] = (UIElement*) malloc(sizeof(UIImage));

	UIImage* pUIImage = (UIImage*)uiElementTab[nbUIElement];

//	mGUI_CopyString(name, uiElementTab[nbUIElement]->name);
	pUIImage->super.name = name;
	pUIImage->super.position = position;
	pUIImage->super.uiElementType = kUIImage;
	pUIImage->super.interactive = interactive;
	pUIImage->super.selected = false;

	memcpy(pUIImage->image, image, sizeof(bool)*imageSize.x*imageSize.y);
	pUIImage->imageSize = imageSize;

	nbUIElement++;
	}


UIPage* mGUI_GetPageFromName(const char* name)
	{
	for(int i = 0; i < nbUIPage; i++)
		{
		if(strcmp(uiPageTab[i]->name, name) == 0)
			{
			return uiPageTab[i];
			}
		}
	return uiPageTab[0]; // Returns the error page
	}

UIElement* mGUI_GetElementFromName(const char* name)
	{
	for(int i = 0; i < nbUIElement; i++)
		{
		if(strcmp(uiElementTab[i]->name, name) == 0)
			{
			return uiElementTab[i];
			}
		}
	return uiElementTab[0]; // Returns the error text
	}

void mGUI_AddElementToPage(const char* uiElementName, const char* uiPageName)
	{

	UIPage* pUIPage = mGUI_GetPageFromName(uiPageName);

	pUIPage->uiElementNameTab = (char**) realloc(pUIPage->uiElementNameTab, (pUIPage->nbUIElement+1)*sizeof(char*));
//	mGUI_CopyString(uiElementName, pUIPage->uiElementNameTab[pUIPage->nbUIElement]);
	pUIPage->uiElementNameTab[pUIPage->nbUIElement] = uiElementName;

	pUIPage->nbUIElement++;

	}



void mGUI_PrintPage(const char* name)
	{

	mGraphics_FillBuffer(buffer, false);

	UIPage* pUIPage = mGUI_GetPageFromName(name);

	for(int i = 0; i < pUIPage->nbUIElement; i++)
		{
		mGUI_PrintElement(pUIPage->uiElementNameTab[i]);
		}
	mGraphics_Print(buffer);
	}

void mGUI_PrintElement(const char* name)
	{
	UIElement* pUIElement = mGUI_GetElementFromName(name);

	switch (pUIElement->uiElementType)
		{
		case kUIText:
			mGUI_PrintText((UIText*)pUIElement);
			break;

		case kUIImage:
			mGUI_PrintImage((UIImage*)pUIElement);
			break;

		default:
			break;
		}

	}

void mGUI_PrintText(UIText* pUIText)
	{
	point textSize = mGraphics_GetTextSize(pUIText->text, pixelFont4x5);
	point textPosition = {pUIText->super.position.x+1, pUIText->super.position.y+1};
	point endPosition = {pUIText->super.position.x+textSize.x+1, pUIText->super.position.y+textSize.y+1};
	mGraphics_DrawBox(buffer, pUIText->super.position, endPosition, pUIText->super.selected, 1, true);
	mGraphics_DrawText(buffer, pUIText->text, pixelFont4x5, textPosition, pUIText->super.selected);
	}

void mGUI_PrintImage(UIImage* pUIImage)
	{

	}

void mGUI_SetCurrentPage(const char* uiPageName)
	{
	UIPage* pUIPage = mGUI_GetPageFromName(uiPageName);
	uiContext.uiPageName = pUIPage->name;
	uiContext.cursor = -1;

	for(int i = 0; i < pUIPage->nbUIElement; i++)
		{
		UIElement* pUIElement = mGUI_GetElementFromName(pUIPage->uiElementNameTab[i]);
		if(pUIElement->interactive == true)
			{
			uiContext.cursor = i;
			pUIElement->selected =  true;
			break;
			}
		}
	}

// true: down, false: up
void mGUI_NavigateInteractive(bool direction)
	{
	UIPage* pUIPage = mGUI_GetPageFromName(uiContext.uiPageName);

	for(int i = 0; i < pUIPage->nbUIElement; i++)
		{
		UIElement* pUIElement = mGUI_GetElementFromName(pUIPage->uiElementNameTab[i]);
		pUIElement->selected = false;
		}

	int step = direction ? 1 : -1;
	int currentCursor = (uiContext.cursor + pUIPage->nbUIElement + step)%pUIPage->nbUIElement;

	while(currentCursor != uiContext.cursor)
		{
			UIElement* pUIElement = mGUI_GetElementFromName(pUIPage->uiElementNameTab[currentCursor]);

			if(pUIElement->interactive == true)
				{
				pUIElement->selected = true;
				uiContext.cursor = currentCursor;
				break;
				}

			currentCursor = (currentCursor+pUIPage->nbUIElement+step)%pUIPage->nbUIElement;
		}

	}

void mGUI_PrintCurrentPage()
	{
	mGUI_PrintPage(uiContext.uiPageName);
	}

//  FIXME Doesn't work
void mGUI_CopyString(const char* source, char* target)
	{
	target = (char*) malloc(strlen(source)+1);
	memcpy(target, source, strlen(source)+1);
	}
