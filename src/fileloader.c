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
// 	     FILELOADER OPERATIONS 	 //
///////////////////////////////////
void CompleteFileLoad()
/* Mengembalikan GameMap yang sudah berisi data lengkap dari file */
{
	CurrentPlayer = Player1;
	GameMapCreate(&GameState, Map, Record, CurrentPlayer, BuildingRelation);
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
	AdvChar();
	AdvInt();
	PositionX = X;
	AdvInt();
	PositionY = X;
	P = PointCreate(PositionX, PositionY);
	B = BuildingCreate(1, 1, P);
	printf("%d\n", BuildingArrayNeff(Record));
	printf("%d\n", BuildingArrayMaxElement(Record));
	BuildingArrayAddAsLastElement(&Record, B);
	MapMatrixElement(Map, P) = 1;
	AdvLine();

	
	// Load Player 2's Castle
	AdvChar();
	AdvInt();
	PositionX = X;
	AdvInt();
	PositionY = X;
	P = PointCreate(PositionX, PositionY);
	B = BuildingCreate(1, 2, P);
	BuildingArrayAddAsLastElement(&Record, B);
	MapMatrixElement(Map, P) = 2;
	AdvLine();

	// Load Other Buildings
	for(i = 1; i <= BuildingArrayMaxElement(Record) - 2; i++){
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
		P = PointCreate(PositionX, PositionY);
		B = BuildingCreate(kind, 0, P);
		BuildingArrayAddAsLastElement(&Record, B);
		MapMatrixElement(Map, P) = i + 2;
		AdvLine();
	}
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



void LoadMapSize()
/* Menangani pembacaan ukuran peta dari file */
/* I.S : Map sembarang */
/* F.S : Ukuran Map efektif terdefinisi */
{
	int MapCol;
	int MapRow;

	AdvInt();
	MapRow = X;

	AdvInt();
	MapCol = X;

	MapMatrixCreateEmpty(&Map, MapRow, MapCol);

	AdvLine();

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


void StartLoading(char* filename)
/* Memulai pembacaan dari file konfigurasi */
/* I.S : Pita file kosong */
/* F.S : File siap dibaca dan sekuens pembacaan dimulai */
{
	OpenFile(filename);
	Player1 = PlayerCreate(1, 'b');
	Player2 = PlayerCreate(2, 'r');
	LoadingSequence();
}

#endif