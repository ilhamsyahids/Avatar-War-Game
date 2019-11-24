//================================================//
//								       			  //
//					  SkillQueue             	  //
//                                     			  //
//------------------------------------------------//
// File : skillqueue.c */              			  //
//----------------------------------------------- //
// Implementasi ADT SkillQueue dengan representasi//
// array secara eksplisit dan alokasi dinamik 	//
// Implementasi Versi III dengan circular buffer//
//==============================================//

///////////////////////////
//		  INCLUDE	 	 //
///////////////////////////

#include "skill.h"
#include "skillqueue.h"
#include "pcolor.h"

///////////////////////////
// 		CONSTRUCTOR 	 //
///////////////////////////
void SkillQueueCreateEmpty(SkillQueue *Q)
{
    /* I.S. sembarang */
    /* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
    /* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
    /* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
    /* Proses : Melakukan alokasi, membuat sebuah Q kosong */
    (*Q).T = (SkillQueueInfotype *)malloc((SkillQueueMaximumElement + 1) * sizeof(SkillQueueInfotype));
    if ((*Q).T != NULL)
    {
        SkillQueueMaxElement(*Q) = SkillQueueMaximumElement;
        SkillQueueHead(*Q) = SkillQueueNil;
        SkillQueueTail(*Q) = SkillQueueNil;
    }
    else
    {
        SkillQueueMaxElement(*Q) = 0;
    }
}

///////////////////////////
// 		DESTRUCTOR 	 	 //
///////////////////////////
void SkillQueueDealokasi(SkillQueue *Q)
{
    /* Proses: Mengembalikan memori Q */
    /* I.S. Q pernah dialokasi */
    /* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
    SkillQueueMaxElement(*Q) = 0;
    free((*Q).T);
}

///////////////////////////
// 		 PREDIKAT		 //
///////////////////////////
boolean IsSkillQueueEmpty(SkillQueue Q)
{
    /* Mengirim true jika Q kosong: lihat definisi di atas */
    return (SkillQueueHead(Q) == SkillQueueNil) && (SkillQueueTail(Q) == SkillQueueNil);
}

boolean IsSkillQueueFull(SkillQueue Q)
{
    /* Mengirim true jika tabel penampung elemen Q sudah penuh */
    /* yaitu mengandung elemen sebanyak MaxEl */
    return (((SkillQueueTail(Q) - SkillQueueHead(Q) + SkillQueueMaxElement(Q)) % SkillQueueMaxElement(Q)) + 1) == SkillQueueMaxElement(Q);
}

//////////////////////////////////
// 	   SKILLQUEUE OPERATIONS	//
//////////////////////////////////
int SkillQueueNBElmt(SkillQueue Q)
{
    /* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
    if (IsSkillQueueEmpty(Q))
    {
        return 0;
    }
    return (((SkillQueueTail(Q) - SkillQueueHead(Q) + SkillQueueMaxElement(Q)) % SkillQueueMaxElement(Q)) + 1);
}

void SkillQueueAddSkill(SkillQueue *Q, SkillQueueInfotype X)
{
    /* Proses: Menambahkan X pada Q dengan aturan FIFO */
    /* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
    /* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
    if (IsSkillQueueEmpty(*Q))
    {
        SkillQueueHead(*Q) = 1;
        SkillQueueTail(*Q) = 1;
        SkillQueueInfoTail(*Q) = X;
    }
    else if (!IsSkillQueueFull(*Q))
    {
        SkillQueueTail(*Q) = (SkillQueueTail(*Q) % SkillQueueMaxElement(*Q) + 1);
        SkillQueueInfoTail(*Q) = X;
    }
}

void SkillQueueDelSkill(SkillQueue *Q, SkillQueueInfotype *X)
{
    /* Proses: Menghapus X pada Q dengan aturan FIFO */
    /* I.S. Q tidak mungkin kosong */
    /* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
    *X = SkillQueueInfoHead(*Q);
    if (SkillQueueHead(*Q) == SkillQueueTail(*Q))
    {
        SkillQueueHead(*Q) = SkillQueueNil;
        SkillQueueTail(*Q) = SkillQueueNil;
    }
    else
    {
        SkillQueueHead(*Q) = (SkillQueueHead(*Q) % SkillQueueMaxElement(*Q)) + 1;
    }
}

SkillQueueInfotype SkillUseSkill(SkillQueue *Q)
{
    /* Mengeluarkan HEAD dari Q yang berisi Skill menghapusnya dari Q dengan aturan FIFO */
    /* X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer setelah
    penghapusan Q mungkin kosong */
    SkillQueueInfotype X;
    SkillQueueDelSkill(Q, &X);
    return X;
}

void PrintQueueSkill(SkillQueue Q)
{
    /* Proses: Mencetak seluruh Skill pada QueueSkill dengan aturan FIFO */
    /* I.S. Sembarang */
    /* F.S. Tercetak ke layar daftar skill yang ada dengan "SKILL : [skill], [skill], [skill]", 
    apabila QueueSkill kosong maka akan tercetak ke layar "SKILL : Tidak Ada Skill Tersedia"*/

    SkillQueueInfotype tempDel;

    if (IsSkillQueueEmpty(Q))
    {
        print_cyan("Tidak Ada Skill Tersedia\n");
    }
    else
    {
        int count = 1;
        print_cyan("Skill Available :\n");
        while (!IsSkillQueueEmpty(Q))
        {
            SkillQueueDelSkill(&Q, &tempDel);
            printf("%d. ", count);
            printf("%s", SkillGetName(SkillKind(tempDel)));
            if (count == 1)
            {
                print_yellow("  <=== Can be used");
            }
            if (!IsSkillQueueEmpty(Q))
            {
                printf("\n");
            }
            count += 1;
        }
        printf("\n");
    }
}

SkillQueue SkillQueueCopySkillQueue(SkillQueue Q)
/* Mengirimkan salinan dari SkillQueue Q menjadi SkillQueue baru */
{
    SkillQueue QCopy;
    Skill STemp;

    SkillQueueCreateEmpty(&QCopy);

    while (!IsSkillQueueEmpty(Q))
    {
        SkillQueueDelSkill(&Q, &STemp);
        SkillQueueAddSkill(&QCopy, STemp);
    }

    return QCopy;
}
