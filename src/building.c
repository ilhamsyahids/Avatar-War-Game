//==============================================//
//                                              //
//                   Building                   //
//                                              //
//----------------------------------------------//
// File : building.c */                         //
//----------------------------------------------//
// Definisi ADT Building                        //
// Building menjadi tempat semua aksi terjadi   //
// di dalam game                                //
//==============================================//

///////////////////////////
//        INCLUDE        //
///////////////////////////
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "point.h"

///////////////////////////
//        SELECTOR       //
///////////////////////////
int BuildingKind(Building B)
{
    /** Mengembalikan kind building */
    return B.kind;
}

int BuildingPlayer(Building B)
{
    /* Mengembalikan player building */
    return B.player;
}
int BuildingLevel(Building B)
{
    /* Mengembalikan Level building */
    return B.level;
}
int BuildingSoldierCount(Building B)
{
    /* Mengembalikan SoldierCount building */
    return B.soldierCount;
}
int BuildingSoldierAddValue(Building B)
{
    /* Mengembalikan SoldierAddValue building */
    return B.soldierAddValue;
}
int BuildingMaximumSoldierAddCount(Building B)
{
    /* Mengembalikan MaximumSoldierAddCount building */
    return B.maximumSoldierAddCount;
}
int BuildingSoldierAddCount(Building B)
{
    /* Mengembalikan Soldier Count building */
    return B.soldierAddCount;
}
boolean BuildingHasDefense(Building B)
{
    /* Mengembalikan apakah building memiliki defense */
    return B.hasDefense;
}
boolean BuildingHasAttacked(Building B)
{
    /* Mengembalikan apakah building sudah menyerang pada turn tersebut*/
    return B.hasAttacked;
}

POINT BuildingPosition(Building B)
{
    /* Mengembalikan posisi building */
    return B.position;
}

///////////////////////////
//       PROTOTYPE       //
///////////////////////////
int BuildingGetU(int kind)
{
    /* Mengirimkan nilai U untuk kind tertentu */
    int U;
    if (kind == 1)
        U = 40;
    else if (kind == 2)
        U = 30;
    else if (kind == 3)
        U = 80;
    else
        U = 20;
    return U;
}

int BuildingGetA(int kind, int level)
{
    /* Mengirimkan nilai A untuk kind dan level tertentu */
    int A;
    if (kind == 1)
        switch (level)
        {
        case 1:
            A = 10;
            break;
        case 2:
            A = 15;
            break;
        case 3:
            A = 20;
            break;
        default:
            A = 25;
            break;
        }
    else if (kind == 2)
        switch (level)
        {
        case 1:
            A = 5;
            break;
        case 2:
            A = 10;
            break;
        case 3:
            A = 20;
            break;
        default:
            A = 30;
            break;
        }
    else if (kind == 3)
        switch (level)
        {
        case 1:
            A = 10;
            break;
        case 2:
            A = 20;
            break;
        case 3:
            A = 30;
            break;
        default:
            A = 40;
            break;
        }
    else
        switch (level)
        {
        case 1:
            A = 5;
            break;
        case 2:
            A = 10;
            break;
        case 3:
            A = 15;
            break;
        default:
            A = 20;
            break;
        }
    return A;
}

int BuildingGetM(int kind, int level)
{
    /* Mengirimkan nilai M untuk kind dan level tertentu */
    int value;
    if (kind == 1)
        switch (level)
        {
        case 1:
            value = 40;
            break;
        case 2:
            value = 60;
            break;
        case 3:
            value = 80;
            break;
        default:
            value = 100;
            break;
        }
    else if (kind == 2)
        switch (level)
        {
        case 1:
            value = 20;
            break;
        case 2:
            value = 30;
            break;
        case 3:
            value = 40;
            break;
        default:
            value = 50;
            break;
        }
    else if (kind == 3)
        switch (level)
        {
        case 1:
            value = 20;
            break;
        case 2:
            value = 40;
            break;
        case 3:
            value = 60;
            break;
        default:
            value = 80;
            break;
        }
    else
        switch (level)
        {
        case 1:
            value = 20;
            break;
        case 2:
            value = 30;
            break;
        case 3:
            value = 40;
            break;
        default:
            value = 50;
            break;
        }
    return value;
}

boolean BuildingGetP(int kind, int level)
{
    /* Mengirimkan nilai P untuk kind dan level tertentu */
    int value;
    if (kind == 1)
        value = false;
    else if (kind == 2)
        value = true;
    else if (kind == 3)
        switch (level)
        {
        case 1:
            value = false;
            break;
        case 2:
            value = false;
            break;
        case 3:
            value = true;
            break;
        default:
            value = true;
            break;
        }
    else
        value = false;
    return value;
}

char *BuildingGetName(int kind)
{
    /* Mengirimkan nama building dengan kind tertentu */
    char *Name;
    if (kind == 1)
        Name = "Castle";
    else if (kind == 2)
        Name = "Tower";
    else if (kind == 3)
        Name = "Fort";
    else
        Name = "Village";
    return Name;
}

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
Building BuildingCreate(int kind, int player, POINT position)
{
    /* Mengirimkan building yang sudah diset kind, player, level, dan positionnya */
    Building B;
    B.kind = kind;
    B.player = player;
    B.position = position;

    return B;
}

Building BuildingCreateDummy()
{
    /* Mengirimkan building dummy dengan kind 0 */
    Building B;
    B.kind = 0;
    return B;
}

void BuildingInitialize(Building *B)
{
    /* I.S. Atribut B yang telah diset hanya kind, player, dan position */
    /* F.S. Atribut Elemen B lengkap dengan spesifikasi */
    /* level = 1
        soldierCount = U
        soldierAddValue = A
        maximumSoldierCount = M
        isDefended = P
        hasAttacked = false
    */
    /* Proses : Melakukan setup sesuai kind */
    int kind = (*B).kind;
    int level = 1;
    (*B).level = level;
    (*B).soldierCount = BuildingGetU(kind);
    (*B).soldierAddValue = BuildingGetA(kind, level);
    (*B).maximumSoldierAddCount = BuildingGetM(kind, level);
    (*B).soldierAddCount = 0;
    (*B).hasDefense = BuildingGetP(kind, level);
    (*B).hasAttacked = false;
}

void BuildingResetStatus(Building *B)
{
    /* I.S Building telah terisinisialisasi sembarang */
    /* F.S HasAttacked building diset menjadi false */
    (*B).hasAttacked = false;
}

void BuildingRefreshStatus(Building *B)
{
    /* I.S Building telah terisinisialisasi sembarang */
    /* F.S Atribut soldierAddValue maximumSoldierAddCount hasAttacked hasDefense
    diset ulang sesuai level 
    soldierAddCount diset menjadi 0 */

    (*B).soldierAddValue = BuildingGetA(kind, level);
    (*B).maximumSoldierAddCount = BuildingGetM(kind, level);
    (*B).soldierAddCount = 0;
    (*B).hasDefense = BuildingGetP(kind, level);
    (*B).hasAttacked = false;

}

///////////////////////////
//        PREDIKAT       //
///////////////////////////
boolean IsBuildingEmpty(Building B)
{
    /* Mengirimkan apakah pasukan di markas kosong */
    return B.soldierCount <= 0;
}

boolean CanBuildingAddPasukan(Building B)
{
    /* Mengirimkan apakah pasukan di bangunan masih dapat ditambah */
    /* soldierAddCount < maximumSoldierAddCount */
    return B.soldierAddCount < B.maximumSoldierAddCount;
}

boolean IsBuildingLevelMax(Building B)
{
    /* Mengirimkan apakah level bangunan sudah maximum (4) */
    return B.level >= 4;
}

boolean CanBuildingAttack(Building B)
{
    /* Mengirimkan apakah building dapat menyerang */

    return !((B).hasAttacked);
}

boolean CanBuildingLevelUp(Building B)
{
    /* Mengirimkan apakah building dapat level up */
    return (IsBuildingLevelMax(B) || (B.soldierCount < B.maximumSoldierAddCount / 2)) ? false : true;
}

///////////////////////////
//       PRIMITIVES      //
///////////////////////////
void BuildingIncreasePasukan(Building *B, int value)
{
    /* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
    /* F.S. Jumlah pasukan bertambah sesuai parameter value */
    /* Proses: Menambahkan value pada soldierCount dari Building */
    /* Jika jumlah akhir melebihi jumlah pasukan yang dapat ditampung,
        soldierCount akan sama dengan M */
    int count = (*B).soldierCount;
    count += value;
    if (count >= 1000000)
    {
        count = 1000000;
    }

    (*B).soldierCount = count;

    //(*B).solderAddCount += value;
}

void BuildingDecreasePasukan(Building *B, int value)
{
    /* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
    /* F.S. Jumlah pasukan berkurang sesuai parameter value */
    /* Proses: Mengurangkan value pada soldierCount dari Building */
    /* Jika jumlah akhir kurang dari 0, soldierCount akan menjadi 0 */
    int count = (*B).soldierCount;
    count += value;
    if (count <= 0)
    {
        count = 0;
    }

    (*B).soldierCount = count;
}

void BuildingChangePlayer(Building *B)
{
    /* I.S. Bangunan ke-index BL terdefinisi milik salah satu player */
    /* F.S. Bangunan ke-index BL berubah kepemilikan menjadi player yang lain */
    /* Proses: Mengganti nilai atribut player pada Building dan kembali inisialisasi Building. */
    int player = ((*B).player == 1) ? 2 : 1;
    (*B).player = player;
}

void BuildingLevelUp(Building *B)
{
    /* I.S. Bangunan ke-index BL sudah terdefinisi*/
    /* F.S. Atribut building akan menjadi sbb: */
    /* Level bertambah 1 dan soldierCount berkurang sebesar M/2 */
    /* Atau : Level tetap karena sudah maksimum atau soldierCount kurang (berikan prompt) */
    /* Proses: Mengecek apakah levelup bisa dilakukan, jika bisa FS1 jika tidak FS2 */
    if (CanBuildingLevelUp(*B))
    {
        (*B).level += 1;
        (*B).soldierCount -= (*B).maximumSoldierAddCount / 2;
        BuildingRefreshStatus(B);
    }
    else
    {
        printf("Jumlah pasukan %s kurang untuk level up\n", BuildingGetName((*B).kind));
    }
}

//////////////////////////////////
//      BUILDING OPERATIONS     //
//////////////////////////////////
void BuildingPrintInfo(Building B)
{
    /* Mencetak isi info Building B ke layar */
    /* I.S. B terdefinisi */
    /* F.S. B tercetak ke layar dengan format:
        <Nama Bangunan> <(Posisi)> <Jumlah Pasukan> <Level>
        */

    printf("%s ", BuildingGetName(B.kind));
    TulisPOINT(B.position);
    printf(" %d ", B.soldierCount);
    printf("lv. %d", B.level);
}