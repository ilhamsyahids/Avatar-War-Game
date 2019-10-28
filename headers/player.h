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

///////////////////////
//  Definisi Player  //
///////////////////////
typedef struct {
    int role;  	 /* [1..2] menandakan Player 1, 2 menandakan Player 2*/

    char color; /* Color disesuaikan dengan yang tersedia di pcolor.h
                    R, G, Y, B, M, C */

    BuildingArray playerBuildingList; /* Akan dirubah menjadi Building List
                                        berisi list bangunan pemain */

    int totalSoldier; /* Jumlah total pasukan pada bangunan yang dimiliki */
    
    SkillQueue playerSkillQueue; /* SKillQueue yang dimiliki player*/
} Player;

///////////////////////////
//      SELECTOR GET     //
///////////////////////////
int PlayerRole(Player P);
/* Mengirimkan role player, player 1 atau 2 */

char PlayerColor(Player P)
/* Mengirimkan char yang berisi penanda warna player */

BuildingArray PlayerBuildingList(Player P);
/* Mengirimkan List bangunan pemain */
/* BuildingArray akan diganti menjadi BuildingList*/

int PlayerTotalSoldier(Player P);
/* Mengirimkan jumlah total pasukan pada bangunan yang dimiliki player */

SkillQueue PlayerSkillQueue(Player P);
/* Mengirimkan SkillQueue player pada saat itu */

int PlayerBuildingCount(Player P);


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
