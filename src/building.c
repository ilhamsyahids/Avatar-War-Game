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
#include "building.h"

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
Building BuildingCreate(int kind, int player, Point position)
{
    /* Mengirimkan building yang sudah diset kind, player, level, dan positionnya */
    Building B;

    BuildingKind(B) = kind;
    BuildingPlayer(B) = player;
    BuildingPosition(B) = position;
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
        hasDefense = P
        hasAttacked = false
        hasMovedPasukan = false
    */
    /* Proses : Melakukan setup sesuai kind */

    int kind = BuildingKind(*B);
    int level = 1;

    BuildingLevel(*B) = level;
    BuildingSoldierCount(*B) = BuildingGetU(kind);
    BuildingSoldierAddValue(*B) = BuildingGetA(kind, level);
    BuildingMaximumSoldierAddCount(*B) = BuildingGetM(kind, level);
    BuildingSoldierAddCount(*B) = 0;
    BuildingHasDefense(*B) = BuildingGetP(kind, level);
    BuildingHasAttacked(*B) = false;
    BuildingHasMovedPasukan(*B) = false;
}

///////////////////////////
//        PREDIKAT       //
///////////////////////////
boolean IsBuildingEmpty(Building B)
{
    /* Mengirimkan apakah pasukan di markas kosong */
    return (BuildingSoldierCount(B) <= 0);
}

boolean CanBuildingAddPasukan(Building B)
{
    /* Mengirimkan apakah pasukan di bangunan masih dapat ditambah */
    /* soldierAddCount < maximumSoldierAddCount */
    return (BuildingSoldierAddCount(B) < BuildingMaximumSoldierAddCount(B));
}

boolean IsBuildingLevelMax(Building B)
{
    /* Mengirimkan apakah level bangunan sudah maximum (4) */
    return (BuildingLevel(B) >= 4);
}

boolean CanBuildingAttack(Building B)
{
    /* Mengirimkan apakah building dapat menyerang */

    return (!BuildingHasAttacked(B));
}

boolean CanBuildingLevelUp(Building B)
{
    /* Mengirimkan apakah building dapat level up */

    return (IsBuildingLevelMax(B) || (BuildingSoldierCount(B) < (BuildingMaximumSoldierAddCount(B) / 2))) ? false : true;
}

/////////////////////////////////////
//       BUILDING OPERATIONS       //
/////////////////////////////////////
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

char BuildingGetAcronym(int kind)
/* Mengirimkan akronim nama building untuk kind tertentu */
{
    char Acronym;
    if (kind == 1)
        Acronym = 'C';
    else if (kind == 2)
        Acronym = 'T';
    else if (kind == 3)
        Acronym = 'F';
    else
        Acronym = 'V';
    return Acronym;
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

void BuildingPrintInfo(Building B)
{
    /* Mencetak isi info Building B ke layar */
    /* I.S. B terdefinisi */
    /* F.S. B tercetak ke layar dengan format:
        <Nama Bangunan> <(Posisi)> <Jumlah Pasukan> <Level>
        */
    printf("%s ", BuildingGetName(B.kind));
    PointPrint(BuildingPosition(B));
    printf(" %d ", BuildingSoldierCount(B));
    printf("lv. %d", BuildingLevel(B));
}

void BuildingResetStatus(Building *B)
{
    /* I.S Building telah terisinisialisasi sembarang */
    /* F.S hasAttacked dan hasMovedPasukan building diset menjadi false */
    BuildingHasAttacked(*B) = false;
    BuildingHasMovedPasukan(*B) = false;
}

void BuildingRefreshStatus(Building *B)
{
    /* I.S Building telah terisinisialisasi sembarang */
    /* F.S Atribut soldierAddValue maximumSoldierAddCount hasDefense
    diset ulang sesuai level 
    soldierAddCount diset menjadi 0 */
    int kind = BuildingKind(*B);
    int level = BuildingLevel(*B);

    BuildingSoldierAddValue(*B) = BuildingGetA(kind, level);
    BuildingMaximumSoldierAddCount(*B) = BuildingGetM(kind, level);
    BuildingSoldierAddCount(*B) = 0;
    BuildingHasDefense(*B) = BuildingGetP(kind, level);
}

void BuildingIncreasePasukan(Building *B, int value)
{
    /* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
    /* F.S. Jumlah pasukan bertambah sesuai parameter value */
    /* Proses: Menambahkan value pada soldierCount dari Building */
    /* Jika jumlah akhir melebihi jumlah pasukan yang dapat ditampung,
        soldierCount akan sama dengan M */
    int count = BuildingSoldierCount(*B);

    count += value;
    if (count >= 1000000)
    {
        count = 1000000;
    }

    BuildingSoldierCount(*B) = count;
}

void BuildingDecreasePasukan(Building *B, int value)
{
    /* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
    /* F.S. Jumlah pasukan berkurang sesuai parameter value */
    /* Proses: Mengurangkan value pada soldierCount dari Building */
    /* Jika jumlah akhir kurang dari 0, soldierCount akan menjadi 0 */
    int count = BuildingSoldierCount(*B);

    count -= value;
    if (count <= 0)
    {
        count = 0;
    }

    BuildingSoldierCount(*B) = count;
}

void BuildingChangePlayer(Building *B, int role)
{
    /* I.S. Bangunan ke-index BL terdefinisi milik salah satu player */
    /* F.S. Bangunan ke-index BL berubah kepemilikan menjadi player yang lain */
    /* Proses: Mengganti nilai atribut player pada Building dan kembali inisialisasi Building. */
    //int player = (BuildingPlayer(*B) == 1) ? 2 : 1;
    BuildingLevel(*B) = 1;
    BuildingPlayer(*B) = role;
    BuildingRefreshStatus(B);
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
        int nextLevel = (BuildingLevel(*B) + 1);
        int soldierDecreasedValue = (BuildingSoldierCount(*B) - (BuildingMaximumSoldierAddCount(*B) / 2));
        BuildingLevel(*B) = nextLevel;
        BuildingSoldierCount(*B) = soldierDecreasedValue;

        BuildingRefreshStatus(B);
    }
    else
    {
        printf("Jumlah pasukan %s kurang untuk level up\n", BuildingGetName((*B).kind));
    }
}
