#include <stdio.h>
#include "building.h"
#include "point.h"
#include "pcolor.h"

int main()
{
    Building B;
    Point P;
    P = MakePOINT(5, 4);
    B = BuildingCreate(1, 2, P);
    BuildingInitialize(&B);
    BuildingPrintInfo(B);
    printf("\n");
    BuildingLevelUp(&B);
    printf("%d\n", B.player);
    BuildingChangePlayer(&B);
    printf("%d\n", B.player);
    BuildingPrintInfo(B);
}