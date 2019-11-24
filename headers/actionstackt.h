//==============================================//
//								       			//
//				  Action Stack             		//
//                                     			//
//----------------------------------------------//
// File : actionstackt.h */              		//
//----------------------------------------------//
// Definisi ADT Action Stack					//
// Action Stack digunakan untuk menyimpan 		//
// History Action yang dilakukan player di turn	//
// Stack akan dikosongkan tiap end_turn dan     //
// pengaktifan skill							//
// Action Stack dibuat dengan alokasi DINAMIS	//
//==============================================//

#ifndef _ACTIONSTACKT_H
#define _ACTIONSTACKT_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"
#include "player.h"
#include "gamemap.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
#define ActionStackNil 0;
/* Nil adalah action stack dengan elemen kosong . */

typedef GameMap ActionStackInfotype; /* Tipe Elemen tabel */
typedef int ActionStackAddress;		 /* TIpe Indeks tabel */

///////////////////////////
// 	Definisi Stack  	 //
///////////////////////////
/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct
{
	ActionStackInfotype *T; /* tabel penyimpan elemen */
	ActionStackAddress TOP; /* alamat TOP: elemen puncak */
	int MaxElement;			/* Jumlah elemen maksimum stack */
} ActionStack;
/* Definisi stack S kosong : S.TOP = ActionStackNil */
/* Elemen yang dipakai menyimpan nilai Stack T[1]..T[MaxElement] */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika S adalah Stack, maka akses elemen : */
#define ActionStackTop(S) (S).TOP
#define ActionStackInfoTop(S) (S).T[(S).TOP]

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void ActionStackCreateEmpty(ActionStack *S, int maxElement);
/* I.S. sembarang; */
/* F.S. Mengalokasikan sebuah actopn stack S yang kosong berkapasitas maxElement */
/* jadi indeksnya antara 1.. maxElement+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai StackNil */

void ActionStackRealokasi(ActionStack *S);
/* I.S. S Penuh; */
/* F.S. Merealokasikan sebuah action stack S yang sebelumnya berkapasitas maxElement menjadi maxElement + 1*/

///////////////////////////
// 		 DESTRUCTOR 	 //
///////////////////////////
void ActionStackDealokasi(ActionStack *S);
/* I.S. S terdefinisi; */
/* F.S. T(S) dikembalikan ke system, MaxElement(S)=0; TOP(S)=StackNil */

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsActionStackEmpty(ActionStack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean IsActionStackFull(ActionStack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

///////////////////////////////////////
// 	     ACTION STACK OPERATIONS 	 //
///////////////////////////////////////
void ActionStackPush(ActionStack *S, ActionStackInfotype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong dan mungkin penuh*/
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 dan ketika S sebelumnya penuh maka akan dilakukan realloc*/

void ActionStackPop(ActionStack *S, ActionStackInfotype *X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void ActionStackEmpty(ActionStack *S);
/* Mengosongkan Action Stack */
/* I.S. S terdefinisi dan mungkin kosong */
/* F.S. S menjadi kosong dengan MaxElement tidak berubah */

#endif