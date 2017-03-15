#ifndef GAMBAR_TULISAN_H
#define GAMBAR_TULISAN_H

#include <stdio.h>
#include "glob_var_type.h"
#include "gambar.h"

#define BPP 32

typedef struct karakter_t {
	char ch;
	int width;
	int height;
	warna* pix;
} Karakter;

Karakter A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,SP;

/* inisialisasi variabel karakter */
extern void initKarakter();

/* nilai width bmp ada di offset 18 pd header */
int getBmpWidth(FILE* streamIn);

/* nilai height bmp ada di offset 22 pd header */
int getBmpHeight(FILE* streamIn);

/* mengembalikan variabel karakter yang telah diinisialisasi */
Karakter setKarakter(Karakter* kar, char ch);

/* menghapus background karakter yang berwarna KEYING_COLOR */
void removeBackground(Karakter* kar);

/* menggambar karakter tunggal ke layar */
void drawKarakter(Karakter karakter, titik p);

/* menggambar tulisan ke layar */
void drawTulisan(Karakter* ch, titik p, int nKarakter);

/* mencetak atribut karakter */
void printStatus(Karakter kar);

#endif