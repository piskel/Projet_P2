/*
 * gGUI.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#include "gGUI.h"
#include "gMBox.h"

#include "mGUI.h"

#include "mPump.h"

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

	mGUI_CreateText("sensors_menu_soil_humidity", (point){0, 8}, true, "soil_humidity_page", "Soil humidity");
	mGUI_AddElementToPage("sensors_menu_soil_humidity", "sensors_menu_page");


	mGUI_CreatePage("water_level_page");
	mGUI_CreateText("water_level_text", (point){0, 0}, false, "", "N/A");
	mGUI_AddElementToPage("water_level_text", "water_level_page");


	mGUI_CreatePage("soil_humidity_page");
	mGUI_CreateText("soil_humidity_text", (point){0, 0}, false, "", "N/A");
	mGUI_AddElementToPage("soil_humidity_text", "soil_humidity_page");


	mGUI_SetCurrentPage("main_menu_page");


	mPump_Setup();

	}

void gGUI_Execute()
	{
	if(gInput.buttonJustPressedTab[0])
		{
		mGUI_SetCurrentPage("main_menu_page");
		}
	else if(gInput.buttonJustPressedTab[1]) // Move up
		{
		mPump_Enable();
		mGUI_NavigateInteractive(false);
		}
	else if(gInput.buttonJustPressedTab[2]) // Move down
		{

		mPump_Disable();
		mGUI_NavigateInteractive(true);
		}
	else if(gInput.buttonJustPressedTab[3])
		{
		mGUI_GoToLinkedPage();
		}

	UIText* pUIWaterLevelText = (UIText*)mGUI_GetElementFromName("water_level_text");
	UIText* pUISoilHumidityText = (UIText*)mGUI_GetElementFromName("soil_humidity_text");



	char waterLeveText[3];
	itoa((int)(gSensors.waterLevel*100), waterLeveText, 10);
	pUIWaterLevelText->text = waterLeveText;

	char soilHumidity[3];
	itoa((int)(gSensors.soilHumidity*100), soilHumidity, 10);
	pUISoilHumidityText->text = soilHumidity;

	mGUI_PrintCurrentPage();

	gGUI.currentPageName = mGUI_GetCurrentPageName();
	gGUI.currentElementName = mGUI_GetCurrentElementName();

	}
