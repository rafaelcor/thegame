#include "common.h"

Uint16 cubes[1000], id_inv[8] = {1, 2, 3, 4, 5, 6, 26, 0}, miniactual = 0;
Uint8 inv[8] = {1, 2, 4, 8, 16, 32, 64, 0};
bool is_selected = false;
int selected[3];

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
  if((not tex) and pr[1] == GL_FILL){
   if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+CUBE_SIZE-0.5
) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
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
  if((not tex) and pr[1] == GL_FILL){
   if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*(y-1) < -posy-0.5 and CUBE_SIZE*(y-1)+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*(y-1) < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*(y-1)+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
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
  if((not tex) and pr[1] == GL_FILL){
   if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
    if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posz -= movz;
      movz = 0;
     }
    }
    if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
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
  if((not tex) and pr[1] == GL_FILL){
   if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
    if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posz -= movz;
      movz = 0;
     }
    }
    if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posz -= movz;
      movz = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
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
  if((not tex) and pr[1] == GL_FILL){
   if((CUBE_SIZE*x > posx-2.4 and CUBE_SIZE*x < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
    if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posx -= movx;
      movx = 0;
     }
    }
    if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
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
  if((not tex) and pr[1] == GL_FILL){
   if((CUBE_SIZE*x+CUBE_SIZE > posx-2.4 and CUBE_SIZE*x+CUBE_SIZE < posx+2.4) or (CUBE_SIZE*x < posx-2.4 and CUBE_SIZE*x+CUBE_SIZE > posx-2.4) or (CUBE_SIZE*x < posx+2.4 and CUBE_SIZE*x+CUBE_SIZE > posx+2.4)){
    if((CUBE_SIZE*z > -posz-1.4 and CUBE_SIZE*z < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posx -= movx;
      movx = 0;
     }
    }
    if((CUBE_SIZE*z+CUBE_SIZE > -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE < -posz+1.4) or (CUBE_SIZE*z < -posz-1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz-1.4) or (CUBE_SIZE*z < -posz+1.4 and CUBE_SIZE*z+CUBE_SIZE > -posz+1.4)){
     if((CUBE_SIZE*y > -posy-0.5 and CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
      colision = true;
      posx -= movx;
      movx = 0;
     }
     if((CUBE_SIZE*y+CUBE_SIZE > -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE < -posy+(CUBE_SIZE-0.5)) or (CUBE_SIZE*y < -posy-0.5 and CUBE_SIZE*y+CUBE_SIZE > -posy-0.5) or (CUBE_SIZE*y < -posy+(CUBE_SIZE-0.5) and CUBE_SIZE*y+CUBE_SIZE > -posy+(CUBE_SIZE-0.5))){
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
 GLuint tarriba, tabajo, tcostado;
 tarriba = cubestex[(cubes[z+10*(x+10*y)]-1)*3+1];
 tabajo = cubestex[(cubes[z+10*(x+10*y)]-1)*3];
 tcostado = cubestex[(cubes[z+10*(x+10*y)]-1)*3+2];

 if(is_selected and selected[0] == z and selected[1] == x and selected[2] == y){
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

 farriba(x, y, z, tarriba);
 fabajo(x, y, z, tabajo);
 fadelante(x, y, z, tcostado);
 fatras(x, y, z, tcostado);
 fizquierda(x, y, z, tcostado);
 fderecha(x, y, z, tcostado);
}

void create_plain(int z, int x, int y){
 glColor3ub(x*6, y, z);
 farriba(x, y, z, 0);
 glColor3ub(x*6+1, y, z);
 fabajo(x, y, z, 0);
 glColor3ub(x*6+2, y, z);
 fadelante(x, y, z, 0);
 glColor3ub(x*6+3, y, z);
 fatras(x, y, z, 0);
 glColor3ub(x*6+4, y, z);
 fizquierda(x, y, z, 0);
 glColor3ub(x*6+5, y, z);
 fderecha(x, y, z, 0);
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
 glColor3ub(200, 200, 200);
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
}

void take_cube(){
 for(int x = 0 ; x<8 ; x++){
  if(id_inv[x] == cubes[selected[0]+10*(selected[1]+10*selected[2])] and inv[x] < 64){
   inv[x]++;
   cubes[selected[0]+10*(selected[1]+10*selected[2])] = 0;
   return;
  }
 }
 for(int x = 0 ; x<8 ; x++){
  if(!id_inv[x]){
   id_inv[x] = cubes[selected[0]+10*(selected[1]+10*selected[2])];
   inv[x]++;
   cubes[selected[0]+10*(selected[1]+10*selected[2])] = 0;
   return;
  }
 }
}

void put_cube(){
 switch(selected_face){
  case 0: // Arriba
   cubes[selected[0]+10*(selected[1]+10*(selected[2]+1))] = id_inv[miniactual];
   break;
  case 1: // Abajo
   cubes[selected[0]+10*(selected[1]+10*(selected[2]-1))] = id_inv[miniactual];
   break;
  case 2: // Adelante
   cubes[(selected[0]+1)+10*(selected[1]+10*selected[2])] = id_inv[miniactual];
   break;
  case 3: // Atras
   cubes[(selected[0]-1)+10*(selected[1]+10*selected[2])] = id_inv[miniactual];
   break;
  case 4: // Izquierda
   cubes[selected[0]+10*((selected[1]-1)+10*selected[2])] = id_inv[miniactual];
   break;
  case 5: // Derecha
   cubes[selected[0]+10*((selected[1]+1)+10*selected[2])] = id_inv[miniactual];
   break;
 }
 inv[miniactual]--;
 if(!inv[miniactual]){ id_inv[miniactual] = 0; }
}
