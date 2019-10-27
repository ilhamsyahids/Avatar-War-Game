//==============================================//
//                                              //
//                   Point                   	//
//                                              //
//----------------------------------------------//
// File : point.h */                        	//
//----------------------------------------------//
// Definisi ADT Point                      		//
// Point adalah representasi titik di koordinat //
// 2 dimensi dengan titik seperti index matrix 	//
//==============================================//

//----------------------------------------------//
//			  Contoh Visualisasi titik			//
//----------------------------------------------//
// 					A  .  .						//
// 					.  .  .						//
// 					.  B  .						//
//												//						
// Ruang 3x3 di atas adalah bidang koordinat 2D	//
// A menempati Point (1,1)						//
// B menempati Point (3,2)						//
//----------------------------------------------//		

#ifndef _POINT_H
#define _POINT_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include "boolean.h"

////////////////////////////////////
//     Definisi elemen Point   	  //
////////////////////////////////////
typedef struct
{
    float X; /* absis   */
    float Y; /* ordinat */
} Point;


///////////////////////////
//        SELECTOR       //
///////////////////////////
float PointX(Point P);
/* Mengembalikan nilai X dari point */

float PointY(Point P);
/* Mengembalikan nilai Y dari point */

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
Point PointCreate(float X, float Y);
/* Membentuk sebuah Point dari komponen-komponennya */

///////////////////////////
//        PREDIKAT       //
///////////////////////////
boolean PointEQ(Point P1, Point P2);
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */

//////////////////////////////////
//      POINT OPERATIONS     	//
//////////////////////////////////
/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void PointRead(Point *P);
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   Point P berdasarkan dari nilai X dan Y tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */

void PointPrint(Point P);
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   dengan enter di belakang
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */

#endif