//==============================================//
//								       			//
//					GameMap             		//
//                                     			//
//----------------------------------------------//
// File : gamemap.c */              			//
//----------------------------------------------//
// Definisi ADT GameMap yang menghubungkan		//
// MapMatrix dengan BuildingArray               //
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "mapmatrix.h"
#include "buildingarray.h"
#include "player.h"
#include "buildingrelationgraph.h"
#include "gamemap.h"

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void GameMapCreate(GameMap *G, MapMatrix map, BuildingArray record, Player Player1, Player Player2, BuildingRelationGraph BuildingRelation)
/* Membentuk sebuah GameMap yang berisi BuildingMap, BuildingRecord dan currentPlayer */
/* I.S. map, record, Player1, Player2 diinisiasi di luar method sebelum dimasukkan sebagai parameter */
/* F.S. Terbentuk GameMap yang berisi keadaan game pada saat itu*/
{
	BuildingMap(*G) = map;
	BuildingRecord(*G) = record;
	Player1(*G) = Player1;
	Player2(*G) = Player2;
	BuildingRelation(*G) = BuildingRelation;
}

///////////////////////////////////
// 	    MAP MATRIX OPERATIONS 	 //
///////////////////////////////////
void GameMapSetCurrentPlayer(GameMap *G, int role)
/* Mengeset CurrentPlayer menjadi sesuai role */
/* I.S. CurrentPlayer sembarang */
/* F.S. CurrentPlayer menjadi Player1 (jika role 1) dan sebaliknya */
{
	if(role == 1){
		CurrentPlayer(*G) = Player1(*G);
	} else{
		CurrentPlayer(*G) = Player2(*G);
	}
}
void GameMapInitializeAllComponents(GameMap *G)
/* Menginisialisasi semua komponen pada GameMap kecuali CurrentPlayer */
/* I.S. BuildingMap, BuildingRecord, Player1, Player2, BuildingRelation belum diinisialisasi */
/* F.S. Semua komponen kecuali CurrentPlayer terinisialisasi dan siap pakai */
{
	// Initialize Building
	BuildingArrayInitializeAllBuilding(&BuildingRecord(*G));
	
	// Initialize Player
	PlayerInitialize(&(Player1(*G)),BuildingRecord(*G));
	PlayerInitialize(&(Player2(*G)),BuildingRecord(*G));
}

void GameMapChangePlayer(GameMap *G)
/* Menukar currentPlayer dengan player yang lain */
/* I.S currentPlayer GameMap adalah 1/2 */
/* F.S curretntPlayer GameMap menjadi 2/1 */
{

	if (CurrentPlayer(*G).role == 1)
		CurrentPlayer(*G) = Player2(*G);
	else
		CurrentPlayer(*G) = Player1(*G);
}

void GameMapPrintInfo(GameMap G)
/* Mencetak info GameMap sebagai berikut */
/* [MapMatrixPrintMap(BuildingMap(G))]
	******
	*X   *
	*   Y*
	*Z   *
	******
	Player <PlayerRole(CurrentPlayer(G))>
	Daftar Building:[BuildingListPrintInfo(PlayerOwnedBuildingList(CurrentPlayer(G)))]
	1. X (1,1) 30 Lv. 1
	2....
	..
	[Print(SkillGetAcronym(SkillKind(SkillQueueInfoHead(PlayerCurrentSkillQueue(CurrentPlayer(G))))))]   
	Available Skill: IU

*/
{
	MapMatrixPrintMap(BuildingMap(G), BuildingRecord(G));
	BuildingListPrintInfo(PlayerOwnedBuildingList(CurrentPlayer(G)), BuildingRecord(G));
	PrintQueueSkill(PlayerCurrentSkillQueue(CurrentPlayer(G)));
}