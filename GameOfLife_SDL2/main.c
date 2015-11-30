#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gol_grid.h"
#include "gol_main.h"

#define __DEBUG__

#ifdef __DEBUG__
#include "debugmalloc.h"
#endif // __DEBUG__

int main(int argc, char *argv[])
{
   #ifdef __DEBUG__
   debugmalloc_naplofajl("debug_gol.txt");
   #endif // __DEBUG__

   // A jatek fobb valtozoit tartalmazo struktura
   GameVars game_vars;
   game_vars.state = STATE_INIT;

   int quit = 0;
   while (!quit) {
      // Allapotgep vezerlese
      game_vars.state = Game_StateMachine(&game_vars);
      // Kilepes, ha elertuk a vegallapotot
      if (game_vars.state == STATE_INVALID) {
         quit = 1;
      }
   }
   #ifdef __DEBUG__
   debugmalloc_dump();
   #endif // __DEBUG__
   return 0;
}
