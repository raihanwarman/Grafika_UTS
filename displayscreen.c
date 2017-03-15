#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "glob_var_type.h"
#include "framebuffer_init.h"

pFirst = {0,0};
pLast  = {1366, 768};

void displayWelcomeScreen(int dur) {
  warna bg = {70,60,220,255};
  titik p;
  int in;

  //printf("displayWelcomeScreen started\n");

  for (int i=0;i<global_vinfo.yres-20;i++) {
    for (int j=0;j<global_vinfo.xres;j++) {
      buffer_r[i][j] = bg.r;
      buffer_g[i][j] = bg.g;
      buffer_b[i][j] = bg.b;
      buffer_a[i][j] = bg.a;

      p.x = j;
      p.y = i;

      //DrawDot(tmpTitik, bg);

      long int position = (p.x + global_vinfo.xoffset) * (global_vinfo.bits_per_pixel / 8) +
         (p.y + global_vinfo.yoffset) * global_finfo.line_length;

      if(global_vinfo.bits_per_pixel == 32){
          *(global_fbp + position) = bg.b;
          *(global_fbp + position + 1) = bg.g;
          *(global_fbp + position + 2) = bg.r;
          *(global_fbp + position + 3) = bg.a;
      }else{
          // assume 16 bit bgolor
          int b = bg.b;
          int g = bg.g;
          int r = bg.r;
          unsigned short int t = r<<11 | g << 5 | b;
          *((unsigned short int*)(global_fbp + position)) = t;
      }
    }
  }
  sleep(dur);
  // refreshBuffer(p0,p1);
  // loadBuffer();
}