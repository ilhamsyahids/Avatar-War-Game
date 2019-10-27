//==============================================//
//								       			//
//					Matrix             			//
//                                     			//
//----------------------------------------------//
// File : matrix.h */              				//
//----------------------------------------------//
// Definisi ADT Matrix dengan elemen integer	//
//  											//
// 												//
//==============================================//

#ifndef _MATRIX_H
#define _MATRIX_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
/* Ukuran minimum dan maksimum baris dan kolom */
const int MatrixBarisMinimum = 1;

const int MatrixBarisMaximum = 100;

const int MatrixKolomMinimimum = 1;

const int MatrixKolomMaximum = 100;

typedef int MatrixIdxType; /* TIpe Indeks Matrix (baris dan kolom) */
typedef int MatrixElType;	/* Tipe Elemen Matrix */


///////////////////////////
// 	Definisi Matrix  	 //
///////////////////////////
typedef struct
{
    MatrixElType Mem[MatrixBarisMaximum + 1][MatrixKolomMaximum + 1];
    int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
    int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrix;
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks Matrix yang digunakan: [MatrixBarisMinimum..MatrixBarisMaximum][MatrixKolomMinimum..MatrixKolomMaximum] */
/* Memori Matrix yang dipakai selalu di "ujung kiri atas" */

///////////////////////////
// 		 SELECTOR		 //
///////////////////////////
int MatrixNBrsEff(Matrix M);
/* Mengembalikan nilai banyak baris yang terdefinisi */

int MatrixNKolEff(Matrix M);
/* Mengembalikan nilai banyak kolom yang terdefinisi */

int MatrixNBElmt(Matrix M);
/* Mengirimkan banyaknya elemen M */

MatrixElType MatrixElement(Matrix M, int row, int col);
/* Mengembalikan nilai elemen matrix M baris row kolom col */

MatrixIdxType MatrixFirstIdxBaris(Matrix M);
/* Mengirimkan indeks baris terkecil M */

MatrixIdxType MatrixFirstIdxKolom(Matrix M);
/* Mengirimkan indeks kolom terkecil M */

MatrixIdxType MatrixLastIdxBaris(Matrix M);
/* Mengirimkan indeks baris terbesar M */

MatrixIdxType MatrixLastIdxKolom(Matrix M);
/* Mengirimkan indeks kolom terbesar M */

MatrixElType GetElmtDiagonal(Matrix M, MatrixIdxType i);
/* Mengirimkan elemen M(i,i) */


///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void MatrixCreateEmpty(int row, int col, Matrix *M);
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran row x column di "ujung kiri" memori */
/* I.S. row dan col adalah valid untuk memori matriks yang dibuat */
/* F.S. Matrix M sesuai dengan definisi di atas terbentuk */


///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsMatrixIdxValid(MatrixIdxType row, MatrixIdxType col);
/* Mengirimkan true jika row, col adalah indeks yang valid untuk matrix apa pun */

boolean IsMatrixIdxEff(Matrix M, MatrixIdxType row, MatrixIdxType col);
/* Mengirimkan true jika row, col adalah indeks efektif bagi M */

boolean IsMatrixSquare(Matrix M);
/* Mengirimkan trus jika M adalah Matrix bujur sangkar */

boolean IsMatrixSimetric(Matrix M);
/* Mengirimkan true jika M adalah Matrix simetri */

///////////////////////////
// 	     PRIMITIVES 	 //
///////////////////////////
void MatrixCopy(Matrix MIn, Matrix *MHsl);
/* Melakukan pengopian matrix MIn ke MHsl */

void MatrixReadTab(Matrix *M, int row, int col);
/* I.S. IsMatrixIdxValid(row,column) */
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran row x col */
/* Proses: Melakukan MatrixCreateEmpty(M,row,col) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika row = 3 dan col = 3, maka contoh cara membaca isi matrix :
1 2 3
4 5 6
8 9 10
*/

void MatrixPrintTab(Matrix M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matrix 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

Matrix MatrixAdd(Matrix M1, Matrix M2);
/* Prekondisi : M1 berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matrix: M1 + M2 */

Matrix MatrixSubstract(Matrix M1, Matrix M2);
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matrix: salinan M1 – M2 */

Matrix MatrixTimesConstant(Matrix M, MatrixElType X);
/* Mengirim hasil perkalian setiap elemen M dengan X */

boolean MatrixEQ(Matrix M1, Matrix M2);
/* Mengirimkan true jika M1 = M2, yaitu MatrixNBElmt(M1) = MatrixNBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */

boolean MatrixEQSize(Matrix M1, Matrix M2);
/* Mengirimkan true jika ukuran efektif matrix M1 sama dengan ukuran efektif M2 */
/* yaitu MatrixNBrsEff(M1) = MatrixNBrsEff (M2) dan MatrixNKolEff (M1) = MatrixNKolEff (M2) */


#endif