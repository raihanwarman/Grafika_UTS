#include "gambarwindow.h"
#include "kineticObject.h"
#include "displayscreen.h"
#include "gambartulisan.h"
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
pthread_t thread0; 		//thread input capture
struct input_event ev;	//something-something keylogger
int keypress = 0;
titik p11 = {200,300};
titik p22 = {200,560};
kineticObject player;
kineticObject enemy[1000];
kineticObject road[5];
int lastEnemy;
ssize_t n;
int lastRoad;
int score = 0;

int windowSideLength;

titik pl0 = {0,0};
titik pl1 = {799,699};
//titik pw0 = {810,0};
//titik pw1 = {1209,349};
titik pw0 = {0,0};
titik pw1 = {399,349};
int fd;

int main()
{
//**setup-pendengar-keyboard********************************************************************
	// Input keyboard device file
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    const char *dev = "/dev/input/event3";
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
	initKarakter();

	srand(time(NULL));
	warna c = {255,255,255,255};
	warna bound = {10,10,10,10};
	titik p1 = {400,430};
	titik p2 = {1200,430};
	titik p3 = {2500,560};
	titik p4 = {2500,300};
	titik p5 = {220,100};
	titik l1 = {100,100};
	titik l2 = {100,190};
	titik l3 = {160, 190};
	titik l4 = {160, 170};
	titik l5 = {120, 170};
	titik l6 = {120,100};
	titik arrL[6];
	titik o1 = {180,100};
	titik o2 = {240,100};
	titik o3 = {240, 190};
	titik o4 = {180, 190};
	titik arrO[4];
	titik oo1 = {190, 120};
	titik oo2 = {230, 120};
	titik oo3 = {230, 170};
	titik oo4 = {190,170};
	titik arrOO[4];
	titik s1 = {260, 100};
	titik s2 = {320, 100};
	titik s3 = {320, 120};
	titik s4 = {280, 120};
	titik s5 = {280, 140};
	titik s6 = {320, 140};
	titik s7 = {320, 190};
	titik s8 = {260, 190};
	titik s9 = {260, 170};
	titik s10 = {300, 170};
	titik s11 = {300, 160};
	titik s12 = {260, 160};
	titik arrS[12];
	titik e1 = {340, 100};
	titik e2 = {400, 100};
	titik e3 = {400, 120};
	titik e4 = {370, 120};
	titik e5 = {370, 140};
	titik e6 = {400, 140};
	titik e7 = {400, 160};
	titik e8 = {370, 160};
	titik e9 = {370, 170};
	titik e10 = {400, 170};
	titik e11 = {400, 190};
	titik e12 = {340, 190};
	titik arrE[12];
	arrL[0] = l1;
	arrL[1] = l2;
	arrL[2] = l3;
	arrL[3] = l4;
	arrL[4] = l5;
	arrL[5] = l6;
	arrO[0] = o1;
	arrO[1] = o2;
	arrO[2] = o3;
	arrO[3] = o4;
	arrOO[0] = oo1;
	arrOO[1] = oo2;
	arrOO[2] = oo3;
	arrOO[3] = oo4;
	arrS[0] = s1;
	arrS[1] = s2;
	arrS[2] = s3;
	arrS[3] = s4;
	arrS[4] = s5;
	arrS[5] = s6;
	arrS[6] = s7;
	arrS[7] = s8;
	arrS[8] = s9;
	arrS[9] = s10;
	arrS[10] = s11;
	arrS[11] = s12;
	arrE[0] = e1;
	arrE[1] = e2;
	arrE[2] = e3;
	arrE[3] = e4;
	arrE[4] = e5;
	arrE[5] = e6;
	arrE[6] = e7;
	arrE[7] = e8;
	arrE[8] = e9;
	arrE[9] = e10;
	arrE[10] = e11;
	arrE[11] = e12;
	titik arrP[2];
	arrP[0] = p3;
	arrP[1] = p4;

	displayWelcomeScreen(0);

	titik pTulisanTabrax = {300, 300};
	Karakter tabraxMe[] = {T,A,B,R,A,X,SP,M,E};
	drawTulisan(tabraxMe, pTulisanTabrax, 9);

	spawnPlayer();

  titik pEnemy = {600, 560};
  while (pEnemy.x <= 2600) {
    int x = rand() % 2;
    if (x == 0) {
      pEnemy.y = 300;
    } else {
      pEnemy.y = 560;
    }
    spawnEnemy(pEnemy);
    pEnemy.x += 300;
  }
	spawnRoad(p1);
  for (int aa = 0; aa < 4; aa++) {
      p1.x += 800;
      spawnRoad(p1);
  }

	setPlayerImage();
	setEnemyImage();
	setRoadImage();

	titik origin = {150,450};
	refreshBuffer(pl0,pl1);
	refreshBuffer_window(pw0,pw1);

	drawObjects();
  drawScore(score);
	loadBuffer();

	loadBuffer_window();

	//deklarasi variabel
	int startTime;
	int endTime;
	double elapsedTime;

	//create mobil player
	if (player.status==1) {
		pthread_create(&thread0, NULL, preUpdate, NULL);
	}

	int enemyStart;
	enemyStart = clock();
	int n;
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

		if (player.status==5) {
			break;
		}

		if(player.status>1 && player.status <=5){
			destroy(&player);
		}

		//gambar
		refreshBuffer(pl0,pl1);

		refreshBuffer_window(pw0,pw1);

		drawObjects();
    drawScore(score);
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
		if (endTime-enemyStart>5000000) {
			n = rand() %2;
			spawnEnemy(arrP[n]);
			enemyStart = endTime;
		}


		if(elapsedTime > 17) //biar 60fps
		{
			//do nothing
		}
		else
		{
			usleep((17-elapsedTime)*1000);
		}
	}
	//tulis game over
	refreshBuffer(pl0,pl1);
	bufferDrawPlane(arrL, c, 6);
	bufferDrawPlane(arrO, c, 4);
	bufferDrawPlane(arrOO, c, 4);
	bufferDrawPlane(arrS, c, 12);
	bufferDrawPlane(arrE, c, 12);
	loadBuffer();
	return 0;
}


void drawObjects()
{
	warna c = {255,255,255,255};
	warna black = {10,10,10,255};
  warna green = {1, 255, 1, 255};
  warna orange = {255, 153, 1, 255};
  warna red = {255, 1, 1, 255};
  warna lightblue = {102, 255, 255, 255};

  //gambar jalan
  titik topleft = {0, 230};
  titik bottomright = {2500, 630};
  fillRectangle(topleft, bottomright, green);
  fillRectangleWindow(scaleDotInWindow(topleft), scaleDotInWindow(bottomright), green);
	for(int i=0; i<5; i++)
	{
		if(road[i].status > 0)
		{
			//bufferDrawPlaneSolidCitra(road[i].image, road[i].position, green, green, 4);
      furnishRoad(&road[i]);
		}
	}

	//gambar player
	if(player.status > 0)
	{
		bufferDrawPlaneSolidCitra(player.image, player.position, lightblue, black, 18);
    if (player.status == 1) {
      furnishPlayer(&player);
    }
	}

	//gambar musuh
	for(int i=0; i<1000; i++)
	{
		if(enemy[i].status > 0)
		{
			bufferDrawPlaneSolidCitra(enemy[i].image, enemy[i].position, orange, red, 19);
      if (enemy[i].status == 1) {
        furnishEnemy(&enemy[i]);
      }
		}
	}
}

void update()
{
	runObject();
}


void *preUpdate(){
	while(1){
		// get stored value on keyboard device reference file
	    n = read(fd, &ev, sizeof ev);
	    // check if no stored value on device file
	    if (n == (ssize_t)-1) {

	    }
	    int wt = 50; //window transition
	    // if keystroke is stored on keyboard device reference file
	    if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
	        if(ev.value == 1){ // when it pressed, 0 is released
	        	printf("----%d----",ev.code);
	            switch(ev.code){
	                case 103:
						//move up
						if (player.status==1) {
							moveObject(p11, &player);
						}

						break;


	                case 108:
	                    // move down
	                    if (player.status==1) {
							moveObject(p22, &player);
						}

	                    break;

	                case 30:
	                	// Case A -> window goes left
	                	if(windowPosition.x -wt >= 0){
	                		windowPosition.x -= wt;
	                	} else {
	                		windowPosition.x = 0;
	                	}
	                	break;

	                case 31:
	                	// Case S -> window goes down
	                	if(windowPosition.y + 200 + wt < GLOBAL_LAYAR_Y){
	                		windowPosition.y+= wt;
	                	}
	                	else {
	                		windowPosition.y = 500;
	                	}
	                	break;

	                case 32:
	                	// Case D -> window goes right
	                	if(windowPosition.x + 300 + wt < GLOBAL_LAYAR_X){
	                		windowPosition.x += wt;
	                	}
	                	else {
	                		windowPosition.x = 700;
	                	}
	                	break;

	                case 17:
	                	// Case W -> window goes up
	                	if(windowPosition.y -wt >= 0){
	                		windowPosition.y-=wt;
	                	}
	                	else {
	                		windowPosition.y = 0;
	                	}
	                	break;

	                default:
	                    break;

	            }
	            keypress = 1;
	        }

	        if(ev.value == 0){
	        	keypress = 0;
	        }
	    }
	}
}
