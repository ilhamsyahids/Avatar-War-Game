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
#include "fileloader.h"
#include "mesinkata.h"
#include "actionstackt.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
GameMap GameState;
ActionStack GameStateStack;
char InputString[51];

///////////////////////////////////
// 	      MAIN FUNCTIONS 	 	 //
///////////////////////////////////
void PreTurn(int player){
	//ActionStackEmpty(&GameStateStack);
	BuildingArrayRefreshAllBuilding(&BuildingRecord(GameState));
	GameMapPrintInfo(GameState);
}

void StartTurn(int player){
	PreTurn(player);
	//InTurn(player);

	//PostTurn(player);
}

void PrintWelcome(){
	printf("###################################\n");
	printf("##  WELCOME TO AVATAR WORLD WAR  ##\n");
	printf("###################################\n");
	printf("\n");
}

void StartGame(){
	PrintWelcome();
	scanf("%s", InputString);
	StartReadingKata(InputString);
	if(IsKataSame("Start", 5)){
		StartTurn(1);
	}

}
void Setup(char* filename){
	StartLoading(filename, 'b', 'r');
	CompleteFileLoad(&GameState);
	GameMapInitializeAllComponents(&GameState);
	GameMapSetCurrentPlayer(&GameState, 2);
	//ActionStackCreateEmpty(&GameStateStack, 10);
}

int main(){
	Setup("pitakar.txt");
	StartGame();
	//GameMapPrintInfo(GameState);

	//BuildingRelationGraphPrintInfo(BuildingRelation(GameState));

	
	return 0;
}