#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "graph.h"

int main(){
	Graph G;
	GraphAddress V;
	GraphAddress VTest;
	AdjacentGraphAddress P;
	AdjacentGraphAddress PTest;

	GraphCreateEmpty(&G);

	printf("%d\n",GraphFirstAddress(G));

	printf("%d\n",IsGraphEmpty(G));

	//ALLOCATION TEST
	/*
	V = GraphVertexAlokasi(2);
	printf("%d\n",GraphVertexInfo(V));
	printf("%d\n",GraphVertexNext(V));
	printf("%d\n",GraphVertexFirstAdjacent(V));

	printf("%d\n",IsAdjacentGraphEmpty(V));

	P = GraphAdjacentVertexAlokasi(100);
	printf("%d\n",GraphAdjacentVertexInfo(P));
	printf("%d\n",GraphAdjacentVertexNextAdjacent(P));*/

	//DEALLOCATION TEST
	/*
	GraphVertexDealokasi(&V);
	printf("%d\n",GraphVertexInfo(V));
	printf("%d\n",GraphVertexNext(V));
	printf("%d\n",GraphVertexFirstAdjacent(V));

	GraphAdjacentVertexDealokasi(&P);
	printf("%d\n",GraphAdjacentVertexInfo(P));
	printf("%d\n",GraphAdjacentVertexNextAdjacent(P));*/

	//VERTEX INSERT TEST
	GraphInsertVertex(&G, 5);
	/*
	printf("%d\n",GraphFirstAddress(G));
	printf("%d\n",IsGraphEmpty(G));
	printf("%d\n",GraphVertexInfo(GraphFirstAddress(G)));
	printf("%d\n",GraphVertexNext(GraphFirstAddress(G)));
	printf("%d\n",GraphVertexFirstAdjacent(GraphFirstAddress(G)));
	*/

	GraphInsertVertex(&G, 10);
	GraphInsertVertex(&G, 13);
	GraphInsertVertex(&G, 11);
	GraphInsertVertex(&G, 15);
	GraphInsertVertex(&G, 17);
	/*
	printf("%d\n",GraphFirstAddress(G));
	printf("%d\n",IsGraphEmpty(G));
	printf("%d\n",GraphVertexInfo(GraphFirstAddress(G)));
	printf("%d\n",GraphVertexInfo(GraphVertexNext(GraphFirstAddress(G))));
	printf("%d\n",GraphVertexFirstAdjacent(GraphFirstAddress(G)));

	printf("%d\n",IsVertexInGraph(G, 3));
	printf("%d\n",IsVertexInGraph(G, 5));
	printf("%d\n",IsVertexInGraph(G, 10));
	printf("%d\n",IsVertexInGraph(G, 15));
	*/

	/*
	VTest = GraphAddressSearch(G, 5);
	printf("%d\n",VTest);
	printf("%d\n",GraphVertexInfo(VTest));

	VTest = GraphAddressSearch(G, 7);
	printf("%d\n",VTest);
	//printf("%d\n",GraphVertexInfo(VTest));
	*/

	VTest = GraphAddressSearch(G, 10);
	printf("%d\n",VTest);
	printf("%d\n",GraphVertexInfo(VTest));
	
	//ADJACENT VERTEX INSERT TEST
	printf("%d\n",IsAdjacentGraphEmpty(VTest));
	GraphInsertAdjacentVertex(VTest,11);
	GraphInsertAdjacentVertex(VTest, 13);
	GraphInsertAdjacentVertex(VTest, 15);
	printf("%d\n",IsAdjacentGraphEmpty(VTest));
	printf("%d\n",GraphAdjacentVertexInfo(GraphVertexFirstAdjacent(VTest)));
	printf("%d\n",IsAdjacentWithVertex(VTest, 13));
	
	//GraphInsertAdjacentVertex(VTest, 11);
	printf("%d\n",IsAdjacentGraphEmpty(VTest));
	printf("%d\n",GraphAdjacentVertexInfo(GraphVertexFirstAdjacent(VTest)));
	printf("%d\n",IsAdjacentWithVertex(VTest, 11));

	PTest = GraphAdjacentAddressSearch(VTest, 11);
	printf("%d\n",GraphAdjacentVertexInfo(PTest));

	VTest = GraphAddressSearch(G, 5);
	GraphInsertAdjacentVertex(VTest, 13);
	GraphInsertAdjacentVertex(VTest, 11);
	//GraphInsertAdjacentVertex(VTest, 15);
	PTest = GraphAdjacentAddressSearch(VTest, 11);
	printf("%d\n",GraphAdjacentVertexInfo(PTest));

	GraphPrintInfo(G);

	printf("jumlah vertex : %d\n", GraphNbElmt(G));

	VTest = GraphAddressSearch(G, 10);
	GraphDeleteAdjacentVertex(VTest, 17);

	GraphPrintInfo(G);

	GraphDeleteVertex(&G, 20);
	GraphPrintInfo(G);

	return 0;
}