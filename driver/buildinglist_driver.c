
#include "boolean.h"
#include "buildingarray.h"
#include "buildinglist.h"
#include "mapmatrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    BuildingList L;
    MapMatrix M;
    BuildingArray B;
    Building BB;
    int i;
    int j;
    Point P;

    BuildingListCreateEmpty(&L);
    if (IsBuildingListEmpty(L))
    {
        BuildingListInsertValueFirst(&L, 2);
        BuildingListInsertValueLast(&L, 3);
        BuildingListInsertValueFirst(&L, 1);

        MapMatrixCreateEmpty(&M, 3, 3);
        BuildingArrayCreateEmpty(&B, 3);

        BB = BuildingCreate(1, 1, PointCreate(1, 1));
        BuildingArrayAddAsLastElement(&B, BB);
        MapMatrixElement(M, PointCreate(1, 1)) = 1;
        // printf("%d", MapMatrixElement(M, PointCreate(1, 1)));

        BB = BuildingCreate(2, 1, PointCreate(2, 3));
        BuildingArrayAddAsLastElement(&B, BB);
        MapMatrixElement(M, PointCreate(2, 3)) = 2;

        BB = BuildingCreate(3, 2, PointCreate(3, 2));
        BuildingArrayAddAsLastElement(&B, BB);
        MapMatrixElement(M, PointCreate(3, 2)) = 3;

        BuildingListInsertValueLast(&L, 2);
        BuildingListPrintInfo(L, B);
        BuildingListDeleteValue(&L, 2);
        printf("\n");
        BuildingListPrintInfo(L, B);
        printf("\n");
        BuildingListInfotype x;
        BuildingListDeleteValueFirst(&L, &x);
        BuildingPrintInfo(BuildingArrayElement(B, x));
        printf("\n");
        BuildingListPrintInfo(L, B);

        BuildingList LL = CopyBuildingList(L);
        BuildingListPrintInfo(LL, B);
    }

    return 0;
}