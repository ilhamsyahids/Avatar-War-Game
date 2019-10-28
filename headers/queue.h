//==============================================//
//								       			//
//					Queue             			//
//                                     			//
//----------------------------------------------//
// File : queue.h */              				//
//----------------------------------------------//
// Definisi ADT Queue dengan representasi		//
// array secara eksplisit dan alokasi dinamik 	//
// Implementasi Versi III dengan circular buffer//
//==============================================//

#ifndef _QUEUE_H
#define _QUEUE_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
#define QueueNil 0;
/* Konstanta untuk mendefinisikan address tak terdefinisi */

typedef int QueueInfotype;	/* Tipe Elemen tabel */
typedef int QueueAddress; 	/* TIpe Indeks tabel */


///////////////////////////
// 	   Definisi Queue    //
///////////////////////////
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct
{
    QueueInfotype *T;  /* tabel penyimpan elemen */
    QueueAddress HEAD; /* alamat penghapusan */
    QueueAddress TAIL; /* alamat penambahan */
    int MaxElement;    /* Max elemen queue */
} Queue;
/* Definisi Queue kosong: HEAD=QueueNil; TAIL=QueueNil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define QueueHead(Q) 		(Q).HEAD
#define QueueTail(Q) 		(Q).TAIL
#define QueueInfoHead(Q) 	(Q).T[(Q).HEAD]
#define QueueInfoTail(Q) 	(Q).T[(Q).TAIL]
#define QueueMaxElement(Q) 	(Q).MaxElement

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void QueueCreateEmpty(Queue *Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

///////////////////////////
// 		DESTRUCTOR 	 	 //
///////////////////////////
void QueueDealokasi(Queue *Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsQueueEmpty(Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */

boolean IsQueueFull(Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElement */

///////////////////////////////
// 	     QUEUE OPERATIONS 	 //
///////////////////////////////
int QueueNBElmt(Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

void QueueAddElement(Queue *Q, QueueInfotype X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */

void QueueDelElement(Queue *Q, QueueInfotype *X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

#endif