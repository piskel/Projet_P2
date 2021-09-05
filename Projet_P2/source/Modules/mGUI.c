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

static int nbUIPage = 0;
static int nbUIElement = 0;

static UIContext** uiContextTab;
static int uiContextTabSize = 0;

void mGUI_Setup()
	{
	mGraphics_Setup();

	uiPageTab = (UIPage**) malloc(sizeof(UIPage*));
	uiElementTab = (UIElement**) malloc(sizeof(UIElement*));
	uiContextTab = (UIContext**) malloc(sizeof(UIContext*));

	mGUI_CreatePage("error_page");
	mGUI_CreateText("error_text", (point){0, 0}, false, "", "ERROR");
	mGUI_AddElementToPage("error_text", "error_page");


	mGUI_SetCurrentPage("error_page");
	}

UIPage* mGUI_CreatePage(char* name)
	{

	uiPageTab = (UIPage**) realloc(uiPageTab, (nbUIPage+1)*sizeof(UIPage*));
	uiPageTab[nbUIPage] = (UIPage*) malloc(sizeof(UIPage));

	uiPageTab[nbUIPage]->name = name;
	uiPageTab[nbUIPage]->nbUIElement = 0;
	uiPageTab[nbUIPage]->uiElementNameTab = (char**) malloc(sizeof(char*));


	nbUIPage++;

	return uiPageTab[nbUIPage];
	}

UIText* mGUI_CreateText(char* name, point position, bool interactive, char* linkedPage, char* text)
	{
	uiElementTab = (UIElement**) realloc(uiElementTab, (nbUIElement+1)*sizeof(UIElement*));
	uiElementTab[nbUIElement] = (UIElement*) malloc(sizeof(UIText));

	UIText* pUIText = (UIText*)uiElementTab[nbUIElement];

	pUIText->super.name = name;
	pUIText->super.position = position;
	pUIText->super.uiElementType = kUIText;
	pUIText->super.interactive = interactive;
	pUIText->super.selected = false;
	pUIText->super.linkedPage = linkedPage;
	pUIText->text = text;

	nbUIElement++;

	return pUIText;
	}

UIImage* mGUI_CreateImage(char* name, point position, bool interactive, char* linkedPage, bool* image, point imageSize)
	{
	uiElementTab = (UIElement**) realloc(uiElementTab, (nbUIElement+1)*sizeof(UIElement*));
	uiElementTab[nbUIElement] = (UIElement*) malloc(sizeof(UIImage));

	UIImage* pUIImage = (UIImage*)uiElementTab[nbUIElement];

	pUIImage->super.name = name;
	pUIImage->super.position = position;
	pUIImage->super.uiElementType = kUIImage;
	pUIImage->super.interactive = interactive;
	pUIImage->super.selected = false;
	pUIImage->super.linkedPage = linkedPage;

	memcpy(pUIImage->image, image, sizeof(bool)*imageSize.x*imageSize.y);
	pUIImage->imageSize = imageSize;

	nbUIElement++;

	return pUIImage;
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

void mGUI_AddElementToPage(const char* uiPageName, char* uiElementName)
	{

	UIPage* pUIPage = mGUI_GetPageFromName(uiPageName);

	pUIPage->uiElementNameTab = (char**) realloc(pUIPage->uiElementNameTab, (pUIPage->nbUIElement+1)*sizeof(char*));
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

void mGUI_SetInitContext(const char* uiPageName)
	{
	uiContextTab[0] = (UIContext*) malloc(sizeof(UIContext));

	UIPage* pUIPage = mGUI_GetPageFromName(uiPageName);
	uiContextTab[0]->uiPageName = pUIPage->name;
	uiContextTab[0]->cursor = -1;

	if(uiContextTabSize == 0)  uiContextTabSize = 1;

	// Sets the initial cursor position
	for(int i = 0; i < pUIPage->nbUIElement; i++)
		{
		UIElement* pUIElement = mGUI_GetElementFromName(pUIPage->uiElementNameTab[i]);
		if(pUIElement->interactive == true)
			{
			uiContextTab[0]->cursor = i;
			pUIElement->selected =  true;
			break;
			}
		}
	}

void mGUI_SetCurrentPage(const char* uiPageName)
	{

	if(uiContextTabSize == 0)
	{
		mGUI_SetInitContext(uiPageName);
		return;
	}
	if(strcmp(mGUI_GetPageFromName(uiPageName)->name, mGUI_GetCurrentPageName())==0) return;

	UIPage* pUICurrentPage = mGUI_GetPageFromName(mGUI_GetCurrentContext()->uiPageName);

	// Deselects all the elements on the current page
	for(int i = 0; i < pUICurrentPage->nbUIElement; i++)
	{
		UIElement* pUIElement = mGUI_GetElementFromName(pUICurrentPage->uiElementNameTab[i]);
		pUIElement->selected = false;
	}

	uiContextTabSize++;
	uiContextTab = (UIContext**) realloc(uiContextTab, uiContextTabSize*sizeof(UIContext*));

	uiContextTab[uiContextTabSize-1] = (UIContext*) malloc(sizeof(UIContext));

	UIPage* pUIPage = mGUI_GetPageFromName(uiPageName);
	mGUI_GetCurrentContext()->uiPageName = pUIPage->name;
	mGUI_GetCurrentContext()->cursor = -1;

	mGUI_NavigateInteractive(true);
	}


void mGUI_PreviousContext()
	{
	// Abort if there is one or no context in the tab
	if(uiContextTabSize <= 1) return;

	uiContextTabSize--;

	free(uiContextTab[uiContextTabSize]); // Free value in the tab

	// Rescale the tab size
	uiContextTab = (UIContext**) realloc(uiContextTab, uiContextTabSize*sizeof(UIContext*));

	if(mGUI_GetCurrentContext()->cursor >= 0)
		{
		UIElement* pUIElement = mGUI_GetElementFromName(mGUI_GetCurrentElementName());
		pUIElement->selected = true;
		}
	}

// true: down, false: up
void mGUI_NavigateInteractive(bool direction)
	{
	UIPage* pUIPage = mGUI_GetPageFromName(uiContextTab[uiContextTabSize-1]->uiPageName);

	bool check = false;
	// Deselects all the elements and checks if there are any interactive ones
	for(int i = 0; i < pUIPage->nbUIElement; i++)
		{
		UIElement* pUIElement = mGUI_GetElementFromName(pUIPage->uiElementNameTab[i]);
		pUIElement->selected = false;
		if(pUIElement->interactive) check = true;
		}

	// Abort if there are no interactive elements
	if(!check) return;


	int step = direction ? 1 : -1;

	int currentCursor = (mGUI_GetCurrentContext()->cursor + pUIPage->nbUIElement + step)%pUIPage->nbUIElement;

	do{
		UIElement* pUIElement = mGUI_GetElementFromName(pUIPage->uiElementNameTab[currentCursor]);

		if(pUIElement->interactive == true)
			{
			pUIElement->selected = true;
			mGUI_GetCurrentContext()->cursor = currentCursor;
			break;
			}

		currentCursor = (currentCursor+pUIPage->nbUIElement+step)%pUIPage->nbUIElement;

	}while(currentCursor != mGUI_GetCurrentContext()->cursor);


	}

void mGUI_PrintCurrentPage()
	{
	mGUI_PrintPage(uiContextTab[uiContextTabSize-1]->uiPageName);
	}


char* mGUI_GetCurrentPageName()
	{
	return uiContextTab[uiContextTabSize-1]->uiPageName;
	}

char* mGUI_GetCurrentElementName()
	{
	return mGUI_GetPageFromName(uiContextTab[uiContextTabSize-1]->uiPageName)->uiElementNameTab[uiContextTab[uiContextTabSize-1]->cursor];
	}


UIPage* mGUI_GetCurrentPage()
	{
	return mGUI_GetPageFromName(mGUI_GetCurrentPageName());
	}
UIElement* mGUI_GetCurrentElement()
	{
	return mGUI_GetElementFromName(mGUI_GetCurrentElementName());
	}

UIContext* mGUI_GetCurrentContext()
	{
	return uiContextTab[uiContextTabSize-1];
	}


void mGUI_GoToLinkedPage()
	{
	UIContext* pUIContext = mGUI_GetCurrentContext();
	if(pUIContext->cursor < 0) return;
	UIElement* pUIElement = mGUI_GetElementFromName(mGUI_GetCurrentElementName());
	mGUI_SetCurrentPage(pUIElement->linkedPage);
	}
