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
		CurrentPlayer(*G) = 1;
	} else if(role == 2){
		CurrentPlayer(*G) = 2;
	}
}

void GameMapSetNextPlayer(GameMap *G, int role)
/* Mengeset NextPlayer menjadi sesuai role */
/* I.S. NextPlayer sembarang */
/* F.S. NextPlayer menjadi Player1 (jika role 1) dan sebaliknya */
{
	if(role == 1){
		NextPlayer(*G) = 1;
	} else if(role == 2){
		NextPlayer(*G) = 2;
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
/* Menukar currentPlayer dengan NextPlayer */
/* I.S currentPlayer GameMap adalah 1/2 */
/* F.S curretntPlayer GameMap menjadi 2/1 */
{

	if (NextPlayer(*G) == 1){
		CurrentPlayer(*G) = 1;
		NextPlayer(*G) = 2;
	}
	else if(NextPlayer(*G) == 2){
		CurrentPlayer(*G) = 2;
		NextPlayer(*G) = 1;
	}
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
	printf("======================================\n");
	if((CurrentPlayer(G)) == 1){
		printf("====          Player 1 Turn        ===\n");
	} else{
		printf("====          Player 2 Turn        ===\n");
	}
	printf("======================================\n");
	MapMatrixPrintMap(BuildingMap(G), BuildingRecord(G));
	BuildingListPrintInfo(PlayerOwnedBuildingList(GameMapGetCurrentPlayer(G)), BuildingRecord(G));
	PrintQueueSkill(PlayerCurrentSkillQueue(GameMapGetCurrentPlayer(G)));
}

GameMap GameMapCopyCurrentMap(GameMap G)
/* Mengirimkan salinan dari GameMap G menjadi GameMap yang baru dan independen */
{
	GameMap GCopy;
	MapMatrix MapCopy;
	BuildingArray RecordCopy;
	int CurrentPlayerCopy;
	int NextPlayerCopy;
	Player Player1Copy;
	Player Player2Copy;
	BuildingRelationGraph RelationCopy;

	MapCopy = BuildingMap(G);
	RecordCopy = BuildingArrayCopyArray(BuildingRecord(G));
	CurrentPlayerCopy = CurrentPlayer(G);
	NextPlayerCopy = NextPlayer(G);
	Player1Copy = PlayerCopyPlayer(Player1(G), RecordCopy);
	Player2Copy = PlayerCopyPlayer(Player2(G), RecordCopy);
	RelationCopy = BuildingRelation(G);

	GameMapCreate(&GCopy, MapCopy, RecordCopy, Player1Copy, Player2Copy, RelationCopy);
	GameMapSetCurrentPlayer(&GCopy, CurrentPlayerCopy);

	return GCopy;

}

///////////////////////////////
// STILL BUGGING DONT USE!!! //
///////////////////////////////
Player GameMapGetCurrentPlayer(GameMap G)
/* Mengembalikan player yang sedang menjalani turnnya dari GameMap */
{
	if(CurrentPlayer(G) == 1){
		return Player1(G);
	} else {
		return Player2(G);
	}
	
}

