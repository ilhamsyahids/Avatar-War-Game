//==============================================//
//                                              //
//        	  BuildingRelationGraph	        	//
//                                              //
//----------------------------------------------//
// File : buildingrelationgraph.c */ 	       	//
//----------------------------------------------//
// Definisi ADT BuildingRelationGraph  			//
// Dengan relasi direpresentasikan dalam 		//
// adjacency list								//
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "buildingrelationgraph.h"

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void BuildingRelationGraphCreateEmpty(BuildingRelationGraph *G)
/* I.S. Sembarang */
/* F.S. Terbentuk BuildingRelationGraph Kosong */
{
	BuildingRelationGraphFirstAddress(*G) = BuildingRelationGraphNil;
}

BuildingRelationGraphAddress BuildingRelationGraphVertexAlokasi(BuildingRelationGraphInfotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilkan V, */
/* maka BuildingRelationGraphVertexInfo(V) = X, BuildingRelationGraphVertexNext(V) = BuildingRelationGraphNil dan */
/* BuildingRelationGraphVertextFirstAdjacent = BuildingRelationGraphNil */
{
	BuildingRelationGraphAddress V;

	V = (BuildingRelationGraphAddress) malloc (1* sizeof(BuildingRelationGraphVertex));

	if(V){
		BuildingRelationGraphVertexInfo(V) = X;
		BuildingRelationGraphVertexNext(V) = BuildingRelationGraphNil;
		BuildingRelationGraphVertexFirstAdjacent(V) = BuildingRelationGraphNil;
	}

	return V;
}

AdjacentBuildingRelationGraphAddress BuildingRelationGraphAdjacentVertexAlokasi(BuildingRelationGraphInfotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilakn P, */
/* maka BuildingRelationGraphAdjacentVertexInfo(P) = X, BuildingRelationGraphAdjacentVertexNextAdjacent(P) = BuildingRelationGraphNil */
{
	AdjacentBuildingRelationGraphAddress P;

	P = (AdjacentBuildingRelationGraphAddress) malloc (1* sizeof(BuildingRelationGraphAdjacentVertex));

	if(P){
		BuildingRelationGraphAdjacentVertexInfo(P)  = X;
		BuildingRelationGraphAdjacentVertexNextAdjacent(P) = BuildingRelationGraphNil;
	}

	return P;
}

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void BuildingRelationGraphVertexDealokasi(BuildingRelationGraphAddress V)
/* I.S. V terdefinisi */
/* F.S. V dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address V */
{
	free(V);
}

void BuildingRelationGraphAdjacentVertexDealokasi(AdjacentBuildingRelationGraphAddress P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(P);
}

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsBuildingRelationGraphEmpty(BuildingRelationGraph G)
/* Mengirim true jika BuildingRelationGraph kosong */
{
	return BuildingRelationGraphFirstAddress(G) == BuildingRelationGraphNil;
}

boolean IsAdjacentBuildingRelationGraphEmpty(BuildingRelationGraphAddress V)
/* Mengirim true jika vertex dengan BuildingRelationGraphAddress V tidak memiliki tetangga */
{
	return BuildingRelationGraphVertexFirstAdjacent(V) == BuildingRelationGraphNil;
}

boolean IsVertexInBuildingRelationGraph(BuildingRelationGraph G, BuildingRelationGraphInfotype X)
/* Mengirim true jika vertex dengan info X ada pada BuildingRelationGraph */
{	
	BuildingRelationGraphAddress V;
	boolean found;

	found = false;
	if(IsBuildingRelationGraphEmpty(G)){
		return found;
	} else{
		V = BuildingRelationGraphFirstAddress(G);
		found = (BuildingRelationGraphVertexInfo(V) == X);
		while((BuildingRelationGraphVertexNext(V) != BuildingRelationGraphNil) && (!found)){
			V = BuildingRelationGraphVertexNext(V);
			found = (BuildingRelationGraphVertexInfo(V) == X);
		}
		return found;
	}
}

boolean IsAdjacentWithVertex(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X)
/* Mengirim true jika vertex dengan info X adalah tetagga dengan Vertex dengan address V */ 
{
	AdjacentBuildingRelationGraphAddress P;
	boolean found;

	found = false;
	if(IsAdjacentBuildingRelationGraphEmpty(V)){
		return found;
	} else{
		P = BuildingRelationGraphVertexFirstAdjacent(V);
		found = (BuildingRelationGraphAdjacentVertexInfo(P) == X);
		while((BuildingRelationGraphAdjacentVertexNextAdjacent(P) != BuildingRelationGraphNil) && (!found)){
			P = BuildingRelationGraphAdjacentVertexNextAdjacent(P);
			found = (BuildingRelationGraphAdjacentVertexInfo(P) == X);
		}
		return found;
	}
}

//////////////////////////
//    BuildingRelationGraph OPERATIONS  //
//////////////////////////
BuildingRelationGraphAddress BuildingRelationGraphAddressSearch(BuildingRelationGraph G, BuildingRelationGraphInfotype X)
/* Mencari apakah ada elemen BuildingRelationGraph (vertex) dengan BuildingRelationGraphVertexInfo(V) = X */
/* Jika ada, mengirimkan address vertex tersebut */
/* Jika tidak ada, mengirimkan Nil */
{
	BuildingRelationGraphAddress V;
	boolean found;

	V = BuildingRelationGraphNil;
	found = false;

	if(IsBuildingRelationGraphEmpty(G)){
		return V;
	} else{
		V = BuildingRelationGraphFirstAddress(G);
		found = (BuildingRelationGraphVertexInfo(V) == X);
		while((BuildingRelationGraphVertexNext(V) != BuildingRelationGraphNil) && (!found)){
			V = BuildingRelationGraphVertexNext(V);
			found = (BuildingRelationGraphVertexInfo(V) == X);
		}
		if(BuildingRelationGraphVertexInfo(V) != X){
			V = BuildingRelationGraphNil;
		}
		return V;
	}
}

AdjacentBuildingRelationGraphAddress BuildingRelationGraphAdjacentAddressSearch(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X)
/* Mencari apakah vertex dengan address V bertetangga dengan X */
/* Jika ya, mengirimkan address X pada adjacency list */
{
	AdjacentBuildingRelationGraphAddress P;
	boolean found;

	P = BuildingRelationGraphNil;
	found = false;

	if(IsAdjacentBuildingRelationGraphEmpty(V)){
		return P;
	} else{
		P = BuildingRelationGraphVertexFirstAdjacent(V);
		found = (BuildingRelationGraphAdjacentVertexInfo(P) == X);
		while((BuildingRelationGraphAdjacentVertexNextAdjacent(P) != BuildingRelationGraphNil) && (!found)){
			P = BuildingRelationGraphAdjacentVertexNextAdjacent(P);
			found = (BuildingRelationGraphAdjacentVertexInfo(P) == X);
		}
		if(BuildingRelationGraphAdjacentVertexInfo(P) != X){
			P = BuildingRelationGraphNil;
		}
		return P;
	}
}

void BuildingRelationGraphInsertVertex(BuildingRelationGraph *G, BuildingRelationGraphInfotype X)
/* I.S. G mungkin kosong */
/* F.S. Elemen terakhir G adalah vertex dengan info X */
/* Dilakukan pengecekan terlebih dahulu agar tidak ada 2 vertex yang sama di BuildingRelationGraph */
/* Pastikan dilakukan alokasi sebelum memasukkan ke BuildingRelationGraph */
{
	BuildingRelationGraphAddress V;
	BuildingRelationGraphAddress VLast;

	V = BuildingRelationGraphVertexAlokasi(X);

	if(IsBuildingRelationGraphEmpty(*G)){
		BuildingRelationGraphFirstAddress(*G) = V;
	} else{
		if(!IsVertexInBuildingRelationGraph(*G, X)){
			VLast = BuildingRelationGraphFirstAddress(*G);
			while(BuildingRelationGraphVertexNext(VLast) != BuildingRelationGraphNil){
				VLast = BuildingRelationGraphVertexNext(VLast);
			}
			BuildingRelationGraphVertexNext(VLast) = V;
		}
	}
}

void BuildingRelationGraphInsertAdjacentVertex(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X)
/* I.S. BuildingRelationGraphVertexFirstAdjacent(V) mungkin kosong */
/* F.S. Elemen terakhir adjacency list V adalah X */
/* Dilakukan pengecekan terlebihi dahulu agar tidak ada 2 adjacency vertex yang dimasukkan */
/* Pastikan melakukan alokasi terlebih dahulu */
{
	AdjacentBuildingRelationGraphAddress P;
	AdjacentBuildingRelationGraphAddress PLast;

	P = BuildingRelationGraphAdjacentVertexAlokasi(X);
	if(IsAdjacentBuildingRelationGraphEmpty(V)){
		BuildingRelationGraphVertexFirstAdjacent(V) = P;
	} else{
		if(!IsAdjacentWithVertex(V, X)){
			PLast = BuildingRelationGraphVertexFirstAdjacent(V);
			while(BuildingRelationGraphAdjacentVertexNextAdjacent(PLast) != BuildingRelationGraphNil){
				PLast = BuildingRelationGraphAdjacentVertexNextAdjacent(PLast);
			}
			BuildingRelationGraphAdjacentVertexNextAdjacent(PLast) = P;
		}
	}
}

void BuildingRelationGraphDeleteAdjacentVertex(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X)
/* I.S. V Sembarang */
/* F.S. Jika ada elemen adjacent vertex BuildingRelationGraph beraddress P, dengan BuildingRelationGraphAdjacentVertexInfo(P) = X  */
/* Maka P dihapus dari BuildingRelationGraph dan di-dealokasi */
/* Jika tidak ada elemen adjacent vertex BuildingRelationGraph dengan BuildingRelationGraphAdjacentVertexInfo(P) = X, maka adjacency list tetap */
/* Adjacency List mungkin menjadi kosong karena penghapusan */
{
	AdjacentBuildingRelationGraphAddress P;
	AdjacentBuildingRelationGraphAddress PPrec;
	AdjacentBuildingRelationGraphAddress PSucc;
	AdjacentBuildingRelationGraphAddress PDel;

	if(IsAdjacentWithVertex(V, X)){
		P = BuildingRelationGraphAdjacentAddressSearch(V, X);
		if (P == BuildingRelationGraphVertexFirstAdjacent(V)){ // First Element
			PDel = P;
			BuildingRelationGraphVertexFirstAdjacent(V) = BuildingRelationGraphAdjacentVertexNextAdjacent(P);
			BuildingRelationGraphAdjacentVertexDealokasi(PDel);
		} else{
			PPrec = BuildingRelationGraphVertexFirstAdjacent(V);
			while(BuildingRelationGraphAdjacentVertexNextAdjacent(PPrec) != P){
				PPrec = BuildingRelationGraphAdjacentVertexNextAdjacent(PPrec);
			}
			PDel = P;
			PSucc = BuildingRelationGraphAdjacentVertexNextAdjacent(P);
			BuildingRelationGraphAdjacentVertexNextAdjacent(PPrec) = PSucc;
			BuildingRelationGraphAdjacentVertexDealokasi(PDel);
		}

	} 
}

void BuildingRelationGraphDeleteVertex(BuildingRelationGraph *G, BuildingRelationGraphInfotype X)
/* I.S. G Sembarang */
/* F.S. Jika ada elemen BuildingRelationGraph beraddress V, dengan BuildingRelationGraphVertexInfo(V) = X  */
/* Maka V dihapus dari BuildingRelationGraph dan di-dealokasi */
/* Jika tidak ada elemen BuildingRelationGraph dengan BuildingRelationGraphVertexInfo(V) = X, maka BuildingRelationGraph tetap */
/* BuildingRelationGraph mungkin menjadi kosong karena penghapusan */
/* PERHATIKAN bahwa jika vertex X dihapus, maka vertex lain yang bertetangga dengan X */
/* Juga harus dihapus ketetanggaannya */
{
	BuildingRelationGraphAddress V;
	BuildingRelationGraphAddress VPrec;
	BuildingRelationGraphAddress VSucc;
	BuildingRelationGraphAddress VDel;

	if(IsVertexInBuildingRelationGraph(*G, X)){
		V = BuildingRelationGraphAddressSearch(*G, X);
		if(V == BuildingRelationGraphFirstAddress(*G)){ // First Element
			VDel = V;
			BuildingRelationGraphFirstAddress(*G) = BuildingRelationGraphVertexNext(V);
			BuildingRelationGraphVertexDealokasi(VDel);
		} else{
			VPrec = BuildingRelationGraphFirstAddress(*G);
			while(BuildingRelationGraphVertexNext(VPrec) != V){
				VPrec = BuildingRelationGraphVertexNext(VPrec);
			}
			VDel = V;
			VSucc = BuildingRelationGraphVertexNext(V);
			BuildingRelationGraphVertexNext(VPrec) = VSucc;
			BuildingRelationGraphVertexDealokasi(VDel);
		}
		// Deleting others adjacency
		V = BuildingRelationGraphFirstAddress(*G);
		if(IsAdjacentWithVertex(V, X)){
			BuildingRelationGraphDeleteAdjacentVertex(V,X);
		}
		while(BuildingRelationGraphVertexNext(V) != BuildingRelationGraphNil){
			V = BuildingRelationGraphVertexNext(V);
			if(IsAdjacentWithVertex(V, X)){
				BuildingRelationGraphDeleteAdjacentVertex(V,X);
			}
		}
	}
}

int BuildingRelationGraphNbElmt(BuildingRelationGraph G)
/* Mengembalikan jumlah vertex yang terdapat dalam BuildingRelationGraph G */
{
	int count;
	BuildingRelationGraphAddress V;

	count = 0;

	if(IsBuildingRelationGraphEmpty(G)){
		return count;
	} else{
		V = BuildingRelationGraphFirstAddress(G);
		count += 1;
		while(BuildingRelationGraphVertexNext(V) != BuildingRelationGraphNil){
			V = BuildingRelationGraphVertexNext(V);
			count += 1;
		}
		return count;
	}
}

void BuildingRelationGraphPrintInfo(BuildingRelationGraph G)
/* I.S. BuildingRelationGraph mungkin kosong */
/* F.S. Jika BuildingRelationGraph tidak kosong, isi BuildingRelationGraph dicetak ke bawah dengan format :*/
/* <info vertex 1> bertetangga dengan <info vertex 2> .... */
/* <info vertex 2> bertetangga dengan <info vertex 1> .... */
/* dan seterusnya */
/* Tambahkan enter di akhir penulisan */
{
	BuildingRelationGraphAddress V;
	AdjacentBuildingRelationGraphAddress P;

	if(!IsBuildingRelationGraphEmpty(G)){
		V = BuildingRelationGraphFirstAddress(G);
		printf("%d berhubungan dengan",BuildingRelationGraphVertexInfo(V));

		if(!IsAdjacentBuildingRelationGraphEmpty(V)){
			P = BuildingRelationGraphVertexFirstAdjacent(V);
			printf(" %d",BuildingRelationGraphAdjacentVertexInfo(P));
			
			while(BuildingRelationGraphAdjacentVertexNextAdjacent(P) != BuildingRelationGraphNil){
				P = BuildingRelationGraphAdjacentVertexNextAdjacent(P);
				printf(" %d",BuildingRelationGraphAdjacentVertexInfo(P));
			}
		}
		printf("\n");
		while(BuildingRelationGraphVertexNext(V) != BuildingRelationGraphNil){
			V = BuildingRelationGraphVertexNext(V);
			printf("%d berhubungan dengan",BuildingRelationGraphVertexInfo(V));
			if(!IsAdjacentBuildingRelationGraphEmpty(V)){
				P = BuildingRelationGraphVertexFirstAdjacent(V);
				printf(" %d",BuildingRelationGraphAdjacentVertexInfo(P));
				while(BuildingRelationGraphAdjacentVertexNextAdjacent(P) != BuildingRelationGraphNil){
					P = BuildingRelationGraphAdjacentVertexNextAdjacent(P);
					printf(" %d",BuildingRelationGraphAdjacentVertexInfo(P));
				}
			}
			printf("\n");
		}
	} 
}