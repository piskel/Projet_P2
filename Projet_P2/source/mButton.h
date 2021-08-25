/*
 * mButton.h
 *
 *  Created on: 23 août 2021
 *      Author: luc.froideva
 */

#ifndef MBUTTON_H_
#define MBUTTON_H_

typedef enum
{
	kMaskButton0=0,
	kMaskButton1=1,
	kMaskButton2=2,
	kMaskButton3=3,
} ButtonMaskEnum;


void mButton_Setup();

bool mButton_Read(ButtonMaskEnum aButton);

#endif /* MBUTTON_H_ */
