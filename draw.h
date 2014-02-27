#ifndef DRAW_H
#define DRAW_H

#include "common.h"

extern SDL_Window *window;
extern SDL_Renderer *sdlRenderer;
extern Uint8 selected_face; // Arriba-Abajo-Adelante-Atras-Izquierda-Derecha
extern GLuint cubestex[26*3], puntero, mini[26], fboId, nums[10], nums_r[10];
extern bool selbuf;
extern TTF_Font *minifont;

void glEnable2D();
void glDisable2D();
GLuint load_tex(const char*, SDL_Surface*);
void reshape(int, int);
void update_z(Uint8, Uint8);
void update_y(Uint8);
void update();

#endif
