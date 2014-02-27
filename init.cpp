#include "common.h"

void inexit(){
 TTF_CloseFont(minifont);
 TTF_Quit();
 SDL_Quit();
}
 
void init(){
 if(SDL_Init(SDL_INIT_VIDEO) < 0){
  fprintf(stderr, "Fallo al iniciar el video: %s\n", SDL_GetError());
  exit(1);
 }

 atexit(inexit);

 if(TTF_Init() == -1) {
  fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
  exit(1);
 }

 SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
 SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
 SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
 SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

 window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_OPENGL);
 sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
 SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);

 loadfuncs();

 glClearColor(0.3, 0.7, 0.9, 0);
 
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
  cubestex[(x-1)*3] = load_tex(buff, NULL);
  snprintf(buff, 17, "Cubos/%db.png", x);
  cubestex[(x-1)*3+1] = load_tex(buff, NULL);
  snprintf(buff, 17, "Cubos/%dc.png", x);
  cubestex[(x-1)*3+2] = load_tex(buff, NULL);
 }

 puntero = load_tex("Puntero.png", NULL);

 minifont = TTF_OpenFont("FreeSerif.ttf", 16);
 if(!minifont){
  fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
  exit(1);
 }

 SDL_Surface *text_surface;
 SDL_Color white = {255, 255, 255}, red = {0, 0, 255};

 for(short i = 0 ; i<10 ; i++){
  char num[2] = {'0', 0};
  num[0] += i;
  text_surface = TTF_RenderUTF8_Blended(minifont, num, white);
  if(!minifont){
   fprintf(stderr, "TTF_RenderUTF8 %d: %s\n", i, TTF_GetError());
   exit(1);
  }
  nums[i] = load_tex("", text_surface);
 }
 for(short i = 0 ; i<10 ; i++){
  char num[2] = {'0', 0};
  num[0] += i;
  text_surface = TTF_RenderUTF8_Blended(minifont, num, red);
  if(!minifont){
   fprintf(stderr, "TTF_RenderUTF8 %d: %s\n", i, TTF_GetError());
   exit(1);
  }
  nums_r[i] = load_tex("", text_surface);
 }

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

 glDisable(GL_BLEND);
 for(unsigned short x=0; x<26; x++){
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mini[x], 0);
  create_mini(cubestex[(x*3)+1], cubestex[x*3], cubestex[(x*3)+2]);
 }
 glEnable(GL_BLEND);
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

 reshape(WIN_W, WIN_H);
}
