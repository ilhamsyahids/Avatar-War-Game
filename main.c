//==============================================//
//								       			//
//					  Main             			//
//                                     			//
//----------------------------------------------//
// File : main.c */		              			//
//----------------------------------------------//
// Program Utama dari game AVATAR WORLD WAR		//
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
char testchar;
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

	if (IsKataSame("Attack", 6))
	{
		Attack(&GameState);
		ActionStackPush(&GameStateStack, GameMapPush);
	}
	else if (IsKataSame("LevelUp", 7))
	{
		Level_up(&GameState);
		ActionStackPush(&GameStateStack, GameMapPush);
	}
	else if (IsKataSame("Move", 4))
	{
		Move(&GameState);
		ActionStackPush(&GameStateStack, GameMapPush);
	}
	else if (IsKataSame("Skill", 5))
	{
		Skills(&GameState);
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
			ActionStackPop(&GameStateStack, &GameState);
		}
	}
	else if (IsKataSame("End_Turn", 8))
	{
		ActionStackEmpty(&GameStateStack);
		BattlePhase = 3;
	}
	else if (IsKataSame("Exit", 4))
	{
		exit(0);
	}
	else if (IsKataSame("Help", 4))
	{
		printf("Command tersedia\n");
		printf("1. Attack\n");
		printf("2. LevelUp\n");
		printf("3. Skill\n");
		printf("4. Move\n");
		printf("5. Undo\n");
		printf("6. End_Turn\n");
		printf("7. Exit\n");
		printf("8. Help\n");
	}
	else
	{
		printf("Command tersebut tidak tersedia\n");
		printf("Command tersedia\n");
		printf("1. Attack\n");
		printf("2. LevelUp\n");
		printf("3. Skill\n");
		printf("4. Move\n");
		printf("5. Undo\n");
		printf("6. End_Turn\n");
		printf("7. Exit\n");
		printf("8. Help\n");
	}
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
		if (IsBuildingListAllLevel4(PlayerOwnedBuildingList(GameMapGetCurrentPlayer(GameState)), BuildingRecord(GameState)) && BattlePhase == 3)
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
	if (AddIR == 2 && BattlePhase == 3)
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

void RefreshAddFlags()
{
	AddET = 0;
	AddIR = 0;
	AddBR = 0;
}

void RefreshSkillFlags()
{
	RefreshAddFlags();
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
		CheckAddFlags();
		ExecuteAddFlags();
		BattlePhase = 1;
		GameMapChangePlayer(&GameState);
	}
	else if (!InGame)
	{
		if (BuildingListNbElmt(PlayerOwnedBuildingList(Player1(GameState))) == 0)
		{
			printf("=================================================\n");
			printf("|                 PLAYER 2 WINS                 |\n");
			printf("-------------------------------------------------\n");
			printf("| Seluruh bangunan Player 1 telah ditaklukkan ! |\n");
			printf("| Player 2 berhasil menguasai dunia!            |\n");
			printf("=================================================\n");
		}
		else if (BuildingListNbElmt(PlayerOwnedBuildingList(Player2(GameState))) == 0)
		{
			printf("=================================================\n");
			printf("|                 PLAYER 1 WINS                 |\n");
			printf("-------------------------------------------------\n");
			printf("| Seluruh bangunan Player 2 telah ditaklukkan ! |\n");
			printf("| Player 1 berhasil menguasai dunia !           |\n");
			printf("=================================================\n");
		}
		RefreshSkillFlags();
		BattlePhase = 0;
	}
}
void InTurn(int player)
{
	while (InGame && BattlePhase == 2)
	{
		CheckAddFlags();
		GameMapPrintInfo(GameState);
		print_magenta("Enter Command: \n");
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
		BuildingArrayResetAllBuilding(&BuildingRecord(GameState));
		RefreshSkillFlags();
		//CheckAddFlags();
		BuildingArrayIncreaseOwnedPasukanBuilding(&BuildingRecord(GameState), player);
		BattlePhase = 2;
	}
}

void PrintWelcome()
{
	print_yellow("	  _______           _______ _________ _______  _______\n");
	print_yellow("	  (  ___  )|\\     /|(  ___  )\\__   __/(  ___  )(  ____ )\n");
	print_yellow("	  | (   ) || )   ( || (   ) |   ) (   | (   ) || (    )|\n");
	print_yellow("	  | (___) || |   | || (___) |   | |   | (___) || (____)|\n");
	print_yellow("	  |  ___  |( (   ) )|  ___  |   | |   |  ___  ||     __)\n");
	print_yellow("	  | (   ) | \\ \\_/ / | (   ) |   | |   | (   ) || (\\ (\n");
	print_yellow("	  | )   ( |  \\   /  | )   ( |   | |   | )   ( || ) \\ \\__\n");
	print_yellow("	  |/     \\|   \\_/   |/     \\|   )_(   |/     \\||/   \\__/\n");
	print_yellow("\n");
	print_yellow("          _______  _______  _        ______              _______  _______ \n");
	print_yellow("|\\     /|(  ___  )(  ____ )( \\      (  __  \\   |\\     /|(  ___  )(  ____ )\n");
	print_yellow("| )   ( || (   ) || (    )|| (      | (  \\  )  | )   ( || (   ) || (    )|\n");
	print_yellow("| | _ | || |   | || (____)|| |      | |   ) |  | | _ | || (___) || (____)|\n");
	print_yellow("| |( )| || |   | ||     __)| |      | |   | |  | |( )| ||  ___  ||     __)\n");
	print_yellow("| || || || |   | || (\\ (   | |      | |   ) |  | || || || (   ) || (\\ (   \n");
	print_yellow("| () () || (___) || ) \\ \\__| (____/\\| (__/  )  | () () || )   ( || ) \\ \\__\n");
	print_yellow("(_______)(_______)|/   \\__/(_______/(______/   (_______)|/     \\||/   \\__/\n");
	print_yellow("\n");
	print_yellow("	  	  ######################################\n");
	print_yellow("	  	  ##                 #                ##\n");
	print_yellow("	  	  ##      Start      #      Exit      ##\n");
	print_yellow("	  	  ##                 #                ##\n");
	print_yellow("	  	  ######################################\n");
	print_yellow("\n");
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
	StartLoading(filename, 'r', 'b');
	CompleteFileLoad(&GameState);
	GameMapInitializeAllComponents(&GameState);
	GameMapSetCurrentPlayer(&GameState, 1);
	GameMapSetNextPlayer(&GameState, 2);
	ActionStackCreateEmpty(&GameStateStack, 10);
}

int main()
{
	printf("Masukkan nama file konfigurasi : ");
	scanf("%s", InputString);
	Setup(InputString);
	PrintWelcome();

	print_magenta("Enter Command:\n");
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
		PreTurn(player);
		InTurn(player);
		PostTurn(player);
	}

	return 0;
}