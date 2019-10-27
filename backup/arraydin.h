//==============================================//
//                                              //
//                 ExplicitArray                //
//                                              //
//----------------------------------------------//
// File : exparray.h */                         //
//----------------------------------------------//
// Definisi ADT array dengan banyaknya elemen   //
// didefinisikan secara eksplisit               //
// (berlamawanan dengan ImpArray)               //
// dan memori tabel dinamik                     //
//==============================================//

#ifndef _EXPARRAY_H
#define _EXPARRAY_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include "boolean.h"
#include <stdlib.h>

///////////////////////////////////
//        CONST & TYPEDEF        //
///////////////////////////////////
const int ExplicitArrayIdxMin = 1;
/* Indeks minimum array */

const int ExplicitArrayIdxUndef = -999;

typedef int ExplicitArrayIdxType; /* type indeks */
typedef int ExplicitArrayElType;  /* type elemen tabel */


//////////////////////////////
//  Definisi ExplicitArray  //
//////////////////////////////
typedef struct
{
    ExplicitArrayElType *TI; /* memori tempat penyimpan elemen (container) */
    int Neff;   /* >=0, banyaknya elemen efektif */
    int MaxElement;  /* ukuran elemen */
} ExplicitArray;
/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Jika T adalah TabInt, cara deklarasi dan akses: */
/* Definisi :
  Tabel kosong: T.Neff = 0
  Definisi elemen pertama : T.TI[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=T.Neff */

///////////////////////////
//        SELECTOR       //
///////////////////////////
int ExplicitArrayNeff(ExplicitArray T);
/* Mengembalikan nilai Neff dari Explicit Array */

ExplicitArrayElType* ExplicitArrayTab(ExplicitArray T);
/* Mengirimkan T.TI */

ExplicitArrayElType ExplicitArrayTabElement(ExplicitArray T, ExplicitArrayIdxType i);
/* Mengirimkan (T).TI[(i)] */

int ExplicitArrayMaxElement(ExplicitArray T);
/* Mengirimkan nilai MaxElement dari Explicit Array */

/* *** Banyaknya elemen *** */
int ExplicitArrayNbElmt(TabInt T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */

ExplicitArrayIdxType ExplicitArrayFirstIdx(ExplicitArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
ExplicitArrayIdxType ExplicitArrayLastIdx(ExplicitArray T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void ExplicitArrayCreateEmpty(ExplicitArray *T, int maxel);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void ExplicitArrayDealokasi(ExplicitArray *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxElement(T)=0; Neff(T)=0 */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsExplicitArrayIdxValid(ExplicitArray T, ExplicitArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/

boolean IsExplicitArrayIdxEff(ExplicitArray T, ExplicitArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara ExplicitArrayFirstIdx(T)..ExplicitArrayLastIdx(T) */

/* *** Test tabel kosong *** */
boolean IsExplicitArrayEmpty(ExplicitArray T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */

/* *** Test tabel penuh *** */
boolean IsExplicitArrayFull(ExplicitArray T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */


boolean IsExplicitArrayEQ(ExplicitArray T1, ExplicitArray T2);
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */

//////////////////////////////////
//    IMPLICITARRAY OPERATIONS  //
//////////////////////////////////
void ExplicitArrayReadTab(ExplicitArray *T);
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */

void ExplicitArrayPrintTab(ExplicitArray T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

TabInt ExplicitArrayPlusMinusTab(ExplicitArray T1, ExplicitArrayPlus T2, boolean plus);
/* Prekondisi : T1 dan T2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
ExplicitArrayIdxType ExplicitArrayIndexSearch(ExplicitArray T, ExplicitArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */

boolean ExplicitArrayBooleanSearch(ExplicitArray T, ExplicitArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */

void ExplicitArrayCopyTab(ExplicitArray Tin, ExplicitArray *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */

/* ********** SORTING ********** */
void ExplicitArraySort(ExplicitArray *T, boolean asc);
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void ExplicitArrayAddAsLastElement(ExplicitArray *T, ExplicitArrayElType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
void ExplicitArrayDeleteLastElement(ExplicitArray *T, ExplicitArrayElType *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

/* ********* MENGUBAH UKURAN ARRAY ********* */
void ExplicitArrayGrowTab(ExplicitArray *T, int num);
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */

void ExplicitArrayShrinkTab(ExplicitArray *T, int num);
/* Proses : Mengurangi max element sebanyak num */
/* I.S. Tabel sudah terdefinisi, ukuran MaxEl > num, dan Neff < MaxEl - num. */
/* F.S. Ukuran tabel berkurang sebanyak num. */

void ExplicitArrayCompactTab(ExplicitArray *T);
/* Proses : Mengurangi max element sehingga Neff = MaxEl */
/* I.S. Tabel tidak kosong */
/* F.S. Ukuran MaxEl = Neff */

#endif