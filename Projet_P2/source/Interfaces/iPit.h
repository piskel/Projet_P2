/*
------------------------------------------------------------
Copyright 2003-200x Haute Ecole ARC Ing�nierie,
All rights reserved
------------------------------------------------------------
Nom du fichier : iPit.h
Auteur et Date : Monnerat Serge, 12 mars 20xx

But : interface du p�riph�rique PIT

Modifications
Date		Faite		Ctrl		Description

----------------------------------------------------------
*/

#ifndef __iPit__
#define __iPit__

#include <def.h>

// Enum�ration des PIT
typedef enum
{
	kPit0,
	kPit1
}PitEnum;

//------------------------------------------------------------
// Configuration du PIT
// aPIT0PeriodeMs  	: p�riode en ms du PIT0
// aPIT1PeriodeMs  	: p�riode en ms du PIT1
//------------------------------------------------------------
void iPit_Config(unsigned int aPIT0PeriodeMs,unsigned int aPIT1PeriodeMs);

//------------------------------------------------------------
// Start Pit
// aPit		: which PIT
//------------------------------------------------------------
void iPit_StartPit(PitEnum aPit);

//------------------------------------------------------------
// Lecture du flag indiquant que 500ms sont �chus
// Retour  : �tat du flag
//------------------------------------------------------------
bool iPit_GetFlag(void);

//------------------------------------------------------------
// Reset du flag indiquant que 500ms sont �chus
// Retour  : �tat du flag
//------------------------------------------------------------
void iPit_ResetFlag(void);

//------------------------------------------------------------
// Init de la structure des delays
//------------------------------------------------------------
void iPit_InitDelay(void);

//------------------------------------------------------------
// Prise d'un delays
// aDelay: l'attente � effectuer (multiple de la p�riode PIT)
// Retour: le num�ro du delay attribu� ou -1 si plus de delay dispo
//------------------------------------------------------------
int iPit_GetDelay(unsigned int aDelay);

//------------------------------------------------------------
// Contr�le si le d�lais est �chu
// aDelayNb	: le num�ro du compteur de temps
// Retour		: l'�tat du flag
//------------------------------------------------------------
bool iPit_IsDelayDone(unsigned int aDelayNb);

//------------------------------------------------------------
// Lib�re un compteur de temps
// aDelayNb	: le num�ro du compteur de temps
//------------------------------------------------------------
void iPit_DelayRelease(unsigned int aDelayNb);

#endif
