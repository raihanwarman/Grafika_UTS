#include "kineticObject.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265

extern int lastEnemy;
extern int lastRoad;


extern kineticObject player;
extern kineticObject enemy[100];
extern kineticObject road[2];

void setupImageCar(kineticObject *car){
    //SETUP BUAT GAMBAR MOBIL
}

void setupImageRoad(kineticObject *road){
    //SETUP BUAT GAMBAR JALAN
}

void checkCollision(int carLength){
    for(int i=0;i<lastEnemy;i++){
        float distance = sqrt((player.position.x - enemy[i].position.x)*(player.position.x - enemy[i].position.x)+
        (player.position.y-enemy[i].position.y)*(player.position.y-enemy[i].position.y));
            if(distance<=carLength){
                startCrash(player);
                startCrash(enemy[i]);
            }
    }
}

int checkRoadOutOfBound(){
    for(int i=0;i<lastRoad;i++){
        if(road[i].position.x >GLOBAL_LAYAR_X)
            return 1;
    }
    return 0;
}

void spawnPlayer(){
    titik playerPosition = {25,1}; // NANTI DI GANTI
    player.position = playerPosition;
    player.speed = 0;
    player.direction= 1 // 1 ke kanan ,  -1 ke kiri
    player.status=1;
    setupImageCar(&player);
}

void spawnEnemy(){
    titik enemyPosition={25,50}; // NANTI DI GANTI
    enemy[lastEnemy].position - enemyPosition;
    enemy[lastEnemy].speed = 5;
    enemy[lastEnemy].direction= -1 // 1 ke kanan ,  -1 ke kiri
    enemy[lastEnemy].status=1;
    setupImageCar(&enemy[lastEnemy]);
    lastEnemy++;
}

void spawnRoad(){
    titik roadPosition = {25,50};// NANTI DI GANTI
    road[lastRoad].position = roadPosition;;
    road[lastRoad].speed = 3;
    road[lastRoad].direction=-1 // 1 ke kanan ,  -1 ke kiri
    road[lastRooad].status=1;
    setupImageRoad(&road[lastRoad]);
    lastRoad++;
}


void runObject(){
    //Jalanin enemy car ==========================================================
    //Asumsi enemy hanya jalan horizontal
    for(int i=0;i<lastEnemy;i++){
        if(enemy[i].status==1){
            enemy[i].position.x = enemy[i].position.x + (enemy[i].direction*enemy[i].speed);
            enemy[i].position.y = enemy[i].position.y+0;
        }
    }
    //Jalanin petak road =========================================================
    //Asumsi road hanya jalan horizontal
    for(int i=0;i<lastRoad;i++){
        if(road[i].status==1){
            road[i].position.x = road[i].position.x + (road[i].direction*road[i].speed);
            road[i].position.y = road[i].position.y+0;
        }
    }
}

void moveObject(titik p,kineticObject *o){
    o->position.x = p.x;
    o->position.y = p.y;
}

void destroy(kineticObject *o){
    o->status = 0;
}

void startCrash(kineticObject *o){
    int randomInt  = 1;
    o->status = 99;
    o->speed = o->speed/5;
    o->direction = randomInt;
}

void crashProcess(){
    //putar image object;
}




void setPlayerImage() {
  player.image = (titik*) malloc(18 * sizeof(titik));
  player.image[0].x = -70; player.image[0].y = 0;
  player.image[1].x = 40; player.image[1].y = 0;
  player.image[2].x = 30; player.image[2].y = -25;
  player.image[3].x = 40; player.image[3].y = -25;
  player.image[4].x = 50; player.image[4].y = 0;
  player.image[5].x = 70; player.image[5].y = 0;
  player.image[6].x = 75; player.image[6].y = 5;
  player.image[7].x = 75; player.image[7].y = 30;
  player.image[8].x = 50; player.image[8].y = 30;
  player.image[9].x = 42; player.image[9].y = 17;
  player.image[10].x = 34; player.image[10].y = 17;
  player.image[11].x = 26; player.image[11].y = 30;
  player.image[12].x = -26; player.image[12].y = 30;
  player.image[13].x = -34; player.image[13].y = 17;
  player.image[14].x = -42; player.image[14].y = 17;
  player.image[15].x = -50; player.image[15].y = 30;
  player.image[16].x = -75; player.image[16].y = 30;
  player.image[17].x = -75; player.image[17].y = 5;
}

void setEnemyImage() {
  int i;
  for (i = 0; i < ENEMY_N; i++) {
    enemy[i].image = (titik *) malloc (19 * sizeof(titik));
    enemy[i].image[0].x = -75; enemy[i].image[0].y = 0;
    enemy[i].image[1].x = -40; enemy[i].image[1].y = 0;
    enemy[i].image[2].x = -40; enemy[i].image[2].y = -20;
    enemy[i].image[3].x = -5; enemy[i].image[3].y = -20;
    enemy[i].image[4].x = 0; enemy[i].image[4].y = -30;
    enemy[i].image[5].x = 5; enemy[i].image[5].y = -20;
    enemy[i].image[6].x = 40; enemy[i].image[6].y = -20;
    enemy[i].image[7].x = 40; enemy[i].image[7].y = 0;
    enemy[i].image[8].x = 75; enemy[i].image[8].y = 0;

    enemy[i].image[9].x = 75; enemy[i].image[9].y = 30;
    enemy[i].image[10].x = 40; enemy[i].image[10].y = 30;
    enemy[i].image[11].x = 32; enemy[i].image[11].y = 17;
    enemy[i].image[12].x = 24; enemy[i].image[12].y = 17;
    enemy[i].image[13].x = 16; enemy[i].image[13].y = 30;
    enemy[i].image[14].x = -16; enemy[i].image[14].y = 30;
    enemy[i].image[15].x = -24; enemy[i].image[15].y = 17;
    enemy[i].image[16].x = -32; enemy[i].image[16].y = 17;
    enemy[i].image[17].x = -40; enemy[i].image[17].y = 30;
    enemy[i].image[18].x = -75; enemy[i].image[18].y = 30;
  }
}
