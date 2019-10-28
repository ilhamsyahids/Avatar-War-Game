//==============================================//
//                                              //
//                    List                     	//
//                                              //
//----------------------------------------------//
// File : list.h */                            	//
//----------------------------------------------//
// Definisi ADT List berkait 					//
// List memiliki representasi fisik pointer     //
// Representasi address dengan pointer          //
//==============================================//

#ifndef _LIST_H
#define _LIST_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include "boolean.h"

///////////////////////////////////
//        CONST & TYPEDEF        //
///////////////////////////////////
#define ListNil NULL

typedef int ListInfotype;
typedef struct TListElement *ListAddress;

//////////////////////////////////////
//  Definisi List dan ElementList  	//
//////////////////////////////////////
typedef struct TListElement
{
    ListInfotype info;
    ListAddress next;
} ListElement;

typedef struct
{
    ListAddress First;
} List;
/* List kosong : ListFirstAddress(L) = Nil */
/* Setiap elemen dengan address P dapat diacu ListElementInfo(P), ListElementNext(P) */
/* Elemen terakhir list : jika addressnya Last, maka ListElementNext(Last)=Nil */


//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika L adalah List dan P adalah ListAddress, maka akses elemen : */
#define ListElementInfo(P) 		(P)->info
#define ListElementNext(P) 		(P)->next
#define ListFirstAddress(L) 	((L).First)

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void ListCreateEmpty(List *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

ListAddress ListElementAlokasi(ListInfotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka ListElementInfo(P)=X, ListElementNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void ListElementDealokasi(ListAddress *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsListEmpty(List L);
/* Mengirim true jika list kosong */

/////////////////////////
//    LIST OPERATIONS  //
/////////////////////////
ListAddress ListAddressSearch(List L, ListInfotype X);
/* Mencari apakah ada elemen list dengan ListElementInfo(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

void ListInsertValueFirst(List *L, ListInfotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void ListInsertValueLast(List *L, ListInfotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void ListDeleteValueFirst(List *L, ListInfotype *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void ListDeleteValueLast(List *L, ListInfotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

void ListDeleteValue(List *L, ListInfotype X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan ListElementInfo(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan ListElementInfo(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

void ListPrintInfo(List L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Dengan tambahan enter di akhir */

int ListNbElmt(List L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

#endif