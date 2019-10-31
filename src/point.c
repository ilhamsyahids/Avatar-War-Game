#include "point.h"
#include <stdio.h>

#define PI 3.14159265358979323846

/* *** Konstruktor membentuk Point *** */
Point MakePoint(int X, int Y)
/* Membentuk sebuah Point dari komponen-komponennya */
{
    // KAMUS
    Point P;

    // ALGORITMA
    P.X = X;
    P.Y = Y;
    return P;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void PointRead(Point *P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   Point P berdasarkan dari nilai X dan Y tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
    int x, y;
    scanf("%f", &x);
    scanf("%f", &y);
    *P = MakePoint(x, y);
}

void PointPrint(Point P)
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   dengan enter di belakang
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
{
    printf("(%d,%d)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean PointEQ(Point P1, Point P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
    return ((PointX(P1) == PointX(P2) && (PointY(P1) == PointY(P2))));
}