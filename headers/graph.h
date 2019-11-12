//==============================================//
//                                              //
//                 	  Graph	                  	//
//                                              //
//----------------------------------------------//
// File : graph.h */                	      	//
//----------------------------------------------//
// Definisi ADT Graph  			       			//
// Dengan relasi direpresentasikan dalam 		//
// adjacency list								//
//==============================================//

#ifndef _GRAPH_H
#define _GRAPH_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

///////////////////////////////////
//        CONST & TYPEDEF        //
///////////////////////////////////
#define GraphNil NULL

typedef int GraphInfotype;
typedef struct TGraphVertex *GraphAddress;
typedef struct TGraphAdjacentVertex *AdjacentGraphAddress;

//////////////////////////////////////////////////////////
//  Definisi Graph, GraphVertex dan GraphAdjacentVertex //
////////////////////////////////////////////////////////// 
typedef struct TGraphVertex {
	GraphInfotype info;
	GraphAddress next;
	AdjacentGraphAddress firstAdjacent;
} GraphVertex;

typedef struct TGraphAdjacentVertex {
	GraphInfotype info;
	AdjacentGraphAddress nextAdjacent;
} GraphAdjacentVertex;

typedef struct {
	GraphAddress First;
} Graph;

/* Graph Kosong : GraphFirstAddress(G) = GraphNil */
/* Setiap vertex pada graph dengan address V dapat diacu dengan GraphVertexInfo(V), GraphVertexNext(V) */
/* Untuk melihat ketetanggaan sebuah vertex dengan vertex lain dilakukan dengan mengakses 
	GraphVertexFirstAdjacent(V) */
/* Vertex dengan next = GraphNil berarti merupakan vertex terakhir pada graph */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika G adalah Graph, V adalah GraphAddress dan P adalah AdjacentGraphAddress, maka akses elemen : */
#define GraphVertexInfo(V)					(V)->info
#define GraphVertexNext(V) 					(V)->next
#define GraphVertexFirstAdjacent(V)			(V)->firstAdjacent
#define GraphAdjacentVertexInfo(P) 			(P)->info
#define GraphAdjacentVertexNextAdjacent(P) 	(P)->nextAdjacent
#define GraphFirstAddress(G) 				((G).First)


///////////////////////////
//       CONSTRUCTOR     //
///////////////////////////
void GraphCreateEmpty(Graph *G);
/* I.S. Sembarang */
/* F.S. Terbentuk Graph Kosong */

GraphAddress GraphVertexAlokasi(GraphInfotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilkan V, */
/* maka GraphVertexInfo(V) = X, GraphVertexNext(V) = Nil dan */
/* GraphVertextFirstAdjacent = Nil */

AdjacentGraphAddress GraphAdjacentVertexAlokasi(GraphInfotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misal menghasilakn P, */
/* maka GraphAdjacentVertexInfo(P) = X, GraphAdjacentVertexNextAdjacent(P) = Nil */

///////////////////////////
//       DESTRUCTOR      //
///////////////////////////
void GraphVertexDealokasi(GraphAddress V);
/* I.S. V terdefinisi */
/* F.S. V dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address V */

void GraphAdjacentVertexDealokasi(AdjacentGraphAddress P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

///////////////////////////
//       PREDIKAT        //
///////////////////////////
boolean IsGraphEmpty(Graph G);
/* Mengirim true jika Graph kosong */

boolean IsAdjacentGraphEmpty(GraphAddress V);
/* Mengirim true jika vertex dengan GraphAddress V tidak memiliki tetangga */

boolean IsVertexInGraph(Graph G, GraphInfotype X);
/* Mengirim true jika vertex dengan info X ada pada Graph */

boolean IsAdjacentWithVertex(GraphAddress V, GraphInfotype X);
/* Mengirim true jika vertex dengan info X adalah tetagga dengan Vertex dengan address V */ 

//////////////////////////
//    GRAPH OPERATIONS  //
//////////////////////////
GraphAddress GraphAddressSearch(Graph G, GraphInfotype X);
/* Mencari apakah ada elemen graph (vertex) dengan GraphVertexInfo(V) = X */
/* Jika ada, mengirimkan address vertex tersebut */
/* Jika tidak ada, mengirimkan Nil */

AdjacentGraphAddress GraphAdjacentAddressSearch(GraphAddress V, GraphInfotype X);
/* Mencari apakah vertex dengan address V bertetangga dengan X */
/* Jika ya, mengirimkan address X pada adjacency list */

void GraphInsertVertex(Graph *G, GraphInfotype X);
/* I.S. G mungkin kosong */
/* F.S. Elemen terakhir G adalah vertex dengan info X */
/* Dilakukan pengecekan terlebih dahulu agar tidak ada 2 vertex yang sama di graph */
/* Pastikan dilakukan alokasi sebelum memasukkan ke Graph */

void GraphInsertAdjacentVertex(GraphAddress V, GraphInfotype X);
/* I.S. GraphVertexFirstAdjacent(V) mungkin kosong */
/* F.S. Elemen terakhir adjacency list V adalah X */
/* Dilakukan pengecekan terlebihi dahulu agar tidak ada 2 adjacency vertex yang dimasukkan */
/* Pastikan melakukan alokasi terlebih dahulu */

void GraphDeleteAdjacentVertex(GraphAddress V, GraphInfotype X);
/* I.S. V Sembarang */
/* F.S. Jika ada elemen adjacent vertex graph beraddress P, dengan GraphAdjacentVertexInfo(P) = X  */
/* Maka P dihapus dari graph dan di-dealokasi */
/* Jika tidak ada elemen adjacent vertex graph dengan GraphAdjacentVertexInfo(P) = X, maka adjacency list tetap */
/* Adjacency List mungkin menjadi kosong karena penghapusan */

void GraphDeleteVertex(Graph *G, GraphInfotype X);
/* I.S. G Sembarang */
/* F.S. Jika ada elemen graph beraddress V, dengan GraphVertexInfo(V) = X  */
/* Maka V dihapus dari graph dan di-dealokasi */
/* Jika tidak ada elemen graph dengan GraphVertexInfo(V) = X, maka graph tetap */
/* Graph mungkin menjadi kosong karena penghapusan */
/* PERHATIKAN bahwa jika vertex X dihapus, maka vertex lain yang bertetangga dengan X */
/* Juga harus dihapus ketetanggaannya */

int GraphNbElmt(Graph G);
/* Mengembalikan jumlah vertex yang terdapat dalam graph G */

void GraphPrintInfo(Graph G);
/* I.S. Graph mungkin kosong */
/* F.S. Jika Graph tidak kosong, isi graph dicetak ke bawah dengan format :*/
/* <info vertex 1> bertetangga dengan <info vertex 2> .... */
/* <info vertex 2> bertetangga dengan <info vertex 1> .... */
/* dan seterusnya */
/* Tambahkan enter di akhir penulisan */
#endif