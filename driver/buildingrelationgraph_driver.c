#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "buildingrelationgraph.h"

int main(){
	BuildingRelationGraph G;
	BuildingRelationGraphAddress V;
	BuildingRelationGraphAddress VTest;
	AdjacentBuildingRelationGraphAddress P;
	AdjacentBuildingRelationGraphAddress PTest;

	BuildingRelationGraphCreateEmpty(&G);

	printf("%d\n",BuildingRelationGraphFirstAddress(G));

	printf("%d\n",IsBuildingRelationGraphEmpty(G));

	//ALLOCATION TEST
	/*
	V = BuildingRelationGraphVertexAlokasi(2);
	printf("%d\n",BuildingRelationGraphVertexInfo(V));
	printf("%d\n",BuildingRelationGraphVertexNext(V));
	printf("%d\n",BuildingRelationGraphVertexFirstAdjacent(V));

	printf("%d\n",IsAdjacentBuildingRelationGraphEmpty(V));

	P = BuildingRelationGraphAdjacentVertexAlokasi(100);
	printf("%d\n",BuildingRelationGraphAdjacentVertexInfo(P));
	printf("%d\n",BuildingRelationGraphAdjacentVertexNextAdjacent(P));*/

	//DEALLOCATION TEST
	/*
	BuildingRelationGraphVertexDealokasi(&V);
	printf("%d\n",BuildingRelationGraphVertexInfo(V));
	printf("%d\n",BuildingRelationGraphVertexNext(V));
	printf("%d\n",BuildingRelationGraphVertexFirstAdjacent(V));

	BuildingRelationGraphAdjacentVertexDealokasi(&P);
	printf("%d\n",BuildingRelationGraphAdjacentVertexInfo(P));
	printf("%d\n",BuildingRelationGraphAdjacentVertexNextAdjacent(P));*/

	//VERTEX INSERT TEST
	BuildingRelationGraphInsertVertex(&G, 5);
	/*
	printf("%d\n",BuildingRelationGraphFirstAddress(G));
	printf("%d\n",IsBuildingRelationGraphEmpty(G));
	printf("%d\n",BuildingRelationGraphVertexInfo(BuildingRelationGraphFirstAddress(G)));
	printf("%d\n",BuildingRelationGraphVertexNext(BuildingRelationGraphFirstAddress(G)));
	printf("%d\n",BuildingRelationGraphVertexFirstAdjacent(BuildingRelationGraphFirstAddress(G)));
	*/

	BuildingRelationGraphInsertVertex(&G, 10);
	BuildingRelationGraphInsertVertex(&G, 13);
	BuildingRelationGraphInsertVertex(&G, 11);
	BuildingRelationGraphInsertVertex(&G, 15);
	BuildingRelationGraphInsertVertex(&G, 17);
	/*
	printf("%d\n",BuildingRelationGraphFirstAddress(G));
	printf("%d\n",IsBuildingRelationGraphEmpty(G));
	printf("%d\n",BuildingRelationGraphVertexInfo(BuildingRelationGraphFirstAddress(G)));
	printf("%d\n",BuildingRelationGraphVertexInfo(BuildingRelationGraphVertexNext(BuildingRelationGraphFirstAddress(G))));
	printf("%d\n",BuildingRelationGraphVertexFirstAdjacent(BuildingRelationGraphFirstAddress(G)));

	printf("%d\n",IsVertexInBuildingRelationGraph(G, 3));
	printf("%d\n",IsVertexInBuildingRelationGraph(G, 5));
	printf("%d\n",IsVertexInBuildingRelationGraph(G, 10));
	printf("%d\n",IsVertexInBuildingRelationGraph(G, 15));
	*/

	/*
	VTest = BuildingRelationGraphAddressSearch(G, 5);
	printf("%d\n",VTest);
	printf("%d\n",BuildingRelationGraphVertexInfo(VTest));

	VTest = BuildingRelationGraphAddressSearch(G, 7);
	printf("%d\n",VTest);
	//printf("%d\n",BuildingRelationGraphVertexInfo(VTest));
	*/

	VTest = BuildingRelationGraphAddressSearch(G, 10);
	printf("%d\n",VTest);
	printf("%d\n",BuildingRelationGraphVertexInfo(VTest));
	
	//ADJACENT VERTEX INSERT TEST
	printf("%d\n",IsAdjacentBuildingRelationGraphEmpty(VTest));
	BuildingRelationGraphInsertAdjacentVertex(VTest,11);
	BuildingRelationGraphInsertAdjacentVertex(VTest, 13);
	BuildingRelationGraphInsertAdjacentVertex(VTest, 15);
	printf("%d\n",IsAdjacentBuildingRelationGraphEmpty(VTest));
	printf("%d\n",BuildingRelationGraphAdjacentVertexInfo(BuildingRelationGraphVertexFirstAdjacent(VTest)));
	printf("%d\n",IsAdjacentWithVertex(VTest, 13));
	
	//BuildingRelationGraphInsertAdjacentVertex(VTest, 11);
	printf("%d\n",IsAdjacentBuildingRelationGraphEmpty(VTest));
	printf("%d\n",BuildingRelationGraphAdjacentVertexInfo(BuildingRelationGraphVertexFirstAdjacent(VTest)));
	printf("%d\n",IsAdjacentWithVertex(VTest, 11));

	PTest = BuildingRelationGraphAdjacentAddressSearch(VTest, 11);
	printf("%d\n",BuildingRelationGraphAdjacentVertexInfo(PTest));

	VTest = BuildingRelationGraphAddressSearch(G, 5);
	BuildingRelationGraphInsertAdjacentVertex(VTest, 13);
	BuildingRelationGraphInsertAdjacentVertex(VTest, 11);
	//BuildingRelationGraphInsertAdjacentVertex(VTest, 15);
	PTest = BuildingRelationGraphAdjacentAddressSearch(VTest, 11);
	printf("%d\n",BuildingRelationGraphAdjacentVertexInfo(PTest));

	BuildingRelationGraphPrintInfo(G);

	VTest = BuildingRelationGraphAddressSearch(G, 10);
	BuildingRelationGraphDeleteAdjacentVertex(VTest, 17);

	BuildingRelationGraphPrintInfo(G);

	BuildingRelationGraphDeleteVertex(&G, 20);
	BuildingRelationGraphPrintInfo(G);

	return 0;
}