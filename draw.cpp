#include "common.h"

SDL_Window *window;
SDL_Renderer *sdlRenderer;
Uint8 selected_face; // Arriba-Abajo-Adelante-Atras-Izquierda-Derecha
GLuint cubestex[26*3], puntero, mini[26], fboId, nums[10], nums_r[10];
TTF_Font *minifont;

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

GLuint load_tex(const char *name, SDL_Surface *usurface){
 SDL_Surface *surface;
 if(usurface){ surface = usurface; }
 else{ surface = IMG_Load(name); }
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
 glClearColor(1, 0, 0, 1);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 for(int x = 0 ; x<10 ; x++){
  for(int y = 0 ; y<10 ; y++){
   for(int z = 0 ; z<10 ; z++){
    if(z >= -posz/CUBE_SIZE-6 and z <= -posz/CUBE_SIZE+6 and x >= posx/CUBE_SIZE-6 and x <= posx/CUBE_SIZE+6 and y >= -posy/CUBE_SIZE-6 and y <= -posy/CUBE_SIZE+6){
     if(cubes[z+10*(x+10*y)]){ create_plain(z, x, y); }
    }
   }
  }
 }
 glFlush();
 glFinish();
 unsigned char data[3] = {0, 0, 0};
 glReadPixels(WIN_W/2, WIN_H/2, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
 if(data[0] != 255){
  selected[0] = data[2];
  selected[1] = data[0]/6;
  selected[2] = data[1];
  selected_face = data[0]-selected[1]*6;
  is_selected = true;
 }
 else{ is_selected = false; }

 glColor3ub(255, 255, 255);
 glClearColor(0.3, 0.7, 0.9, 0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 for(int x = 0 ; x<10 and x<(int)posx/CUBE_SIZE ; x++){
  update_y(x);
 }
 for(int x = 9 ; x>(int)posx/CUBE_SIZE and x>-1 ; x--){
  update_y(x);
 }
 if((int)posx/CUBE_SIZE>=0 and (int)posx/CUBE_SIZE<10){
  update_y(posx/CUBE_SIZE);
 }

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
   glColor4ub(100, 100, 100, 200);
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

  if(id_inv[x]){
   glColor4ub(255, 255, 255, 255);
   glBindTexture(GL_TEXTURE_2D, mini[id_inv[x]-1]);
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
   if(inv[x]/100){
    if(inv[x] < 64){ glBindTexture(GL_TEXTURE_2D, nums[inv[x]/100]); }
    else{ glBindTexture(GL_TEXTURE_2D, nums_r[inv[x]/100]); }
    glBegin(GL_QUADS);
     glTexCoord2f(0,0);
     glVertex2f(WIN_W/2-38*4+38*x+9, WIN_H-20);
     glTexCoord2f(1,0);
     glVertex2f(WIN_W/2-38*4+38*x+18, WIN_H-20);
     glTexCoord2f(1,1);
     glVertex2f(WIN_W/2-38*4+38*x+18, WIN_H-39);
     glTexCoord2f(0,1);
     glVertex2f(WIN_W/2-38*4+38*x+9, WIN_H-39);
    glEnd();
    if(inv[x] < 64){ glBindTexture(GL_TEXTURE_2D, nums[(inv[x]/10)%10]); }
    else{ glBindTexture(GL_TEXTURE_2D, nums_r[(inv[x]/10)%10]); }
    glBegin(GL_QUADS);
     glTexCoord2f(0,0);
     glVertex2f(WIN_W/2-38*4+38*x+18, WIN_H-20);
     glTexCoord2f(1,0);
     glVertex2f(WIN_W/2-38*4+38*x+27, WIN_H-20);
     glTexCoord2f(1,1);
     glVertex2f(WIN_W/2-38*4+38*x+27, WIN_H-39);
     glTexCoord2f(0,1);
     glVertex2f(WIN_W/2-38*4+38*x+18, WIN_H-39);
    glEnd();
   }
   else if((inv[x]/10)%10){
    if(inv[x] < 64){ glBindTexture(GL_TEXTURE_2D, nums[(inv[x]/10)%10]); }
    else{ glBindTexture(GL_TEXTURE_2D, nums_r[(inv[x]/10)%10]); }
    glBegin(GL_QUADS);
     glTexCoord2f(0,0);
     glVertex2f(WIN_W/2-38*4+38*x+18, WIN_H-20);
     glTexCoord2f(1,0);
     glVertex2f(WIN_W/2-38*4+38*x+27, WIN_H-20);
     glTexCoord2f(1,1);
     glVertex2f(WIN_W/2-38*4+38*x+27, WIN_H-39);
     glTexCoord2f(0,1);
     glVertex2f(WIN_W/2-38*4+38*x+18, WIN_H-39);
    glEnd();
   }
   if(inv[x] < 64){ glBindTexture(GL_TEXTURE_2D, nums[inv[x]%10]); }
   else{ glBindTexture(GL_TEXTURE_2D, nums_r[inv[x]%10]); }
   glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(WIN_W/2-38*4+38*x+27, WIN_H-20);
    glTexCoord2f(1,0);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-20);
    glTexCoord2f(1,1);
    glVertex2f(WIN_W/2-38*4+38*x+36, WIN_H-39);
    glTexCoord2f(0,1);
    glVertex2f(WIN_W/2-38*4+38*x+27, WIN_H-39);
   glEnd();
  }
 }

 glDisable2D();
 glFlush();
}
