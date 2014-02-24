#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "load.h"

#define PI 3.1415927
#define WIN_W 500
#define WIN_H 400
#define CUBE_SIZE 7

float posz = -10, posx = 0, posy = -10, movx = 0, movy = 0, movz = 0, caida = 0;
Uint16 cubes[1000], minisel[8] = {1, 2, 3, 4, 5, 6, 7, 0}, miniactual = 0;
Uint8 selected_face; // Arriba-Abajo-Adelante-Atras-Izquierda-Derecha
bool is_selected = false, move = false, selbuf, colision;
int selected[3];
SDL_Window *window;
GLuint cubestex[26*3], puntero, mini[26], fboId;

void exit(){
 SDL_Quit();
}

void farriba(int x, int y, int z, GLuint tex){
 if(y == 9 or not cubes[z+10*(x+10*(y+1))]){
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS); // Arriba
   if(tex) glTexCoord2f(0, 0);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z);
   if(tex) glTexCoord2f(1, 0);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z);
   if(tex) glTexCoord2f(1, 1);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(0, 1);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z+CUBE_SIZE);
  glEnd();

  int pr[2];
  glGetIntegerv(GL_POLYGON_MODE, pr);
  if(pr[1] == GL_FILL){
   if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
    if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
     if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
    }
    if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
     if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
    }
   }
  }
 }
}

void fabajo(int x, int y, int z, GLuint tex){
 if(y and not cubes[z+10*(x+10*(y-1))]){
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS); // Abajo
   if(tex) glTexCoord2f(0, 0);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y, CUBE_SIZE*z);
   if(tex) glTexCoord2f(0, 1);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(1, 1);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(1, 0);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y, CUBE_SIZE*z);
  glEnd();

  int pr[2];
  glGetIntegerv(GL_POLYGON_MODE, pr);
  if(pr[1] == GL_FILL){
   if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*(y-1) < -posy-0.5 and CUBE_SIZE*(y-1)+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*(y-1) < -posy+2.2 and CUBE_SIZE*(y-1)+CUBE_SIZE > -posy+2.2)){
    if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
     if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
    }
    if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
     if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
      colision = true;
      posy -= movy;
      movy = 0;
      caida = 0;
     }
    }
   }
  }
 }
}

void fadelante(int x, int y, int z, GLuint tex){
 if(z == 9 or not cubes[(z+1)+10*(x+10*y)]){
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS); // Adelante
   if(tex) glTexCoord2f(0, 0);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(1, 0);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(1, 1);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(0, 1);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y, CUBE_SIZE*z+CUBE_SIZE);
  glEnd();

  int pr[2];
  glGetIntegerv(GL_POLYGON_MODE, pr);
  if(pr[1] == GL_FILL){
   if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
    if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
    }
    if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
    }
   }
  }
 }
}

void fatras(int x, int y, int z, GLuint tex){
 if(z == 0 or not cubes[(z-1)+10*(x+10*y)]){
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS); // Atras
   if(tex) glTexCoord2f(0, 0);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z);
   if(tex) glTexCoord2f(1, 0);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z);
   if(tex) glTexCoord2f(1, 1);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y, CUBE_SIZE*z);
   if(tex) glTexCoord2f(0, 1);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y, CUBE_SIZE*z);
  glEnd();

  int pr[2];
  glGetIntegerv(GL_POLYGON_MODE, pr);
  if(pr[1] == GL_FILL){
   if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
    if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
    }
    if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posz -= movz;
      movz = 0;
     }
    }
   }
  }
 }
}

void fizquierda(int x, int y, int z, GLuint tex){
 if(x == 0 or not cubes[z+10*((x-1)+10*y)]){
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS); // Izquierda
   if(tex) glTexCoord2f(0, 0);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z);
   if(tex) glTexCoord2f(1, 0);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(1, 1);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(0, 1);
   glVertex3f(CUBE_SIZE*x, CUBE_SIZE*y, CUBE_SIZE*z);
  glEnd();

  int pr[2];
  glGetIntegerv(GL_POLYGON_MODE, pr);
  if(pr[1] == GL_FILL){
   if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
    if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
    }
    if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
    }
   }
  }
 }
}

void fderecha(int x, int y, int z, GLuint tex){
 if(x == 9 or not cubes[z+10*((x+1)+10*y)]){
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS); // Derecha
   if(tex) glTexCoord2f(0, 0);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z+CUBE_SIZE);
   if(tex) glTexCoord2f(1, 0);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y+CUBE_SIZE, CUBE_SIZE*z);
   if(tex) glTexCoord2f(1, 1);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y, CUBE_SIZE*z);
   if(tex) glTexCoord2f(0, 1);
   glVertex3f(CUBE_SIZE*x+CUBE_SIZE, CUBE_SIZE*y, CUBE_SIZE*z+CUBE_SIZE);
  glEnd();

  int pr[2];
  glGetIntegerv(GL_POLYGON_MODE, pr);
  if(pr[1] == GL_FILL){
   if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
    if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
    }
    if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+2.2) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+2.2 and CUBE_SIZE*y+CUBE_SIZE > -posy+2.2)){
      colision = true;
      posx -= movx;
      movx = 0;
     }
    }
   }
  }
 }
}

void create_cube(int z, int x, int y){
 GLuint tarriba = cubestex[(cubes[z+10*(x+10*y)]-1)*3+1];
 GLuint tabajo = cubestex[(cubes[z+10*(x+10*y)]-1)*3];
 GLuint tcostado = cubestex[(cubes[z+10*(x+10*y)]-1)*3+2];
 unsigned short z1, z2;
 glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, &z1);

 if(is_selected and selected[0] == z and selected[1] == x and selected[2] == y){
  if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBindTexture(GL_TEXTURE_2D, 0);
   glColor3ub(0, 0, 0);
   farriba(x, y, z, 0);
   fabajo(x, y, z, 0);
   fadelante(x, y, z, 0);
   fatras(x, y, z, 0);
   fizquierda(x, y, z, 0);
   fderecha(x, y, z, 0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glColor3ub(255, 255, 255);
  }
 }

 farriba(x, y, z, tarriba);
 if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
  glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, &z2);
  if(z1>z2){
   z1 = z2;
   selected_face = 0;
   selected[0] = z;
   selected[1] = x;
   selected[2] = y;
   selbuf = true; }
 }

 fabajo(x, y, z, tabajo);
 if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
  glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, &z2);
  if(z1>z2){
   z1 = z2;
   selected_face = 1;
   selected[0] = z;
   selected[1] = x;
   selected[2] = y;
   selbuf = true; }
 }

 fadelante(x, y, z, tcostado);
 if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
  glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, &z2);
  if(z1>z2){
   z1 = z2;
   selected_face = 2;
   selected[0] = z;
   selected[1] = x;
   selected[2] = y;
   selbuf = true; }
 }

 fatras(x, y, z, tcostado);
 if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
  glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, &z2);
  if(z1>z2){
   z1 = z2;
   selected_face = 3;
   selected[0] = z;
   selected[1] = x;
   selected[2] = y;
   selbuf = true; }
 }

 fizquierda(x, y, z, tcostado);
 if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
  glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, &z2);
  if(z1>z2){
   z1 = z2;
   selected_face = 4;
   selected[0] = z;
   selected[1] = x;
   selected[2] = y;
   selbuf = true; }
 }

 fderecha(x, y, z, tcostado);
 if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
  glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, &z2);
  if(z1>z2){
   z1 = z2;
   selected_face = 4;
   selected[0] = z;
   selected[1] = x;
   selected[2] = y;
   selbuf = true; }
 }
}

void glEnable2D(){
 int vPort[4];

 glGetIntegerv(GL_VIEWPORT, vPort);

 glMatrixMode(GL_PROJECTION);
 glPushMatrix();
 glLoadIdentity();

 gluOrtho2D(0, vPort[2], 0, vPort[3]);
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
 glLoadIdentity();

 glDisable(GL_DEPTH_TEST);
}

void glDisable2D(){
 glMatrixMode(GL_PROJECTION);
 glPopMatrix();
 glMatrixMode(GL_MODELVIEW);
 glPopMatrix();
 glEnable(GL_DEPTH_TEST);
}

void create_mini(GLuint tarriba, GLuint tabajo, GLuint tcostado){
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
 glTranslatef(0, 0, -3);
 glRotatef(30, 1, 0, 0);
 glRotatef(45, 0, 1, 0);

 glColor3ub(255, 255, 255);

 glBindTexture(GL_TEXTURE_2D, tarriba); // Arriba
 glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-0.9, 0.9, -0.9);
  glTexCoord2f(1, 0);
  glVertex3f(0.9, 0.9, -0.9);
  glTexCoord2f(1, 1);
  glVertex3f(0.9, 0.9, 0.9);
  glTexCoord2f(0, 1);
  glVertex3f(-0.9, 0.9, 0.9);
 glEnd();
 glBindTexture(GL_TEXTURE_2D, tcostado); // Adelante
 glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-0.9, 0.9, 0.9);
  glTexCoord2f(1, 0);
  glVertex3f(0.9, 0.9, 0.9);
  glTexCoord2f(1, 1);
  glVertex3f(0.9, -0.9, 0.9);
  glTexCoord2f(0, 1);
  glVertex3f(-0.9, -0.9, 0.9);
 glEnd();
 glBindTexture(GL_TEXTURE_2D, tcostado); // Izquierda
 glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-0.9, 0.9, -0.9);
  glTexCoord2f(1, 0);
  glVertex3f(-0.9, 0.9, 0.9);
  glTexCoord2f(1, 1);
  glVertex3f(-0.9, -0.9, 0.9);
  glTexCoord2f(0, 1);
  glVertex3f(-0.9, -0.9, -0.9);
 glEnd();
}

GLuint load_tex(const char *name){
 SDL_Surface *surface = IMG_Load(name);
 GLuint tex = 0;
 glGenTextures(1, &tex);
 glBindTexture(GL_TEXTURE_2D, tex);
 int Mode = GL_RGB;
 if(surface->format->BytesPerPixel == 4){
  Mode = GL_RGBA;
 }
 gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h, Mode, GL_UNSIGNED_BYTE, surface->pixels);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 SDL_FreeSurface(surface);
 return tex;
}

void reshape(int width, int height){
 glViewport(0, 0, width, height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(60, (width*1.0)/height, 1, 100);
 glMatrixMode(GL_MODELVIEW);
}

void update_z(Uint8 x, Uint8 y){
 for(int z = 0 ; z<10 and z<-posz/CUBE_SIZE ; z++){
  if(cubes[z+10*(x+10*y)]){
   create_cube(z, x, y);
  }
 }
 for(int z = 9 ; z>-posz/CUBE_SIZE and z>=0 ; z--){
  if(cubes[z+10*(x+10*y)]){
   create_cube(z, x, y);
  }
 }
 if((int)-posz/CUBE_SIZE>=0 and (int)-posz/CUBE_SIZE<10){
  int z = -posz/CUBE_SIZE;
  if(cubes[z+10*(x+10*y)]){
   create_cube(z, x, y);
  }
 }
}

void update_y(Uint8 x){
 for(int y = 0 ; y<10 and y<-posy/CUBE_SIZE ; y++){
  update_z(x, y);
 }
 for(int y = 9 ; y>-posy/CUBE_SIZE and y>=0 ; y--){
  update_z(x, y);
 }
 if((int)-posy/CUBE_SIZE>=0 and (int)-posy/CUBE_SIZE<10){
  update_z(x, -posy/CUBE_SIZE);
 }
}

void update(){
 selbuf = false;
 for(int x = 0 ; x<10 and x<(int)posx/CUBE_SIZE ; x++){
  update_y(x);
 }
 for(int x = 9 ; x>(int)posx/CUBE_SIZE and x>-1 ; x--){
  update_y(x);
 }
 if((int)posx/CUBE_SIZE>=0 and (int)posx/CUBE_SIZE<10){
  update_y(posx/CUBE_SIZE);
 }
 is_selected = selbuf;

 glEnable2D();
 glBindTexture(GL_TEXTURE_2D, puntero);
 glBegin(GL_QUADS);
  glTexCoord2f(0,0);
  glVertex2f(WIN_W/2-14, WIN_H/2+14);
  glTexCoord2f(1,0);
  glVertex2f(WIN_W/2+14, WIN_H/2+14);
  glTexCoord2f(1,1);
  glVertex2f(WIN_W/2+14, WIN_H/2-14);
  glTexCoord2f(0,1);
  glVertex2f(WIN_W/2-14, WIN_H/2-14);
 glEnd();

 for(Uint8 x=0 ; x<8 ; x++){
  glBindTexture(GL_TEXTURE_2D, 0);
  if(miniactual == x){
   glColor4ub(255, 255, 255, 200);
   glBegin(GL_QUADS);
    glVertex2f(WIN_W/2-38*4+38*x, WIN_H-3);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-3);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-39);
    glVertex2f(WIN_W/2-38*4+38*x, WIN_H-39);
   glEnd();
  }
  else{
   glColor4ub(191, 191, 191, 166);
   glBegin(GL_QUADS);
    glVertex2f(WIN_W/2-38*4+38*x, WIN_H-3);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-3);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-39);
    glVertex2f(WIN_W/2-38*4+38*x, WIN_H-39);
   glEnd();
  }

  if(minisel[x]){
   glColor4ub(255, 255, 255, 255);
   glBindTexture(GL_TEXTURE_2D, mini[minisel[x]-1]);
   glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex2f(WIN_W/2-38*4+38*x, WIN_H-3);
    glTexCoord2f(1,1);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-3);
    glTexCoord2f(1,0);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-39);
    glTexCoord2f(0,0);
    glVertex2f(WIN_W/2-38*4+38*x, WIN_H-39);
   glEnd();
  }
 }

 glDisable2D();
 glFlush();
}
 
void init(){
 glClearColor(1, 0, 1, 0);
 
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_DEPTH);
 glEnable(GL_BLEND);
 glCullFace(GL_FRONT);
 glEnable(GL_CULL_FACE);
 glEnable(GL_POLYGON_OFFSET_LINE);
 glPolygonOffset(-1, -1);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
 glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 glEnable(GL_TEXTURE_2D);

 char buff[17];
 for(unsigned short x=1; x<27; x++){
  snprintf(buff, 17, "Cubos/%da.png", x);
  cubestex[(x-1)*3] = load_tex(buff);
  snprintf(buff, 17, "Cubos/%db.png", x);
  cubestex[(x-1)*3+1] = load_tex(buff);
  snprintf(buff, 17, "Cubos/%dc.png", x);
  cubestex[(x-1)*3+2] = load_tex(buff);
 }

 puntero = load_tex("Puntero.png");

 glGenTextures(26, mini);
 for(unsigned short x=0; x<26; x++){
  glBindTexture(GL_TEXTURE_2D, mini[x]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 36, 36, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
 }
 glBindTexture(GL_TEXTURE_2D, 0);

 glGenFramebuffers(1, &fboId);
 glBindFramebuffer(GL_FRAMEBUFFER, fboId);
 GLuint rboId;
 glGenRenderbuffers(1, &rboId);
 glBindRenderbuffer(GL_RENDERBUFFER, rboId);
 glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 36, 36);
 glBindRenderbuffer(GL_RENDERBUFFER, 0);
 glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);

 reshape(36, 36);

 for(unsigned short x=0; x<26; x++){
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mini[x], 0);
  create_mini(cubestex[(x*3)+1], cubestex[x*3], cubestex[(x*3)+2]);
 }
 glBindFramebuffer(GL_FRAMEBUFFER, 0);
 glDeleteFramebuffers(1, &fboId);

 SDL_ShowCursor(0);
 //SDL_SetRelativeMouseMode(SDL_TRUE); // Activar cuando se consdere pertinente
 
 for(short i = 0; i<1000; i++){
  cubes[i] = 0;
 }
 for(Uint8 x = 0; x<10; x++){
  for(Uint8 y = 0; y<10; y++){
   cubes[y+10*x] = 1;
   cubes[y+10*(x+10*9)] = 1;
   cubes[9+10*(x+10*y)] = 1;
   cubes[0+10*(x+10*y)] = 2;
  }
 }
}
 
int main(){
 if(SDL_Init(SDL_INIT_VIDEO) < 0){
  fprintf(stderr, "Fallo al iniciar el video: %s\n", SDL_GetError());
  return 1;
 }


 SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
 SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
 SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
 SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

 window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_OPENGL);
 SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
 SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);

 loadfuncs();

 init();
 reshape(WIN_W, WIN_H);

 SDL_Event event;
 short angxz = 0, angy = 0;
 float rad, sx = 0, sz = -1;

 const Uint8 *keystate;

 loop:
  colision = false;
  SDL_PumpEvents();
  while(SDL_PollEvent(&event)){
   if(event.type == SDL_QUIT){
    SDL_Quit();
    return 0; }
   if(event.type == SDL_MOUSEMOTION and event.motion.state&SDL_BUTTON(1)){
    move = true;
    rad = angy*PI/180;
    angxz += event.motion.yrel;
    angy += event.motion.xrel;
    sx += (event.motion.xrel/((float) 100))*cos(rad);
    sz += (event.motion.xrel/((float) 100))*sin(rad); }
   if(event.type == SDL_MOUSEBUTTONUP){
    if(not move and is_selected){
     if(event.button.button == SDL_BUTTON_RIGHT){
      cubes[selected[0]+10*(selected[1]+10*selected[2])] = 0;
     }
     if(event.button.button == SDL_BUTTON_LEFT and minisel[miniactual]){
      switch(selected_face){
       case 0: // Arriba
        cubes[selected[0]+10*(selected[1]+10*(selected[2]+1))] = minisel[miniactual];
        break;
       case 1: // Abajo
        cubes[selected[0]+10*(selected[1]+10*(selected[2]-1))] = minisel[miniactual];
        break;
       case 2: // Adelante
        cubes[(selected[0]+1)+10*(selected[1]+10*selected[2])] = minisel[miniactual];
        break;
       case 3: // Atras
        cubes[(selected[0]-1)+10*(selected[1]+10*selected[2])] = minisel[miniactual];
        break;
       case 4: // Izquierda
        cubes[selected[0]+10*((selected[1]-1)+10*selected[2])] = minisel[miniactual];
        break;
       case 5: // Derecha
        cubes[selected[0]+10*((selected[1]+1)+10*selected[2])] = minisel[miniactual];
        break;
      }
     }
    }
    else if(move){
     move = false;
    }
   }
  }

  movx = 0;
  movy = 0;
  movz = 0;
  keystate = SDL_GetKeyboardState(NULL);
   
  if(keystate[SDL_SCANCODE_RIGHT] or keystate[SDL_SCANCODE_D]){
   angy++;
   rad = angy*PI/180;
   sx += 0.1*cos(rad);
   sz += 0.1*sin(rad);
  }
  if(keystate[SDL_SCANCODE_LEFT] or keystate[SDL_SCANCODE_A]){
   angy--;
   rad = angy*PI/180;
   sx -= 0.1*cos(rad);
   sz -= 0.1*sin(rad);
  }
  if(keystate[SDL_SCANCODE_UP] or keystate[SDL_SCANCODE_W]){
   movx = 0.1*sin(rad);
   movx *= CUBE_SIZE;
   posx += movx;
   movz = 0.1*cos(rad);
   movz *= CUBE_SIZE;
   posz += movz;
   if(not SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)){
    angxz = 0;
   }
  }
  if(keystate[SDL_SCANCODE_DOWN] or keystate[SDL_SCANCODE_S]){
   movx = -(0.1*sin(rad));
   movx *= CUBE_SIZE;
   posx += movx;
   movz = -(0.1*cos(rad));
   movz *= CUBE_SIZE;
   posz += movz;
   if(not SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)){
    angxz = 0;
   }
  }
  if(keystate[SDL_SCANCODE_SPACE] and !caida){
   caida = CUBE_SIZE*-0.5;
  }
  if((keystate[SDL_SCANCODE_LSHIFT] or keystate[SDL_SCANCODE_RSHIFT])){
   movy = 0.15;
   posy += 0.15;  
  }
  if(keystate[SDL_SCANCODE_1]){
   miniactual = 0;
  }
  if(keystate[SDL_SCANCODE_2]){
   miniactual = 1;
  }
  if(keystate[SDL_SCANCODE_3]){
   miniactual = 2;
  }
  if(keystate[SDL_SCANCODE_4]){
   miniactual = 3;
  }
  if(keystate[SDL_SCANCODE_5]){
   miniactual = 4;
  }
  if(keystate[SDL_SCANCODE_6]){
   miniactual = 5;
  }
  if(keystate[SDL_SCANCODE_7]){
   miniactual = 6;
  }
  if(keystate[SDL_SCANCODE_8]){
   miniactual = 7;
  }
  caida += CUBE_SIZE*0.05;
  movy += caida;
  posy += caida;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(angy, 0, 1, 0);
  glRotatef(angxz, cos(rad), 0, sin(rad));
  glTranslatef(-posx, posy-CUBE_SIZE, posz);
  glColor3ub(255, 255, 255);
  update();

  if(colision){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glRotatef(angy, 0, 1, 0);
   glRotatef(angxz, cos(rad), 0, sin(rad));
   glTranslatef(-posx, posy-CUBE_SIZE, posz);
   glColor3ub(255, 255, 255);
   update();
  }

  SDL_GL_SwapWindow(window);
  SDL_RenderPresent(sdlRenderer);
 goto loop;
 return 0;
}
