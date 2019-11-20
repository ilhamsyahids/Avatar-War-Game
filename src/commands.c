#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

void attack(Player P, BuildingArray T) {
	idx UsedBuildingIdx, AttackedBuildingIdx, UsedSoldier;
	writeln("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P,T);
	printf("Bangunan yang digunakan untuk menyerang: ");
	do {
		UsedBuildingIdx = scanf("%d",&UsedBuildingIdx); // memilih bangunan untuk menyerang
	} while ((UsedBuildingIdx > 0) && (UsedBuildingIdx <= T.Neff));
	
	if (/*bangunan ada yang terhubung*/) {
		printf("Daftar bangunan yang dapat diserang: ");
		// cetak bangunan lawan yg berhubungan
		printf("Bangunan yang diserang: ");
		scanf("%d", &AttackedBuildingIdx);
		printf("Jumlah pasukan: ");
		scanf("%d",&UsedSoldier);
		BuildingSoldierCount(T.TI[UsedBuildingIdx]) -= UsedSoldier;

		boolean success = false;
		if (BuildingHasDefense(T.TI[AttackedBuildingIdx])) {
			UsedSoldier *= (0.75);
		}
		// skenario attack
		if (UsedSoldier < BuildingSoldierCount(T.TI[AttackedBuildingIdx])) {
				// kepemilikan tetap
				// soldier di bangunan lawan berkurang
				BuildingSoldierCount(T.TI[AttackedBuildingIdx]) -= UsedSoldier;

			} else if (UsedSoldier = BuildingSoldierCount(T.TI[AttackedBuildingIdx])) {
				success = true;
				// kepemilikan berpindah
				// soldier di bangunan tsb: 0
				BuildingSoldierCount(T.TI[AttackedBuildingIdx]) = 0;
			} else { // UsedSoldier > BuildingSoldierCount(T.TI[AttackedBuildingIdx])
				success = true;
				// kepemilikan berpindah
				// soldier di bangunan tsb = soldier lawan - soldier pemain
				BuildingSoldierCount(T.TI[AttackedBuildingIdx]) -= UsedSoldier;
				if (BuildingHasDefense(T.TI[AttackedBuildingIdx])) { 
					BuildingSoldierCount(T.TI[AttackedBuildingIdx]) *= (4/3);
				}
			}
			
		if (success) printf("Bangunan menjadi milikmu!\n");
		else printf("Bangunan gagal direbut.\n"); // attack failed
	} else { // bangunan tidak ada yg terhubung 
		printf("Tidak ada bangunan yang dapat diserang\n");
	}
}

void level_up(Player P, BuildingArray T) {
	int BuildingIdx;
	BuildingArrayElType BuildingElmt;
	printf("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P,T);
	printf("Bangunan yang akan di level up: ");
	scanf("%d",&BuildingIdx);
	if (IsBuildingLevelMax) printf("Level %s-mu sudah maksimum!\n", ); 
	else {
		BuildingElmt = T.TI[BuildingIdx];
		BuildingLevelUp(&BuildingElmt);
		if (CanBuildingLevelUp(&BuildingElmt)) {
				printf("Level %s-mu meningkat menjadi %d!\n", BuildingGetName(BuildingKind(BuildingElmt)), BuildingLevel(BuildingElmt));
		} else printf("Jumlah pasukan %s kurang untuk level up\n", BuildingGetName(BuildingKind(BuildingElmt)))
	}
}

void skill();

void undo();

// void end_turn();

void move (Player P, BuildingArray T) {
	int BuildingIdx1, BuildingIdx2, UsedSoldier;
	BuildingArrayElType Building1, Building2;
	printf("Daftar bangunan:\n");
	PlayerPrintOwnedBuilding(P,T);
	printf("Pilih bangunan: ");
	scanf("%d",&BuildingIdx1);
	Building1 = T.TI[BuildingIdx1];
	printf("Daftar bangunan terdekat: ");
	// print bangunan terhubung
	printf("Bangunan yang akan menerima: ");
	scanf("%d",&BuildingIdx2);
	Building2 = T.TI[BuildingIdx2];
	printf("Jumlah pasukan: ")
	scanf("%d",&UsedSoldier);

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

#endif