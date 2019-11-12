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

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
GameMap G;
MapMatrix Map;
BuildingArray Record;
Player CurrentPlayer;
BuildingRelationGraph BuildingRelation;

///////////////////////////////////
// 	     FILELOADER OPERATIONS 	 //
///////////////////////////////////
void StartLoading(char* filename)
/* Memulai pembacaan dari file konfigurasi */
/* I.S : Pita file kosong */
/* F.S : File siap dibaca dan sekuens pembacaan dimulai */
{
	OpenFile(filename);
	LoadingSequence();
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

void LoadMapSize()
/* Menangani pembacaan ukuran peta dari file */
/* I.S : Map sembarang */
/* F.S : Ukuran Map efektif terdefinisi */
{
	int MapCol;
	int MapRow;

	AdvInt();
	MapCol = X;

	AdvInt();
	MapRow = X;

	MapMatrixCreateEmpty(&Map, MapRow, MapCol);

	AdvLine();

}

void LoadBuildingCount()
/* Menangani pembacaan banyaknya bangunan pada peta dari file */
/* I.S : Record sembarang */
/* F.S : Ukuran maksimum Record terdefinisi */
{
	int BuildingCount;
	int i;

	AdvInt();
	BuildingCount = X;

	BuildingArrayCreateEmpty(&Record, BuildingCount);
	BuildingRelationGraphCreateEmpty(&BuildingRelation);

	for(i = 1; i <= BuildingCount; i++){
		BuildingRelationGraphInsertVertex(&BuildingRelation, i);
	}

	AdvLine();
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

	// Load Player 1's Castle
	AdvChar();
	AdvInt();
	PositionX = X;
	AdvInt();
	PositionY = X;
	B = BuildingCreate(1, 1, PointCreate(PositionX, PositionY));
	BuildingArrayAddAsLastElement(&Record, B);
	AdvLine();

	// Load Player 2's Castle
	AdvChar();
	AdvInt();
	PositionX = X;
	AdvInt();
	PositionY = X;
	B = BuildingCreate(1, 2, PointCreate(PositionX, PositionY));
	BuildingArrayAddAsLastElement(&Record, B);
	AdvLine();

	// Load Other Buildings
	for(i = 1, i <= BuildingArrayMaxElement(Record) - 2, i++){
		AdvChar();
		if(CC == 'C'){
			kind = 1;
		} else if(CC == 'T'){
			kind = 2;
		} else if(CC == 'F'){
			kind = 3;
		} else if(CC == 'V'){
			kind = 4;
		}
		AdvInt();
		PositionX = X;
		AdvInt();
		PositionY = X;
		B = BuildingCreate(kind, 0, PointCreate(PositionX, PositionY));
		BuildingArrayAddAsLastElement(&Record, B);
		AdvLine();
	}
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
			AdvInt();
			if(X == 1){
				BuildingRelationGraphInsertAdjacentVertex(V, j);
			}
		}
		AdvLine();
	}
}

void CompleteFileLoad()
/* Mengembalikan GameMap yang sudah berisi data lengkap dari file */
{
	GameMapCreate(&G, Map, Record, CurrentPlayer, BuildingRelation);
}
#endif