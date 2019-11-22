#include <stdio.h>
#include "building.h"
#include "point.h"

int main()
{
    Building B;
    Point P;
    P = PointCreate(5, 4);
    B = BuildingCreate(1, 2, P);
    BuildingInitialize(&B);
    BuildingPrintInfo(B);
    printf("\n");
    BuildingLevelUp(&B); // soldier menjadi 20
    BuildingPrintInfo(B);
    int count = BuildingSoldierCount(B);
    printf(" %d\n", count);
    BuildingDecreasePasukan(&B, 5);
    printf("%d\n", B.player);
    BuildingChangePlayer(&B);
    printf("%d\n", B.player);
    count = BuildingSoldierCount(B);
    printf("%d\n", count);
    BuildingDecreasePasukan(&B, 5);
    BuildingPrintInfo(B);
    printf("\n");
    BuildingLevelUp(&B);
    printf("\n");
    BuildingDecreasePasukan(&B, 10);
    BuildingPrintInfo(B);
}