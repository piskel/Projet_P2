/*
 * gGUI.c
 *
 *  Created on: 30 août 2021
 *      Author: luc.froideva
 */

#include "gGUI.h"
#include "string.h"
#include "stdlib.h"

#include "gMBox.h"
#include "mGUI.h"

#include "mPump.h"

#define GUI_WATER_LEVEL_TEXT "Water lvl. : "
#define GUI_SOIL_HUM_TEXT 	 "Soil hum.  : "
#define GUI_LIGHT_TEXT		 "Vis. light : "
#define GUI_IR_TEXT			 "IR         : "
#define GUI_TEMP_TEXT		 "Temp.      : "
#define GUI_PRESS_TEXT		 "Pressure   : "
#define GUI_HUM_TEXT		 "Humidity   : "

#define GUI_MAX_TEXT_SIZE 24

static char txtWaterLevel[GUI_MAX_TEXT_SIZE] = "NaN";
static char txtSoilHum[GUI_MAX_TEXT_SIZE] = "NaN";
static char txtLight[GUI_MAX_TEXT_SIZE] = "NaN";
static char txtIR[GUI_MAX_TEXT_SIZE] = "NaN";
static char txtTemp[GUI_MAX_TEXT_SIZE] = "NaN";
static char txtPress[GUI_MAX_TEXT_SIZE] = "NaN";
static char txtHum[GUI_MAX_TEXT_SIZE] = "NaN";

static UIText* pUIWaterLevelLabel;
static UIText* pUISoilHumLabel;
static UIText* pUILightLabel;
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
	mGUI_CreateText("main_menu_com", (point){0, 8}, true, "com_menu_page", "Connectivity");
	mGUI_CreateText("main_menu_settings", (point){0, 8}, true, "settings_menu_page", "Settings");
	mGUI_CreateText("main_menu_about", (point){0, 16}, true, "about_page", "About");

	mGUI_AddElementToPage("main_menu_page", "main_menu_sensors");
//	mGUI_AddElementToPage("main_menu_page", "main_menu_com");
	mGUI_AddElementToPage("main_menu_page", "main_menu_settings");
	mGUI_AddElementToPage("main_menu_page", "main_menu_about");

	///////////////////////////////////////////////////////////
	// SENSORS PAGE ///////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("sensors_page");

	pUIWaterLevelLabel 	= mGUI_CreateText("water_level_label", 	(point){0, 0}, 	false, "", txtWaterLevel);
	pUISoilHumLabel 	= mGUI_CreateText("soil_hum_label", 	(point){0, 8}, 	false, "", txtSoilHum);
	pUILightLabel		= mGUI_CreateText("light_label", 		(point){0, 16}, false, "", txtLight);
	pUIIRLabel			= mGUI_CreateText("ir_label", 			(point){0, 24}, false, "", txtIR);
	pUITempLabel		= mGUI_CreateText("temp_label", 		(point){0, 32}, false, "", txtTemp);
	pUIPressLabel		= mGUI_CreateText("press_label", 		(point){0, 40}, false, "", txtPress);
	pUIHumLabel			= mGUI_CreateText("hum_label", 			(point){0, 48}, false, "", txtHum);

	mGUI_AddElementToPage("sensors_page", "water_level_label");
	mGUI_AddElementToPage("sensors_page", "soil_hum_label");
	mGUI_AddElementToPage("sensors_page", "light_label");
	mGUI_AddElementToPage("sensors_page", "ir_label");
	mGUI_AddElementToPage("sensors_page", "temp_label");
	mGUI_AddElementToPage("sensors_page", "press_label");
	mGUI_AddElementToPage("sensors_page", "hum_label");

	///////////////////////////////////////////////////////////
	// SETTINGS PAGE //////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("settings_menu_page");

	mGUI_CreateText("settings_toggle_pump", (point){0, 0}, true, "",  "Toggle pump");
//	mGUI_CreateText("settings_reset_i2c1", (point){0, 8}, true, "",  "Reset I2C 1");

	mGUI_AddElementToPage("settings_menu_page", "settings_toggle_pump");
//	mGUI_AddElementToPage("settings_menu_page", "settings_reset_i2c1");

	///////////////////////////////////////////////////////////
	// ABOUT PAGE /////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("about_page");

	mGUI_CreateText("label_about_1", (point){8,  0}, false, "", "Plant monitoring");
	mGUI_CreateText("label_about_2", (point){24, 24}, false, "", "HE-ARC 2021");
	mGUI_CreateText("label_about_3", (point){32, 48}, false, "", "Made by");
	mGUI_CreateText("label_about_4", (point){16, 56}, false, "", "Luc Froidevaux");

	mGUI_AddElementToPage("about_page", "label_about_1");
	mGUI_AddElementToPage("about_page", "label_about_2");
	mGUI_AddElementToPage("about_page", "label_about_3");
	mGUI_AddElementToPage("about_page", "label_about_4");



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
		gGUI_HandleActions();
		}

	gGUI_RenderValues();

	mGUI_PrintCurrentPage();

	gGUI.currentPageName = mGUI_GetCurrentPageName();
	gGUI.currentElementName = mGUI_GetCurrentElementName();

	}


void gGUI_RenderValues()
	{
	strcpy(txtWaterLevel, GUI_WATER_LEVEL_TEXT);
//	itoa(gSensors.waterLevel, &(txtWaterLevel[13]), 10);
	gGUI_FormatValue(gSensors.waterLevel, txtWaterLevel, 13, " %");

	strcpy(txtSoilHum, GUI_SOIL_HUM_TEXT);
	itoa((int)gSensors.soilHumidity, &(txtSoilHum[13]), 10);

	strcpy(txtLight, GUI_LIGHT_TEXT);
	gGUI_FormatValue(gSensors.visibleLight, txtLight, 13, "lx");
//	itoa(gSensors.visibleLight, &(txtLight[13]), 10);

	strcpy(txtIR, GUI_IR_TEXT);
	itoa(gSensors.ir, &(txtIR[13]), 10);

	strcpy(txtTemp, GUI_TEMP_TEXT);
	gGUI_FormatValue(gSensors.temperature, txtTemp, 13, "°C");

	strcpy(txtPress, GUI_PRESS_TEXT);
	gGUI_FormatValue(gSensors.pressure, txtPress, 13, "hPa");

	strcpy(txtHum, GUI_HUM_TEXT);
	gGUI_FormatValue(gSensors.humidity, txtHum, 13, " %");

	}


void gGUI_HandleActions()
	{
	if(strlen(mGUI_GetCurrentElement()->linkedPage) != 0)
		{
		mGUI_GoToLinkedPage();
		return;
		}
	else
		{
		if(mGUI_GetCurrentElement() == mGUI_GetElementFromName("settings_toggle_pump"))
			{
//			gOutput.enablePump = !gOutput.enablePump;
			gGUI.enablePump = !gGUI.enablePump;
			}
		}

	}


void gGUI_FormatValue(int value, char* string, int pos, const char* unit)
	{
	char testSize[GUI_MAX_TEXT_SIZE];
	itoa(value, testSize, 10);
	int valLen = strlen(testSize);

	if(valLen+pos+strlen(unit) >= GUI_MAX_TEXT_SIZE) return;

	itoa(value, &(string[pos]), 10);
	strcpy(&(string[pos+valLen]), unit);
	}
