/*
------------------------------------------------------------
Copyright 2003-20xx Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier :	iCpu.c
Auteur et Date :	Monnerat Serge 8.5.20xx

Description dans le fichier iCpu.h
------------------------------------------------------------
*/

#include <Interfaces/iCpu.h>
#include <MKL46Z4.h>

//------------------------------------------------------------
// Core and peripheral clock init
// External clock = 8MHz
// Core clock = 48MHz
// Peripheral bus = 24MHz
// Flexbus = 24MHz
// Flash = 24MHz
//------------------------------------------------------------
void iCpu_CLKInit(void)
{;
	
	// 1.	Configuration du type de quartz utilis�, 
	// de l'échelle de sa fr�quence et du type de connexion du quartz externe de 8 MHz dans le registre MCG Control Register 2
	MCG->C2 &= 0xC3;		// Reset des champs
	MCG->C2 |= 0x1C;		// Range0=01, HGO0=1 et EREFS0=1

	
	// S�lection de la source du clock, division de la fr�quence de la source du clock, 
	// attention pour le passage en mode FBE (FLL Bypass External Clock)
	MCG->C1 &= 0x03;		// Reset des champs
	MCG->C1 |= 0x98;		// CLKS=10, FRDIV=011 et IREFS=0
	
	// 3.	Attendre de l�oscillateur externe soit initialiser, que le clock source de la FLL soit le clock externe et 
	// que c�est bien l�horloge externe comme source du clock MCGOUTCLK (le clock source CPU et BUS), 
	// c�est-�-dire que l�on est pass� en mode FBE
	while((MCG->S & 0x02)==0); 		// Wait OSCINIT0 = 1
	while((MCG->S & 0x10)==0x10); 	// Wait IREFST = 0
	while((MCG->S & 0x08)!=0x08); 	// Wait CLKST = 01
	
	// 4.	Configuration d�une fr�quence de r�f�rence correcte pour la PLL (entre 2 et 4MHz)
	MCG->C5 &= 0xE0;		// Reset des champs
	MCG->C5 |= 0x03;		// PRDIV0=00011
	
	// 5.	Passage en mode PBE (PLL Bypass External Clock)
	MCG->C6 &= 0xA0;		// Reset des champs
	MCG->C6|= 0x40;		// PLLS=1 et VDIV0=0
	
	// 6.	Attendre que la source du clock CPU soit la PLL et attendre que le clock PLL soit stable.
	while((MCG->S & 0x20)==0); 		// Wait PLLST = 1
	while((MCG->S & 0x40)==0x0); 	// Wait LOCK0 = 1
	
	// 7.	Transition en mode PEE
	MCG->C1 &= 0x3F;		// CLKS=0

	// 8.	Attendre que la PLL soit la source du clock CPU
	while((MCG->S & 0x0C)!=0x0C); 		// Wait CLKST = 11
}




