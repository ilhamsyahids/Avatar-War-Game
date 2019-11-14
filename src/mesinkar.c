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

static FILE *pita;
static int retval;

///////////////////////////////////
// 	     MESINKAR OPERATIONS 	 //
///////////////////////////////////
void OpenFile(char* filename){
    pita = fopen(filename, "r");
}

void CloseFile(){
    fclose(pita);
}

void AdvChar(){
    retval = fscanf(pita, "%c", &CC);
}

void AdvInt(){
    retval = fscanf(pita, "%d", &X);
}

void AdvLine(){
    retval = fscanf(pita, "\n", &CC);
}
