#include "common.h"

float posz = -(CUBE_SIZE*5), posx = CUBE_SIZE*5, posy = -10, movx = 0, movy = 0, movz = 0, caida = 0;
bool colision, move = false;
short angxz = 0, angy = 0;
float rad, sx = 0, sz = -1;

void move_update(const Uint8 *keystate){
 if(keystate[SDL_SCANCODE_RIGHT] or keystate[SDL_SCANCODE_D]){
  angy += 3;
  rad = angy*PI/180;
  sx += 0.1*cos(rad);
  sz += 0.1*sin(rad);
 }
 if(keystate[SDL_SCANCODE_LEFT] or keystate[SDL_SCANCODE_A]){
  angy -= 3;
  rad = angy*PI/180;
  sx -= 0.1*cos(rad);
  sz -= 0.1*sin(rad);
 }
 if(keystate[SDL_SCANCODE_UP] or keystate[SDL_SCANCODE_W]){
  movx = 0.1*sin(rad)*2;
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
  movx = -(0.1*sin(rad)*2);
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
  movy = 0.90;
  posy += 0.90;  
 }
}
