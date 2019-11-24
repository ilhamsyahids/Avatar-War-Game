//==============================================//
//                                              //
//        	  BuildingRelationGraph	        	//
//                                              //
//----------------------------------------------//
// File : buildingrelationgraph.h */ 	       	//
//----------------------------------------------//
// Definisi ADT BuildingRelationGraph  			//
// Dengan relasi direpresentasikan dalam 		//
// adjacency list								//
//==============================================//

#ifndef _BUILDINGRELATIONGRAPH_H
#define _BUILDINGRELATIONGRAPH_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

///////////////////////////////////
//        CONST & TYPEDEF        //
///////////////////////////////////
#define BuildingRelationGraphNil NULL

typedef int BuildingRelationGraphInfotype;
typedef struct TBuildingRelationGraphVertex *BuildingRelationGraphAddress;
typedef struct TBuildingRelationGraphAdjacentVertex *AdjacentBuildingRelationGraphAddress;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Definisi BuildingRelationGraph, BuildingRelationGraphVertex dan BuildingRelationGraphAdjacentVertex //
////////////////////////////////////////////////////////// ///////////////////////////////////////////////
typedef struct TBuildingRelationGraphVertex
{
	BuildingRelationGraphInfotype info;
	BuildingRelationGraphAddress next;
	AdjacentBuildingRelationGraphAddress firstAdjacent;
} BuildingRelationGraphVertex;

typedef struct TBuildingRelationGraphAdjacentVertex
{
	BuildingRelationGraphInfotype info;
	AdjacentBuildingRelationGraphAddress nextAdjacent;
} BuildingRelationGraphAdjacentVertex;

typedef struct
{
	BuildingRelationGraphAddress First;
} BuildingRelationGraph;

/* BuildingRelationGraph Kosong : BuildingRelationGraphFirstAddress(G) = BuildingRelationGraphNil */
/* Setiap vertex pada graph dengan address V dapat diacu dengan BuildingRelationGraphVertexInfo(V), BuildingRelationGraphVertexNext(V) */
/* Untuk melihat ketetanggaan sebuah vertex dengan vertex lain dilakukan dengan mengakses 
	BuildingRelationGraphVertexFirstAdjacent(V) */
/* Vertex dengan next = BuildingRelationGraphNil berarti merupakan vertex terakhir pada graph */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika G adalah BuildingRelationGraph, V adalah BuildingRelationGraphAddress dan P adalah AdjacentBuildingRelationGraphAddress, maka akses elemen : */
#define BuildingRelationGraphVertexInfo(V) (V)->info
#define BuildingRelationGraphVertexNext(V) (V)->next
#define BuildingRelationGraphVertexFirstAdjacent(V) (V)->firstAdjacent
#define BuildingRelationGraphAdjacentVertexInfo(P) (P)->info
#define BuildingRelationGraphAdjacentVertexNextAdjacent(P) (P)->nextAdjacent
#define BuildingRelationGraphFirstAddress(G) ((G).First)

///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void BuildingRelationGraphCreateEmpty(BuildingRelationGraph *G);
/* I.S. Sembarang */
/* F.S. Terbentuk BuildingRelationGraph Kosong */

BuildingRelationGraphAddress BuildingRelationGraphVertexAlokasi(BuildingRelationGraphInfotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilkan V, */
/* maka BuildingRelationGraphVertexInfo(V) = X, BuildingRelationGraphVertexNext(V) = Nil dan */
/* BuildingRelationGraphVertextFirstAdjacent = Nil */

AdjacentBuildingRelationGraphAddress BuildingRelationGraphAdjacentVertexAlokasi(BuildingRelationGraphInfotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilakn P, */
/* maka BuildingRelationGraphAdjacentVertexInfo(P) = X, BuildingRelationGraphAdjacentVertexNextAdjacent(P) = Nil */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void BuildingRelationGraphVertexDealokasi(BuildingRelationGraphAddress V);
/* I.S. V terdefinisi */
/* F.S. V dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address V */

void BuildingRelationGraphAdjacentVertexDealokasi(AdjacentBuildingRelationGraphAddress P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsBuildingRelationGraphEmpty(BuildingRelationGraph G);
/* Mengirim true jika BuildingRelationGraph kosong */

boolean IsAdjacentBuildingRelationGraphEmpty(BuildingRelationGraphAddress V);
/* Mengirim true jika vertex dengan BuildingRelationGraphAddress V tidak memiliki tetangga */

boolean IsVertexInBuildingRelationGraph(BuildingRelationGraph G, BuildingRelationGraphInfotype X);
/* Mengirim true jika vertex dengan info X ada pada BuildingRelationGraph */

boolean IsAdjacentWithVertex(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X);
/* Mengirim true jika vertex dengan info X adalah tetagga dengan Vertex dengan address V */

//////////////////////////
//    BuildingRelationGraph OPERATIONS  //
//////////////////////////
BuildingRelationGraphAddress BuildingRelationGraphAddressSearch(BuildingRelationGraph G, BuildingRelationGraphInfotype X);
/* Mencari apakah ada elemen BuildingRelationGraph (vertex) dengan BuildingRelationGraphVertexInfo(V) = X */
/* Jika ada, mengirimkan address vertex tersebut */
/* Jika tidak ada, mengirimkan Nil */

AdjacentBuildingRelationGraphAddress BuildingRelationGraphAdjacentAddressSearch(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X);
/* Mencari apakah vertex dengan address V bertetangga dengan X */
/* Jika ya, mengirimkan address X pada adjacency list */

void BuildingRelationGraphInsertVertex(BuildingRelationGraph *G, BuildingRelationGraphInfotype X);
/* I.S. G mungkin kosong */
/* F.S. Elemen terakhir G adalah vertex dengan info X */
/* Dilakukan pengecekan terlebih dahulu agar tidak ada 2 vertex yang sama di BuildingRelationGraph */
/* Pastikan dilakukan alokasi sebelum memasukkan ke BuildingRelationGraph */

void BuildingRelationGraphInsertAdjacentVertex(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X);
/* I.S. BuildingRelationGraphVertexFirstAdjacent(V) mungkin kosong */
/* F.S. Elemen terakhir adjacency list V adalah X */
/* Dilakukan pengecekan terlebihi dahulu agar tidak ada 2 adjacency vertex yang dimasukkan */
/* Pastikan melakukan alokasi terlebih dahulu */

void BuildingRelationGraphDeleteAdjacentVertex(BuildingRelationGraphAddress V, BuildingRelationGraphInfotype X);
/* I.S. V Sembarang */
/* F.S. Jika ada elemen adjacent vertex BuildingRelationGraph beraddress P, dengan BuildingRelationGraphAdjacentVertexInfo(P) = X  */
/* Maka P dihapus dari BuildingRelationGraph dan di-dealokasi */
/* Jika tidak ada elemen adjacent vertex BuildingRelationGraph dengan BuildingRelationGraphAdjacentVertexInfo(P) = X, maka adjacency list tetap */
/* Adjacency List mungkin menjadi kosong karena penghapusan */

void BuildingRelationGraphDeleteVertex(BuildingRelationGraph *G, BuildingRelationGraphInfotype X);
/* I.S. G Sembarang */
/* F.S. Jika ada elemen BuildingRelationGraph beraddress V, dengan BuildingRelationGraphVertexInfo(V) = X  */
/* Maka V dihapus dari BuildingRelationGraph dan di-dealokasi */
/* Jika tidak ada elemen BuildingRelationGraph dengan BuildingRelationGraphVertexInfo(V) = X, maka BuildingRelationGraph tetap */
/* BuildingRelationGraph mungkin menjadi kosong karena penghapusan */
/* PERHATIKAN bahwa jika vertex X dihapus, maka vertex lain yang bertetangga dengan X */
/* Juga harus dihapus ketetanggaannya */

int BuildingRelationGraphNbElmt(BuildingRelationGraph G);
/* Mengembalikan jumlah vertex yang terdapat dalam BuildingRelationGraph G */

void BuildingRelationGraphPrintInfo(BuildingRelationGraph G);
/* I.S. BuildingRelationGraph mungkin kosong */
/* F.S. Jika BuildingRelationGraph tidak kosong, isi BuildingRelationGraph dicetak ke bawah dengan format :*/
/* <info vertex 1> bertetangga dengan <info vertex 2> .... */
/* <info vertex 2> bertetangga dengan <info vertex 1> .... */
/* dan seterusnya */
/* Tambahkan enter di akhir penulisan */

#endif