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
    BuildingListElement *P = (BuildingListElement *)malloc(sizeof(BuildingListElement));

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
void BuildingListElementDealokasi(BuildingListAddress *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(*P);
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
    BuildingListAddress *P = BuildingListFirstAddress(*L);
    BuildingListFirstAddress(*L) = BuildingListElementNext(*P);
    (*X) = BuildingListElementInfo(*P);
    BuildingListElementNext(*P) = BuildingListNil;
    BuildingArrayDealokasi(*P);
}

void BuildingListDeleteValueLast(BuildingList *L, BuildingListInfotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    BuildingListAddress *P = BuildingListFirstAddress(*L);
    if (*P == BuildingListNil)
        BuildingListCreateEmpty(L);
    else
    {
        BuildingListAddress last = *P;
        while (BuildingListElementNext(BuildingListElementNext(last)) != BuildingListNil)
            last = BuildingListElementNext(last);
        last = BuildingListElementNext(last);
        (*P) = BuildingListElementNext(last);
        (*X) = BuildingListElementInfo(*P);
        BuildingListElementNext(last) = BuildingListNil;
        BuildingArrayDealokasi(*P);
    }
}

void BuildingListDeleteValue(BuildingList *L, BuildingListInfotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan BuildingListElementInfo(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan BuildingListElementInfo(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    BuildingListAddress *P = BuildingListAddressSearch(*L, X);
    if (*P = BuildingListNil)
    {
        BuildingListAddress prev = BuildingListFirstAddress(*L);
        if (prev == P)
            BuildingListDeleteValueFirst(L, &X);
        else
        {
            while (BuildingListElementNext(prev) != *P)
                prev = BuildingListElementNext(prev);
            BuildingListElementNext(prev) = BuildingListElementNext(BuildingListElementNext(prev));
        }
        BuildingListElementDealokasi(P);
    }
}

void BuildingListPrintInfo(BuildingList L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Dengan tambahan enter di akhir */

int BuildingListNbElmt(BuildingList L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
