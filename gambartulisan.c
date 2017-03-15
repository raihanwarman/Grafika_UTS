#include <stdio.h>
#include <string.h>
#include "gambartulisan.h"
#include "framebuffer_init.h"

titik pCursor;
const warna KEYING_COLOR = {255,255,255,255};
extern Karakter A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,SP;

extern void initKarakter() {
	setKarakter(&A,'a');
	setKarakter(&B,'b');
	setKarakter(&C,'c');
	setKarakter(&D,'d');
	setKarakter(&E,'e');
	setKarakter(&F,'f');
	setKarakter(&G,'g');
	setKarakter(&H,'h');
	setKarakter(&I,'i');
	setKarakter(&J,'j');
	setKarakter(&K,'k');
	setKarakter(&L,'l');
	setKarakter(&M,'m');
	setKarakter(&N,'n');
	setKarakter(&O,'o');
	setKarakter(&P,'p');
	setKarakter(&Q,'q');
	setKarakter(&R,'r');
	setKarakter(&S,'s');
	setKarakter(&T,'t');
	setKarakter(&U,'u');
	setKarakter(&V,'v');
	setKarakter(&W,'w');
	setKarakter(&X,'x');
	setKarakter(&Y,'y');
	setKarakter(&Z,'z');
	setKarakter(&SP,' ');
}

int getBmpWidth(FILE* streamIn) {	
    fseek(streamIn, 18, SEEK_SET);
    return (int) getc(streamIn);
}

int getBmpHeight(FILE* streamIn) {
    fseek(streamIn, 22, SEEK_SET);
    return (int) getc(streamIn);
}


Karakter setKarakter(Karakter* kar, char ch) {
    (*kar).ch = ch;
	if (ch==' ') return;

	FILE* streamIn;
	//char* inputFile = "alphabet-bmp/rgb.bmp";
	char* inputFile = strdup("alphabet-bmp/X-100.bmp");
	inputFile[13] = ch;

	int bpp = global_vinfo.bits_per_pixel;   //24 -> RGB, 32 -> RGBA
	int i,j, offset;

    streamIn = fopen(inputFile, "r");
    if (streamIn == (FILE *)0){
        printf("File opening error ocurred. Exiting program.\n");
        printf("File : %s\n", inputFile);
        exit(-1);
    }

    (*kar).width = getBmpWidth(streamIn);
    (*kar).height = getBmpHeight(streamIn);

	(*kar).pix = (warna*) malloc((*kar).width * (*kar).height*sizeof(warna));
	
	fseek(streamIn, 54, SEEK_SET); 
	for (i=(*kar).height-1; i>=0; i--){
		for (j=0; j<(*kar).width; j++){
            offset = ((*kar).width*i) + j;
            (*kar).pix[offset].b = getc(streamIn);
            (*kar).pix[offset].g = getc(streamIn);
            (*kar).pix[offset].r = getc(streamIn);
            (*kar).pix[offset].a = getc(streamIn);
            (*kar).pix[offset].a = 255;
		}
	}
    fclose(streamIn);
    removeBackground(kar);

}

void removeBackground(Karakter* kar) {
	int i,j,offset;
	for (i=(*kar).height-1; i>=0; i--){
		for (j=0; j<(*kar).width; j++){
            offset = ((*kar).width*i) + j;
			if ((*kar).pix[offset].r == KEYING_COLOR.r
				&& (*kar).pix[offset].g ==KEYING_COLOR.g
				&& (*kar).pix[offset].b == KEYING_COLOR.b) {

				(*kar).pix[offset].a = 0;
				//printf("rem \n");
			} else {
				//printf("not rem \n");
			} 
		}
	}
}

void drawKarakter(Karakter kar, titik p) {
	int i,j, offset;
	
	//printf("Drawing %c at %d,%d\n", kar.ch, p.x,p.y);
	if (kar.ch==' ') return;

	warna bg = {100,100,255,255};

	titik p0;
	p0.x = p.x;
	p0.y = p.y;
	int ci=0, cj=0;
	for (i=p0.y; i<p0.y+kar.height; i++) {
    	for (j=p0.x; j<p0.x+kar.width; j++) {
	      buffer_r[i][j] = bg.r;
	      buffer_g[i][j] = bg.g;
	      buffer_b[i][j] = bg.b;
	      buffer_a[i][j] = bg.a;

			p.x = j;
			p.y = i;

			long int position = (p.x + global_vinfo.xoffset) * (global_vinfo.bits_per_pixel / 8) +
				(p.y + global_vinfo.yoffset) * global_finfo.line_length;

            // offset = (kar.width*ci) + cj;
            offset = cj;
			if(global_vinfo.bits_per_pixel == 32 ){
				if (kar.pix[offset].a==255){
					*(global_fbp + position) = kar.pix[offset].b;
					*(global_fbp + position + 1) = kar.pix[offset].g;
					*(global_fbp + position + 2) = kar.pix[offset].r;
					*(global_fbp + position + 3) = kar.pix[offset].a;
				} 
				// else {
				// 	*(global_fbp + position) = 0;
				// 	*(global_fbp + position + 1) = 0;
				// 	*(global_fbp + position + 2) = 0;
				// 	*(global_fbp + position + 3) = 0;
				// }
			}
			cj++;
			//printf("%d ",cj);
		}
		ci++;
		//printf("\n%d\n\n\n",ci);
	}
	p0.x = 0; p0.y=0;

	titik p1={1366, 768};
	// refreshBuffer(p0,p1);
	//loadBuffer();
}


void drawTulisan(Karakter* ch, titik p, int nKarakter) {
	int i;
	pCursor.x = p.x;
	pCursor.y = p.y;

	for (i=0; i<nKarakter; i++) {
		// printf("drwawing %c - dimen: %dx%d at (%d,%d)\n", 
		// 	ch[i].ch,ch[i].width,ch[i].height, pCursor.x, pCursor.y);
		if (ch[i].ch==' ') {
			pCursor.x+=30;
		} else {
			drawKarakter(ch[i], pCursor);
			pCursor.x += ch[i].width;
		}
	}
}

void printStatus(Karakter kar) {
	printf("ch		: %c\n", kar.ch);
	printf("width	: %d\n", kar.width);
	printf("height	: %d\n", kar.height);
}