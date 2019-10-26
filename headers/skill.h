//==============================================//
//								       			//
//					 Skill                		//
//                                     			//
//----------------------------------------------//
// File : skill.h */                 			//
//----------------------------------------------//
// Definisi ADT Skill                          	//
// Skill memiliki jenis dan efek yang beragam	//
// pada keberjalanan game                       //
//==============================================//

#ifndef _skill_H
#define _skill_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

///////////////////////////
// Definisi elemen Skill //
///////////////////////////
typedef struct {
    int kind;  /* [1..4] Menandakan jenis skill */
    		   /* 1 = Instant Upgrade (IU)
    		      2 = Extra Turn (ET)
    		      3 = Instant Reinforcement (IR)
    		      4 = Barrage (BR) */
} Skill;


///////////////////////////
// 		 SELEKTOR		 //
///////////////////////////
int SkillKind(Skill S);
/* Mengembalikan kind dari Skill */

///////////////////////////
// 		 PROTOTYPE		 //
///////////////////////////
char* SkillGetName(int kind);
/* Mengembalikan string nama skill dengan kind tertentu */

char* SkillGetEffect(int kind);
/* Mengembalikan string efek skill dengan kind tertentu */

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
Skill SkillCreate(int kind);
/* Mengembalikan skill yang kindnya telah diset */

//////////////////////////////////
// 		 SKILL OPERATIONS		//
//////////////////////////////////
// Gonna still be added

#endif