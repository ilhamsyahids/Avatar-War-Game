//==============================================//
//                                              //
//                BuildingArray                 //
//                                              //
//----------------------------------------------//
// File : buildingarray.h */                    //
//----------------------------------------------//
// Definisi ADT BuildingArray                   //
// Dengan representasi array eksplisit dan      //
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
#define BuildingArrayIdxMin 1
/* Indeks minimum building array */

#define BuildingArrayIdxUndef -999
/* Indeks tak terdefinisi building array */

typedef int BuildingArrayIdxType;     /* type indeks */
typedef Building BuildingArrayElType; /* type elemen tabel */

//////////////////////////////
//  Definisi BuildingArray  //
//////////////////////////////
typedef struct
{
  BuildingArrayElType *TI; /* memori tempat penyimpan elemen (container) */
  int Neff;                /* >= 0, banyaknya elemen efektif */
  int MaxElement;          /* ukuran array maksimum */
} BuildingArray;
/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Definisi :
  Tabel kosong: T.Neff(T) = 0
  Definisi elemen pertama : T.TI[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=T.Neff */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika T adalah BuildingArray, maka akses elemen : */
#define BuildingArrayTab(T) (T).TI
#define BuildingArrayElement(T, i) (T).TI[(i)]
#define BuildingArrayNeff(T) (T).Neff
#define BuildingArrayMaxElement(T) (T).MaxElement

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

//////////////////////////////////
//    BUILDINGARRAY OPERATIONS  //
//////////////////////////////////
BuildingArrayIdxType BuildingArrayGetFirstIdx(BuildingArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */

BuildingArrayIdxType BuildingArrayGetLastIdx(BuildingArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

void BuildingArrayAddAsLastElement(BuildingArray *T, BuildingArrayElType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

void BuildingArrayInitializeAllBuilding(BuildingArray *T);
/* Menginisialisasi seluruh Building pada Array dengan BuildingInitialize */
/* I.S. T berisi Building yang hanya sudah diCreate */
/* F.S. T berisi Building yang seluruhnya sudah terinisialisasi */

void BuildingArrayResetAllBuilding(BuildingArray *T);
/* Merefresh seluruh Building pada Array dengan BuildingRefreshStatus */
/* I.S. T berisi Building yang sudah terinisialisasi */
/* F.S. Building pada T direfresh */

void BuildingArrayIncreasePlayerOwnedPasukanBuilding(BuildingArray *T, int P, int value);
/* Menambahkan pasukan sebanyak value pada seluruh bangunan yang dikuasai P */
/* I.S. T berisi building dengan SoldierCount sembarang */
/* F.S. T berisi building dengan SoldierCount milik player P bertambah sebanyak value */

void BuildingArrayDecreasePlayerOwnedPasukanBuilding(BuildingArray *T, int P, int value);
/* Mengurangi pasukan sebanyak value pada seluruh bangunan yang dikuasai P */
/* I.S. T berisi building dengan SoldierCount sembarang */
/* F.S. T berisi building dengan SoldierCount milik player P berkurang sebanyak value */

void BuildingArrayIncreaseOwnedPasukanBuilding(BuildingArray *T, int P);
/* Menambahkan Pasukan pada semua bangunan yang ada kepemilikan player */
/* Penambahan dilakukan jika bertemu kasus akhir turn */
/* I.S. T berisi building dengan SoldierCount sembarang */
/* F.S. T berisi building dengan SoldierCount yang sudah ditambah sesuai dengan A */

void BuildingArrayLevelUpOwnedPlayerBuilding(BuildingArray *T, int P);
/* Menaikkan level bangunan yang dimiliki player P sebanyak 1 level */
/* I.S. T berisi building dengan level sembarang */
/* F.S. T berisi building player P dengan level bertambah 1 */
/* Jika level sudah maksimum sebelum bertambah, akan muncul prompt dan tidak akan bertambah level */

BuildingArray BuildingArrayCopyArray(BuildingArray T);
/* Mengirimkan salinan BuildingArray T menjadi BuildingArray baru */

#endif