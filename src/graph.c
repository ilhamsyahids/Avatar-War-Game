//==============================================//
//                                              //
//                 	  Graph	                  	//
//                                              //
//----------------------------------------------//
// File : graph.c*/                	      		//
//----------------------------------------------//
// Implementasi ADT Graph  			       		//
// Dengan relasi direpresentasikan dalam 		//
// adjacency list								//
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "graph.h"

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void GraphCreateEmpty(Graph *G)
/* I.S. Sembarang */
/* F.S. Terbentuk Graph Kosong */
{
	GraphFirstAddress(*G) = GraphNil;
}

GraphAddress GraphVertexAlokasi(GraphInfotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilkan V, */
/* maka GraphVertexInfo(V) = X, GraphVertexNext(V) = GraphNil dan */
/* GraphVertextFirstAdjacent = GraphNil */
{
	GraphAddress V;

	V = (GraphAddress) malloc (1* sizeof(GraphVertex));

	if(V){
		GraphVertexInfo(V) = X;
		GraphVertexNext(V) = GraphNil;
		GraphVertexFirstAdjacent(V) = GraphNil;
	}

	return V;
}

AdjacentGraphAddress GraphAdjacentVertexAlokasi(GraphInfotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilakn P, */
/* maka GraphAdjacentVertexInfo(P) = X, GraphAdjacentVertexNextAdjacent(P) = GraphNil */
{
	AdjacentGraphAddress P;

	P = (AdjacentGraphAddress) malloc (1* sizeof(GraphAdjacentVertex));

	if(P){
		GraphAdjacentVertexInfo(P)  = X;
		GraphAdjacentVertexNextAdjacent(P) = GraphNil;
	}

	return P;
}

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void GraphVertexDealokasi(GraphAddress V)
/* I.S. V terdefinisi */
/* F.S. V dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address V */
{
	free(V);
}

void GraphAdjacentVertexDealokasi(AdjacentGraphAddress P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(P);
}

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsGraphEmpty(Graph G)
/* Mengirim true jika Graph kosong */
{
	return GraphFirstAddress(G) == GraphNil;
}

boolean IsAdjacentGraphEmpty(GraphAddress V)
/* Mengirim true jika vertex dengan GraphAddress V tidak memiliki tetangga */
{
	return GraphVertexFirstAdjacent(V) == GraphNil;
}

boolean IsVertexInGraph(Graph G, GraphInfotype X)
/* Mengirim true jika vertex dengan info X ada pada Graph */
{	
	GraphAddress V;
	boolean found;

	found = false;
	if(IsGraphEmpty(G)){
		return found;
	} else{
		V = GraphFirstAddress(G);
		found = (GraphVertexInfo(V) == X);
		while((GraphVertexNext(V) != GraphNil) && (!found)){
			V = GraphVertexNext(V);
			found = (GraphVertexInfo(V) == X);
		}
		return found;
	}
}

boolean IsAdjacentWithVertex(GraphAddress V, GraphInfotype X)
/* Mengirim true jika vertex dengan info X adalah tetagga dengan Vertex dengan address V */ 
{
	AdjacentGraphAddress P;
	boolean found;

	found = false;
	if(IsAdjacentGraphEmpty(V)){
		return found;
	} else{
		P = GraphVertexFirstAdjacent(V);
		found = (GraphAdjacentVertexInfo(P) == X);
		while((GraphAdjacentVertexNextAdjacent(P) != GraphNil) && (!found)){
			P = GraphAdjacentVertexNextAdjacent(P);
			found = (GraphAdjacentVertexInfo(P) == X);
		}
		return found;
	}
}

//////////////////////////
//    GRAPH OPERATIONS  //
//////////////////////////
GraphAddress GraphAddressSearch(Graph G, GraphInfotype X)
/* Mencari apakah ada elemen graph (vertex) dengan GraphVertexInfo(V) = X */
/* Jika ada, mengirimkan address vertex tersebut */
/* Jika tidak ada, mengirimkan Nil */
{
	GraphAddress V;
	boolean found;

	V = GraphNil;
	found = false;

	if(IsGraphEmpty(G)){
		return V;
	} else{
		V = GraphFirstAddress(G);
		found = (GraphVertexInfo(V) == X);
		while((GraphVertexNext(V) != GraphNil) && (!found)){
			V = GraphVertexNext(V);
			found = (GraphVertexInfo(V) == X);
		}
		if(GraphVertexInfo(V) != X){
			V = GraphNil;
		}
		return V;
	}
}

AdjacentGraphAddress GraphAdjacentAddressSearch(GraphAddress V, GraphInfotype X)
/* Mencari apakah vertex dengan address V bertetangga dengan X */
/* Jika ya, mengirimkan address X pada adjacency list */
{
	AdjacentGraphAddress P;
	boolean found;

	P = GraphNil;
	found = false;

	if(IsAdjacentGraphEmpty(V)){
		return P;
	} else{
		P = GraphVertexFirstAdjacent(V);
		found = (GraphAdjacentVertexInfo(P) == X);
		while((GraphAdjacentVertexNextAdjacent(P) != GraphNil) && (!found)){
			P = GraphAdjacentVertexNextAdjacent(P);
			found = (GraphAdjacentVertexInfo(P) == X);
		}
		if(GraphAdjacentVertexInfo(P) != X){
			P = GraphNil;
		}
		return P;
	}
}

void GraphInsertVertex(Graph *G, GraphInfotype X)
/* I.S. G mungkin kosong */
/* F.S. Elemen terakhir G adalah vertex dengan info X */
/* Dilakukan pengecekan terlebih dahulu agar tidak ada 2 vertex yang sama di graph */
/* Pastikan dilakukan alokasi sebelum memasukkan ke Graph */
{
	GraphAddress V;
	GraphAddress VLast;

	V = GraphVertexAlokasi(X);

	if(IsGraphEmpty(*G)){
		GraphFirstAddress(*G) = V;
	} else{
		if(!IsVertexInGraph(*G, X)){
			VLast = GraphFirstAddress(*G);
			while(GraphVertexNext(VLast) != GraphNil){
				VLast = GraphVertexNext(VLast);
			}
			GraphVertexNext(VLast) = V;
		}
	}
}

void GraphInsertAdjacentVertex(GraphAddress V, GraphInfotype X)
/* I.S. GraphVertexFirstAdjacent(V) mungkin kosong */
/* F.S. Elemen terakhir adjacency list V adalah X */
/* Dilakukan pengecekan terlebihi dahulu agar tidak ada 2 adjacency vertex yang dimasukkan */
/* Pastikan melakukan alokasi terlebih dahulu */
{
	AdjacentGraphAddress P;
	AdjacentGraphAddress PLast;

	P = GraphAdjacentVertexAlokasi(X);
	if(IsAdjacentGraphEmpty(V)){
		GraphVertexFirstAdjacent(V) = P;
	} else{
		if(!IsAdjacentWithVertex(V, X)){
			PLast = GraphVertexFirstAdjacent(V);
			while(GraphAdjacentVertexNextAdjacent(PLast) != GraphNil){
				PLast = GraphAdjacentVertexNextAdjacent(PLast);
			}
			GraphAdjacentVertexNextAdjacent(PLast) = P;
		}
	}
}

void GraphDeleteAdjacentVertex(GraphAddress V, GraphInfotype X)
/* I.S. V Sembarang */
/* F.S. Jika ada elemen adjacent vertex graph beraddress P, dengan GraphAdjacentVertexInfo(P) = X  */
/* Maka P dihapus dari graph dan di-dealokasi */
/* Jika tidak ada elemen adjacent vertex graph dengan GraphAdjacentVertexInfo(P) = X, maka adjacency list tetap */
/* Adjacency List mungkin menjadi kosong karena penghapusan */
{
	AdjacentGraphAddress P;
	AdjacentGraphAddress PPrec;
	AdjacentGraphAddress PSucc;
	AdjacentGraphAddress PDel;

	if(IsAdjacentWithVertex(V, X)){
		P = GraphAdjacentAddressSearch(V, X);
		if (P == GraphVertexFirstAdjacent(V)){ // First Element
			PDel = P;
			GraphVertexFirstAdjacent(V) = GraphAdjacentVertexNextAdjacent(P);
			GraphAdjacentVertexDealokasi(PDel);
		} else{
			PPrec = GraphVertexFirstAdjacent(V);
			while(GraphAdjacentVertexNextAdjacent(PPrec) != P){
				PPrec = GraphAdjacentVertexNextAdjacent(PPrec);
			}
			PDel = P;
			PSucc = GraphAdjacentVertexNextAdjacent(P);
			GraphAdjacentVertexNextAdjacent(PPrec) = PSucc;
			GraphAdjacentVertexDealokasi(PDel);
		}

	} 
}

void GraphDeleteVertex(Graph *G, GraphInfotype X)
/* I.S. G Sembarang */
/* F.S. Jika ada elemen graph beraddress V, dengan GraphVertexInfo(V) = X  */
/* Maka V dihapus dari graph dan di-dealokasi */
/* Jika tidak ada elemen graph dengan GraphVertexInfo(V) = X, maka graph tetap */
/* Graph mungkin menjadi kosong karena penghapusan */
/* PERHATIKAN bahwa jika vertex X dihapus, maka vertex lain yang bertetangga dengan X */
/* Juga harus dihapus ketetanggaannya */
{
	GraphAddress V;
	GraphAddress VPrec;
	GraphAddress VSucc;
	GraphAddress VDel;

	if(IsVertexInGraph(*G, X)){
		V = GraphAddressSearch(*G, X);
		if(V == GraphFirstAddress(*G)){ // First Element
			VDel = V;
			GraphFirstAddress(*G) = GraphVertexNext(V);
			GraphVertexDealokasi(VDel);
		} else{
			VPrec = GraphFirstAddress(*G);
			while(GraphVertexNext(VPrec) != V){
				VPrec = GraphVertexNext(VPrec);
			}
			VDel = V;
			VSucc = GraphVertexNext(V);
			GraphVertexNext(VPrec) = VSucc;
			GraphVertexDealokasi(VDel);
		}
		// Deleting others adjacency
		V = GraphFirstAddress(*G);
		if(IsAdjacentWithVertex(V, X)){
			GraphDeleteAdjacentVertex(V,X);
		}
		while(GraphVertexNext(V) != GraphNil){
			V = GraphVertexNext(V);
			if(IsAdjacentWithVertex(V, X)){
				GraphDeleteAdjacentVertex(V,X);
			}
		}
	}
}

int GraphNbElmt(Graph G)
/* Mengembalikan jumlah vertex yang terdapat dalam graph G */
{
	int count;
	GraphAddress V;

	count = 0;

	if(IsGraphEmpty(G)){
		return count;
	} else{
		V = GraphFirstAddress(G);
		count += 1;
		while(GraphVertexNext(V) != GraphNil){
			V = GraphVertexNext(V);
			count += 1;
		}
		return count;
	}
}

void GraphPrintInfo(Graph G)
/* I.S. Graph mungkin kosong */
/* F.S. Jika Graph tidak kosong, isi graph dicetak ke bawah dengan format :*/
/* <info vertex 1> bertetangga dengan <info vertex 2> .... */
/* <info vertex 2> bertetangga dengan <info vertex 1> .... */
/* dan seterusnya */
/* Tambahkan enter di akhir penulisan */
{
	GraphAddress V;
	AdjacentGraphAddress P;

	if(!IsGraphEmpty(G)){
		V = GraphFirstAddress(G);
		printf("%d berhubungan dengan",GraphVertexInfo(V));

		if(!IsAdjacentGraphEmpty(V)){
			P = GraphVertexFirstAdjacent(V);
			printf(" %d",GraphAdjacentVertexInfo(P));
			
			while(GraphAdjacentVertexNextAdjacent(P) != GraphNil){
				P = GraphAdjacentVertexNextAdjacent(P);
				printf(" %d",GraphAdjacentVertexInfo(P));
			}
		}
		printf("\n");
		while(GraphVertexNext(V) != GraphNil){
			V = GraphVertexNext(V);
			printf("%d berhubungan dengan",GraphVertexInfo(V));
			if(!IsAdjacentGraphEmpty(V)){
				P = GraphVertexFirstAdjacent(V);
				printf(" %d",GraphAdjacentVertexInfo(P));
				while(GraphAdjacentVertexNextAdjacent(P) != GraphNil){
					P = GraphAdjacentVertexNextAdjacent(P);
					printf(" %d",GraphAdjacentVertexInfo(P));
				}
			}
			printf("\n");
		}
	} 
}
