/* File : commands.c */
/* Berisi list command yang bisa dilakukan pemain pada suatu turn */

///////////////////////////
//        INCLUDE        //
///////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gamemap.h>

void Attack(GameMap G)
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
	Player P;
	BuildingArray T = BuildingRecord(G);
	BuildingRelationGraph GG = BuildingRelation(G);
	if (CurrentPlayer(G) == 1)
		P = Player1(G);
	else
		P = Player2(G);

	int UsedBuildingIdx, AttackedBuildingIdx, UsedSoldier;
	int i = 1;
	printf("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P, T);
	do
	{
		printf("Bangunan yang digunakan untuk menyerang: ");
		scanf("%d", &UsedBuildingIdx); // memilih bangunan untuk menyerang
	} while (UsedBuildingIdx > BuildingListNbElmt(PlayerOwnedBuildingList(P)) || (UsedBuildingIdx <= 0));

	BuildingListAddress BB = BuildingListFirstAddress(PlayerOwnedBuildingList(P));
	while (i < UsedBuildingIdx)
	{
		i++;
		BB = BuildingListElementNext(BB);
	}
	BuildingArrayElType *SelectedBuilding = &T.TI[BuildingListElementInfo(BB)];

	i = 1;

	BuildingRelationGraphAddress V = BuildingRelationGraphFirstAddress(GG);
	AdjacentBuildingRelationGraphAddress PP = BuildingRelationGraphVertexFirstAdjacent(V);
	int num = 1;
	BuildingArrayElType *AttackedBuilding;
	Building AttackedArray[50];
	BuildingListInfotype AttackedArrayIdx[50];
	if (PP != BuildingRelationGraphNil)
	{
		printf("Daftar bangunan yang dapat diserang: \n");
		while (PP != BuildingRelationGraphNil)
		{
			AttackedBuilding = &BuildingArrayElement(T, BuildingRelationGraphAdjacentVertexInfo(PP));
			if (BuildingPlayer(*AttackedBuilding) != CurrentPlayer(G))
			{
				printf("%d. ", num);
				num++;
				BuildingPrintInfo(*AttackedBuilding);
				printf("\n");
				AttackedArray[num] = *AttackedBuilding;
				AttackedArrayIdx[num] = BuildingRelationGraphAdjacentVertexInfo(PP);
			}
			PP = BuildingRelationGraphAdjacentVertexNextAdjacent(PP);
		}
		// printf("%d\n", BuildingRelationGraphAdjacentVertexInfo(PP));
		do
		{
			printf("Bangunan yang diserang: ");
			scanf("%d", &AttackedBuildingIdx);
		} while ((AttackedBuildingIdx > num - 1) || (AttackedBuildingIdx < 1));

		*AttackedBuilding = AttackedArray[AttackedBuildingIdx + 1];
		printf("Jumlah pasukan: ");
		scanf("%d", &UsedSoldier);
		BuildingSoldierCount(*SelectedBuilding) -= UsedSoldier;

		boolean success = false;
		if (BuildingHasDefense(*AttackedBuilding))
		{
			UsedSoldier *= (0.75);
		}

		if (UsedSoldier < BuildingSoldierCount(*AttackedBuilding))
		{
			BuildingSoldierCount(*AttackedBuilding) -= UsedSoldier;
			BuildingPrintInfo(*AttackedBuilding);
		}
		else if (UsedSoldier == BuildingSoldierCount(*AttackedBuilding))
		{
			success = true;

			BuildingSoldierCount(*AttackedBuilding) = 0;
			BuildingPrintInfo(*AttackedBuilding);
		}
		else
		{ // UsedSoldier > BuildingSoldierCount(T.TI[AttackedBuildingIdx])
			success = true;
			BuildingSoldierCount(*AttackedBuilding) = (-1) * (BuildingSoldierCount(*AttackedBuilding) - UsedSoldier);
		}

		if (success)
		{
			BuildingChangePlayer(AttackedBuilding);
			BuildingPrintInfo(*AttackedBuilding);
			BuildingListInsertValueLast(&PlayerOwnedBuildingList(P), AttackedArrayIdx[num]);
			printf("Bangunan menjadi milikmu!\n");
		}
		else
			printf("Bangunan gagal direbut.\n");
	}
	else
	{
		printf("Tidak ada bangunan yang dapat diserang\n");
	}
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
	if (IsBuildingLevelMax(BuildingElmt))
		printf("Level %s-mu sudah maksimum!\n", BuildingGetName(BuildingKind(BuildingElmt)));
	else
	{
		BuildingLevelUp(&BuildingElmt);
		if (CanBuildingLevelUp(BuildingElmt))
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