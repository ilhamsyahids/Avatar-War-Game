//==============================================//
//                                              //
//                   MesinKata                	//
//                                              //
//----------------------------------------------//
// File : mesinkata.h */                      	//
//----------------------------------------------//
// Definisi Mesin Kata 		        			//
// Digunakan untuk membaca file	luar dan input	//
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"
#include "mesinkata.h"
#include <stdio.h>

///////////////////////////////////
//		  Extern Variables	 	 //
///////////////////////////////////
Kata CKata;
boolean EOK;

///////////////////////////////////
// 	     MESINKATA OPERATIONS 	 //
///////////////////////////////////
void StartReadingKata(char* Input)
/* Memulai pembacaan kata dari input */
/* I.S. CKata Sembarang */
/* F.S. CKata berisi karakter pertama input */
{
	for(int i = 0; i < KataLength(CKata); i++){
		KataArrayKarakter(CKata, i) = '#';
	}
	StringInput = Input;
	StringIndex = 0;
	KataLength(CKata) = 0;
	AdvStringChar();		
	AdvReadingKata();
}

void AdvReadingKata()
/* Melanjutkan pembacaan kata dari input */
/* I.S. CKata Sembarang */
/* F.S. Elemen terakhir CKata adalah karakter selanjutnya dari input */
{
	while(CC != KataMark){
		KataArrayKarakter(CKata, StringIndex - 1) = CC;
		KataLength(CKata) += 1;
		AdvStringChar();
	}
}

boolean IsKataSame(char* CMP, int CMPLength)
/* Mengirimkan apakah kata CMP sama dengan CKata */
{
	int i;
	boolean same;

	i = 0;
	same = (CMPLength == KataLength(CKata));

	while((same) && (i < CMPLength)){
		same = (CMP[i] == KataArrayKarakter(CKata, i));
		i += 1;
	}

	return same;
}

