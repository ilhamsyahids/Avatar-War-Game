//==============================================//
//                                              //
//                 MesinKarakter                //
//                                              //
//----------------------------------------------//
// File : mesinkar.h */                      	//
//----------------------------------------------//
// Definisi Mesin Karakter 		        		//
// Digunakan untuk membaca file	luar			//
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "mesinkar.h"
#include <stdio.h>

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
char CC;
int X;
boolean EOP;
int StringIndex;
char *StringInput;

///////////////////////////////////
//		  Static Variables	 	 //
///////////////////////////////////
static FILE *pita;
static int retval;

///////////////////////////////////
// 	     MESINKAR OPERATIONS 	 //
///////////////////////////////////
void OpenFile(char *filename)
{
    pita = fopen(filename, "r");
}

void CloseFile()
{
    fclose(pita);
}

void AdvFileChar()
{
    retval = fscanf(pita, "%c", &CC);
}

void AdvFileInt()
{
    retval = fscanf(pita, "%d", &X);
}

void AdvFileLine()
{
    retval = fscanf(pita, "\n", &CC);
}

void AdvStringChar()
/* String dimajukan satu karakter */
/* I.S : CC adalah karakter sembarang */
/* F.S : CC adalah karakter berikutnya */
{
    CC = StringInput[StringIndex];
    StringIndex = StringIndex + 1;
}
