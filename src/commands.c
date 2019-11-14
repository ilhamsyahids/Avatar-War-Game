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
		BuildingSoldierCount(T.TI[i]) -= UsedSoldier;

		boolean success;
		// skenario attack

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
		} 
	}
}

void skill;

void undo;

void end_turn;
void move ();
void exit;

#endif