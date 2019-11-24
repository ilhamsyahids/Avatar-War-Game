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
  BuildingArrayTab(*T) = (BuildingArrayElType *)malloc((maxel + 1) * sizeof(BuildingArrayElType));
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

void BuildingArrayAddAsLastElement(BuildingArray *T, BuildingArrayElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
  if(IsBuildingArrayEmpty(*T)){
    BuildingArrayElement((*T), 1) = X;
    BuildingArrayNeff(*T) =  BuildingArrayNeff(*T) + 1;
  } else{
    if(!IsBuildingArrayFull(*T)){
      BuildingArrayElement((*T), BuildingArrayNeff(*T) + 1) = X;
      BuildingArrayNeff(*T) =  BuildingArrayNeff(*T) + 1;
    }
  } 
}

void BuildingArrayInitializeAllBuilding(BuildingArray *T)
/* Menginisialisasi seluruh Building pada Array dengan BuildingInitialize */
/* I.S. T berisi Building yang hanya sudah diCreate */
/* F.S. T berisi Building yang seluruhnya sudah terinisialisasi */
{
  for(int i = 1; i <= BuildingArrayNeff(*T); i++){
    BuildingInitialize(&(BuildingArrayElement((*T), i)));
  }
}

void BuildingArrayResetAllBuilding(BuildingArray *T)
/* Merefresh seluruh Building pada Array dengan BuildingRefreshStatus */
/* I.S. T berisi Building yang sudah terinisialisasi */
/* F.S. Building pada T direfresh */
{
  for(int i = 1; i <= BuildingArrayNeff(*T); i++){
    BuildingResetStatus(&(BuildingArrayElement((*T), i)));
  }
}

void BuildingArrayIncreasePlayerOwnedPasukanBuilding(BuildingArray *T, int P, int value)
/* Menambahkan pasukan sebanyak value pada seluruh bangunan yang dikuasai P */
/* I.S. T berisi building dengan SoldierCount sembarang */
/* F.S. T berisi building dengan SoldierCount milik player P bertambah sebanyak value */
{
  for(int i = 1; i <= BuildingArrayNeff(*T); i++){ 
    if(BuildingPlayer(BuildingArrayElement((*T), i)) == (P)){
      BuildingIncreasePasukan(&(BuildingArrayElement((*T), i)), value);
    }
  } 
}

void BuildingArrayDecreasePlayerOwnedPasukanBuilding(BuildingArray *T, int P, int value)
/* Mengurangi pasukan sebanyak value pada seluruh bangunan yang dikuasai P */
/* I.S. T berisi building dengan SoldierCount sembarang */
/* F.S. T berisi building dengan SoldierCount milik player P berkurang sebanyak value */
{
  for(int i = 1; i <= BuildingArrayNeff(*T); i++){ 
    if(BuildingPlayer(BuildingArrayElement((*T), i)) == (P)){
      BuildingDecreasePasukan(&(BuildingArrayElement((*T), i)), value);
    }
  } 
}

void BuildingArrayIncreaseOwnedPasukanBuilding(BuildingArray *T, int P)
/* Menambahkan Pasukan pada semua bangunan yang ada kepemilikan player */
/* Penambahan dilakukan jika bertemu kasus akhir turn */
/* I.S. T berisi building dengan SoldierCount sembarang */
/* F.S. T berisi building dengan SoldierCount yang sudah ditambah sesuai dengan A */
{
  for(int i = 1; i <= BuildingArrayNeff(*T); i++){ 
    if((BuildingPlayer(BuildingArrayElement((*T), i)) == P) && (CanBuildingAddPasukan(BuildingArrayElement((*T), i)))){
      BuildingIncreasePasukan(&(BuildingArrayElement((*T), i)), BuildingSoldierAddValue(BuildingArrayElement((*T), i)));
      BuildingSoldierAddCount(BuildingArrayElement((*T), i)) += BuildingSoldierAddValue(BuildingArrayElement((*T), i));  
    }
  } 
}

void BuildingArrayLevelUpOwnedPlayerBuilding(BuildingArray *T, int P)
/* Menaikkan level bangunan yang dimiliki player P sebanyak 1 level */
/* I.S. T berisi building dengan level sembarang */
/* F.S. T berisi building player P dengan level bertambah 1 */
/* Jika level sudah maksimum sebelum bertambah, akan muncul prompt dan tidak akan bertambah level */
{
  for(int i = 1; i <= BuildingArrayNeff(*T); i++){ 
    if(BuildingPlayer(BuildingArrayElement((*T), i)) == (P)){
      if(!IsBuildingLevelMax(BuildingArrayElement((*T), i))){
        int nextLevel = (BuildingLevel(BuildingArrayElement((*T), i))) + 1;
        BuildingLevel(BuildingArrayElement((*T), i)) = nextLevel;
        BuildingRefreshStatus(&BuildingArrayElement((*T), i));
      }
    }
  } 
}

BuildingArray BuildingArrayCopyArray(BuildingArray T)
/* Mengirimkan salinan BuildingArray T menjadi BuildingArray baru */
{

  BuildingArray TNew;

  BuildingArrayCreateEmpty(&TNew, BuildingArrayMaxElement(T));

  for(int i = 1; i <= BuildingArrayNeff(T); i++){ 
    BuildingArrayAddAsLastElement(&TNew, BuildingArrayElement(T,i));
  } 

  return TNew;
}