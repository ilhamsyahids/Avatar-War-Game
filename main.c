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
#include "commands.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
GameMap GameState;
ActionStack GameStateStack;
char InputString[51];
int testint;
int UniversalCounter;

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
void ClearScreen()
{
	system("cls");
}

void ReadCommand()
{
	GameMap GameMapPush;
	GameMapPush = GameMapCopyCurrentMap(GameState);
	BuildingRecord(GameMapPush) = BuildingArrayCopyArray(BuildingRecord(GameState));

	//CheckAddFlags();
	if (IsKataSame("Attack", 6))
	{
		printf("Attack");
Attack(GameState);
		ActionStackPush(&GameStateStack, GameMapPush);
	}
	else if (IsKataSame("LevelUp", 7))
	{
		//Command(LevelUp);
		printf("LevelUp");
		ActionStackPush(&GameStateStack, GameMapPush);
	}
	else if (IsKataSame("Move", 4))
	{
		//Command(Move);
		printf("Move");
		ActionStackPush(&GameStateStack, GameMapPush);
	}
	else if (IsKataSame("Skill", 5))
	{
		//Command(Skill);
		printf("Skill");
		//BuildingListDeleteValueLast(&PlayerOwnedBuildingList(Player2(GameState)), &testint);
		GameMapSetNextPlayer(&GameState, 1);
		ActionStackEmpty(&GameStateStack);
	}
	else if (IsKataSame("Undo", 4))
	{
		if (IsActionStackEmpty(GameStateStack))
		{
			printf("Tidak ada Action yang dapat diundo!\n");
		}
		else
		{
			printf("Undo");
			printf("PopepdState\n");
			ActionStackPop(&GameStateStack, &GameState);
			GameMapPrintInfo(GameState);
		}
	}
	else if (IsKataSame("End_Turn", 8))
	{
		printf("End_Turn");
		ActionStackEmpty(&GameStateStack);
		BattlePhase = 3;
	}
	else if (IsKataSame("Exit", 4))
	{
		printf("Exit");
	}
	else
	{
		printf("Others");
	}
	//CheckAddFlags();
}
void CheckAddFlags()
{
	//ET
	int player = CurrentPlayer(GameState);
	int countFort = 0;
	if (AddET == 0)
	{
		if (player == 1)
		{
			Player PlayerCurrent = Player2(GameState);
			countFort = BuildingListNbElmtKind(PlayerOwnedBuildingList(PlayerCurrent), BuildingRecord(GameState), 3);
			if (countFort > 0)
			{
				AddET = 1;
			}
		}
		else if (player == 2)
		{
			Player PlayerCurrent = Player1(GameState);
			countFort = BuildingListNbElmtKind(PlayerOwnedBuildingList(PlayerCurrent), BuildingRecord(GameState), 3);
			if (countFort > 0)
			{
				AddET = 1;
			}
		}
	}
	else if (AddET == 1)
	{
		if (player == 1)
		{
			Player TopOfStackPlayer = Player2(ActionStackInfoTop(GameStateStack));
			Player PlayerCurrent = Player2(GameState);
			UniversalCounter = BuildingListNbElmtKind(PlayerOwnedBuildingList(TopOfStackPlayer), BuildingRecord(GameState), 3) - BuildingListNbElmtKind(PlayerOwnedBuildingList(PlayerCurrent), BuildingRecord(GameState), 3);
			if (UniversalCounter > 0)
			{
				AddET = 2;
			}
		}
		else if (player == 2)
		{
			Player TopOfStackPlayer = Player1(ActionStackInfoTop(GameStateStack));
			Player PlayerCurrent = Player1(GameState);
			UniversalCounter = BuildingListNbElmtKind(PlayerOwnedBuildingList(TopOfStackPlayer), BuildingRecord(GameState), 3) - BuildingListNbElmtKind(PlayerOwnedBuildingList(PlayerCurrent), BuildingRecord(GameState), 3);
			if (UniversalCounter > 0)
			{
				AddET = 2;
			}
		}
	}

	//IR
	if (AddIR == 0)
	{
		if (BuildingListNbElmt(PlayerOwnedBuildingList(GameMapGetCurrentPlayer(GameState))) != 0)
		{
			AddIR = 1;
		}
	}
	else if (AddIR == 1)
	{
		if (IsBuildingListAllLevel4(PlayerOwnedBuildingList(GameMapGetCurrentPlayer(GameState)), BuildingRecord(GameState)))
		{
			AddIR = 2;
		}
	}

	//BR
	if (AddBR == 0)
	{
		if (BuildingListNbElmt(PlayerOwnedBuildingList(GameMapGetCurrentPlayer(GameState))) == 9)
		{
			AddBR = 1;
		}
	}
	else if (AddBR == 1)
	{
		if (BuildingListNbElmt(PlayerOwnedBuildingList(GameMapGetCurrentPlayer(GameState))) == 10)
		{
			AddBR = 2;
		}
	}
}

void ExecuteAddFlags()
{
	// IR
	if (AddIR == 2)
	{
		Skill AddSkill = SkillCreate(3);
		if (CurrentPlayer(GameState) == 1)
		{
			SkillQueueAddSkill(&PlayerCurrentSkillQueue(Player1(GameState)), AddSkill);
		}
		else if (CurrentPlayer(GameState) == 2)
		{
			SkillQueueAddSkill(&PlayerCurrentSkillQueue(Player2(GameState)), AddSkill);
		}

		AddIR = 0;
	}

	// BR
	if (AddBR == 2)
	{
		Skill AddSkill = SkillCreate(4);
		if (CurrentPlayer(GameState) == 1)
		{
			SkillQueueAddSkill(&PlayerCurrentSkillQueue(Player2(GameState)), AddSkill);
		}
		else if (CurrentPlayer(GameState) == 2)
		{
			SkillQueueAddSkill(&PlayerCurrentSkillQueue(Player1(GameState)), AddSkill);
		}
		AddBR = 0;
	}

	// ET
	if (AddET == 2)
	{
		Skill AddSkill = SkillCreate(2);
		if (CurrentPlayer(GameState) == 1)
		{
			SkillQueueAddSkill(&PlayerCurrentSkillQueue(Player2(GameState)), AddSkill);
		}
		else if (CurrentPlayer(GameState) == 2)
		{
			SkillQueueAddSkill(&PlayerCurrentSkillQueue(Player1(GameState)), AddSkill);
		}
		AddET = 0;
	}
}
void RefreshTriggerFlags()
{
	TriggerET = false;
	TriggerIR = false;
	TriggerBR = false;
}

void RefreshAddFlags()
{
	AddET = 0;
	AddIR = 0;
	AddBR = 0;
}

void RefreshSkillFlags()
{
	RefreshAddFlags();
	RefreshTriggerFlags();
}

void CheckBattleCondition()
{
	InGame = (BuildingListNbElmt(PlayerOwnedBuildingList(Player1(GameState))) != 0 && BuildingListNbElmt(PlayerOwnedBuildingList(Player2(GameState))) != 0);
}

void PostTurn(int player)
{
	CheckBattleCondition();
	if (InGame && BattlePhase == 3)
	{
		printf("PostTurn");
		BattlePhase = 1;
		GameMapChangePlayer(&GameState);
	}
	else if (!InGame)
	{
		if (BuildingListNbElmt(PlayerOwnedBuildingList(Player1(GameState))) == 0)
		{
			printf("PLAYER 1 KALAH");
		}
		else if (BuildingListNbElmt(PlayerOwnedBuildingList(Player2(GameState))) == 0)
		{
			printf("PLAYER 2 KALAH");
		}
		RefreshSkillFlags;
		BattlePhase = 0;
	}
}
void InTurn(int player)
{
	while (InGame && BattlePhase == 2)
	{
		ClearScreen();
		CheckAddFlags();
		GameMapPrintInfo(GameState);
		printf("Enter Command: \n");
		scanf("%s", &InputString);
		StartReadingKata(InputString);
		ReadCommand();
		CheckAddFlags();
		ExecuteAddFlags();
		CheckBattleCondition();
	}
}

void PreTurn(int player)
{
	CheckBattleCondition();
	if (InGame && BattlePhase == 1)
	{
		ActionStackEmpty(&GameStateStack);
		BuildingArrayRefreshAllBuilding(&BuildingRecord(GameState));
		BuildingArrayIncreaseOwnedPasukanBuilding(&BuildingRecord(GameState));
		RefreshSkillFlags();
		CheckAddFlags();
		BattlePhase = 2;
	}
}

void PrintWelcome()
{
	printf("	  _______           _______ _________ _______  _______\n");
	printf("	  (  ___  )|\\     /|(  ___  )\\__   __/(  ___  )(  ____ )\n");
	printf("	  | (   ) || )   ( || (   ) |   ) (   | (   ) || (    )|\n");
	printf("	  | (___) || |   | || (___) |   | |   | (___) || (____)|\n");
	printf("	  |  ___  |( (   ) )|  ___  |   | |   |  ___  ||     __)\n");
	printf("	  | (   ) | \\ \\_/ / | (   ) |   | |   | (   ) || (\\ (\n");
	printf("	  | )   ( |  \\   /  | )   ( |   | |   | )   ( || ) \\ \\__\n");
	printf("	  |/     \\|   \\_/   |/     \\|   )_(   |/     \\||/   \\__/\n");
	printf("\n");
	printf("          _______  _______  _        ______              _______  _______ \n");
	printf("|\\     /|(  ___  )(  ____ )( \\      (  __  \\   |\\     /|(  ___  )(  ____ )\n");
	printf("| )   ( || (   ) || (    )|| (      | (  \\  )  | )   ( || (   ) || (    )|\n");
	printf("| | _ | || |   | || (____)|| |      | |   ) |  | | _ | || (___) || (____)|\n");
	printf("| |( )| || |   | ||     __)| |      | |   | |  | |( )| ||  ___  ||     __)\n");
	printf("| || || || |   | || (\\ (   | |      | |   ) |  | || || || (   ) || (\\ (   \n");
	printf("| () () || (___) || ) \\ \\__| (____/\\| (__/  )  | () () || )   ( || ) \\ \\__\n");
	printf("(_______)(_______)|/   \\__/(_______/(______/   (_______)|/     \\||/   \\__/\n");
	printf("\n");
	printf("	  	  ######################################\n");
	printf("	  	  ##                 #                ##\n");
	printf("	  	  ##      Start      #      Exit      ##\n");
	printf("	  	  ##                 #                ##\n");
	printf("	  	  ######################################\n");
	printf("\n");
}

void StartGame()
{
	InGame = true;
	BattlePhase = 1;
}

void PreGame()
{
}
void Setup(char *filename)
{
	StartLoading(filename, 'b', 'r');
	CompleteFileLoad(&GameState);
	GameMapInitializeAllComponents(&GameState);
	GameMapSetCurrentPlayer(&GameState, 1);
	GameMapSetNextPlayer(&GameState, 2);
	ActionStackCreateEmpty(&GameStateStack, 10);
}

int main()
{
	Setup("pitakar.txt");
	PrintWelcome();

	printf("Enter Command:\n");
	scanf("%s", InputString);
	StartReadingKata(InputString);
	if (IsKataSame("Start", 5))
	{
		ClearScreen();
		StartGame();
	}
	else if (IsKataSame("Exit", 4))
	{
		exit(0);
	}

	while (InGame)
	{
		int player = CurrentPlayer(GameState);
		ClearScreen();
		PreTurn(player);
		InTurn(player);
		PostTurn(player);
	}
	//GameMapPrintInfo(GameState);

	//BuildingRelationGraphPrintInfo(BuildingRelation(GameState));

	return 0;
}