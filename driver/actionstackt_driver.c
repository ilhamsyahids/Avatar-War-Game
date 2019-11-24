#include "actionstackt.h"
#include "gamemap.h"

int main(){
	GameMap GameState;
	ActionStack GameStateStack;
	Player Player1;
	Player Player2;
	MapMatrix Map;
	BuildingArray Record;
	BuildingRelationGraph Relation;

	Player1 = PlayerCreate(1, 'b');
	Player2 = PlayerCreate(2, 'r');
	ActionStackCreateEmpty(&GameStateStack, 10);
	BuildingArrayCreateEmpty(&Record, 1);

	int PositionX = 1;
	int PositionY = 2;
	Point P = PointCreate(PositionX, PositionY);
	Building B = BuildingCreate(1, 1, P);
	BuildingInitialize(&B);
	BuildingArrayAddAsLastElement(&Record, B);

	GameMapCreate(&GameState, Map, Record, Player1, Player2, Relation);
	GameMapSetCurrentPlayer(&GameState, 1);
	printf("Array neff : %d\n", BuildingArrayNeff(BuildingRecord(GameState)));
	printf("Castle Soldier : %d\n",
			BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameState),1)));
	printf("Owned by player %d\n",
			BuildingPlayer(BuildingArrayElement(BuildingRecord(GameState),1)));
	GameMap GameMapPush = GameState;
	BuildingRecord(GameMapPush) = BuildingArrayCopyArray(BuildingRecord(GameState));
	ActionStackPush(&GameStateStack, GameMapPush);

	GameMapChangePlayer(&GameState);
	BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameState),1)) += 1;
	//BuildingChangePlayer(&BuildingArrayElement(BuildingRecord(GameState),1));
	BuildingArrayNeff(BuildingRecord(GameState)) += 1;
	printf("Array neff : %d\n", BuildingArrayNeff(BuildingRecord(GameState)));
	printf("Castle Soldier : %d\n",
			BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameState),1)));
	printf("Owned by player %d\n",
			BuildingPlayer(BuildingArrayElement(BuildingRecord(GameState),1)));
	GameMapPush = GameState;
	BuildingRecord(GameMapPush) = BuildingArrayCopyArray(BuildingRecord(GameState));
	printf("Push Array neff : %d\n", BuildingArrayNeff(BuildingRecord(GameMapPush)));
	
	ActionStackPush(&GameStateStack, GameMapPush);


	ActionStackPop(&GameStateStack, &GameState);
	printf("Array neff : %d\n", BuildingArrayNeff(BuildingRecord(GameState)));
	printf("Castle Soldier : %d\n",
			BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameState),1)));
	printf("Owned by player %d\n",
			BuildingPlayer(BuildingArrayElement(BuildingRecord(GameState),1)));

	ActionStackPop(&GameStateStack, &GameState);
	printf("Array neff : %d\n", BuildingArrayNeff(BuildingRecord(GameState)));
	printf("Castle Soldier : %d\n",
			BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameState),1)));
	printf("Owned by player %d\n",
			BuildingPlayer(BuildingArrayElement(BuildingRecord(GameState),1)));

	
	return 0;
}