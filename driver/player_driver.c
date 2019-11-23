#include "player.h"

int main(){
	BuildingArray B;
	Building BB;
	Player Player1, Player1Copy;

	
	int i;
	int j;
	Point P;
	BuildingArrayCreateEmpty(&B, 3);
	Player1 = PlayerCreate(1, 'b');
	

	BB = BuildingCreate(1, 1, PointCreate(1,1));
	BuildingArrayAddAsLastElement(&B, BB);
	
	
	BB = BuildingCreate(2, 0, PointCreate(2,3));
	BuildingArrayAddAsLastElement(&B, BB);


	BB = BuildingCreate(3, 1, PointCreate(3,2));
	BuildingArrayAddAsLastElement(&B, BB);

	PlayerInitialize(&Player1, B);

	PlayerPrintCurrentStatus(Player1, B);

	Player1Copy = PlayerCopyPlayer(Player1, B);

	PlayerPrintCurrentStatus(Player1Copy, B);

	BuildingListInsertValueLast(&PlayerOwnedBuildingList(Player1), 2);
	
	PlayerPrintCurrentStatus(Player1, B);
	PlayerPrintCurrentStatus(Player1Copy, B);

	return 0;
}
