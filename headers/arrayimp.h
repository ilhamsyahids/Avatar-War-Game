//==============================================//
//                                              //
//                ImplicitArray                 //
//                                              //
//----------------------------------------------//
// File : arrayimp.h */                         //
//----------------------------------------------//
// Definisi ADT ImplicitArray                   //
// Dengan representasi array implisit dan       //
// alokasi dinamik                              //
//==============================================//

#ifndef _ARRAYIMP_H
#define _ARRAYIMP_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

///////////////////////////////////
//         CONST & TYPEDEF       //
///////////////////////////////////
const int ImplicitArrayIdxMin = 1;
/* Indeks minimum array */

const int ImplicitArrayIdxUndef = -999;
/* Indeks tak terdefinisi*/

const int ImplicitArrayValUndef = -999;
/* Indeks tak terdefinisi*/

typedef int ImplicitArrayIdxType; /* type indeks */
typedef int ImplicitArrayElType;  /* type elemen tabel */


//////////////////////////////
//  Definisi ImplicitArray  //
//////////////////////////////
typedef struct
{
    ImplicitArrayElType *TI; /* memori tempat penyimpan elemen (container) */
    int MaxElement;  /* ukuran elemen */
} ImplicitArray;
/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Definisi :
  Tabel kosong: NbElmt(T) = 0
  Definisi elemen pertama : T.TI[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=NbElmt(T) */


///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void ImplicitArrayCreateEmpty(ImplicitArray *T, int maxel);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */
/* Setiap elemen diisi dengan elemen dummy ValUndef */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void ImplicitArrayDealokasi(ImplicitArray *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0 */

///////////////////////////
//        SELECTOR       //
///////////////////////////
ImplicitArrayElType* ImplicitArrayTab(ImplicitArray T);
/* Mengirimkan T.TI */

ImplicitArrayElType ImplicitArrayTabElement(ImplicitArray T, ImplicitArrayIdxType i);
/* Mengirimkan (T).TI[(i)] */

/* *** Banyaknya elemen *** */
int ImplicitArrayNBElmt(ImplicitArray T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */

/* *** Daya tampung container *** */
int ImplicitArrayMaxElement(ImplicitArray T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */

ImplicitArrayIdxType ImplicitArrayGetFirstIdx(ImplicitArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */

ImplicitArrayIdxType ImplicitArrayGetLastIdx(ImplicitArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsImplicitArrayIdxValid(ImplicitArray T, ImplicitArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/

boolean IsImplicitArrayIdxEff(ImplicitArray T, ImplicitArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

boolean IsImplicitArrayEmpty(ImplicitArray T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean IsImplicitArrayFull(ImplicitArray T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

boolean IsImplicitArrayEQ(ImplicitArray T1, ImplicitArray T2);
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */


///////////////////////////
//       PRIMITIVES      //
///////////////////////////
ImplicitArray ImplicitArrayPlusMinusTab(ImplicitArray T1, ImplicitArray T2, boolean plus);
/* Prekondisi : T1 dan T2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */

ImplicitArrayIdxType ImplicitArrayIndexSearch(ImplicitArray T, ImplicitArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */

boolean ImplicitArrayBooleanSearch(ImplicitArray T, ImplicitArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */

void ImplicitArrayCopyTab(ImplicitArray Tin, ImplicitArray *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */

void ImplicitArraySort(ImplicitArray *T, boolean asc);
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */

void ImplicitArrayAddAsLastElement(ImplicitArray *T, ImplicitArrayElType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

void ImplicitArrayDeleteLastElement(ImplicitArray *T, ImplicitArrayElType *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

/* ********* MENGUBAH UKURAN ARRAY ********* */
void ImplicitArrayGrowTab(ImplicitArray *T, int num);
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */

void ImplicitArrayShrinkTab(ImplicitArray *T, int num);
/* Proses : Mengurangi max element sebanyak num */
/* I.S. Tabel sudah terdefinisi, ukuran MaxEl > num, dan Neff < MaxEl - num. */
/* F.S. Ukuran tabel berkurang sebanyak num. */

void ImplicitArrayCompactTab(ImplicitArray *T);
/* Proses : Mengurangi max element sehingga Neff = MaxEl */
/* I.S. Tabel tidak kosong */
/* F.S. Ukuran MaxEl = Neff */

//////////////////////////////////
//    IMPLICITARRAY OPERATIONS  //
//////////////////////////////////
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void ImplicitArrayReadTab(ImplicitArray *T);
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
void ImplicitArrayPrintTab(ImplicitArray T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

#endif