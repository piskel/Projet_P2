/*
 * mGpio.h
 *
 *  Created on: 23 août 2021
 *      Author: luc.froideva
 */

#ifndef MGPIO_H_
#define MGPIO_H_

typedef enum
{
	kMaskGpio0=0,
	kMaskGpio1=1,
	kMaskGpio2=2,
	kMaskGpio3=3,
	kMaskGpio4=4,
	kMaskGpio5=5,
	kMaskGpio6=6,
	kMaskGpio7=7,
} GpioMaskEnum;

void mGpio_Setup();

void mGpio_Enable(GpioMaskEnum aGpio);
void mGpio_Disable(GpioMaskEnum aGpio);


#endif /* MGPIO_H_ */
