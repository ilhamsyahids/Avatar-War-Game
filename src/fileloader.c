//==============================================//
//                                              //
//                 FileLoader                  	//
//                                              //
//----------------------------------------------//
// File : fileloader.c */                      	//
//----------------------------------------------//
// Implementasi modul FileLoader         		//
// FileLoader adalah modul yang mengurus 		//
// seluruh pembacaan file konfigurasi			//
//==============================================//

#ifndef _FILELOADER_H
#define _FILELOADER_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "fileloader.h"
#include "mesinkar.h"
#include "gamemap.h"

MapMatrix Map;
BuildingArray Record;
Player Player1;
Player Player2;
BuildingRelationGraph BuildingRelation;

///////////////////////////////////
// 	     FILELOADER OPERATIONS 	 //
///////////////////////////////////
void CompleteFileLoad(GameMap *G)
/* Mengembalikan GameMap yang sudah berisi data lengkap dari file */
{
	GameMapCreate(G, Map, Record, Player1, Player2, BuildingRelation);
	CurrentPlayer(*G) = Player1(*G);
}



void LoadBuildingRelation()
/* Menangani pembacaan hubungan antar bangunan pada peta */
/* I.S : */
/* F.S : */
{
	int i;
	int j;
	BuildingRelationGraphAddress V;
	AdjacentBuildingRelationGraphAddress P;

	for(i = 1; i <= BuildingArrayNeff(Record); i++){
		V = BuildingRelationGraphAddressSearch(BuildingRelation, i);
		for(j = 1; j <= BuildingArrayNeff(Record); j++){
			AdvFileInt();
			if(X == 1){
				BuildingRelationGraphInsertAdjacentVertex(V, j);
			}
		}
		AdvFileLine();
	}
}



void LoadBuildingList()
/* Menangani pembacaan daftar bangunan yang ada di peta */
/* I.S : Ukuran maksimum Record terdefinisi */
/* F.S : Record berisi seluruh bangunan yang ada di file */
{
	int i;
	int kind;
	int PositionX;
	int PositionY;
	Building B;
	Point P;

	// Load Player 1's Castle
	AdvFileChar();
	AdvFileInt();
	PositionX = X;
	AdvFileInt();
	PositionY = X;
	P = PointCreate(PositionX, PositionY);
	B = BuildingCreate(1, 1, P);
	BuildingArrayAddAsLastElement(&Record, B);
	MapMatrixElement(Map, P) = 1;
	AdvFileLine();

	
	// Load Player 2's Castle
	AdvFileChar();
	AdvFileInt();
	PositionX = X;
	AdvFileInt();
	PositionY = X;
	P = PointCreate(PositionX, PositionY);
	B = BuildingCreate(1, 2, P);
	BuildingArrayAddAsLastElement(&Record, B);
	MapMatrixElement(Map, P) = 2;
	AdvFileLine();

	// Load Other Buildings
	for(i = 1; i <= BuildingArrayMaxElement(Record) - 2; i++){
		AdvFileChar();
		if(CC == 'C'){
			kind = 1;
		} else if(CC == 'T'){
			kind = 2;
		} else if(CC == 'F'){
			kind = 3;
		} else if(CC == 'V'){
			kind = 4;
		}
		AdvFileInt();
		PositionX = X;
		AdvFileInt();
		PositionY = X;
		P = PointCreate(PositionX, PositionY);
		B = BuildingCreate(kind, 0, P);
		BuildingArrayAddAsLastElement(&Record, B);
		MapMatrixElement(Map, P) = i + 2;
		AdvFileLine();
	}
}


void LoadBuildingCount()
/* Menangani pembacaan banyaknya bangunan pada peta dari file */
/* I.S : Record sembarang */
/* F.S : Ukuran maksimum Record terdefinisi */
{
	int BuildingCount;
	int i;

	AdvFileInt();
	BuildingCount = X;

	BuildingArrayCreateEmpty(&Record, BuildingCount);
	BuildingRelationGraphCreateEmpty(&BuildingRelation);

	for(i = 1; i <= BuildingCount; i++){
		BuildingRelationGraphInsertVertex(&BuildingRelation, i);
	}

	AdvFileLine();
}



void LoadMapSize()
/* Menangani pembacaan ukuran peta dari file */
/* I.S : Map sembarang */
/* F.S : Ukuran Map efektif terdefinisi */
{
	int MapCol;
	int MapRow;

	AdvFileInt();
	MapRow = X;

	AdvFileInt();
	MapCol = X;

	MapMatrixCreateEmpty(&Map, MapRow, MapCol);

	AdvFileLine();

}

void LoadingSequence()
/* Seluruh sekuens pembacaan dijalankan pada method ini */
/* I.S : G, Map, Record, CurrentPlayer sembarang */
/* F.S : Terbentuk G dengan atribut Map, Record dan CurrentPlayer sesuai file */
{
	LoadMapSize();
	LoadBuildingCount();
	LoadBuildingList();
	LoadBuildingRelation();
}


void StartLoading(char* filename, char Player1Color, char Player2Color)
/* Memulai pembacaan dari file konfigurasi */
/* I.S : Pita file kosong, GameMap belum siap diload */
/* F.S : File siap dibaca, GameMap siap diload, dan sekuens pembacaan dimulai */
{
	OpenFile(filename);
	Player1 = PlayerCreate(1, Player1Color);
	Player2 = PlayerCreate(2, Player2Color);
	LoadingSequence();
}

#endif