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

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////



///////////////////////////////
// 		Definisi GameMap  	 //
///////////////////////////////
typedef struct
{
    MapMatrix BuildingMap;			/* Matrix peta untuk bangunan */	
    BuildingArray BuildingRecord;	/* Daftar seluruh bangunan di peta */
    Player currentPlayer;	   		/* Player yang sedang menjalankan turn saat itu */
} GameMap;

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika M adalah GameMap, maka akses elemen : */
#define BuildingMap(M) 			(M).BuildingMap
#define BuildingRecord(M) 		(M).BuildingRecord
#define CurrentPlayer(M)		(M).currentPlayer

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void GameMapCreate(MapMatrix map, BuildingArray record, Player currentPlayer);
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