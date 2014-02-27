#include "common.h"
 
int main(){
 init();

 SDL_Event event;
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
     if(event.button.button == SDL_BUTTON_RIGHT and (!id_inv[miniactual] or (id_inv[miniactual] == cubes[selected[0]+10*(selected[1]+10*selected[2])] and inv[miniactual] < 64))){
      id_inv[miniactual] = cubes[selected[0]+10*(selected[1]+10*selected[2])];
      inv[miniactual]++;
      cubes[selected[0]+10*(selected[1]+10*selected[2])] = 0;
     }
     if(event.button.button == SDL_BUTTON_LEFT and id_inv[miniactual]){
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

  move_update(keystate);

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
  
  #if FLY
   caida += 0;
  #else
   caida += CUBE_SIZE*GRAVEDAD;
  #endif

  movy += caida;
  posy += caida;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(angy, 0, 1, 0);
  glRotatef(angxz, cos(rad), 0, sin(rad));
  glTranslatef(-posx, posy-(CUBE_SIZE+CUBE_SIZE/2.0), posz);
  glColor3ub(255, 255, 255);
  update();

  if(colision){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glRotatef(angy, 0, 1, 0);
   glRotatef(angxz, cos(rad), 0, sin(rad));
   glTranslatef(-posx, posy-(CUBE_SIZE+CUBE_SIZE/2.0), posz);
   glColor3ub(255, 255, 255);
   update();
  }

  SDL_GL_SwapWindow(window);
  SDL_RenderPresent(sdlRenderer);
 goto loop;
 return 0;
}
