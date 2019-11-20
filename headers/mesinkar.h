//==============================================//
//                                              //
//                 MesinKarakter                //
//                                              //
//----------------------------------------------//
// File : mesinkar.h */                      	//
//----------------------------------------------//
// Definisi Mesin Karakter 		        		//
// Digunakan untuk membaca file	luar dan input	//
//==============================================//

#ifndef _MESIN_KAR_H_
#define _MESIN_KAR_H_

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
extern char CC;
extern int X;
extern boolean EOP;
extern int StringIndex;
extern char* StringInput;

///////////////////////////////////
// 	     MESINKAR OPERATIONS 	 //
///////////////////////////////////
void OpenFile(char* filename);
/* Menyiapkan file untuk dibaca */
/* I.S : pita masih kosong */
/* F.S : pita sudah berisi file yang siap dibaca */

void CloseFile();
/* Menutup file agar tidak bisa dibaca lagi */
/* I.S : pita siap dibaca */
/* F.S : pita menjadi kosong lagi */

void AdvFileChar();
/* File dimajukan satu karakter */
/* I.S : CC adalah karakter sembarang */
/* F.S : CC adalah karakter berikutnya */

void AdvFileInt();
/* File dimajukan satu integer */
/* I.S : X adalah integer sembarang */
/* F.S : X adalah integer berikutnya */

void AdvFileLine();
/* File dimajukan satu baris */
/* I.S : CC adalah karakter sembarang */
/* F.S : CC adalah karakter newline ('\n')*/

void AdvStringChar();
/* String dimajukan satu karakter */
/* I.S : CC adalah karakter sembarang */
/* F.S : CC adalah karakter berikutnya */

#endif