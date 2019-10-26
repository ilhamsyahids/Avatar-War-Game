/* File : player.h */
/* Definisi ADT Player */

#ifndef _player_H
#define _player_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

/* Definisi Player */
typedef struct {
    int role;  	 /* [1..2] menandakan Player 1, 2 menandakan PLayer 2*/
    int player;  /* [0..2] Menandakan player mana yang memiliki bangunan */
                 /* 0 = No Player
                    1 = Player 1
                    2 = Player 2 */
    int level; /* [0..4] Level dari bangunan */
    int soldierCount; /* Jumlah pasukan yang ada di bangunan */
    int soldierAddValue; /* A = Nilai penambahan pasukan */
    int maximumSoldierAddCount; /* M = Batas atas jumlah penambahan pasukan di bangunan */
    int soldierAddCount;  /* Menandakan berapa banyak pasukan yang telah ditambah */
    boolean isDefended; /* Boolean untuk menandakan apakah bangunan dilindungi */ 
    boolean hasAttacked;
    POINT position; /* Posisi bangunan dalam map */
} Player;
