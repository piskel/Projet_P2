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
typedef int bool;
#define TRUE 1
#define true 1
#define FALSE 0
#define false 0

//-----------------------------------------------------------------------------
// D�claration des macros permettant l'enable/disable des interruptions
//-----------------------------------------------------------------------------
// Enable maskable interrupts
#define EnableInterrupts __asm(" CPSIE i");

// Disable maskable interrupts
#define DisableInterrupts __asm(" CPSID i");


#endif
