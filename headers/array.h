//==============================================//
//                                              //
//                    ARRAY                     //
//                                              //
//----------------------------------------------//
// File : array.h */                            //
//----------------------------------------------//
// Definisi ADT array dengan banyaknya elemen   //
// didefinisikan secara eksplisit               //
// (berlamawanan dengan ImpArray)               //
// dan memori tabel dinamik                     //
//==============================================//

#ifndef _ARRAY_H
#define _ARRAY_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include "boolean.h"
#include <stdlib.h>

///////////////////////////////////
//        CONST & TYPEDEF        //
///////////////////////////////////
#define ArrayIdxMin 1;
/* Indeks minimum array */

#define ArrayIdxUndef -999;
/* Indeks tak terdefinisi array */

typedef int ArrayIdxType; /* type indeks */
typedef int ArrayElType;  /* type elemen tabel */


//////////////////////
//  Definisi Array  //
//////////////////////
typedef struct
{
    ArrayElType *TI;  /* memori tempat penyimpan elemen (container) */
    int Neff;         /* >=0, banyaknya elemen efektif */
    int MaxElement;   /* ukuran array maksimum */
} Array;
/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Jika T adalah TabInt, cara deklarasi dan akses: */
/* Definisi :
  Tabel kosong: T.Neff = 0
  Definisi elemen pertama : T.TI[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=T.Neff */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika T adalah Array, maka akses elemen : */
#define ArrayTab(T)         (T).TI
#define ArrayElement(T,i)   (T).TI[(i)]
#define ArrayNeff(T)        (T).Neff
#define ArrayMaxElement(T)  (T).MaxElement

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void ArrayCreateEmpty(Array *T, int maxel);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void ArrayDealokasi(Array *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxElement(T)=0; Neff(T)=0 */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsArrayIdxValid(Array T, ArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/

boolean IsArrayIdxEff(Array T, ArrayIdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara ArrayFirstIdx(T)..ArrayLastIdx(T) */

/* *** Test tabel kosong *** */
boolean IsArrayEmpty(Array T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */

/* *** Test tabel penuh *** */
boolean IsArrayFull(Array T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */


boolean IsArrayEQ(Array T1, Array T2);
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */

//////////////////////////
//    ARRAY OPERATIONS  //
//////////////////////////
ArrayIdxType ArrayGetFirstIdx(Array T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */

ArrayIdxType ArrayGetLastIdx(Array T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

void ArrayReadTab(Array *T);
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */

void ArrayPrintTab(Array T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
ArrayIdxType ArrayIndexSearch(Array T, ArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */

boolean ArrayBooleanSearch(Array T, ArrayElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */

void ArrayCopyTab(Array Tin, Array *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */

/* ********** SORTING ********** */
void ArraySort(Array *T, boolean asc);
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void ArrayAddAsLastElement(Array *T, ArrayElType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
void ArrayDeleteLastElement(Array *T, ArrayElType *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

/* ********* MENGUBAH UKURAN ARRAY ********* */
void ArrayGrowTab(Array *T, int num);
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */

void ArrayShrinkTab(Array *T, int num);
/* Proses : Mengurangi max element sebanyak num */
/* I.S. Tabel sudah terdefinisi, ukuran MaxEl > num, dan Neff < MaxEl - num. */
/* F.S. Ukuran tabel berkurang sebanyak num. */

void ArrayCompactTab(Array *T);
/* Proses : Mengurangi max element sehingga Neff = MaxEl */
/* I.S. Tabel tidak kosong */
/* F.S. Ukuran MaxEl = Neff */

#endif