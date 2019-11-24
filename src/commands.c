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

	int UsedBuildingIdx, AttackedBuildingIdx, UsedSoldier, GuardSoldier;
	int i = 1;
	BuildingList CanAttackBuildingList;

	printf("Daftar bangunan:\n");
	CanAttackBuildingList = PlayerGetOwnedCanAttackBuilding(P, T);
	PlayerPrintOwnedCanAttackBuilding(P, T);
	//PlayerPrintOwnedBuilding(P, T);
	if(BuildingListNbElmt(CanAttackBuildingList) > 0){
		do
		{
			printf("Bangunan yang digunakan untuk menyerang: ");
			scanf("%d", &UsedBuildingIdx); // memilih bangunan untuk menyerang
		} while (UsedBuildingIdx > BuildingListNbElmt(CanAttackBuildingList) || (UsedBuildingIdx <= 0));

		BuildingListAddress BB = BuildingListFirstAddress(CanAttackBuildingList);
		while (i < UsedBuildingIdx)
		{
			i++;
			BB = BuildingListElementNext(BB);
		}
		BuildingArrayElType *SelectedBuilding = &BuildingArrayElement(T, BuildingListElementInfo(BB));
		
		if(BuildingSoldierCount(*SelectedBuilding) > 0){
			i = 1;

			BuildingRelationGraphAddress V = BuildingRelationGraphAddressSearch(GG, BuildingListElementInfo(BB));
			AdjacentBuildingRelationGraphAddress PP = BuildingRelationGraphVertexFirstAdjacent(V);
			int num = 1;
			
			////////////////////
			//  DANGER POINT  //
			////////////////////

			Building TempBuilding;
			Building *DecidedBuilding;
			int AttackedBuilding;
			int AttackedArray[50];
			BuildingListInfotype AttackedArrayIdx[50];
			if (PP != BuildingRelationGraphNil)
			{
				printf("Daftar bangunan yang dapat diserang: \n");
				while (PP != BuildingRelationGraphNil)
				{
					AttackedBuilding = BuildingRelationGraphAdjacentVertexInfo(PP);
					TempBuilding = BuildingArrayElement(BuildingRecord(*G), AttackedBuilding);
					if (BuildingPlayer(TempBuilding) != CurrentPlayer(*G))
					{
						printf("%d. ", num);
						BuildingPrintInfo(TempBuilding);
						printf("\n");
						AttackedArray[num] = AttackedBuilding;
						AttackedArrayIdx[num] = AttackedBuilding;
						

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

					AttackedBuilding = AttackedArray[AttackedBuildingIdx];
					TempBuilding = BuildingArrayElement(BuildingRecord(*G), AttackedBuilding);
					DecidedBuilding = &BuildingArrayElement(BuildingRecord(*G), AttackedBuilding);
					printf("Jumlah pasukan: ");
					do{
						scanf("%d", &UsedSoldier);
					} while(UsedSoldier > BuildingSoldierCount(*SelectedBuilding) || UsedSoldier <= 0);
					

					BuildingDecreasePasukan(SelectedBuilding, UsedSoldier);
					boolean success = false;
					GuardSoldier = BuildingSoldierCount(*DecidedBuilding);
					if (BuildingHasDefense(*DecidedBuilding))
					{
						GuardSoldier *= 4;
						GuardSoldier /= 3;
					}

					if (UsedSoldier < GuardSoldier)
					{
						BuildingDecreasePasukan(DecidedBuilding, UsedSoldier);
						BuildingPrintInfo(*DecidedBuilding);
					}
					else if (UsedSoldier == GuardSoldier)
					{
						success = true;

						BuildingSoldierCount(*DecidedBuilding) = 0;
						//BuildingPrintInfo(*DecidedBuilding);
					}
					else
					{ // UsedSoldier > BuildingSoldierCount(*AttackedBuilding)
						success = true;
						BuildingSoldierCount(*DecidedBuilding) = (-1) * (GuardSoldier - UsedSoldier);
						//BuildingPrintInfo(*DecidedBuilding);
					}

					BuildingHasAttacked(*SelectedBuilding) = true;

					if (success)
					{
						
						BuildingChangePlayer(DecidedBuilding, CurrentPlayer(*G));
						BuildingPrintInfo(*DecidedBuilding);
						BuildingListInsertValueLast(&PlayerOwnedBuildingList(P), AttackedArrayIdx[AttackedBuildingIdx]);
						
						//BuildingPrintInfo(BuildingArrayElement(BuildingRecord(*G), 13));
						
			///////////////////////////
			//  END OF DANGER POINT  //
			///////////////////////////

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
		} else{
			printf("Bangunan yang kamu pilih tidak memiliki pasukan\n");
		}
	} else{
		printf("Kamu tidak punya bangunan yang bisa menyerang\n");
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

void skill(GameMap *G)
/* 	Digunakan untuk memakai skill yang sedang dimiliki oleh pemain. */
{
	Player *P;
	if(CurrentPlayer(*G) == 1){
		P = &Player1(*G);
	} else if(CurrentPlayer(*G) == 2){
		P = &Player2(*G);
	}
	
	if(!IsSkillQueueEmpty(PlayerCurrentSkillQueue((*P)))){
		Skill UsedSkill;

		SkillQueueDelSkill(&PlayerCurrentSkillQueue((*P)), &UsedSkill);
		if(SkillKind(UsedSkill) == 1){
			printf("1");
			BuildingArrayLevelUpOwnedPlayerBuilding(&BuildingRecord(*G), PlayerRole(*P));
		} else if(SkillKind(UsedSkill) == 2){
			GameMapSetNextPlayer(G, CurrentPlayer(*G));
		} else if(SkillKind(UsedSkill) == 3){
			printf("3");
			BuildingArrayIncreasePlayerOwnedPasukanBuilding(&BuildingRecord(*G), PlayerRole(*P), 5);
		} else if(SkillKind(UsedSkill) == 4){
			printf("4");
			if(CurrentPlayer(*G) == 1){
				BuildingArrayDecreasePlayerOwnedPasukanBuilding(&BuildingRecord(*G), 2, 10);
			} else if (CurrentPlayer(*G) == 2){
				BuildingArrayDecreasePlayerOwnedPasukanBuilding(&BuildingRecord(*G), 1, 10);
			}
		}

		//printf("kosong : %d\n", IsSkillQueueEmpty(PlayerCurrentSkillQueue(P))); 
	} else{
		printf("Kamu tidak memiliki skill yang dapat digunakan!\n");
	}		
}
void undo();
/* 	Digunakan untuk membatalkan perintah terakhir. */
/* 	Pemain hanya dapat melakukan UNDO hingga command sesudah END_TURN/SKILL. 
	Artinya, setelah command END_TURN/SKILL, pemain tidak dapat melakukan UNDO lagi. */

void end_turn(GameMap *G)
/* 	Digunakan untuk mengakhiri giliran dari pemain. */
{
	//GameMapChangePlayer(G);
	//BuildingArrayResetAllBuilding(&BuildingRecord(*G));
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
	BuildingList CanMoveBuildingList;

	printf("Daftar bangunan:\n");
	CanMoveBuildingList = PlayerGetOwnedCanMoveBuilding(P,T);
	PlayerPrintOwnedCanMoveBuilding(P,T);
	//PlayerPrintOwnedBuilding(P, T);
	if(BuildingListNbElmt(CanMoveBuildingList) > 0){
		do
		{
			printf("Pilih bangunan: ");
			scanf("%d", &UsedBuildingIdx); // memilih bangunan untuk menyerang
		} while (UsedBuildingIdx > BuildingListNbElmt(CanMoveBuildingList) || (UsedBuildingIdx <= 0));

		BuildingListAddress BB = BuildingListFirstAddress(CanMoveBuildingList);
		while (i < UsedBuildingIdx)
		{
			i++;
			BB = BuildingListElementNext(BB);
		}
		BuildingArrayElType *SelectedBuilding = &BuildingArrayElement(T, BuildingListElementInfo(BB));

		if(BuildingSoldierCount(*SelectedBuilding) > 0){
			BuildingRelationGraphAddress V = BuildingRelationGraphAddressSearch(GG, BuildingListElementInfo(BB));
			AdjacentBuildingRelationGraphAddress PP = BuildingRelationGraphVertexFirstAdjacent(V);
			int num = 1;
			
			////////////////////
			//  DANGER POINT  //
			////////////////////

			Building TempBuilding;
			Building *DestBuilding;
			int DestinationBuilding;
			int DestArray[50];
			BuildingListInfotype DestArrayIdx[50];
			if (PP != BuildingRelationGraphNil)
			{
				printf("Daftar bangunan yang dapat dituju: \n");
				while (PP != BuildingRelationGraphNil)
				{	
					DestinationBuilding = BuildingRelationGraphAdjacentVertexInfo(PP);
					TempBuilding = BuildingArrayElement(BuildingRecord(*G), DestinationBuilding);
					if (BuildingPlayer(TempBuilding) == CurrentPlayer(*G))
					{
						printf("%d. ", num);
						BuildingPrintInfo(TempBuilding);
						printf("\n");
						DestArray[num] = DestinationBuilding;
						DestArrayIdx[num] = DestinationBuilding;
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

					DestinationBuilding = DestArray[DestBuildingIdx];
					DestBuilding = &BuildingArrayElement(BuildingRecord(*G), DestinationBuilding);
					printf("Jumlah pasukan: ");
					do{
						scanf("%d", &UsedSoldier);
					} while(UsedSoldier > BuildingSoldierCount(*SelectedBuilding) || UsedSoldier <= 0);
					

					BuildingDecreasePasukan(SelectedBuilding, UsedSoldier);
					BuildingIncreasePasukan(DestBuilding, UsedSoldier);

					printf("%d pasukan dari ", UsedSoldier);
					BuildingPrintInfo(*SelectedBuilding);
					printf(" telah berpindah ke");
					BuildingPrintInfo(*DestBuilding);
					printf("\n");

					BuildingHasMovedPasukan(*SelectedBuilding) = true;
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
		} else{
			printf("Bangunan yang kamu pilih tidak memiliki pasukan\n");
		}
	} else{
		printf("Kamu tidak punya bangunan yang bisa memindahkan pasukan\n");
	}
	
}
// agar sekali?

// void exit();
/* 	Digunakan untuk keluar dari permainan/program. */