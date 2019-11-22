
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
    int X;

    BuildingListCreateEmpty(&L);
    if (IsBuildingListEmpty(L))
    {
        BuildingListInsertValueFirst(&L, 2);
        BuildingListInsertValueLast(&L, 3);
        BuildingListInsertValueFirst(&L, 1);

        MapMatrixCreateEmpty(&M, 3, 3);
        BuildingArrayCreateEmpty(&B, 3);

        BB = BuildingCreate(2, 1, PointCreate(1, 1));
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
        //BuildingListDeleteValue(&L, 2);
        printf("\n");
        BuildingListPrintInfo(L, B);
        printf("\n");
        BuildingListInfotype x;
        //BuildingListDeleteValueFirst(&L, &x);
        BuildingPrintInfo(BuildingArrayElement(B, x));
        printf("\n");
        BuildingListPrintInfo(L, B);

        printf("Kind 1 : %d\n", BuildingListNbElmtKind(L, B, 1));
        printf("Kind 2 : %d\n", BuildingListNbElmtKind(L, B, 2));
        printf("Kind 3 : %d\n", BuildingListNbElmtKind(L, B, 3));
        printf("Kind 4 : %d\n", BuildingListNbElmtKind(L, B, 4));

        printf("Level 4 all : %d\n", IsBuildingListAllLevel4(L, B));

        BuildingLevel(BuildingArrayElement(B, 1)) = 4;
        BuildingLevel(BuildingArrayElement(B, 2)) = 4;
        BuildingLevel(BuildingArrayElement(B, 3)) = 4; 

        BuildingListPrintInfo(L, B);

        printf("Level 4 all : %d\n", IsBuildingListAllLevel4(L, B));
        
        // di bawah ini ga lewat
        BuildingListDeleteValueLast(&L, &X);
        
        //printf("1\n");
        //BuildingListDeleteValueLast(&L, &X);
        //printf("2\n");
        //BuildingListDeleteValueLast(&L, &X);
        //printf("3\n");
        //BuildingListDeleteValueLast(&L, &X);
        //printf("4\n");
    }

    return 0;
}