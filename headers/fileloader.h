//==============================================//
//                                              //
//                 FileLoader                  	//
//                                              //
//----------------------------------------------//
// File : fileloader.h */                      	//
//----------------------------------------------//
// Definisi modul FileLoader         			//
// FileLoader adalah modul yang mengurus 		//
// seluruh pembacaan file konfigurasi			//
//==============================================//

#ifndef _FILELOADER_H
#define _FILELOADER_H

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "mesinkar.h"
#include "gamemap.h"

///////////////////////////////////
// 	     FILELOADER OPERATIONS 	 //
///////////////////////////////////
void LoadingSequence();
/* Seluruh sekuens pembacaan dijalankan pada method ini */
/* I.S : G, Map, Record, CurrentPlayer sembarang */
/* F.S : Terbentuk G dengan atribut Map, Record dan CurrentPlayer sesuai file */
void StartLoading(char* filename);
/* Memulai pembacaan dari file konfigurasi */
/* I.S : Pita file kosong */
/* F.S : File siap dibaca dan sekuens pembacaan dimulai */


void LoadMapSize();
/* Menangani pembacaan ukuran peta dari file */
/* I.S : Map sembarang */
/* F.S : Ukuran Map efektif terdefinisi */

void LoadBuildingCount();
/* Menangani pembacaan banyaknya bangunan pada peta dari file */
/* I.S : Record sembarang */
/* F.S : Ukuran maksimum Record terdefinisi */

void LoadBuildingList();
/* Menangani pembacaan daftar bangunan yang ada di peta */
/* I.S : Ukuran maksimum Record terdefinisi */
/* F.S : Record berisi seluruh bangunan yang ada di file */

void LoadBuildingRelation();
/* Menangani pembacaan hubungan antar bangunan pada peta */
/* I.S : */
/* F.S : */

GameMap CompleteFileLoad();
/* Mengembalikan GameMap yang sudah berisi data lengkap dari file */

#endif