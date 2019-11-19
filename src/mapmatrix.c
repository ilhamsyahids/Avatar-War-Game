#include <stdio.h>
#include <stdlib.h>
#include "pcolor.h"
#include "boolean.h"
#include "point.h"
#include "buildingarray.h"
#include "mapmatrix.h"
#include "player.h"

/*#include "matrix.h"
///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
/* Ukuran minimum dan maksimum baris dan kolom */
#define MapMatrixBarisMinimum 1

#define MapMatrixBarisMaximum 30

#define MapMatrixKolomMinimimum 1

#define MapMatrixKolomMaximum 20

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
void MapMatrixCreateEmpty(MapMatrix *M, int row, int col){
    MapMatrixNBrsEff(*M) = row;
	MapMatrixNKolEff(*M) = col;
	int i,j;
    Point P;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++){
                    P = PointCreate(i, j);
                    PointPrint(P);
                    printf("\n");
                    MapMatrixElement(*M,P) = 0;}
}
/* Membentuk sebuah MapMatrix "kosong" yang siap diisi berukuran row x column di "ujung kiri" memori */
/* I.S. row dan col adalah valid untuk memori matriks yang dibuat */
/* F.S. Matrix M sesuai dengan definisi di atas terbentuk
		row dan col menjadi NBrsEff dan NKolEff */

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsMapMatrixIdxValid(MapMatrixIdxType index){
    return (PointX(index) >= MapMatrixBarisMinimum) && (PointX(index) <= MapMatrixBarisMaximum) && (PointY(index) >= MapMatrixKolomMinimimum) && (PointY(index) <= MapMatrixKolomMaximum);
}
/* Mengirimkan true jika PointX(index), PointY(index) adalah indeks yang valid untuk matrix apa pun */

boolean IsMapMatrixIdxEff(MapMatrix M, MapMatrixIdxType index){
    return ((MapMatrixBarisMinimum<=PointX(index)) && (PointX(index)<=MapMatrixNBrsEff(M)) && ((MapMatrixKolomMinimimum<=PointY(index)) && (PointY(index)<=MapMatrixNKolEff(M))));
}
/* Mengirimkan true jika PointX(index), PointY(index) adalah indeks efektif bagi M */

///////////////////////////////////
// 	    MAP MATRIX OPERATIONS 	 //
///////////////////////////////////
int MapMatrixNBElmt(MapMatrix M){
    return MapMatrixNBrsEff(M) * MapMatrixNKolEff(M);
}
/* Mengirimkan banyaknya elemen M */

int MapMatrixFirstIdxBaris(MapMatrix M){
    return MapMatrixBarisMinimum;
}
/* Mengirimkan indeks baris terkecil M */

int MapMatrixFirstIdxKolom(MapMatrix M){
    return MapMatrixKolomMinimimum;
}
/* Mengirimkan indeks kolom terkecil M */

int MapMatrixLastIdxBaris(MapMatrix M){
    return MapMatrixNBrsEff(M);
}
/* Mengirimkan indeks baris terbesar M */

int MapMatrixLastIdxKolom(MapMatrix M){
    return MapMatrixNKolEff(M);
}
/* Mengirimkan indeks kolom terbesar M */

/*void MapMatrix(MapMatrix *M, BuildingArray N){
    Point p;
    for (i = 1; i <= BuildingArrayNeff(T); i++)
    {
        p = BuildingPosition(BuildingArrayElement(N, i));
        MapMatrixElement(*M,p);
    }
}*/


void MapMatrixPrintMap(MapMatrix M, BuildingArray T){
    int i;
    int j;
    Point P;
    
    for(i = 0; i <= MapMatrixLastIdxBaris(M) + 1; i++){
        for(j = 0; j <= MapMatrixLastIdxKolom(M) + 1; j++){
            if(i == 0 || i == MapMatrixLastIdxBaris(M) + 1){
                printf("*");
            } else{
                if(j == 0 || j == MapMatrixLastIdxKolom(M) + 1){
                    printf("*");
                } else{
                    P = PointCreate(i, j);
                    if(MapMatrixElement(M, P) != 0){
                        printf("%c", BuildingGetAcronym(BuildingKind(MapMatrixGetBuilding(M, P, T))));
                    } else{
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
    /*
    int i,j;
    for (i=MapMatrixFirstIdxBaris(M); i<=MapMatrixLastIdxBaris(M); i++){
        for (j=MapMatrixFirstIdxKolom(M); j<=MapMatrixLastIdxKolom(M); j++){
            if (i==1 || i==MapMatrixLastIdxBaris || j==1 || j==MapMatrixLastIdxKolom){          
                printf("*");}          
            else{
                printf(" ");}
        }
    }*/
}    
            /*switch (MapMatrixElement(M,i,j)){
				case 'P' : printf(COLOR_LGREEN "%c " COLOR_RESET, Elmt(M,i,j));break;
				case 'M' : printf(COLOR_WHITE "%c " COLOR_RESET, Elmt(M,i,j));break;
				default : printf("%c ",Elmt(M,i,j));break;
			}
        }
        printf("\n");
    }
}
}*/
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

Building MapMatrixGetBuilding(MapMatrix M, MapMatrixIdxType pos, BuildingArray T){
    return BuildingArrayElement(T, MapMatrixElement(M,pos));
    /*Point p;
    int i = 1;
    int j = 1;
    boolean found = false;
    while(i <= MapMatrixBarisMaximum && j <= MapMatrixKolomMaximum && !found){
        PointX(p) = i;
        PointY(p) = j;
        if (MapMatrixElement(M,p) == nomorbuildingarray){
            found = true;
        }
    }
    return BuildingArrayElement(T,nomorbuildingarray);*/
}
/* Mengembalikan building pada point pos */

//procedure func(input a, output b, input/output c)
// procedure func(a, *b, *c)
