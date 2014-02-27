#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "common.h"

extern float posz, posx, posy, movx, movy, movz, caida;
extern bool colision, move;
extern short angxz, angy;
extern float rad, sx, sz;

void move_update(const Uint8*);

#endif
