#include <stdio.h>
#include "gamemap.h"
#include "fileloader.h"

int main(){
	StartLoading("pitakar.txt");
	CompleteFileLoad();

	MapMatrixPrintMap(BuildingMap(GameState), BuildingRecord(GameState));

	for(int i = 1; i <= BuildingArrayNeff(BuildingRecord(GameState)); i++){
		BuildingInitialize(&(BuildingArrayElement(BuildingRecord(GameState), i)));
		
	}

	for(int i = 1; i <= BuildingArrayNeff(BuildingRecord(GameState)); i++){
		BuildingPrintInfo(BuildingArrayElement(BuildingRecord(GameState), i));
		printf("\n");
		
	}
	PlayerInitialize(&Player1,BuildingRecord(GameState));
	PlayerInitialize(&Player2,BuildingRecord(GameState));
	PlayerPrintCurrentStatus(Player2,BuildingRecord(GameState));
	//PlayerPrintOwnedBuilding(CurrentPlayer(G), BuildingRecord(G));
	
	return 0;
}