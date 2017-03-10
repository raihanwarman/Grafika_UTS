#include "gambar.h"
#include "glob_var_type.h"
#include "framebuffer_init.h"

//objek dapat berupa peluru atau pesawat
typedef struct{
	titik position;	
	int speed;  
	int direction;
	int status; 	//-1 inactive, 0 dead, 1 active, 99-50 rotating
	titik* image;
}kineticObject;

extern kineticObject player;
extern kineticObject enemy[100];
extern kineticObject road[2];

int checkCollision(int carLength);   //cek apakah terdapat peluru yang berada sejauh oTaffset dari pesawat,
								     //jika iya kedua objek memiliki isTabrakan true

void runObjects();//ubah position sesuai speed and direction for each enemy

void moveObject(titik p, kineticObject *o); //ubah position objek o menjadi p

void destroy(kineticObject *o); //ubah status menjadi 0

void startCrash(kineticObject *o); //ubah status menjadi 99, speed menjadi 1/5, direction random

void crashProcess(kineticObject *o); //putar image objek o

void spawnPlayer(); //inisialisasi player 

void spawnEnemy(); //insialisasi enemy

void spawnRoad(); //inisialisasi jalan

int checkRoadOutOfBound();//cek apakah jalan di luar layar


