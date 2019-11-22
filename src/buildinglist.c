//==============================================//
//                                              //
//            	  BuildingList                  //
//                                              //
//----------------------------------------------//
// File : BuildingList.c */                     //
//----------------------------------------------//
// Definisi ADT BuildingList  					//
// BuildingList digunakan untuk menyimpan       //
// Index bangunan yang mengacu ke BuildingArray	//
//==============================================//

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include "boolean.h"
#include "buildingarray.h"
#include "buildinglist.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void BuildingListCreateEmpty(BuildingList *L)
/* I.S. sembarang             */
/* F.S. Terbentuk BuildingList kosong */
{
    BuildingListFirstAddress(*L) = BuildingListNil;
}

BuildingListAddress BuildingListElementAlokasi(BuildingListInfotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka BuildingListElementInfo(P)=X, BuildingListElementNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    BuildingListAddress P = (BuildingListAddress)malloc(sizeof(BuildingListElement));

    if (P != BuildingListNil)
    {
        BuildingListElementInfo(P) = X;
        BuildingListElementNext(P) = BuildingListNil;
    }

    return P;
}

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void BuildingListElementDealokasi(BuildingListAddress P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(P);
}

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsBuildingListEmpty(BuildingList L)
/* Mengirim true jika list kosong */
{
    return BuildingListFirstAddress(L) == BuildingListNil;
}

/////////////////////////
//    LIST OPERATIONS  //
/////////////////////////
BuildingListAddress BuildingListAddressSearch(BuildingList L, BuildingListInfotype X)
/* Mencari apakah ada elemen list dengan BuildingListElementInfo(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    boolean found = false;
    BuildingListAddress P = BuildingListFirstAddress(L);

    if (!IsBuildingListEmpty(L))
    {
        while (!found && P != BuildingListNil)
        {
            if (BuildingListElementInfo(P) == X)
                found = true;
            else
                P = BuildingListElementNext(P);
        }
    }
    return found ? P : BuildingListNil;
}

void BuildingListInsertValueFirst(BuildingList *L, BuildingListInfotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    BuildingListAddress P = BuildingListElementAlokasi(X);
    if (P != BuildingListNil)
    {
        BuildingListElementNext(P) = BuildingListFirstAddress(*L);
        BuildingListFirstAddress(*L) = P;
    }
}

void BuildingListInsertValueLast(BuildingList *L, BuildingListInfotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (IsBuildingListEmpty(*L))
    {
        BuildingListInsertValueFirst(L, X);
    }
    else
    {
        BuildingListAddress P = BuildingListElementAlokasi(X);
        if (P != BuildingListNil)
        {
            BuildingListAddress last = BuildingListFirstAddress(*L);
            while (BuildingListElementNext(last) != BuildingListNil)
            {
                last = BuildingListElementNext(last);
            }
            BuildingListElementNext(last) = P;
            BuildingListElementNext(P) = BuildingListNil;
        }
    }
}

void BuildingListDeleteValueFirst(BuildingList *L, BuildingListInfotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    BuildingListAddress P = BuildingListFirstAddress(*L);
    BuildingListFirstAddress(*L) = BuildingListElementNext(P);
    (*X) = BuildingListElementInfo(P);
    BuildingListElementNext(P) = BuildingListNil;
    BuildingListElementDealokasi(P);
}

void BuildingListDeleteValueLast(BuildingList *L, BuildingListInfotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    BuildingListAddress P = BuildingListFirstAddress(*L);
    if (BuildingListElementNext(P) == BuildingListNil)
        BuildingListCreateEmpty(L);
    else
    {
        BuildingListAddress last = P;
        while (BuildingListElementNext(BuildingListElementNext(last)) != BuildingListNil)
            last = BuildingListElementNext(last);
        (P) = BuildingListElementNext(last);
        BuildingListElementNext(last) = BuildingListNil;
    }
    BuildingListElementDealokasi(P);
    (*X) = BuildingListElementInfo(P);
}

void BuildingListDeleteValue(BuildingList *L, BuildingListInfotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan BuildingListElementInfo(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan BuildingListElementInfo(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    BuildingListAddress P = BuildingListAddressSearch(*L, X);
    if (P != BuildingListNil)
    {
        BuildingListAddress prev = BuildingListFirstAddress(*L);
        if (prev == P)
            BuildingListDeleteValueFirst(L, &X);
        else
        {

            while (BuildingListElementNext(prev) != P)
            {
                prev = BuildingListElementNext(prev);
            }
            BuildingListElementNext(prev) = BuildingListElementNext(BuildingListElementNext(prev));
            BuildingListElementDealokasi(P);
        }
    }
}

void BuildingListPrintInfo(BuildingList L, BuildingArray BL)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, list dicetak ke bawah */
/* Elemen list adalah index yang merujuk pada index building di Building Array */
/* Setiap elemen list dicetak building yang berkorespondensi */
/* Misal elemen list : 1 -> 3 -> 5 */
/* maka cetak building dengan index ke 1 3 dan 5 dari BuildingArray, dengan format */
/* 1. PrintBuilding1
   2. PrintBuilding3
   3. PrintBuilding5 */
{
    if (!IsBuildingListEmpty(L))
    {
        int count = 1;
        BuildingListAddress P = BuildingListFirstAddress(L);
        while (P != BuildingListNil)
        {
            printf("%d. ", count);
            BuildingPrintInfo(BuildingArrayElement(BL, BuildingListElementInfo(P)));
            printf("\n");
            P = BuildingListElementNext(P);
            count++;
        }
    }
}

int BuildingListNbElmt(BuildingList L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int count = 0;
    if (!IsBuildingListEmpty(L))
    {
        BuildingListAddress P = BuildingListFirstAddress(L);
        while ((P) != BuildingListNil)
        {
            count++;
            P = BuildingListElementNext(P);
        }
    }
    return count;
}

BuildingList CopyBuildingList(BuildingList BL)
/* Mengirimkan salinan BuildingList BL (menjadi BuildingList baru) */
{
    BuildingList B;
    BuildingListCreateEmpty(&B);
    if (!IsBuildingListEmpty(BL))
    {
        BuildingListAddress P = BuildingListFirstAddress(BL);
        while ((P) != BuildingListNil)
        {
            BuildingListInsertValueLast(&B, BuildingListElementInfo(P));
            P = BuildingListElementNext(P);
        }
    }
    return B;
}
