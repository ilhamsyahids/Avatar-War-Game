//==============================================//
//								       			//
//					Map Matrix             		//
//                                     			//
//----------------------------------------------//
// File : mapmatrix.h */              			//
//----------------------------------------------//
// Definisi ADT MapMatrix dengan elemen index	//
// Yang berkorespondensi dengan BuildingArray 	//
// Alokasi array secara statik					//
//==============================================//

#ifndef _MATRIX_H
#define _MATRIX_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "pcolor.h"
#include "boolean.h"
#include "point.h"
#include "buildingarray.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
/* Ukuran minimum dan maksimum baris dan kolom */
#define MapMatrixBarisMinimum 1

#define MapMatrixBarisMaximum 30

#define MapMatrixKolomMinimimum 1

#define MapMatrixKolomMaximum 20

typedef Point MapMatrixIdxType; 	/* TIpe Indeks Matrix <baris, kolom> */
typedef int MapMatrixElType;		/* Tipe Elemen Matrix */


///////////////////////////////////
// 		Definisi MapMatrix  	 //
///////////////////////////////////
typedef struct
{
    MapMatrixElType Mem[MapMatrixBarisMaximum + 1][MapMatrixKolomMaximum + 1];
    int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
    int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MapMatrix;
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks Matrix yang digunakan: [MatrixBarisMinimum..MatrixBarisMaximum][MatrixKolomMinimum..MatrixKolomMaximum] */
/* Memori Matrix yang dipakai selalu di "ujung kiri atas" */


//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika M adalah Matrix dan P adalah Point, maka akses elemen : */
#define MapMatrixNBrsEff(M) 		(M).NBrsEff
#define MapMatrixNKolEff(M) 		(M).NKolEff
#define MapMatrixElement(M,P) 		(M).Mem[(PointX(P))][(PointY(P))]

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void MapMatrixCreateEmpty(MapMatrix *M, int row, int col);
/* Membentuk sebuah MapMatrix "kosong" yang siap diisi berukuran row x column di "ujung kiri" memori */
/* I.S. row dan col adalah valid untuk memori matriks yang dibuat */
/* F.S. Matrix M sesuai dengan definisi di atas terbentuk
		row dan col menjadi NBrsEff dan NKolEff */

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsMapMatrixIdxValid(MapMatrixIdxType index);
/* Mengirimkan true jika PointX(index), PointY(index) adalah indeks yang valid untuk matrix apa pun */

boolean IsMapMatrixIdxEff(MapMatrix M, MapMatrixIdxType index);
/* Mengirimkan true jika PointX(index), PointY(index) adalah indeks efektif bagi M */

///////////////////////////////////
// 	    MAP MATRIX OPERATIONS 	 //
///////////////////////////////////
int MapMatrixNBElmt(MapMatrix M);
/* Mengirimkan banyaknya elemen M */

int MapMatrixFirstIdxBaris(MapMatrix M);
/* Mengirimkan indeks baris terkecil M */

int MapMatrixFirstIdxKolom(MapMatrix M);
/* Mengirimkan indeks kolom terkecil M */

int MapMatrixLastIdxBaris(MapMatrix M);
/* Mengirimkan indeks baris terbesar M */

int MapMatrixLastIdxKolom(MapMatrix M);
/* Mengirimkan indeks kolom terbesar M */

void MapMatrixPrintMap(MapMatrix M, BuildingArray T);
/* I.S. M terdefinisi */
/* F.S. Map dicetak ke layar dengan format 
*********
*X		*
*		*
*		*
*	   Y*
*********
dibatasi boundary * dengan jumlah NKolEff + 2 untuk atas bawah dan NBrsEff + 2 untuk kanan kiri
X dan Y adalah char bangunan yang dimiliki atau tidak dimiliki pemain 1 atau 2
Jika sebuah bangunan dimiliki pemain, pencetakan char dilakukan dengan warna
Tidak ada spasi antara bangunan 1 dengan yang lain
Ada enter di setiap akhir baris 
*/

Building MapMatrixGetBuilding(MapMatrix M, MapMatrixIdxType pos, BuildingArray T);
/* Mengembalikan building pada point pos */



#endif