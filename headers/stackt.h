//==============================================//
//								       			//
//					Stack             			//
//                                     			//
//----------------------------------------------//
// File : stackt.h */              				//
//----------------------------------------------//
// Definisi ADT stack yang diimplementasi		//
// dengan tabel kontigu dan ukuran sama 		//
// Implementasi dengan alokasi statik			//
//==============================================//

#ifndef _STACKT_H
#define _STACKT_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
const int StackNil = 0;
/* Nil adalah stack dengan elemen kosong . */

const int StackMaximumElement = 10;
/* Karena indeks dalam bhs C dimulai 0 maka tabel dg indeks 0 tidak dipakai */

typedef int StackInfotype;	/* Tipe Elemen tabel */
typedef int StackAddress;   /* TIpe Indeks tabel */


///////////////////////////
// 	Definisi Stack  	 //
///////////////////////////
/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct {
  StackInfotype T[MaxEl+1]; /* tabel penyimpan elemen */
  StackAddress TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[1]..T[MaxEl] */


///////////////////////////
// 		 SELECTOR		 //
///////////////////////////
StackAddress StackTop(Stack S);
/* Mengembalikan address Top dari stack */

StackInfotype StackInfoTop(Stack S);
/* Mengembalikan nilai Top dari stack */


///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void StackCreateEmpty(Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsStackEmpty(Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean IsStackFull(Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

///////////////////////////
// 	     PRIMITIVES 	 //
///////////////////////////
void StackPush(Stack *S, StackInfotype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

void StackPop(Stack *S, StackInfotype *X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

#endif