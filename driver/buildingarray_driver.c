#include "boolean.h"
#include "buildingarray.h"
#include "buildinglist.h"
#include "mapmatrix.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    BuildingArray ArrB;
    Building B;
    Player Player1 = PlayerCreate(1, 'R');
    Player Player2 = PlayerCreate(2, 'B');

    BuildingArrayCreateEmpty(&ArrB, 5);

    B = BuildingCreate(2, 1, PointCreate(1, 1));
    BuildingInitialize(&B);
    BuildingArrayAddAsLastElement(&ArrB, B);

    B = BuildingCreate(4, 2, PointCreate(5, 5));
    BuildingInitialize(&B);
    BuildingArrayAddAsLastElement(&ArrB, B);

    B = BuildingCreate(3, 2, PointCreate(5, 5));
    BuildingArrayAddAsLastElement(&ArrB, B);

    B = BuildingCreate(0, 3, PointCreate(10, 9));
    BuildingArrayAddAsLastElement(&ArrB, B);

    B = BuildingCreate(1, 1, PointCreate(6, 5));
    BuildingArrayAddAsLastElement(&ArrB, B);

    for (int i = 0; i < 5; i++)
    {
        BuildingPrintInfo(BuildingArrayElement(ArrB, i + 1));
        printf("\n");
    }

    printf("\nInit All\n");
    BuildingArrayInitializeAllBuilding(&ArrB);
    for (int i = 0; i < 5; i++)
    {
        BuildingPrintInfo(BuildingArrayElement(ArrB, i + 1));
        printf("\n");
    }

    printf("\nIncrease Soldier Role 1 by 500\n");
    BuildingArrayIncreasePlayerOwnedPasukanBuilding(&ArrB,1,500);
    for (int i = 0; i < 5; i++)
    {
        BuildingPrintInfo(BuildingArrayElement(ArrB, i + 1));
        printf("\n");
    }

    printf("\nDeacrease Soldier Role 2 by 20\n");
    BuildingArrayDecreasePlayerOwnedPasukanBuilding(&ArrB,2,20);
    for (int i = 0; i < 5; i++)
    {
        BuildingPrintInfo(BuildingArrayElement(ArrB, i + 1));
        printf("\n");
    }

    printf("\nLevel Up Building Role 2\n");
    BuildingArrayLevelUpOwnedPlayerBuilding(&ArrB,2);
    for (int i = 0; i < 5; i++)
    {
        BuildingPrintInfo(BuildingArrayElement(ArrB, i + 1));
        printf("\n");
    }

    printf("\nCopy Building Array\n");
    BuildingArray ArrB2 = BuildingArrayCopyArray(ArrB);
    for (int i = 0; i < 5; i++)
    {
        BuildingPrintInfo(BuildingArrayElement(ArrB2, i + 1));
        printf("\n");
    }

    return 0;
}