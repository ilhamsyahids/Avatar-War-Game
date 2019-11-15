//==============================================//
//								       			//
//					SkillQueue             		//
//                                     			//
//----------------------------------------------//
// File : skillqueue.h */              			//
//----------------------------------------------//
// Definisi ADT SkillQueue dengan representasi	//
// array secara eksplisit dan alokasi dinamik 	//
// Implementasi Versi III dengan circular buffer//
//==============================================//

#ifndef _skillqueue_H
#define _skillqueue_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "skill.h"

///////////////////////////////////
//		  CONST & TYPEDEF	 	 //
///////////////////////////////////
#define SkillQueueNil 0
/* Konstanta untuk mendefinisikan address tak terdefinisi */

#define SkillQueueMaximumElement 10
/* Konstanta untuk maksimum jumlah elemen SkillQueue */

typedef Skill SkillQueueInfotype; 	/* Tipe Elemen tabel */
typedef int SkillQueueAddress; 		/* TIpe Indeks tabel */


///////////////////////////
// 	Definisi SkillQueue  //
///////////////////////////
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct
{
    SkillQueueInfotype *T;  /* tabel penyimpan elemen */
    SkillQueueAddress HEAD; /* alamat penghapusan */
    SkillQueueAddress TAIL; /* alamat penambahan */
    int MaxElement;    /* Max elemen queue */
} SkillQueue;
/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

//////////////////////////
//        SELECTOR      //
//////////////////////////
/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah SkillQueue, maka akses elemen : */
#define SkillQueueHead(Q) 			(Q).HEAD
#define SkillQueueTail(Q) 			(Q).TAIL
#define SkillQueueInfoHead(Q) 		(Q).T[(Q).HEAD]
#define SkillQueueInfoTail(Q) 		(Q).T[(Q).TAIL]
#define SkillQueueMaxElement(Q) 	(Q).MaxElement

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void SkillQueueCreateEmpty(SkillQueue *Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

///////////////////////////
// 		DESTRUCTOR 	 	 //
///////////////////////////
void SkillQueueDealokasi(SkillQueue *Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsSkillQueueEmpty(SkillQueue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */

boolean IsSkillQueueFull(SkillQueue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */

//////////////////////////////////
// 	   SKILLQUEUE OPERATIONS	//
//////////////////////////////////
int SkillQueueNBElmt(SkillQueue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

void SkillQueueAddSkill(SkillQueue *Q, SkillQueueInfotype X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */

void SkillQueueDelSkill(SkillQueue *Q, SkillQueueInfotype *X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
SkillQueueInfotype SkillUseSkill(SkillQueue *Q);
/* Mengeluarkan HEAD dari Q yang berisi Skill menghapusnya dari Q dengan aturan FIFO */
/* X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer setelah
    penghapusan Q mungkin kosong */

void PrintQueueSkill(SkillQueue Q);
/* Proses: Mencetak seluruh Skill pada QueueSkill dengan aturan FIFO */
/* I.S. Sembarang */
/* F.S. Tercetak ke layar daftar skill yang ada dengan "SKILL : [skill], [skill], [skill]", 
    apabila QueueSkill kosong maka akan tercetak ke layar "SKILL : Tidak Ada Skill Tersedia"*/


// Gonna still be added

#endif