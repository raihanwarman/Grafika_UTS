#include "gambar.h"
#include "glob_var_type.h"
#include "framebuffer_init.h"

#define ROAD_N 5
#define ENEMY_N 10
#define L_CAR 70
//objek dapat berupa peluru atau pesawat

typedef struct{
    titik position;
    int speed;
    int direction;
    int status; 	//-1 inactive, 0 dead, 1 active, 99-50 rotating
    titik image[20];
    int z;
} kineticObject;

extern int score;
extern int lastEnemy;
extern int lastRoad;

extern kineticObject player;
extern kineticObject enemy[1000];
extern kineticObject road[5];

void checkCollision(int carLength);   //cek apakah terdapat peluru yang berada sejauh oTaffset dari pesawat,
								     //jika iya kedua objek memiliki isTabrakan true

void runObject();//ubah position sesuai speed and direction for each enemy

void moveObject(titik p, kineticObject *o); //ubah position objek o menjadi p

void destroy(kineticObject *o); //ubah status menjadi 0

void startCrash(kineticObject *o); //ubah status menjadi 99, speed menjadi 1/5, direction random

void crashProcessPlayer(kineticObject *o);

void crashProcessEnemy();


void spawnPlayer(); //inisialisasi player

void spawnEnemy(titik p); //insialisasi enemy

void spawnRoad(titik p); //inisialisasi jalan

void checkRoadOutOfBound();//cek apakah jalan di luar layar

void setPlayerImage(); // create the image of player
void setEnemyImage(); // create the image of enemy
void setRoadImage();
void furnishPlayer(kineticObject *player);

void furnishEnemy(kineticObject *enemy);

void furnishRoad(kineticObject *road);
