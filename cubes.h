#ifndef CUBES_H
#define CUBES_H

#include "common.h"

extern Uint16 cubes[1000], id_inv[8], miniactual;
extern Uint8 inv[8];
extern bool is_selected;
extern int selected[3];

void farriba(int, int, int, GLuint);
void fabajo(int, int, int, GLuint);
void fadelante(int, int, int, GLuint);
void fatras(int, int, int, GLuint);
void fizquierda(int, int, int, GLuint);
void fderecha(int, int, int, GLuint);
void create_cube(int, int, int);
void create_plain(int, int, int);
void create_mini(GLuint, GLuint, GLuint);

#endif
