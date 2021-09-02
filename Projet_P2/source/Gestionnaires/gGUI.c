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



void gGUI_Setup()
	{
	mGUI_Setup();


	///////////////////////////////////////////////////////////
	// MAIN MENU //////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("main_menu_page");

	mGUI_CreateText("main_menu_sensors", (point){0, 0}, true, "sensors_menu_page",  "Sensors");
	mGUI_AddElementToPage("main_menu_sensors", "main_menu_page");

	mGUI_CreateText("main_menu_settings", (point){0, 8}, true, "settings_menu_page", "Settings");
	mGUI_AddElementToPage("main_menu_settings", "main_menu_page");

	mGUI_CreateText("main_menu_about", (point){0, 16}, true, "about_page", "About");
	mGUI_AddElementToPage("main_menu_about", "main_menu_page");

	///////////////////////////////////////////////////////////
	// SENSORS MENU ///////////////////////////////////////////
	///////////////////////////////////////////////////////////


	mGUI_CreatePage("sensors_menu_page");

	mGUI_CreateText("sensors_menu_water_level", (point){0, 0}, true, "water_level_page", "Water level");
	mGUI_AddElementToPage("sensors_menu_water_level", "sensors_menu_page");

	mGUI_CreateText("sensors_menu_soil_humidity", (point){0, 8}, true, "soil_humidity_page", "Soil humidity");
	mGUI_AddElementToPage("sensors_menu_soil_humidity", "sensors_menu_page");


	mGUI_CreateText("sensors_menu_light_uv_ir", (point){0, 16}, true, "light_uv_ir_page", "Light/UV/IR");
	mGUI_AddElementToPage("sensors_menu_light_uv_ir", "sensors_menu_page");

	mGUI_CreateText("sensors_menu_temp_press_hum", (point){0, 24}, true, "temp_press_hum_page", "Temp/Press/Hum");
	mGUI_AddElementToPage("sensors_menu_temp_press_hum", "sensors_menu_page");

	///////////////////////////////////////////////////////////
	// WATER LEVEL ////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("water_level_page");
	mGUI_CreateText("water_level_text", (point){0, 0}, false, "", "N/A");
	mGUI_AddElementToPage("water_level_text", "water_level_page");


	///////////////////////////////////////////////////////////
	// SOIL HUMIDITY //////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("soil_humidity_page");
	mGUI_CreateText("soil_humidity_text", (point){0, 0}, false, "", "N/A");
	mGUI_AddElementToPage("soil_humidity_text", "soil_humidity_page");

	///////////////////////////////////////////////////////////
	// UV/LIGHT/IR ////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("light_uv_ir_page");
	mGUI_CreateText("light_text", (point){0, 0}, false, "", "N/A");
	mGUI_CreateText("ir_text", (point){0, 8}, false, "", "N/A");
	mGUI_CreateText("uv_text", (point){0, 16}, false, "", "N/A");
	mGUI_AddElementToPage("light_text", "light_uv_ir_page");
	mGUI_AddElementToPage("ir_text", "light_uv_ir_page");
	mGUI_AddElementToPage("uv_text", "light_uv_ir_page");

	///////////////////////////////////////////////////////////
	// TMP/PRESS/HUM //////////////////////////////////////////
	///////////////////////////////////////////////////////////

	mGUI_CreatePage("temp_press_hum_page");
	mGUI_CreateText("temp_text", (point){0, 0}, false, "", "N/A");
	mGUI_CreateText("press_text", (point){0, 8}, false, "", "N/A");
	mGUI_CreateText("hum_text", (point){0, 16}, false, "", "N/A");
	mGUI_AddElementToPage("temp_text", "temp_press_hum_page");
	mGUI_AddElementToPage("press_text", "temp_press_hum_page");
	mGUI_AddElementToPage("hum_text", "temp_press_hum_page");

//	mGUI_SetCurrentPage("main_menu_page");
	mGUI_SetInitContext("main_menu_page");

	}

void gGUI_Execute()
	{
	if(gInput.buttonJustPressedTab[0])
		{
//		mGUI_SetCurrentPage("main_menu_page");
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

	UIText* pUIWaterLevelText = (UIText*)mGUI_GetElementFromName("water_level_text");
	UIText* pUISoilHumidityText = (UIText*)mGUI_GetElementFromName("soil_humidity_text");
	UIText* pUILightText = (UIText*)mGUI_GetElementFromName("light_text");
	UIText* pUIIRText = (UIText*)mGUI_GetElementFromName("ir_text");
	UIText* pUIUVText = (UIText*)mGUI_GetElementFromName("uv_text");

	UIText* pUITempText = (UIText*)mGUI_GetElementFromName("temp_text");
	UIText* pUIPressText = (UIText*)mGUI_GetElementFromName("press_text");
	UIText* pUIHumText = (UIText*)mGUI_GetElementFromName("hum_text");



	char waterLeveText[10];
	itoa((int)(gSensors.waterLevel), waterLeveText, 10);
	pUIWaterLevelText->text = waterLeveText;

	char soilHumidity[10];
	itoa((int)(gSensors.soilHumidity), soilHumidity, 10);
	pUISoilHumidityText->text = soilHumidity;

	char visibleLight[10];
	itoa((int)(gSensors.visibleLight), visibleLight, 10);
	pUILightText->text = visibleLight;

	char ir[10];
	itoa((int)(gSensors.ir), ir, 10);
	pUIIRText->text = ir;

	char uv[10];
	itoa((int)(gSensors.uv), uv, 10);
	pUIUVText->text = uv;


	char temp[10];
	itoa((int)(gSensors.temperature), temp, 10);
	pUITempText->text = temp;


	char press[10];
	itoa((int)(gSensors.pressure), press, 10);
	pUIPressText->text = press;


	char hum[10];
	itoa((int)(gSensors.humidity), hum, 10);
	pUIHumText->text = hum;

	mGUI_PrintCurrentPage();

	gGUI.currentPageName = mGUI_GetCurrentPageName();
	gGUI.currentElementName = mGUI_GetCurrentElementName();

	}
