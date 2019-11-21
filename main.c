//==============================================//
//								       			//
//					  Main             			//
//                                     			//
//----------------------------------------------//
// File : main.c */		              			//
//----------------------------------------------//
// Definisi ADT GameMap yang menghubungkan		//
// MapMatrix dengan BuildingArray               //
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "fileloader.h"
#include "mesinkata.h"
#include "actionstackt.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
GameMap GameState;
ActionStack GameStateStack;
char InputString[51];
int testint;

boolean InGame;
int BattlePhase;

///////////////////////////////
//		  SKILL FLAGS	 	 //
///////////////////////////////
//SkillAddFlags
int AddET;
int AddIR;
int AddBR;

//SkillTriggerFlags
boolean TriggerET;
boolean TriggerIR;
boolean TriggerBR;

//////////////////////z/////////////
// 	      MAIN FUNCTIONS 	 	 //
///////////////////////////////////
void ClearScreen(){
	system("cls");
}

void ReadCommand(){
	printf("len %d \n", KataLength(CKata));
	if(IsKataSame("Attack", 6)){
		//Command(Attack);
		printf("Attack");
	} else if(IsKataSame("LevelUp", 7)){
		//Command(Attack);

		printf("LevelUp");
		BuildingArrayIncreaseOwnedPasukanBuilding(&BuildingRecord(GameState));
	} else if(IsKataSame("Move", 4)){
		//Command(Attack);
		printf("Move");
		BuildingArrayIncreaseOwnedPasukanBuilding(&BuildingRecord(GameState));
		BuildingListInsertValueLast(&PlayerOwnedBuildingList(CurrentPlayer(GameState)), 3);
	} else if(IsKataSame("Skill", 5)){
		//Command(Attack);
		printf("Skill");
		SkillQueueAddSkill(&PlayerCurrentSkillQueue(CurrentPlayer(GameState)), SkillCreate(2));
	} else if(IsKataSame("Undo", 4)){
		//Command(Attack);
		printf("Undo");
		printf("PopepdState\n");
		ActionStackPop(&GameStateStack, &GameState);
		GameMapPrintInfo(GameState);
		printf("turn %d\n", GameState.turn);
		printf("Castle Soldier : %d\n",
			BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameState),1)));

		//GameMapPrintInfo(GameState);
	} else if(IsKataSame("End_Turn", 8)){
		//Command(Attack);
		printf("End_Turn");
		BattlePhase = 3;
	}  else if(IsKataSame("Exit", 4)){
		//Command(Attack);
		printf("Exit");
		BuildingListDeleteValueLast(&PlayerOwnedBuildingList(CurrentPlayer(GameState)), &testint);
	}  else{
		//Command(Attack);
		printf("Others");
	} 
}
void CheckAddFlags(){
	//ET
	int player = PlayerRole(CurrentPlayer(GameState));
	if(player == 1){
		for(int i = 1; i <= BuildingArrayNeff(BuildingRecord(GameState)); i++){
			Building CurrentBuilding = BuildingArrayElement(BuildingRecord(GameState), i);
			if(BuildingPlayer(CurrentBuilding) == 2){
				if(BuildingKind(CurrentBuilding) == 3){
					AddET = 1;
				}
			}
		}
	} else if (player == 2){
		for(int i = 1; i <= BuildingArrayNeff(BuildingRecord(GameState)); i++){
			Building CurrentBuilding = BuildingArrayElement(BuildingRecord(GameState), i);
			if(BuildingPlayer(CurrentBuilding) == 1){
				if(BuildingKind(CurrentBuilding) == 3){
					AddET = 1;
				}
			}
		}
	}

	//IR
	if(BuildingListNbElmt(PlayerOwnedBuildingList(CurrentPlayer(GameState))) != 0){
		AddIR = 1;
	}

	//BR
	if(BuildingListNbElmt(PlayerOwnedBuildingList(CurrentPlayer(GameState))) == 9){
		AddBR = 1;
	}
}
void RefreshTriggerFlags(){
	TriggerET = false;
	TriggerIR = false;
	TriggerBR = false;
}

void RefreshAddFlags(){
	AddET = 0;
	AddIR = 0;
	AddBR = 0;
}

void RefreshSkillFlags(){
	RefreshAddFlags();
	RefreshTriggerFlags();
}

void PostTurn(int player){
	if(InGame){
		printf("PostTurn");
		GameMapChangePlayer(&GameState);
	}
}
void InTurn(int player){
	while(InGame && BattlePhase == 2){

		//ClearScreen();
		GameMapPrintInfo(GameState);
		printf("Castle Soldier : %d\n",
			BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameState),1)));

		printf("turn %d\n", GameState.turn);
		
		GameMap GameMapPush;
		GameMapPush = GameState;
		BuildingRecord(GameMapPush) = BuildingArrayCopyArray(BuildingRecord(GameState));
		printf("Castle Soldier Push : %d\n",
			BuildingSoldierCount(BuildingArrayElement(BuildingRecord(GameMapPush),1)));

		

		scanf("%s",&InputString);
		StartReadingKata(InputString);
		ReadCommand();


		ActionStackPush(&GameStateStack, GameMapPush);
		GameState.turn += 1;
		//printf("PushedState\n");
		//GameMapPrintInfo(ActionStackInfoTop(GameStateStack));
		//printf("top %d\n", ActionStackTop(GameStateStack));
		
	}
}


void PreTurn(int player){
	if(InGame){
		if(BuildingListNbElmt(PlayerOwnedBuildingList(Player1(GameState))) != 0 && BuildingListNbElmt(PlayerOwnedBuildingList(Player2(GameState))) != 0){
			//ActionStackEmpty(&GameStateStack);
			BuildingArrayRefreshAllBuilding(&BuildingRecord(GameState));
			BuildingArrayIncreaseOwnedPasukanBuilding(&BuildingRecord(GameState));
			RefreshSkillFlags();
			CheckAddFlags();
			BattlePhase = 2;
			//GameMapPrintInfo(GameState);
			//InTurn(player);	
			GameState.turn = 1;
		} else{
			if(BuildingListNbElmt(PlayerOwnedBuildingList(Player1(GameState))) == 0){
				//InGame = false;

			} else if(BuildingListNbElmt(PlayerOwnedBuildingList(Player2(GameState))) == 0){

			}
			InGame = false;
			BattlePhase = 0;
		}
	}
}

void PrintWelcome(){
	printf("###################################\n");
	printf("##  WELCOME TO AVATAR WORLD WAR  ##\n");
	printf("###################################\n");
	printf("\n");
}

void StartGame(){
	InGame = true;
	BattlePhase = 1;
}

void PreGame(){

}
void Setup(char* filename){
	StartLoading(filename, 'b', 'r');
	CompleteFileLoad(&GameState);
	GameMapInitializeAllComponents(&GameState);
	GameMapSetCurrentPlayer(&GameState, 1);
	ActionStackCreateEmpty(&GameStateStack, 10);
}


int main(){
	Setup("pitakar.txt");
	PrintWelcome();

	scanf("%s", InputString);
	StartReadingKata(InputString);
	if(IsKataSame("Start", 5)){
		ClearScreen();
		StartGame();
	}
	
	while(InGame){
		int player = PlayerRole(CurrentPlayer(GameState));
		ClearScreen();
		PreTurn(player);
		InTurn(player);
		PostTurn(player);
	}
	//GameMapPrintInfo(GameState);

	//BuildingRelationGraphPrintInfo(BuildingRelation(GameState));

	
	return 0;
}