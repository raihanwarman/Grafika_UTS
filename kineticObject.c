#include "kineticObject.h"

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
