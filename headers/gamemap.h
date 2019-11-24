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

///////////////////////////////
// 		Definisi GameMap  	 //
///////////////////////////////
typedef struct
{
	MapMatrix BuildingMap;					/* Matrix peta untuk bangunan */
	BuildingArray BuildingRecord;			/* Daftar seluruh bangunan di peta */
	int CurrentPlayer;						/* Player yang sedang menjalankan turn saat itu */
	int NextPlayer;							/* Player yang akan menjalankan turn selanjutnya */
	Player Player1;							/* Detail player 1 pada game */
	Player Player2;							/* Detail player 2 pada game */
	BuildingRelationGraph BuildingRelation; /* Relasi antar bangunan pada peta */
} GameMap;

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika M adalah GameMap, maka akses elemen : */
#define BuildingMap(G) (G).BuildingMap
#define BuildingRecord(G) (G).BuildingRecord
#define CurrentPlayer(G) (G).CurrentPlayer
#define NextPlayer(G) (G).NextPlayer
#define Player1(G) (G).Player1
#define Player2(G) (G).Player2
#define BuildingRelation(G) (G).BuildingRelation

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void GameMapCreate(GameMap *G, MapMatrix map, BuildingArray record, Player Player1, Player Player2, BuildingRelationGraph BuildingRelation);
/* Membentuk sebuah GameMap yang berisi BuildingMap, BuildingRecord dan currentPlayer */
/* I.S. map, record, currentPlayer, Player1, Player2 diinisiasi di luar method sebelum dimasukkan sebagai parameter */
/* F.S. Terbentuk GameMap yang berisi keadaan game pada saat itu*/

///////////////////////////////////
// 	    MAP MATRIX OPERATIONS 	 //
///////////////////////////////////
void GameMapSetCurrentPlayer(GameMap *G, int role);
/* Mengeset CurrentPlayer menjadi sesuai role */
/* I.S. CurrentPlayer sembarang */
/* F.S. CurrentPlayer menjadi Player1 (jika role 1) dan sebaliknya */

void GameMapSetNextPlayer(GameMap *G, int role);
/* Mengeset NextPlayer menjadi sesuai role */
/* I.S. NextPlayer sembarang */
/* F.S. NextPlayer menjadi Player1 (jika role 1) dan sebaliknya */

void GameMapInitializeAllComponents(GameMap *G);
/* Menginisialisasi semua komponen pada GameMap kecuali CurrentPlayer */
/* I.S. BuildingMap, BuildingRecord, Player1, Player2, BuildingRelation belum diinisialisasi */
/* F.S. Semua komponen kecuali CurrentPlayer terinisialisasi dan siap pakai */

void GameMapChangePlayer(GameMap *G);
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

GameMap GameMapCopyCurrentMap(GameMap G);
/* Mengirimkan salinan dari GameMap G menjadi GameMap yang baru dan independen */

Player GameMapGetCurrentPlayer(GameMap G);
/* Mengembalikan player yang sedang menjalani turnnya dari GameMap */

#endif