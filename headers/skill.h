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

#ifndef _SKILL_H
#define _SKILL_H

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

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika S adalah Array, maka akses elemen : */
#define SkillKind(S)	(S).kind

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
Skill SkillCreate(int kind);
/* Mengembalikan skill yang kindnya telah diset */

//////////////////////////////////
// 		 SKILL OPERATIONS		//
//////////////////////////////////
char* SkillGetName(int kind);
/* Mengembalikan string nama skill dengan kind tertentu */

char* SkillGetAcronym(int kind);
/* Mengembalikan akronim nama skill dengan kind tertentu */

char* SkillGetEffect(int kind);
/* Mengembalikan string efek skill dengan kind tertentu */

// Gonna still be added


#endif
