/* File : building.h */
/* Definisi ADT Building dengan representasi array secara implisit dan alokasi dinamik */
/* Elemen Building terurut berdasarkan nomor building */

#ifndef _building_H
#define _building_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "arraydin.h"
#include "point.h"

/* Definisi elemen Building */
typedef struct
{
    int kind;                   /* [1..4] Menandakan jenis bangunan */
                                /*  1 = Castle
                                    2 = Tower
                                    3 = Fort
                                    4 = Village */
    int player;                 /* [0..2] Menandakan player mana yang memiliki bangunan */
                                /*  0 = No Player
                                    1 = Player 1
                                    2 = Player 2 */
    int level;                  /* [0..4] Level dari bangunan */
    int soldierCount;           /* Jumlah pasukan yang ada di bangunan */
    int soldierAddValue;        /* A = Nilai penambahan pasukan */
    int maximumSoldierAddCount; /* M = Batas atas jumlah penambahan pasukan di bangunan */
    int soldierAddCount;        /* Menandakan berapa banyak pasukan yang telah ditambah */
    boolean isDefended;         /* Boolean untuk menandakan apakah bangunan dilindungi */
    boolean hasAttacked;
    POINT position; /* Posisi bangunan dalam map */
} Building;

/* Definisi List Building dengan implementasi array dinamik*/
typedef struct
{
    Building *T; /* tabel penyimpan elemen */
    int NBElmt;  /* Jumlah elemen list sekarang */
    int MaxEl;   /* Max elemen list */
} BuildingList;

/* ********* AKSES (Selektor) ********* */
/* Jika B adalah Building, maka akses elemen : */
#define kind(B) (B).kind
#define player(B) (B).player
#define level(B) (B).level
#define soldierCount(B) (B).soldierCount
#define soldierAddValue(B) (B).soldierAddValue
#define maximumSoldierAddCount(B) (B).maximumSoldierAddCount
#define soldierAddCount(B) (B).soldierAddCount
#define isDefended(B) (B).isDefended
#define hasAttacked(B) (B).hasAttacked
#define position(B) (B).position

/* ********* Prototype ********* */
int NBElmt(BuildingList BL);
/* Mengirimkan banyaknya jumlah building sekarang */

int MaxElmt(BuildingList BL);
/* Mengirimkan maksimum banyaknya jumlah building sekarang */

Building BuildingElmt(BuildingList BL, int index);
/* Mengirimkan building ke-index dari BL */

int UForBuilding(int kind);
/* Mengirimkan nilai U untuk kind tertentu */

int AForBulding(int kind, int level);
/* Mengirimkan nilai A untuk kind dan level tertentu */

int MForBuilding(int kind, int level);
/* Mengirimkan nilai M untuk kind dan level tertentu */

boolean PForBuilding(int kind, int level);
/* Mengirimkan nilai P untuk kind dan level tertentu */

/* *** Kreator *** */
void CreateEmptyBuildingList(BuildingList *BL, int Max);
/* I.S. sembarang */
/* F.S. Sebuah BL kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasikan tipe Building berukuran Max+1 */
/* atau : jika alokasi gagal, BL kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah BL kosong */

void CreateBuilding(BuildingList *BL, int kind, int player, POINT position);
/* I.S. sembarang atau tidak penuh */
/* F.S. Elemen BL bertembah dengan bangunan bertipe kind di posisi position */
/* Proses : Melakukan penambahan bangunan pada NBElmt + 1 dan */
/* Set kind dan position sesuai parameter */

void InitializeBuilding(Building *B);
/* I.S. Atribut B yang telah diset hanya kind, player, dan position */
/* F.S. Atribut Elemen B lengkap dengan spesifikasi */
/* level = 0
   soldierCount = U
   soldierAddValue = A
   maximumSoldierCount = M
   isDefended = P
*/
/* Proses : Melakukan setup sesuai kind */

/* *** Predikat *** */
boolean isPasukanEmpty(Building B);
/* Mengirimkan apakah pasukan di markas kosong */

boolean canAddPasukan(Building B);
/* Mengirimkan apakah pasukan di bangunan masih dapat ditambah */
/* soldierAddCount < maximumSoldierAddCount */

boolean isLevelMax(Building B);
/* Mengirimkan apakah level bangunan sudah maximum (4) */

/* *** Destruktor *** */
void DeAlokasi(BuildingList *BL);
/* Proses: Mengembalikan memori BL */
/* I.S. BL pernah dialokasi */
/* F.S. BL menjadi tidak terdefinisi lagi, MaxEl dan NBElmt diset 0 */

/* *** Primitif *** */
char *GetBuildingName(int kind);
/* Mengirimkan nama building dengan kind tertentu */

void IncreasePasukan(BuildingList *BL, int index, int value);
/* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
/* F.S. Jumlah pasukan bertambah sesuai parameter value */
/* Proses: Menambahkan value pada soldierCount dari Building */
/* Jika jumlah akhir melebihi jumlah pasukan yang dapat ditampung,
   soldierCount akan sama dengan M */

void DecreasePasukan(BuildingList *BL, int index, int value);
/* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
/* F.S. Jumlah pasukan berkurang sesuai parameter value */
/* Proses: Mengurangkan value pada soldierCount dari Building */
/* Jika jumlah akhir kurang dari 0, soldierCount akan menjadi 0 */

void IncreaseAllPasukan(BuildingList *BL);
/* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
/* F.S. Jumlah pasukan bertambah sesuai nilai atribut A dari masing-masing building */
/* Proses: Menambahkan nilai atribut A pada soldierCount dari tiap Building */

void DecreaseAllPasukan(BuildingList *BL);
/* I.S. Jumlah pasukan bangunan ke-index BL sudah terdefinisi */
/* F.S. Jumlah pasukan berkurang sesuai nilai atribut A dari masing-masing building */
/* Proses: Mengurangkan nilai atribut A pada soldierCount dari tiap Building */

void ChangePlayer(BuildingList *BL, int index);
/* I.S. Bangunan ke-index BL terdefinisi milik salah satu player */
/* F.S. Bangunan ke-index BL berubah kepemilikan menjadi player yang lain */
/* Proses: Mengganti nilai atribut player pada Building dan kembali inisialisasi Building. */

void LevelUpBuilding(BuildingList *BL, int index);
/* I.S. Bangunan ke-index BL sudah terdefinisi*/
/* F.S. Atribut building akan menjadi sbb: */
/* Level bertambah 1 dan soldierCount berkurang sebesar M/2 */
/* Atau : Level tetap karena sudah maksimum atau soldierCount kurang (berikan prompt) */
/* Proses: Mengecek apakah levelup bisa dilakukan, jika bisa FS1 jika tidak FS2 */

/* Operasi Tambahan */
Building *GetPlayerBuildingPointer(BuildingList BL, int player);
/* Mengirimkan list pointer ke building yang dimiliki seorang player */

Building *GetCorrelatedBuildingPointer(BuildingList BL, int index);
/* Mengirimkan list pointer ke building yang berhubungan dengan building ke-index di BL*/

void PrintPlayerBuilding(BuildingList BL, int player);
/* Menampilkan ke layar building yang dimiliki seorang player */

void PrintCorrelatedBuilding(Building *BL, int index);
/* Menampilkan ke layar building yang berhubungan dengan building ke-index di BL */

void PrintBuildingInfo(Building B);
/* Mencetak isi info Building B ke layar */
/* I.S. B terdefinisi */
/* F.S. B tercetak ke layar dengan format:
<Nama Bangunan> <(Posisi)> <Jumlah Pasukan> <Level>
*/

void PrintBuildingList(BuildingList BL);
/* Mencetak isi info semua Building di BuildingList ke layar */
/* I.S. BL */
/* F.S. BL tercetak ke layar dengan format:
<index> <Nama Bangunan> <(Posisi)> <Jumlah Pasukan> <Level>
....
....
*/

#endif
