//==============================================//
//								       			//
//					Stack             			//
//                                     			//
//----------------------------------------------//
// File : stackt.h */              				//
//----------------------------------------------//
// Definisi ADT stack yang diimplementasi		//
// dengan tabel kontigu dan ukuran sama 		//
// Implementasi dengan alokasi DINAMIS			//
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
#define StackNil 0;
/* Nil adalah stack dengan elemen kosong . */

typedef int StackInfotype;	/* Tipe Elemen tabel */
typedef int StackAddress;   /* TIpe Indeks tabel */


///////////////////////////
// 	Definisi Stack  	 //
///////////////////////////
/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct {
  	StackInfotype *T; 	/* tabel penyimpan elemen */
  	StackAddress TOP;  	/* alamat TOP: elemen puncak */
	int MaxElement; 	/* Jumlah elemen maksimum stack */
} Stack;
/* Definisi stack S kosong : S.TOP = StackNil */
/* Elemen yang dipakai menyimpan nilai Stack T[1]..T[MaxElement] */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika S adalah Stack, maka akses elemen : */
#define StackTop(S) 		(S).TOP
#define StackInfoTop(S) 	(S).T[(S).TOP]

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void StackCreateEmpty(Stack *S, int maxElement);
/* I.S. sembarang; */
/* F.S. Mengalokasikan sebuah stack S yang kosong berkapasitas maxElement */
/* jadi indeksnya antara 1.. maxElement+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai StackNil */

///////////////////////////
// 		 DESTRUCTOR 	 //
///////////////////////////
void StackDealokasi(Stack *S);
/* I.S. S terdefinisi; */
/* F.S. T(S) dikembalikan ke system, MaxElement(S)=0; TOP(S)=StackNil */

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsStackEmpty(Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean IsStackFull(Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

///////////////////////////////
// 	     STACK OPERATIONS 	 //
///////////////////////////////
void StackPush(Stack *S, StackInfotype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

void StackPop(Stack *S, StackInfotype *X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void StackGrowTab(Stack *T, int num);
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */


#endif