//==============================================//
//                                              //
//            	  BuildingList                  //
//                                              //
//----------------------------------------------//
// File : BuildingList.h */                     //
//----------------------------------------------//
// Definisi ADT BuildingList  					//
// BuildingList digunakan untuk menyimpan       //
// Index bangunan yang mengacu ke BuildingArray	//
//==============================================//

#ifndef _BUILDINGLIST_H
#define _BUILDINGLIST_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include "boolean.h"
#include "buildingarray.h"

///////////////////////////////////
//        CONST & TYPEDEF        //
///////////////////////////////////
#define BuildingListNil NULL

typedef int BuildingListInfotype;
typedef struct TListElement *BuildingListAddress;

//////////////////////////////////////
//  Definisi List dan ElementList  	//
//////////////////////////////////////
typedef struct TBuildingListElement
{
    BuildingListInfotype info;
    BuildingListAddress next;
} BuildingListElement;

typedef struct
{
    BuildingListAddress First;
} BuildingList;
/* List kosong : BuildingListFirstAddress(L) = Nil */
/* Setiap elemen dengan address P dapat diacu BuildingListElementInfo(P),Building ListElementNext(P) */
/* Elemen terakhir list : jika addressnya Last, maka BuildingListElementNext(Last)=Nil */


//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika L adalah BuildingList dan P adalah BuildingListAddress, maka akses elemen : */
#define BuildingListElementInfo(P) 		(P)->info
#define BuildingListElementNext(P) 		(P)->next
#define BuildingListFirstAddress(L) 	((L).First)

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void BuildingListCreateEmpty(BuildingList *L);
/* I.S. sembarang             */
/* F.S. Terbentuk BuildingList kosong */

BuildingListAddress BuildingListElementAlokasi(BuildingListInfotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka BuildingListElementInfo(P)=X, BuildingListElementNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void BuildingListElementDealokasi(BuildingListAddress *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsBuildingListEmpty(BuildingList L);
/* Mengirim true jika list kosong */

/////////////////////////
//    LIST OPERATIONS  //
/////////////////////////
BuildingListAddress BuildingListAddressSearch(BuildingList L, BuildingListInfotype X);
/* Mencari apakah ada elemen list dengan BuildingListElementInfo(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

void BuildingListInsertValueFirst(BuildingList *L, BuildingListInfotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void BuildingListInsertValueLast(BuildingList *L, BuildingListInfotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void BuildingListDeleteValueFirst(BuildingList *L, BuildingListInfotype *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void BuildingListDeleteValueLast(BuildingList *L, BuildingListInfotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

void ListDeleteValue(BuildingList *L, BuildingListInfotype X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan BuildingListElementInfo(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan BuildingListElementInfo(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

void BuildingListPrintInfo(BuildingList L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Dengan tambahan enter di akhir */

int BuildingListNbElmt(BuildingList L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

#endif