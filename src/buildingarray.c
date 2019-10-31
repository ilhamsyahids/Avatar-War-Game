//==============================================//
//                                              //
//                BuildingArray                 //
//                                              //
//----------------------------------------------//
// File : buildingarray.c */                    //
//----------------------------------------------//
// Definisi ADT BuildingArray                   //
// Dengan representasi array eksplisit dan      //
// alokasi dinamik                              //
//==============================================//

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "building.h"
#include "buildingarray.h"

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void BuildingArrayCreateEmpty(BuildingArray *T, int maxel)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */
/* Setiap elemen diisi dengan elemen dummy building (ValUndef) */
{
  BuildingArrayTab(*T) = (BuildingArray *)malloc((maxel + 1) * sizeof(BuildingArray));
  BuildingArrayMaxElement(*T) = maxel;
  BuildingArrayNeff(*T) = 0;
}

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void BuildingArrayDealokasi(BuildingArray *T)
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0 */
{
  free(BuildingArrayTab(*T));
  BuildingArrayNeff(*T) = 0;
  BuildingArrayMaxElement(*T) = 0;
}

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsBuildingArrayIdxValid(BuildingArray T, BuildingArrayIdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
  return ((i >= BuildingArrayIdxMin) && (i <= BuildingArrayMaxElement(T)));
}
boolean IsBuildingArrayIdxEff(BuildingArray T, BuildingArrayIdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
  return ((i >= BuildingArrayIdxMin) && (i <= BuildingArrayNeff(T)));
}

boolean IsBuildingArrayEmpty(BuildingArray T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
  return (BuildingArrayNeff(T) == 0);
}

/* *** Test tabel penuh *** */
boolean IsBuildingArrayFull(BuildingArray T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
  return (BuildingArrayNeff(T) == BuildingArrayMaxElement(T));
}

//////////////////////////////////
//    BUILDINGARRAY OPERATIONS  //
//////////////////////////////////
BuildingArrayIdxType BuildingArrayGetFirstIdx(BuildingArray T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
  return BuildingArrayIdxMin;
}

BuildingArrayIdxType BuildingArrayGetLastIdx(BuildingArray T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
  return BuildingArrayNeff(T) - BuildingArrayGetFirstIdx(T) + 1;
}

void BuildingArrayAddAsLastElement(BuildingArray *T, BuildingArrayElType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
