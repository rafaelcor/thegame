#include "common.h"

glGenFramebuffers_Func glGenFramebuffers = NULL;
glBindFramebuffer_Func glBindFramebuffer = NULL;
glGenRenderbuffers_Func glGenRenderbuffers = NULL;
glBindRenderbuffer_Func glBindRenderbuffer = NULL;
glRenderbufferStorage_Func glRenderbufferStorage = NULL;
glFramebufferRenderbuffer_Func glFramebufferRenderbuffer = NULL;
glFramebufferTexture2D_Func glFramebufferTexture2D = NULL;
glDeleteFramebuffers_Func glDeleteFramebuffers = NULL;

void loadfuncs(){
 glGenFramebuffers = (glGenFramebuffers_Func) SDL_GL_GetProcAddress("glGenFramebuffers");
 if(glGenFramebuffers == NULL){
  fprintf(stderr, "Fallo al cargar glGenFramebuffers\n");
  exit(1);
 }

 glBindFramebuffer = (glBindFramebuffer_Func) SDL_GL_GetProcAddress("glBindFramebuffer");
 if(glBindFramebuffer == NULL){
  fprintf(stderr, "Fallo al cargar glBindFramebuffer\n");
  exit(1);
 }

 glGenRenderbuffers = (glGenRenderbuffers_Func) SDL_GL_GetProcAddress("glGenRenderbuffers");
 if(glGenRenderbuffers == NULL){
  fprintf(stderr, "Fallo al cargar glGenRenderbuffers\n");
  exit(1);
 }

 glBindRenderbuffer = (glBindRenderbuffer_Func) SDL_GL_GetProcAddress("glBindRenderbuffer");
 if(glBindRenderbuffer == NULL){
  fprintf(stderr, "Fallo al cargar glBindRenderbuffer\n");
  exit(1);
 }

 glRenderbufferStorage = (glRenderbufferStorage_Func) SDL_GL_GetProcAddress("glRenderbufferStorage");
 if(glRenderbufferStorage == NULL){
  fprintf(stderr, "Fallo al cargar glRenderbufferStorage\n");
  exit(1);
 }

 glFramebufferRenderbuffer = (glFramebufferRenderbuffer_Func) SDL_GL_GetProcAddress("glFramebufferRenderbuffer");
 if(glFramebufferRenderbuffer == NULL){
  fprintf(stderr, "Fallo al cargar glFramebufferRenderbuffer\n");
  exit(1);
 }

 glFramebufferTexture2D = (glFramebufferTexture2D_Func) SDL_GL_GetProcAddress("glFramebufferTexture2D");
 if(glFramebufferTexture2D == NULL){
  fprintf(stderr, "Fallo al cargar glFramebufferTexture2D\n");
  exit(1);
 }

 glDeleteFramebuffers = (glDeleteFramebuffers_Func) SDL_GL_GetProcAddress("glDeleteFramebuffers");
 if(glDeleteFramebuffers == NULL){
  fprintf(stderr, "Fallo al cargar glDeleteFramebuffers\n");
  exit(1);
 }
}
