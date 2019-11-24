#include <stdio.h>
#include "point.h"

int main()
{
    Point P1 = PointCreate(1, 2);
    Point P2 = PointCreate(1, 2);
    Point P3 = PointCreate(1, 0);
    Point P4;

    if (PointEQ(P1, P2))
    {
        printf("Point P1 dan P2 sama\n tapi coba masukan ini\n");
        PointRead(&P4);
        if (PointEQ(P4, P3))
        {
            printf("Point P3 dan P4 juga sama\n");
        }
        else
        {
            printf("Point P3 dan P4 tidak sama\n");
        }
    }
    printf("P1: ");
    PointPrint(P1);
    printf("\n");
    printf("P2: ");
    PointPrint(P2);
    printf("\n");
    printf("P3: ");
    PointPrint(P3);
    printf("\n");
    printf("P4: ");
    PointPrint(P4);
    printf("\n");
}