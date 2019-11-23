/* File : commands.c */
/* Berisi list command yang bisa dilakukan pemain pada suatu turn */

///////////////////////////
//        INCLUDE        //
///////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gamemap.h>

void Attack(GameMap *G)
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
	Player P = GameMapGetCurrentPlayer(*G);
	BuildingArray T = BuildingRecord(*G);
	BuildingRelationGraph GG = BuildingRelation(*G);

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
	BuildingArrayElType *SelectedBuilding = &BuildingArrayElement(T, BuildingListElementInfo(BB));

	i = 1;

	BuildingRelationGraphAddress V = BuildingRelationGraphAddressSearch(GG, BuildingListElementInfo(BB));
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
			if (BuildingPlayer(*AttackedBuilding) != CurrentPlayer(*G))
			{
				printf("%d. ", num);
				BuildingPrintInfo(*AttackedBuilding);
				printf("\n");
				AttackedArray[num] = *AttackedBuilding;
				AttackedArrayIdx[num] = BuildingRelationGraphAdjacentVertexInfo(PP);
				num++;
			}
			PP = BuildingRelationGraphAdjacentVertexNextAdjacent(PP);
		}

		if (num != 1)
		{

			do
			{
				printf("Bangunan yang diserang: ");
				scanf("%d", &AttackedBuildingIdx);
			} while ((AttackedBuildingIdx > num - 1) || (AttackedBuildingIdx < 1));

			*AttackedBuilding = AttackedArray[AttackedBuildingIdx];
			printf("Jumlah pasukan: ");
			scanf("%d", &UsedSoldier);

			BuildingDecreasePasukan(SelectedBuilding, UsedSoldier);

			boolean success = false;
			if (BuildingHasDefense(*AttackedBuilding))
			{
				UsedSoldier *= (0.75);
			}

			if (UsedSoldier < BuildingSoldierCount(*AttackedBuilding))
			{
				BuildingDecreasePasukan(AttackedBuilding, UsedSoldier);
				BuildingPrintInfo(*AttackedBuilding);
			}
			else if (UsedSoldier == BuildingSoldierCount(*AttackedBuilding))
			{
				success = true;

				BuildingSoldierCount(*AttackedBuilding) = 0;
				BuildingPrintInfo(*AttackedBuilding);
			}
			else
			{ // UsedSoldier > BuildingSoldierCount(*AttackedBuilding)
				success = true;
				BuildingSoldierCount(*AttackedBuilding) = (-1) * (BuildingSoldierCount(*AttackedBuilding) - UsedSoldier);
			}

			if (success)
			{
				BuildingChangePlayer(AttackedBuilding);
				BuildingPrintInfo(*AttackedBuilding);
				BuildingListInsertValueLast(&PlayerOwnedBuildingList(P), AttackedArrayIdx[AttackedBuildingIdx]);
				printf("\nBangunan menjadi milikmu!\n");
			}
			else
				printf("Bangunan gagal direbut.\n");
		}
		else
		{
			printf("Tidak ada bangunan yang dapat diserang\n");
		}
	}
	else
	{
		printf("Tidak ada bangunan yang dapat diserang\n");
	}
}

void level_up(GameMap *G)
/* 	Digunakan untuk menaikkan level dari suatu bangunan. Dalam satu giliran, level up
	dapat dilakukan berkali-kali. */
/* 	F.S. Jika pasukan yang dimiliki cukup, level bangunan bertambah 1. */
/*	Jika pasukan yang dimiliki kurang, level bangunan tetap. */
{
	Player P = GameMapGetCurrentPlayer(*G);
	BuildingArray T = BuildingRecord(*G);
	BuildingRelationGraph GG = BuildingRelation(*G);

	int UsedBuildingIdx;
	int i = 1;
	printf("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P, T);
	do
	{
		printf("Bangunan yang akan di level up: ");
		scanf("%d", &UsedBuildingIdx); // memilih bangunan untuk menyerang
	} while (UsedBuildingIdx > BuildingListNbElmt(PlayerOwnedBuildingList(P)) || (UsedBuildingIdx <= 0));

	BuildingListAddress BB = BuildingListFirstAddress(PlayerOwnedBuildingList(P));
	while (i < UsedBuildingIdx)
	{
		i++;
		BB = BuildingListElementNext(BB);
	}
	BuildingArrayElType *SelectedBuilding = &BuildingArrayElement(T, BuildingListElementInfo(BB));

	if (IsBuildingLevelMax(*SelectedBuilding))
		printf("Level %s-mu sudah maksimum!\n", BuildingGetName(BuildingKind(*SelectedBuilding)));
	else
	{
		if (CanBuildingLevelUp(*SelectedBuilding))
		{
			BuildingLevelUp(SelectedBuilding);
			printf("Level %s-mu meningkat menjadi %d!\n", BuildingGetName(BuildingKind(*SelectedBuilding)), BuildingLevel(*SelectedBuilding));
		}
		else
			printf("Jumlah pasukan %s kurang untuk level up\n", BuildingGetName(BuildingKind(*SelectedBuilding)));
	}
}

void skill();
/* 	Digunakan untuk memakai skill yang sedang dimiliki oleh pemain. */

void undo();
/* 	Digunakan untuk membatalkan perintah terakhir. */
/* 	Pemain hanya dapat melakukan UNDO hingga command sesudah END_TURN/SKILL. 
	Artinya, setelah command END_TURN/SKILL, pemain tidak dapat melakukan UNDO lagi. */

void end_turn(GameMap *G)
/* 	Digunakan untuk mengakhiri giliran dari pemain. */
{
	GameMapChangePlayer(G);
	BuildingArrayRefreshAllBuilding(&BuildingRecord(*G));
}

void move(GameMap *G)
/* 	Digunakan untuk memindahkan pasukan dari suatu bangunan ke bangunan lain 
	milik pemain yang terhubung dengan bangunan tersebut. 
	MOVE hanya dapat dilakukan sekali untuk tiap bangunan pada tiap gilirannya. */
{
	Player P = GameMapGetCurrentPlayer(*G);
	BuildingArray T = BuildingRecord(*G);
	BuildingRelationGraph GG = BuildingRelation(*G);

	int UsedBuildingIdx, DestBuildingIdx, UsedSoldier;
	int i = 1;
	printf("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P, T);
	do
	{
		printf("Pilih bangunan: ");
		scanf("%d", &UsedBuildingIdx); // memilih bangunan untuk menyerang
	} while (UsedBuildingIdx > BuildingListNbElmt(PlayerOwnedBuildingList(P)) || (UsedBuildingIdx <= 0));

	BuildingListAddress BB = BuildingListFirstAddress(PlayerOwnedBuildingList(P));
	while (i < UsedBuildingIdx)
	{
		i++;
		BB = BuildingListElementNext(BB);
	}
	BuildingArrayElType *SelectedBuilding = &BuildingArrayElement(T, BuildingListElementInfo(BB));

	BuildingRelationGraphAddress V = BuildingRelationGraphAddressSearch(GG, BuildingListElementInfo(BB));
	AdjacentBuildingRelationGraphAddress PP = BuildingRelationGraphVertexFirstAdjacent(V);
	int num = 1;
	BuildingArrayElType *DestBuilding;
	Building DestArray[50];
	BuildingListInfotype DestArrayIdx[50];
	if (PP != BuildingRelationGraphNil)
	{
		printf("Daftar bangunan yang dapat dituju: \n");
		while (PP != BuildingRelationGraphNil)
		{
			DestBuilding = &BuildingArrayElement(T, BuildingRelationGraphAdjacentVertexInfo(PP));
			if (BuildingPlayer(*DestBuilding) == CurrentPlayer(*G))
			{
				printf("%d. ", num);
				BuildingPrintInfo(*DestBuilding);
				printf("\n");
				DestArray[num] = *DestBuilding;
				DestArrayIdx[num] = BuildingRelationGraphAdjacentVertexInfo(PP);
				num++;
			}
			PP = BuildingRelationGraphAdjacentVertexNextAdjacent(PP);
		}

		if (num != 1)
		{
			do
			{
				printf("Bangunan tujuan: ");
				scanf("%d", &DestBuildingIdx);
			} while ((DestBuildingIdx > num - 1) || (DestBuildingIdx < 1));

			*DestBuilding = DestArray[DestBuildingIdx];
			printf("Jumlah pasukan: ");
			scanf("%d", &UsedSoldier);

			BuildingDecreasePasukan(SelectedBuilding, UsedSoldier);
			BuildingIncreasePasukan(DestBuilding, UsedSoldier);

			printf("%d pasukan dari ", UsedSoldier);
			BuildingPrintInfo(*SelectedBuilding);
			printf(" telah berpindah ke");
			BuildingPrintInfo(*DestBuilding);
			printf("\n");
		}
		else
		{
			printf("Tidak ada tujuan bangunan yang tersedia\n");
		}
	}
	else
	{
		printf("Tidak ada tujuan bangunan yang tersedia\n");
	}
}
// agar sekali?

// void exit();
/* 	Digunakan untuk keluar dari permainan/program. */