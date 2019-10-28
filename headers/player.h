//==============================================//
//                                              //
//                  Player                      //
//                                              //
//----------------------------------------------//
// File : player.h */                           //
//----------------------------------------------//
// Definisi ADT player                          //
// ADT player akan merepresentasikan player     //
// selama keberjalanan game                     //
//==============================================//

#ifndef _PLAYER_H
#define _PLAYER_H

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "buildingarray.h"
#include "skillqueue.h"
#include "buildinglist.h"

///////////////////////
//  Definisi Player  //
///////////////////////
typedef struct {
    int role;  	 /* [1..2] menandakan Player 1, 2 menandakan Player 2*/

    char color; /* Color disesuaikan dengan yang tersedia di pcolor.h
                    R, G, Y, B, M, C */

    BuildingList ownedBuildingList; /* Berisi index bangunan pemain yang mengacu
                                        ke BuildingArray */

    int totalSoldier; /* Jumlah total pasukan pada bangunan yang dimiliki */
    
    SkillQueue currentSkillQueue; /* SKillQueue yang dimiliki player*/
} Player;

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika P adalah Player, maka akses elemen : */
#define PlayerRole(P)               (P).role
#define PlayerColor(P)              (P).color
#define PlayerOwnedBuildingList(P)  (P).ownedBuildingList
#define PlayerTotalSoldier(P)       (P).totalSoldier
#define PlayerCurrentSkillQueue(P)  (P).currentSkillQueue

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
Player PlayerCreate(int role, int color);
/* Mengembalikan Player yang baru diset role dan colornya saja */

void PlayerInitialize(Player *P);
/* Menginisialisasi atribut lain dari P yang belum diset */
/* I.S. P sudah dibuat dengan PlayerCreate */
/* F.S. playerBuildingList, totalSoldier, dan playerSkillQueue diset */
/* Proses : playerBuildingList didapat dari memfilter BuildingArray di Map sesuai player
            totalSoldier didapat dari mentotal pasukan bangunan yang dimiliki
            playerSkillQueue adalah inisiasi empty dari skillqueue yang kemudian
            dimasukkan skill Instant Upgrade */


//////////////////////////////////
//      PLAYER OPERATIONS       //
//////////////////////////////////
void PlayerPrintCurrentStatus(Player P);
/* Mencetak status player sekarang ke layar */
/* I.S. P terdefinisi */
/* F.S. P tercetak ke layar dengan format:
Player <PlayerRole>
1. <Building-1 Name> <Position> <SoldierCount> lv. <Level>
..
..
Skill Available : <Skill Name>
*/

void PlayerPrintOwnedBuilding(Player P, BuildingArray T);
/* Mencetak bangunan yang dimiliki player ke layar */
/* I.S. P dan T terdefinisi */
/* F.S. bangunan tercetak ke layar dengan format :
1. <Building-1 Name> <Position> <SoldierCount> lv. <Level>
..
..
*/
/* Proses: PlayerOwnedBuildingList berisi index bangunan player pada
            BuildingArray, maka untuk setiap index pada list ambil bangunan yang
            berkorespondensi pada T */

void PlayerRefreshStatus(Player P, BuildingArray T);
/* Memperbarui PlayerOwnedBuildingList dengan BuildingArray terbaru,
kemudian menghitung kembali total pasukan */
/* I.S. P dan T terdefinisi */
/* F.S. PlayerOwnedBuildingList dan PlayerTotalSoldier diperbaharui */
/* Proses : Jika Bangunan milik player di T tidak ada di list, masukkan di belakang
            Jika ada, maka biarkan
            Setelah T selesai diiterasi, hitung jumlah seluruh pasukan */

int PlayerBuildingCount(Player P);
/* Mengembalikan berapa banyak bangunan yang dimiliki player */

int PlayerSoldierCount(Player P);
/* Mengembalikan total berapa banyak pasukan yang dimiliki player */

#endif