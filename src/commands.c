/* File : commands.c */
/* Berisi list command yang bisa dilakukan pemain pada suatu turn */

///////////////////////////
//        INCLUDE        //
///////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <boolean.h>
#include <player.h>
#include <buildinglist.h>

void attack(Player P, BuildingArray T)
/* 	Digunakan untuk melakukan serangan ke bangunan lain. */
/* 	Jika X < Y, maka bangunan yang diserang tetap menjadi milik lawan, namun
	berkurang jumlah pasukannya di bangunan itu menjadi Y - X. Jumlah pasukan di
	bangunan yang menyerang berkurang sebanyak X. */
/* 	Jika X >= Y, maka bangunan yang diserang menjadi milik penyerang, dan memiliki
	jumlah pasukan (X - Y). Jumlah pasukan di bangunan yang menyerang berkurang
	sebanyak X. */
/*  Dalam kasus dimana bangunan yang diserang memiliki pertahanan, nilai serang akan
	menjadi kurang dari X. */
/* 	Bila bangunan berpindah kepemilikan, level akan kembali menjadi 1. */
{
	BuildingArrayIdxType UsedBuildingIdx, AttackedBuildingIdx, UsedSoldier;
	writeln("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P, T);
	printf("Bangunan yang digunakan untuk menyerang: ");
	do
	{
		UsedBuildingIdx = scanf("%d", &UsedBuildingIdx); // memilih bangunan untuk menyerang
	} while ((UsedBuildingIdx > 0) && (UsedBuildingIdx <= T.Neff));

	// if (/*bangunan ada yang terhubung*/)
	// {
	printf("Daftar bangunan yang dapat diserang: ");
	// cetak bangunan lawan yg berhubungan
	printf("Bangunan yang diserang: ");
	scanf("%d", &AttackedBuildingIdx);
	printf("Jumlah pasukan: ");
	scanf("%d", &UsedSoldier);
	BuildingSoldierCount(T.TI[UsedBuildingIdx]) -= UsedSoldier;

	boolean success = false;
	if (BuildingHasDefense(T.TI[AttackedBuildingIdx]))
	{
		UsedSoldier *= (0.75);
	}
	// skenario attack
	if (UsedSoldier < BuildingSoldierCount(T.TI[AttackedBuildingIdx]))
	{
		// kepemilikan tetap
		// soldier di bangunan lawan berkurang
		BuildingSoldierCount(T.TI[AttackedBuildingIdx]) -= UsedSoldier;
	}
	else if (UsedSoldier = BuildingSoldierCount(T.TI[AttackedBuildingIdx]))
	{
		success = true;
		// kepemilikan berpindah
		// soldier di bangunan tsb: 0
		BuildingSoldierCount(T.TI[AttackedBuildingIdx]) = 0;
	}
	else
	{ // UsedSoldier > BuildingSoldierCount(T.TI[AttackedBuildingIdx])
		success = true;
		// kepemilikan berpindah
		// soldier di bangunan tsb = soldier lawan - soldier pemain
		BuildingSoldierCount(T.TI[AttackedBuildingIdx]) -= UsedSoldier;
		if (BuildingHasDefense(T.TI[AttackedBuildingIdx]))
		{
			BuildingSoldierCount(T.TI[AttackedBuildingIdx]) *= (4 / 3);
		}
	}

	if (success)
		printf("Bangunan menjadi milikmu!\n");
	else
		printf("Bangunan gagal direbut.\n"); // attack failed
											 // }
											 // else
											 // { // bangunan tidak ada yg terhubung
											 // 	printf("Tidak ada bangunan yang dapat diserang\n");
											 // }
}

void level_up(Player P, BuildingArray T)
/* 	Digunakan untuk menaikkan level dari suatu bangunan. Dalam satu giliran, level up
	dapat dilakukan berkali-kali. */
/* 	F.S. Jika pasukan yang dimiliki cukup, level bangunan bertambah 1. */
/*	Jika pasukan yang dimiliki kurang, level bangunan tetap. */
{
	int BuildingIdx;
	BuildingArrayElType BuildingElmt;
	printf("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P, T);
	printf("Bangunan yang akan di level up: ");
	scanf("%d", &BuildingIdx);
	BuildingElmt = T.TI[BuildingIdx];
	if (IsBuildingLevelMax)
		printf("Level %s-mu sudah maksimum!\n", BuildingGetName(BuildingKind(BuildingElmt)));
	else
	{
		BuildingLevelUp(&BuildingElmt);
		if (CanBuildingLevelUp(&BuildingElmt))
		{
			printf("Level %s-mu meningkat menjadi %d!\n", BuildingGetName(BuildingKind(BuildingElmt)), BuildingLevel(BuildingElmt));
		}
		else
			printf("Jumlah pasukan %s kurang untuk level up\n", BuildingGetName(BuildingKind(BuildingElmt)));
	}
}

void skill();
/* 	Digunakan untuk memakai skill yang sedang dimiliki oleh pemain. */

void undo();
/* 	Digunakan untuk membatalkan perintah terakhir. */
/* 	Pemain hanya dapat melakukan UNDO hingga command sesudah END_TURN/SKILL. 
	Artinya, setelah command END_TURN/SKILL, pemain tidak dapat melakukan UNDO lagi. */

// void end_turn();
/* 	Digunakan untuk mengakhiri giliran dari pemain. */

void move(Player P, BuildingArray T)
/* 	Digunakan untuk memindahkan pasukan dari suatu bangunan ke bangunan lain 
	milik pemain yang terhubung dengan bangunan tersebut. 
	MOVE hanya dapat dilakukan sekali untuk tiap bangunan pada tiap gilirannya. */
{
	int BuildingIdx1, BuildingIdx2, UsedSoldier;
	BuildingArrayElType Building1, Building2;
	printf("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P, T);
	printf("Pilih bangunan: ");
	scanf("%d", &BuildingIdx1);
	Building1 = T.TI[BuildingIdx1];
	printf("Daftar bangunan terdekat: ");
	// print bangunan terhubung
	printf("Bangunan yang akan menerima: ");
	scanf("%d", &BuildingIdx2);
	Building2 = T.TI[BuildingIdx2];
	printf("Jumlah pasukan: ");
	scanf("%d", &UsedSoldier);

	// move
	BuildingSoldierCount(Building1) -= UsedSoldier;
	BuildingSoldierCount(Building2) += UsedSoldier;

	printf("%d pasukan dari %s ", UsedSoldier, BuildingGetName(BuildingKind(Building1)));
	PointPrint(BuildingPosition(Building1));
	printf(" telah berpindah ke %s ", BuildingGetName(BuildingKind(Building2)));
	PointPrint(BuildingPosition(Building2));
	printf("\n");
}
// agar sekali?

// void exit();
/* 	Digunakan untuk keluar dari permainan/program. */