/*
------------------------------------------------------------
Copyright 2003-200x Haute Ecole ARC Ing�nierie,
All rights reserved
------------------------------------------------------------
Nom du fichier : def.h
Auteur et Date : Monnerat Serge, 12 mars 20xx

But : Partage des constantes, types, etc. communs
			aux fichier du projet

Modifications
Date		Faite		Ctrl		Description

----------------------------------------------------------
*/

#ifndef __DEF__
#define __DEF__

//-----------------------------------------------------------------------------
// D�claration des constantes
//-----------------------------------------------------------------------------
#define kPITTime 1.0

//-----------------------------------------------------------------------------
// D�claration des types
//-----------------------------------------------------------------------------
typedef char bool;
#define TRUE 1
#define true 1
#define FALSE 0
#define false 0


#define DISPLAY_HEIGHT 64
#define DISPLAY_WIDTH 102
#define DISPLAY_PAGE_HEIGHT 8
#define DISPLAY_MEM_SIZE 816
#define DISPLAY_BUFFER_SIZE 6528

typedef struct Point
	{
		int x;
		int y;
	} point;


//-----------------------------------------------------------------------------
// D�claration des macros permettant l'enable/disable des interruptions
//-----------------------------------------------------------------------------
// Enable maskable interrupts
#define EnableInterrupts __asm(" CPSIE i");

// Disable maskable interrupts
#define DisableInterrupts __asm(" CPSID i");


#endif
