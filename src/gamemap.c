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
void GameMapCreate(GameMap *G, MapMatrix map, BuildingArray record, Player CurrentPlayer, BuildingRelationGraph BuildingRelation)
/* Membentuk sebuah GameMap yang berisi BuildingMap, BuildingRecord dan currentPlayer */
/* I.S. map, record, dan currentPlayer diinisiasi di luar method sebelum dimasukkan sebagai parameter */
/* F.S. Terbentuk GameMap yang berisi keadaan game pada saat itu*/
{
	BuildingMap(*G) = map;
	BuildingRecord(*G) = record;
	CurrentPlayer(*G) = CurrentPlayer;
	BuildingRelation(*G) = BuildingRelation;
}

///////////////////////////////////
// 	    MAP MATRIX OPERATIONS 	 //
///////////////////////////////////
void GameMapChangePlayer(GameMap *G)
/* Menukar currentPlayer dengan player yang lain */
/* I.S currentPlayer GameMap adalah 1/2 */
/* F.S curretntPlayer GameMap menjadi 2/1 */
{

	if (CurrentPlayer(*G).role == 1)
		CurrentPlayer(*G).role = 2;
	else
		CurrentPlayer(*G).role = 1;
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
	MapMatrixPrintMap(BuildingMap(G));
	BuildingListPrintInfo(PlayerOwnedBuildingList(CurrentPlayer(G)), BuildingRecord(G));
}