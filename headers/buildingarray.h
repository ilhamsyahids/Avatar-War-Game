//==============================================//
//                                              //
//                BuildingArray                 //
//                                              //
//----------------------------------------------//
// File : buildingarray.h */                    //
//----------------------------------------------//
// Definisi ADT BuildingArray                   //
// Dengan representasi array implisit dan       //
// alokasi dinamik                              //
//==============================================//

#ifndef _BUILDINGARRAY_H
#define _BUILDINGARRAY_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "building.h"

///////////////////////////////////
//         CONST & TYPEDEF       //
///////////////////////////////////
const int BuildingArrayIdxMin = 1;
/* Indeks minimum array */

const int BuildingArrayIdxUndef = -999;
/* Indeks tak terdefinisi*/

const Building BuildingArrayValUndef = BuildingCreateDummy();
/* Elemen dummy array */

typedef int BuildingArrayIdxType;      /* type indeks */
typedef Building BuildingArrayElType;  /* type elemen tabel */


//////////////////////////////
//  Definisi BuildingArray  //
//////////////////////////////
typedef struct
{
    BuildingArrayElType *TI; /* memori tempat penyimpan elemen (container) */
    int MaxEl;  /* ukuran elemen */
} BuildingArray;
/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Definisi :
  Tabel kosong: NbElmt(T) = 0
  Definisi elemen pertama : T.TI[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=NbElmt(T) */


///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void BuildingArrayCreateEmpty(BuildingArray *T, int maxel);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */
/* Setiap elemen diisi dengan elemen dummy building (ValUndef) */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void BuildingArrayDealokasi(BuildingArray *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0 */

///////////////////////////
//        SELECTOR       //
///////////////////////////
BuildingArrayElType* BuildingArrayTab(BuildingArray T);
/* Mengirimkan T.TI */

BuildingArrayElType BuildingArrayTabElement(BuildingArray T, BuildingArrayIdxType i);
/* Mengirimkan (T).TI[(i)] */

int BuildingArrayMaxElement(BuildingArray T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */

BuildingArrayIdxType BuildingArrayGetFirstIdx(BuildingArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */

BuildingArrayIdxType BuildingArrayGetLastIdx(BuildingArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

int BuildingArrayNBElmt(BuildingArray T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsBuildingArrayIdxValid(BuildingArray T, BuildingArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/

boolean IsBuildingArrayIdxEff(BuildingArray T, BuildingArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

boolean IsBuildingArrayEmpty(BuildingArray T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean IsBuildingArrayFull(BuildingArray T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

boolean IsBuildingArrayEQ(BuildingArray T1, BuildingArray T2);
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */


///////////////////////////
//       PRIMITIVES      //
///////////////////////////
BuildingArrayIdxType BuildingArraySearchForIndex(BuildingArray T, BuildingArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
boolean BuildingArraySearchForBoolean(BuildingArray T, BuildingArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */

void BuildingArrayCopyTab(BuildingArray Tin, BuildingArray *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */

void BuildingArrayAddAsLastElement(BuildingArray *T, BuildingArrayElType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

//////////////////////////////////
//    BUILDINGARRAY OPERATIONS  //
//////////////////////////////////
void BuildingArrayPrintTab(BuildingArray T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

// Gonna still be added
#endif