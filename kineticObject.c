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




