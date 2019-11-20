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

#ifndef _MESIN_KATA_H_
#define _MESIN_KATA_H_

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"
#include "mesinkar.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
#define KataMaxLength 50
#define KataMark '\0'

///////////////////////////
// 		Definisi Kata  	 //
///////////////////////////
typedef struct
{
    char KataArray[KataMaxLength + 1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} Kata;

///////////////////////////////////
//		  Extern Variables	 	 //
///////////////////////////////////
extern Kata CKata;
extern boolean EOK;

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika K adalah Kata, maka akses elemen : */
#define KataArray(K)			(K).KataArray
#define KataArrayKarakter(K, i)	(K).KataArray[(i)]
#define KataLength(K)			(K).Length

///////////////////////////////////
// 	     MESINKATA OPERATIONS 	 //
///////////////////////////////////
void StartReadingKata(char* Input);
/* Memulai pembacaan kata dari input */
/* I.S. CKata Sembarang */
/* F.S. CKata berisi karakter pertama input */

void AdvReadingKata();
/* Melanjutkan pembacaan kata dari input */
/* I.S. CKata Sembarang */
/* F.S. Elemen terakhir CKata adalah karakter selanjutnya dari input */

boolean IsKataSame(char* CMP, int CMPLength);
/* Mengirimkan apakah kata CMP sama dengan CKata */

#endif