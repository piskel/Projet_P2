/*
------------------------------------------------------------
Copyright 2003-20xx Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier :	mCpu.c
Auteur et Date :	Monnerat Serge 8.5.20xx

Description dans le fichier mCpu.h
------------------------------------------------------------
*/


#include <iCpu.h>
#include "mCpu.h"

//-----------------------------------------------------------------------
// Congiguration g�n�rale de la CPU
//-----------------------------------------------------------------------
void mCpu_Setup(void)
{
	// Configuration du clock de la CPU et du bus
	iCpu_CLKInit();
}

