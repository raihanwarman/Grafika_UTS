#include "gambarwindow.h"
#include "kineticObject.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void drawObjects();		//menggambar tembakan dan objekTabrak ke buffer
void *preUpdate();		//(1)cek inputuser
void update();	//(1)ubah posisi. (2)spawnObjek, (3)drawBuffer
void postUpdate();	 	//(1)cek kolisi, (2)loadbuffer ke layar

kineticObject player;
kineticObject enemy[100];
kineticObject road[2];
int lastEnemy;
int lastRoad;

int windowSideLength;

titik pl0 = {0,0};
titik pl1 = {799,699};
titik pw0 = {810,0};
titik pw1 = {1209,349};
int fd; 

int main()
{
//**setup-pendengar-keyboard********************************************************************
	// Input keyboard device file
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    const char *dev = "/dev/input/event4";
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    // Open device for reference
    fd = open(dev, O_RDONLY);

    // Check if device is opened
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

//**setup-objek-game****************************************************************************
	init_fb();
	warna c = {255,255,255,255};
	warna bound = {10,10,10, 10};
	titik p1 = {500, 350};
	titik p2 = {1500, 350};
	titik p3 = {530,400};
	spawnPlayer();
	spawnEnemy(p3);
	spawnRoad(p1);
	spawnRoad(p2);

	setPlayerImage();
	setEnemyImage();
	setRoadImage();

	titik origin = {150,450};
	refreshBuffer(pl0,pl1);
	refreshBuffer_window(pw0,pw1);

	drawObjects();
	loadBuffer();

	loadBuffer_window();

	//deklarasi variabel
	int startTime;
	int endTime;
	double elapsedTime;

	//create mobil player


	while(1)
	{
		startTime = clock();

	//do game stuff=======================================================
		//tangkap user-input


		//jalanin objek
		update();
		checkRoadOutOfBound();

		//kalau player collision
		if(player.status>5)
		{
			crashProcessPlayer(&player);
			crashProcessEnemy();
		}

		if(player.status>1 && player.status <=5){
			destroy(&player);
		}

		//gambar
		refreshBuffer(pl0,pl1);
		refreshBuffer_window(pw0,pw1);

		drawObjects();

		loadBuffer();
		loadBuffer_window();

		//gambar di window


		//cek kolisi
		checkCollision(100);

		//looping aspal jalan

	//====================================================================

		endTime = clock();
		elapsedTime =(double) ((double)endTime - (double)startTime);

		//spawn musuh

		if(elapsedTime > 17) //biar 60fps
		{
			//do nothing
		}
		else
		{
			usleep((17-elapsedTime)*1000);
		}
	}

	return 0;
}


void drawObjects()
{
	warna c = {255,255,255,255};
	warna bound = {10,10,10,10};
  warna green = {1, 255, 1, 255};
  warna blue = {1, 1, 255, 255};

  //gambar jalan
  titik mid = {500, 350};
  bufferDrawPlaneSolidCitra(road[0].image, mid, green, green, 4);
	for(int i=0; i<2; i++)
	{
		// if(road[i].status > 0)
    furnishRoad(&road[i]);
	}

	//gambar player
	if(player.status > 0)
	{
		bufferDrawPlaneSolidCitra(player.image, player.position, c, bound, 18);
	}

	//gambar musuh
	for(int i=0; i<100; i++)
	{
		if(enemy[i].status > 0)
		{
			bufferDrawPlaneSolidCitra(enemy[i].image, enemy[i].position, c, bound, 19);
		}
	}
}

void update()
{
	runObject();
}
