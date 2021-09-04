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

#define GUI_WATER_LEVEL_TEXT "Water lvl. : "
#define GUI_SOIL_HUM_TEXT 	 "Soil hum.  : "
#define GUI_LIGHT_TEXT		 "Vis. light : "
#define GUI_UV_TEXT			 "UV         : "
#define GUI_IR_TEXT			 "IR         : "
#define GUI_TEMP_TEXT		 "Temp.      : "
#define GUI_PRESS_TEXT		 "Pressure   : "
#define GUI_HUM_TEXT		 "Humidity   : "

static UIText* pUIWaterLevelLabel;
static UIText* pUISoilHumLabel;
static UIText* pUILightLabel;
static UIText* pUIUVLabel;
static UIText* pUIIRLabel;
static UIText* pUITempLabel;
static UIText* pUIPressLabel;
static UIText* pUIHumLabel;


void gGUI_Setup()
	{
	mGUI_Setup();


	///////////////////////////////////////////////////////////
	// MAIN MENU //////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("main_menu_page");

	mGUI_CreateText("main_menu_sensors", (point){0, 0}, true, "sensors_page",  "Sensors");
	mGUI_CreateText("main_menu_com", (point){0, 8}, true, "com_menu_page", "Communication");
	mGUI_CreateText("main_menu_settings", (point){0, 16}, true, "settings_menu_page", "Settings");
	mGUI_CreateText("main_menu_about", (point){0, 24}, true, "about_page", "About");

	mGUI_AddElementToPage("main_menu_page", "main_menu_sensors");
	mGUI_AddElementToPage("main_menu_page", "main_menu_com");
	mGUI_AddElementToPage("main_menu_page", "main_menu_settings");
	mGUI_AddElementToPage("main_menu_page", "main_menu_about");

	///////////////////////////////////////////////////////////
	// SENSORS PAGE ///////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("sensors_page");

	pUIWaterLevelLabel 	= mGUI_CreateText("water_level_label", 	(point){0, 0}, 	false, "", GUI_WATER_LEVEL_TEXT);
	pUISoilHumLabel 	= mGUI_CreateText("soil_hum_label", 	(point){0, 8}, 	false, "", GUI_SOIL_HUM_TEXT);
	pUILightLabel		= mGUI_CreateText("light_label", 		(point){0, 16}, false, "", GUI_LIGHT_TEXT);
	pUIUVLabel			= mGUI_CreateText("uv_label", 			(point){0, 24}, false, "", GUI_UV_TEXT);
	pUIIRLabel			= mGUI_CreateText("ir_label", 			(point){0, 32}, false, "", GUI_IR_TEXT);
	pUITempLabel		= mGUI_CreateText("temp_label", 		(point){0, 40}, false, "", GUI_TEMP_TEXT);
	pUIPressLabel		= mGUI_CreateText("press_label", 		(point){0, 48}, false, "", GUI_PRESS_TEXT);
	pUIHumLabel			= mGUI_CreateText("hum_label", 			(point){0, 56}, false, "", GUI_HUM_TEXT);

	mGUI_AddElementToPage("sensors_page", "water_level_label");
	mGUI_AddElementToPage("sensors_page", "soil_hum_label");
	mGUI_AddElementToPage("sensors_page", "light_label");
	mGUI_AddElementToPage("sensors_page", "uv_label");
	mGUI_AddElementToPage("sensors_page", "ir_label");
	mGUI_AddElementToPage("sensors_page", "temp_label");
	mGUI_AddElementToPage("sensors_page", "press_label");
	mGUI_AddElementToPage("sensors_page", "hum_label");



	mGUI_SetInitContext("main_menu_page");
	}

void gGUI_Execute()
	{
	if(gInput.buttonJustPressedTab[0])
		{
		mGUI_PreviousContext();
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

	gGUI_RenderValues();

	mGUI_PrintCurrentPage();

	gGUI.currentPageName = mGUI_GetCurrentPageName();
	gGUI.currentElementName = mGUI_GetCurrentElementName();

	}


void gGUI_RenderValues()
	{
//	char value[10];
//	itoa(gSensors.waterLevel, value, 10);
//	pUIWaterLevelLabel = value;
	}
