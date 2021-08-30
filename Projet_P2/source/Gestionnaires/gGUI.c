/*
 * gGUI.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#include "gGUI.h"
#include "gMBox.h"

#include "mGUI.h"

char** pagePath;

void gGUI_Setup()
	{
	mGUI_Setup();

	mGUI_CreatePage("main_menu_page");

	mGUI_CreateText("main_menu_sensors", (point){0, 0}, true, "sensors_menu_page",  "Sensors");
	mGUI_AddElementToPage("main_menu_sensors", "main_menu_page");

	mGUI_CreateText("main_menu_settings", (point){0, 8}, true, "settings_menu_page", "Settings");
	mGUI_AddElementToPage("main_menu_settings", "main_menu_page");

	mGUI_CreateText("main_menu_about", (point){0, 16}, true, "about_page", "About");
	mGUI_AddElementToPage("main_menu_about", "main_menu_page");



	mGUI_CreatePage("sensors_menu_page");

	mGUI_CreateText("sensors_menu_water_level", (point){0, 0}, true, "water_level_page", "Water level");
	mGUI_AddElementToPage("sensors_menu_water_level", "sensors_menu_page");

	mGUI_CreatePage("water_level_page");

	mGUI_CreateText("water_level_text", (point){0, 0}, true, "", "N/A");
	mGUI_AddElementToPage("water_level_text", "water_level_page");


	mGUI_SetCurrentPage("main_menu_page");

	}

void gGUI_Execute()
	{
	if(gInput.buttonJustPressedTab[0])
		{
		mGUI_SetCurrentPage("main_menu_page");
		}
	else if(gInput.buttonJustPressedTab[1]) // Move up
		{
		mGUI_NavigateInteractive(false);
		}
	else if(gInput.buttonJustPressedTab[2]) // Move down
		{
		mGUI_NavigateInteractive(true);
		}
	else if(gInput.buttonJustPressedTab[3])
		{
		mGUI_GoToLinkedPage();
		}

	mGUI_PrintCurrentPage();

	gGUI.currentPageName = mGUI_GetCurrentPageName();
	gGUI.currentElementName = mGUI_GetCurrentElementName();

	}
