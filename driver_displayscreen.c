//#include <pthread.h>
#include "displayscreen.h"
#include "gambartulisan.h"


int main() {
//	pthread_t screen_th, tulisan_th;

	init_fb();
	initKarakter();

	displayWelcomeScreen(1);

	titik p1 = {300, 500};
	Karakter welcome[] = {T,A,B,R,A,X,SP,M,E};
	drawTulisan(welcome, p1, 9);

	return 0;
}