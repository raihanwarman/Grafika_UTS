#include <stdio.h>
#include "gambartulisan.h"

int main() {
	//Karakter A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,SP;
	titik p1 = {30,300};
	titik p2 = {200,400};
	titik p3 = {50,600};

	init_fb();
	
	initKarakter();

	printStatus(A);
	printStatus(Q);
	drawKarakter(Q, p1);
	drawKarakter(A, p2);
	
	Karakter nama[] = {A,M,A,L};
	
	drawTulisan(nama, p3, 4);

}