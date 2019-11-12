//==============================================//
//								       			//
//					GameMap             		//
//                                     			//
//----------------------------------------------//
// File : gamemap.h */              			//
//----------------------------------------------//
// Definisi ADT GameMap yang menghubungkan		//
// MapMatrix dengan BuildingArray               //
//==============================================//

#ifndef _GAMEMAP_H
#define _GAMEMAP_H

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

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////



///////////////////////////////
// 		Definisi GameMap  	 //
///////////////////////////////
typedef struct
{
    MapMatrix BuildingMap;					/* Matrix peta untuk bangunan */	
    BuildingArray BuildingRecord;			/* Daftar seluruh bangunan di peta */
    Player CurrentPlayer;	   				/* Player yang sedang menjalankan turn saat itu */
    BuildingRelationGraph BuildingRelation;	/* Relasi antar bangunan pada peta */
} GameMap;

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika M adalah GameMap, maka akses elemen : */
#define BuildingMap(G) 			(G).BuildingMap
#define BuildingRecord(G) 		(G).BuildingRecord
#define CurrentPlayer(G)		(G).CurrentPlayer
#define BuildingRelation(G)		(G).BuildingRelation

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void GameMapCreate(GameMap *G, MapMatrix map, BuildingArray record, Player CurrentPlayer, BuildingRelationGraph BuildingRelation);
/* Membentuk sebuah GameMap yang berisi BuildingMap, BuildingRecord dan currentPlayer */
/* I.S. map, record, dan currentPlayer diinisiasi di luar method sebelum dimasukkan sebagai parameter */
/* F.S. Terbentuk GameMap yang berisi keadaan game pada saat itu*/

///////////////////////////////////
// 	    MAP MATRIX OPERATIONS 	 //
///////////////////////////////////
void GameMapChangePlayer(GameMap G);
/* Menukar currentPlayer dengan player yang lain */
/* I.S currentPlayer GameMap adalah 1/2 */
/* F.S curretntPlayer GameMap menjadi 2/1 */

void GameMapPrintInfo(GameMap G);
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
#endif