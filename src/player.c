//==============================================//
//                                              //
//                  Player                      //
//                                              //
//----------------------------------------------//
// File : player.c*/                           //
//----------------------------------------------//
// Definisi ADT player                          //
// ADT player akan merepresentasikan player     //
// selama keberjalanan game                     //
//==============================================//

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
#include "player.h"

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
Player PlayerCreate(int role, int color)
/* Mengembalikan Player yang baru diset role dan colornya saja */
{
    Player P;

    PlayerRole(P) = role;
    PlayerColor(P) = color;

    return P;
}

void PlayerInitialize(Player *P, BuildingArray T)
/* Menginisialisasi atribut lain dari P yang belum diset */
/* I.S. P sudah dibuat dengan PlayerCreate */
/* F.S. playerBuildingList, totalSoldier, dan playerSkillQueue diset */
/* Proses : playerBuildingList didapat dari memfilter BuildingArray di Map sesuai player
            totalSoldier didapat dari mentotal pasukan bangunan yang dimiliki
            playerSkillQueue adalah inisiasi empty dari skillqueue yang kemudian
            dimasukkan skill Instant Upgrade */
{
    BuildingList BL;
    SkillQueue S;
    int total;

    // Create Building List and Skill queue
    BuildingListCreateEmpty(&BL);
    SkillQueueCreateEmpty(&S);
    total = 0;

    // Filter BuildingArray
    for(int i = 1; i <= BuildingArrayNeff(T); i++){
        if(BuildingPlayer(BuildingArrayElement(T, i)) == PlayerRole(*P)){
            BuildingListInsertValueLast(&BL,i);
            total += BuildingSoldierCount(BuildingArrayElement(T, i));
        }
    }

    // Initialize Skill
    SkillQueueAddSkill(&S, SkillCreate(1));
    
    PlayerOwnedBuildingList(*P) = BL;
    PlayerTotalSoldier(*P) = total;
    PlayerCurrentSkillQueue(*P) = S;


}


//////////////////////////////////
//      PLAYER OPERATIONS       //
//////////////////////////////////
void PlayerPrintCurrentStatus(Player P, BuildingArray T)
/* Mencetak status player sekarang ke layar */
/* I.S. P terdefinisi */
/* F.S. P tercetak ke layar dengan format:
Player <PlayerRole>
1. <Building-1 Name> <Position> <SoldierCount> lv. <Level>
..
..
Skill Available : <Skill Name>
*/
{
    printf("Player %d\n", PlayerRole(P));
    PlayerPrintOwnedBuilding(P, T);
    PrintQueueSkill(PlayerCurrentSkillQueue(P));
    printf("\n");
}

void PlayerPrintOwnedBuilding(Player P, BuildingArray T)
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
{
    BuildingListAddress V;
    int i;

    V = BuildingListFirstAddress(PlayerOwnedBuildingList(P));
    i = 1;

    if(V){
        Building B = BuildingArrayElement(T,BuildingListElementInfo(V));
        printf("%d. ", i);
        char* name = BuildingGetName(BuildingKind(B));
        printf("%s ", name);
        PointPrint(BuildingPosition(B));
        printf(" %d ", BuildingSoldierCount(B));
        printf("lv. %d\n", BuildingLevel(B));       
    }

    while(BuildingListElementNext(V) != BuildingListNil){
        i += 1;
        V = BuildingListElementNext(V);
        Building B = BuildingArrayElement(T,BuildingListElementInfo(V));
        printf("%d. ", i);
        char* name = BuildingGetName(BuildingKind(B));
        printf("%s ", name);
        PointPrint(BuildingPosition(B));
        printf(" %d ", BuildingSoldierCount(B));
        printf("lv. %d\n", BuildingLevel(B));  
    }
}

void PlayerRefreshStatus(Player *P, BuildingArray T)
/* Memperbarui PlayerOwnedBuildingList dengan BuildingArray terbaru,
kemudian menghitung kembali total pasukan */
/* I.S. P dan T terdefinisi */
/* F.S. PlayerOwnedBuildingList dan PlayerTotalSoldier diperbaharui */
/* Proses : Jika Bangunan milik player di T tidak ada di list, masukkan di belakang
            Jika ada, maka biarkan
            Setelah T selesai diiterasi, hitung jumlah seluruh pasukan */
{
    BuildingList BL;
    int total;
    SkillQueue S;

    // Create Building List and Skill queue
    BuildingListCreateEmpty(&BL);
    SkillQueueCreateEmpty(&S);
    total = 0;

    // Filter BuildingArray
    for(int i = 1; i <= BuildingArrayNeff(T); i++){
        if(BuildingPlayer(BuildingArrayElement(T, i)) == PlayerRole(*P)){
            BuildingListInsertValueLast(&BL,i);
            total += BuildingSoldierCount(BuildingArrayElement(T, i));
        }
    }

    PlayerOwnedBuildingList(*P) = BL;
    PlayerTotalSoldier(*P) = total;
}

int PlayerBuildingCount(Player P)
/* Mengembalikan berapa banyak bangunan yang dimiliki player */
{
    return BuildingListNbElmt(PlayerOwnedBuildingList(P));
}

int PlayerSoldierCount(Player P)
/* Mengembalikan total berapa banyak pasukan yang dimiliki player */
{
    return PlayerTotalSoldier(P);
}

Player PlayerCopyPlayer(Player P, BuildingArray T)
/* Mengirimkan salinan dari Player P menjadi Player yang baru */
{
    Player PlayerCopy;
    int RoleCopy;
    char ColorCopy;

    RoleCopy = PlayerRole(P);
    ColorCopy = PlayerColor(P);

    PlayerCopy = PlayerCreate(RoleCopy, ColorCopy);

    PlayerInitialize(&PlayerCopy, T);

    return PlayerCopy;

}