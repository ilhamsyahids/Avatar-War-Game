#include "mapmatrix.h"

int main(){
	MapMatrix M;
	BuildingArray B;
	Building BB;

	
	int i;
	int j;
	Point P;
	MapMatrixCreateEmpty(&M, 3, 3);
	BuildingArrayCreateEmpty(&B, 3);
	for(i = 1; i <= MapMatrixLastIdxBaris(M); i++){
		for(j = 1; j <= MapMatrixLastIdxKolom(M); j++){
			printf("%d %d ", i,j);	
			P = PointCreate(i, j);
			printf("%d\n",MapMatrixElement(M, P));
		}
		printf("\n");
	}
	
	BB = BuildingCreate(1, 1, PointCreate(1,1));
	BuildingArrayAddAsLastElement(&B, BB);
	MapMatrixElement(M,PointCreate(1,1)) = 1;
	printf("%d",MapMatrixElement(M, PointCreate(1,1)));
	
	
	BB = BuildingCreate(2, 0, PointCreate(2,3));
	BuildingArrayAddAsLastElement(&B, BB);
	MapMatrixElement(M,PointCreate(2,3)) = 2;


	BB = BuildingCreate(3, 2, PointCreate(3,2));
	BuildingArrayAddAsLastElement(&B, BB);
	MapMatrixElement(M,PointCreate(3,2)) = 3;
	
	printf("Kind = %c, player = %d, position = ", BuildingGetAcronym(BuildingKind(BuildingArrayElement(B, 1))),BuildingPlayer(BuildingArrayElement(B, 1)));
	PointPrint(BuildingPosition(BuildingArrayElement(B, 1)));
	printf("\n");
	
	printf("Kind = %c, player = %d, position = ", BuildingGetAcronym(BuildingKind(BuildingArrayElement(B, 2))),BuildingPlayer(BuildingArrayElement(B, 2)));
	PointPrint(BuildingPosition(BuildingArrayElement(B, 2)));
	printf("\n");

	printf("Kind = %c, player = %d, position = ", BuildingGetAcronym(BuildingKind(BuildingArrayElement(B, 3))),BuildingPlayer(BuildingArrayElement(B, 3)));
	PointPrint(BuildingPosition(BuildingArrayElement(B, 3)));
	printf("\n");
	
	
	for(i = 1; i <= MapMatrixLastIdxBaris(M); i++){
		for(j = 1; j <= MapMatrixLastIdxKolom(M); j++){
			printf("%d %d ", i,j);	
			P = PointCreate(i, j);
			printf("%d\n",MapMatrixElement(M, P));
		}
		printf("\n");
	}

	MapMatrixPrintMap(M, B);


	return 0;
}
