//==============================================//
//								       			//
//				  Action Stack             		//
//                                     			//
//----------------------------------------------//
// File : actionstackt.c */              		//
//----------------------------------------------//
// Implementasi ADT Action Stack			    //
// Action Stack digunakan untuk menyimpan 		//
// History Action yang dilakukan player di turn	//
// Stack akan dikosongkan tiap end_turn dan     //
// pengaktifan skill							//
// Action Stack dibuat dengan alokasi DINAMIS	//
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////
#include "boolean.h"
#include "player.h"
#include "gamemap.h"
#include "actionstackt.h"

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void ActionStackCreateEmpty(ActionStack *S, int maxElement)
{
    /* I.S. sembarang; */
    /* F.S. Mengalokasikan sebuah actopn stack S yang kosong berkapasitas maxElement */
    /* jadi indeksnya antara 1.. maxElement+1 karena 0 tidak dipakai */
    /* Ciri stack kosong : TOP bernilai StackNil */
    (*S).T = (ActionStackInfotype *)malloc((maxElement + 1) * sizeof(ActionStackInfotype));
    if ((*S).T != NULL)
    {
        ActionStackTop(*S) = ActionStackNil;
        (*S).MaxElement = maxElement;
    }
    else
    {
        (*S).MaxElement = 0;
    }
}

void ActionStackRealokasi(ActionStack *S)
{
    /* I.S. S Penuh; */
    /* F.S. Merealokasikan sebuah action stack S yang sebelumnya berkapasitas maxElement menjadi maxElement +*/
    (*S).MaxElement++;
    (*S).T = (ActionStackInfotype *)realloc((*S).T, ((*S).MaxElement + 1) * sizeof(ActionStackInfotype));
}
///////////////////////////
// 		 DESTRUCTOR 	 //
///////////////////////////
void ActionStackDealokasi(ActionStack *S)
{
    /* I.S. S terdefinisi; */
    /* F.S. T(S) dikembalikan ke system, MaxElement(S)=0; TOP(S)=StackNil */
    free((*S).T);
}
///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsActionStackEmpty(ActionStack S)
{
    /* Mengirim true jika Stack kosong: lihat definisi di atas */
    return ActionStackTop(S) == ActionStackNil;
}

boolean IsActionStackFull(ActionStack S)
{
    /* Mengirim true jika tabel penampung nilai elemen stack penuh */
    return ActionStackTop(S) == S.MaxElement;
}

///////////////////////////////////////
// 	     ACTION STACK OPERATIONS 	 //
///////////////////////////////////////
void ActionStackPush(ActionStack *S, ActionStackInfotype X)
{
    /* Menambahkan X sebagai elemen Stack S. */
    /* I.S. S mungkin kosong dan mungkin penuh*/
    /* F.S. X menjadi TOP yang baru,TOP bertambah 1 dan ketika S sebelumnya penuh maka akan dilakukan realloc*/
    if (!IsActionStackEmpty(*S))
    {
        if (IsActionStackFull(*S))
        {
            ActionStackRealokasi(S);
        }
        ActionStackTop(*S)++;
    }
    else
    {
        ActionStackTop(*S) = 1;
    }
    ActionStackInfoTop(*S) = X;
}

void ActionStackPop(ActionStack *S, ActionStackInfotype *X)
{
    /* Menghapus X dari Stack S. */
    /* I.S. S  tidak mungkin kosong */
    /* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    *X = ActionStackInfoTop(*S);
    ActionStackTop(*S)--;
}

void ActionStackEmpty(ActionStack *S)
{
    /* Mengosongkan Action Stack */
    /* I.S. S terdefinisi dan mungkin kosong */
    /* F.S. S menjadi kosong dengan MaxElement tidak berubah */
    ActionStackTop(*S) = ActionStackNil;
}
