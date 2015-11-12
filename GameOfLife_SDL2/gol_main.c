#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "gol_grid.h"
#include "gol_main.h"

//#define __DEBUG__

#ifdef __DEBUG__
#include "debugmalloc.h"
#endif // __DEBUG__

static const char GAME_FONT_PATH[] = "assets/fonts/opensans.ttf";
static const int GAME_FONT_SIZE = 20;

static int grid_sizex;
static int grid_sizey;

GameEvent Game_ParseEvent(SDL_Event ev) {
   switch (ev.type) {
      case SDL_KEYDOWN:
         switch (ev.key.keysym.sym) {
            case SDLK_ESCAPE:
               return EV_KEY_ESC;
            case SDLK_SPACE:
               return EV_KEY_SPACE;
            case SDLK_UP:
               return EV_KEY_UP;
            case SDLK_DOWN:
               return EV_KEY_DOWN;
            case SDLK_LEFT:
               return EV_KEY_LEFT;
            case SDLK_RIGHT:
               return EV_KEY_RIGHT;
            default:
               return EV_INVALID;
         }
      case SDL_MOUSEBUTTONDOWN:
         switch (ev.button.button) {
            case SDL_BUTTON_LEFT:
               return EV_MOUSE_L_D;
            case SDL_BUTTON_RIGHT:
               return EV_MOUSE_R_D;
         }
      break;
      case SDL_MOUSEBUTTONUP:
         switch (ev.button.button) {
            case SDL_BUTTON_LEFT:
               return EV_MOUSE_L_U;
            case SDL_BUTTON_RIGHT:
               return EV_MOUSE_R_U;
         }
      case SDL_MOUSEMOTION:
         return EV_MOUSE_MOTION;
      case SDL_QUIT:
         return EV_EXIT;
      default:
         return EV_INVALID;
   }
   return EV_INVALID;
}

GameState Game_StateMachine(GameVars *game_vars) {
   SDL_Event ev;
   GameEvent gameev;

   switch (game_vars->state) {
      case STATE_INIT:
         if (!Game_Init_All(game_vars, "Game of Life")) {
            #ifdef __DEBUG__
            fprintf(stderr, "Init hiba, kilepes...\n");
            #endif // __DEBUG__
            return STATE_EXIT;
         }
         return STATE_MAIN_MENU;
      case STATE_MAIN_MENU:
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         Game_SetFontText(game_vars->game_font, "Főmenü");
         Game_RenderFont(game_vars->game_font, 8, 8);
         Game_SetFontText(game_vars->game_font, "ESC: Kilépés, SPACE: Új élettér, LE: Élettér betöltése");
         Game_RenderFont(game_vars->game_font, 8, 30);
         SDL_RenderPresent(game_vars->renderer);
         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
               case EV_KEY_ESC:
                  return STATE_EXIT;
               case EV_KEY_SPACE:
                  grid_sizex = GRID_SIZE_DEFAULT;
                  grid_sizey = GRID_SIZE_DEFAULT;
                  return STATE_NEW_MENU;
               case EV_KEY_DOWN:
                  return STATE_LOAD_MENU;
               default:
                  break;
            }
         }
         return game_vars->state;
      case STATE_LOAD_MENU:
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         Game_SetFontText(game_vars->game_font, "Élettér betöltése");
         Game_RenderFont(game_vars->game_font, 8, 8);
         Game_SetFontText(game_vars->game_font, "ESC: Főmenü, SPACE: Élettér betöltése");
         Game_RenderFont(game_vars->game_font, 8, 30);
         SDL_RenderPresent(game_vars->renderer);
         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
                  return STATE_EXIT;
               case EV_KEY_ESC:
                  return STATE_MAIN_MENU;
               case EV_KEY_SPACE:
                  if (game_vars->grid == NULL) {
                     game_vars->grid = grid_new(game_vars->renderer, -1, -1);
                     grid_init(game_vars->grid);
                  }
                  return STATE_SIM_PAUSED;
               default:
                  break;
            }
         }
         return game_vars->state;
      case STATE_NEW_MENU:
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         Game_SetFontText(game_vars->game_font, "Új élettér");
         Game_RenderFont(game_vars->game_font, 8, 8);
         Game_SetFontText(game_vars->game_font, "ESC: Főmenü, SPACE: Szimuláció indítása");
         Game_RenderFont(game_vars->game_font, 8, 30);
         Game_SetFontText(game_vars->game_font, "BAL/JOBB: Grid szélessége, FEL/LE: Grid magassága");
         Game_RenderFont(game_vars->game_font, 8, 52);
         char buf[128];
         sprintf(buf, "Szélesség: %d", grid_sizex);
         Game_SetFontText(game_vars->game_font, buf);
         Game_RenderFont(game_vars->game_font, 64, 100);
         sprintf(buf, "Magasság: %d", grid_sizey);
         Game_SetFontText(game_vars->game_font, buf);
         Game_RenderFont(game_vars->game_font, 64, 122);
         SDL_RenderPresent(game_vars->renderer);
         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
                  return STATE_EXIT;
               case EV_KEY_ESC:
                  return STATE_MAIN_MENU;
               case EV_KEY_SPACE:
                  if (game_vars->grid == NULL) {
                     game_vars->grid = grid_new(game_vars->renderer,  grid_sizex, grid_sizey);
                     grid_init(game_vars->grid);
                  }
                  return STATE_SIM_PAUSED;
               case EV_KEY_UP:
                  grid_sizey++;
                  break;
               case EV_KEY_DOWN:
                  if (grid_sizey > 1) {
                     grid_sizey--;
                  }
                  break;
               case EV_KEY_RIGHT:
                  grid_sizex++;
                  break;
               case EV_KEY_LEFT:
                  if (grid_sizex > 1) {
                     grid_sizex--;
                  }
                  break;
               default:
                  break;
            }
         }
         return game_vars->state;
      case STATE_EXIT:
         Game_Destroy_All(game_vars);
         SDL_Quit();
         return STATE_INVALID;
      case STATE_SIM_PAUSED:
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         grid_render(game_vars->renderer, game_vars->grid);
         Game_SetFontText(game_vars->game_font, "Szimuláció (szünetel)");
         Game_RenderFont(game_vars->game_font, 8, 8);
         Game_SetFontText(game_vars->game_font, "ESC: Szimuláció menü, SPACE: Szimuláció futtatása");
         Game_RenderFont(game_vars->game_font, 8, 30);
         SDL_RenderPresent(game_vars->renderer);
         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
                  return STATE_EXIT;
               case EV_KEY_ESC:
                  return STATE_SIM_MENU;
               case EV_KEY_SPACE:
                  return STATE_SIM_RUNNING;
               case EV_MOUSE_L_D:
                  grid_set_alive(game_vars->grid, ev.motion.x/game_vars->grid->cell_size, ev.motion.y/game_vars->grid->cell_size);
                  break;
               case EV_MOUSE_R_D:
                  grid_set_dead(game_vars->grid, ev.motion.x/game_vars->grid->cell_size, ev.motion.y/game_vars->grid->cell_size);
                  break;
               default:
                  break;
            }
         }
         return game_vars->state;
      case STATE_SIM_RUNNING:
         grid_logic(game_vars->grid);
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         grid_render(game_vars->renderer, game_vars->grid);
         Game_SetFontText(game_vars->game_font, "Szimuláció (fut)");
         Game_RenderFont(game_vars->game_font, 8, 8);
         Game_SetFontText(game_vars->game_font, "ESC: Szimuláció menü, SPACE: Szimuláció szüneteltetése");
         Game_RenderFont(game_vars->game_font, 8, 30);
         SDL_RenderPresent(game_vars->renderer);

         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
                  return STATE_EXIT;
               case EV_KEY_ESC:
                  return STATE_SIM_MENU;
               case EV_KEY_SPACE:
                  return STATE_SIM_PAUSED;
               case EV_MOUSE_L_D:
                  grid_set_alive(game_vars->grid, ev.motion.x/game_vars->grid->cell_size, ev.motion.y/game_vars->grid->cell_size);
                  break;
               case EV_MOUSE_R_D:
                  grid_set_dead(game_vars->grid, ev.motion.x/game_vars->grid->cell_size, ev.motion.y/game_vars->grid->cell_size);
                  break;
               default:
                  break;
            }
         }
         return game_vars->state;
      case STATE_SIM_MENU:
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         Game_SetFontText(game_vars->game_font, "Szimuláció menü");
         Game_RenderFont(game_vars->game_font, 8, 8);
         Game_SetFontText(game_vars->game_font, "ESC: Kilépés a főmenübe, SPACE: Vissza a szimulációhoz");
         Game_RenderFont(game_vars->game_font, 8, 30);
         Game_SetFontText(game_vars->game_font, "LE: Szimuláció mentése, FEL: Szimuláció beállításai");
         Game_RenderFont(game_vars->game_font, 8, 52);
         SDL_RenderPresent(game_vars->renderer);
         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
                  return STATE_EXIT;
               case EV_KEY_ESC:
                  if (game_vars->grid != NULL) {
                     grid_free(game_vars->grid);
                     game_vars->grid = NULL;
                  }
                  return STATE_MAIN_MENU;
               case EV_KEY_SPACE:
                  return STATE_SIM_PAUSED;
               case EV_KEY_DOWN:
                  return STATE_SIM_SAVE;
               case EV_KEY_UP:
                  return STATE_SIM_SETTINGS;
               default:
                  break;
            }
         }
         return game_vars->state;
      case STATE_SIM_SETTINGS:
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         Game_SetFontText(game_vars->game_font, "Szimuláció beállításai - ESC: Vissza a Szimuláció menübe");
         Game_RenderFont(game_vars->game_font, 8, 30);
         SDL_RenderPresent(game_vars->renderer);
         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
                  return STATE_EXIT;
               case EV_KEY_ESC:
                  return STATE_SIM_MENU;
               default:
                  break;
            }
         }
         return game_vars->state;
      case STATE_SIM_SAVE:
         SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(game_vars->renderer);
         Game_SetFontText(game_vars->game_font, "Szimuláció mentése - ESC: Vissza a Szimuláció menübe");
         Game_RenderFont(game_vars->game_font, 8, 30);
         SDL_RenderPresent(game_vars->renderer);
         while (SDL_PollEvent(&ev)) {
            gameev = Game_ParseEvent(ev);
            switch (gameev) {
               case EV_EXIT:
                  return STATE_EXIT;
               case EV_KEY_ESC:
                  return STATE_SIM_MENU;
               default:
                  break;
            }
         }
         return game_vars->state;
      default:
         return STATE_EXIT;
   }
}

int Game_Init_All(GameVars *game_vars, const char *title) {
   const int SCREEN_INIT_W = 1280;
   const int SCREEN_INIT_H = 720;

   game_vars->window = NULL;
   game_vars->screen = NULL;
   game_vars->renderer = NULL;
   game_vars->game_font = NULL;
   game_vars->grid = NULL;
   game_vars->state = STATE_INIT;

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
      #endif // __DEBUG__
      return 0;
   }
   if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" )) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL figyelmeztetes: a linearis textura szures nem lett aktivalva\n");
      #endif // __DEBUG__
   }

   game_vars->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_INIT_W, SCREEN_INIT_H, SDL_WINDOW_SHOWN);
   if (game_vars->window == NULL) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
      #endif // __DEBUG__
      return 0;
   }

   game_vars->renderer = SDL_CreateRenderer(game_vars->window, -1, SDL_RENDERER_ACCELERATED);

   if (game_vars->renderer == NULL) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
      #endif // __DEBUG__
      return 0;
   }

   //Initialize renderer color
   SDL_SetRenderDrawColor(game_vars->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

   //Initialize PNG loading
   int imgFlags = IMG_INIT_PNG;
   if (!( IMG_Init( imgFlags ) & imgFlags )) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL_image hiba: %s\n", IMG_GetError());
      #endif // __DEBUG__
      return 0;
   }

   if (TTF_Init() == -1) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL_ttf hiba: %s\n", TTF_GetError());
      #endif // __DEBUG__
      return 0;
   }

   game_vars->game_font = Game_LoadFont(game_vars->renderer,
                                        GAME_FONT_PATH,
                                        "FONT LOADED",
                                        (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF},
                                        GAME_FONT_SIZE);

   if (game_vars->game_font == NULL) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL_ttf hiba: %s\n", TTF_GetError());
      #endif // __DEBUG__
      return 0;

   }

   game_vars->screen = SDL_GetWindowSurface(game_vars->window);
   return 1;
}

void Game_Destroy_All(GameVars *game_vars) {
   if (game_vars->renderer != NULL) {
      SDL_DestroyRenderer(game_vars->renderer);
      game_vars->renderer = NULL;
   }
   if (game_vars->window != NULL) {
      SDL_DestroyWindow(game_vars->window);
      game_vars->window = NULL;
   }
   if (game_vars->game_font != NULL) {
      Game_FreeFont(game_vars->game_font);
      game_vars->game_font = NULL;
   }
   if (game_vars->grid != NULL) {
      grid_free(game_vars->grid);
      game_vars->grid = NULL;
   }
}

SDL_Texture* Game_Load_Texture(const char *path, SDL_Renderer *renderer) {
	SDL_Texture* texture = NULL;
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL) {
		fprintf(stderr, "SDL_image Error: %s\n", IMG_GetError());
	} else {
        texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
		if (texture == NULL) {
			fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(imgSurface);
	}

	return texture;
}

GameFont *Game_LoadFont(SDL_Renderer *renderer, const char* path, const char* init_str, const SDL_Color color, const int text_size) {
   GameFont *gamefont = malloc(sizeof(GameFont));
   if (gamefont == NULL) {
      #ifdef __DEBUG__
      fprintf(stderr, "Malloc hiba a font letrehozasa kozben!\n");
      #endif // __DEBUG__
      return NULL;
   }

   gamefont->renderer = renderer;
   gamefont->font = NULL;
   gamefont->texture = NULL;

   gamefont->font = TTF_OpenFont(path, text_size);
   if (gamefont->font == NULL) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL_ttf hiba: %s\n", TTF_GetError());
      #endif // __DEBUG__
      Game_FreeFont(gamefont);
      return NULL;
   }

   gamefont->color = color;
   if (!Game_SetFontText(gamefont, init_str)) {
      Game_FreeFont(gamefont);
      return NULL;
   }

   return gamefont;
}

void Game_RenderFont(GameFont *game_font, int x, int y) {
    SDL_Rect fontrect = {x, y, game_font->texture_size.x, game_font->texture_size.y};
    SDL_RenderCopy(game_font->renderer, game_font->texture, NULL, &fontrect);
}

int Game_SetFontText(GameFont *gamefont, const char* str) {
   if (gamefont->texture != NULL) {
      SDL_DestroyTexture(gamefont->texture);
      gamefont->texture = NULL;
   }

   // Render font to texture
   SDL_Surface *surface = NULL;
   surface = TTF_RenderUTF8_Blended(gamefont->font, str, gamefont->color);
   if (surface == NULL) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL_ttf hiba: %s\n", TTF_GetError());
      #endif // __DEBUG__
      return 0;
   }
   gamefont->texture = SDL_CreateTextureFromSurface(gamefont->renderer, surface);
   if (gamefont->texture == NULL) {
      #ifdef __DEBUG__
      fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
      #endif // __DEBUG__
      return 0;
   }
   gamefont->texture_size = (Vec2D){surface->w, surface->h};
   SDL_FreeSurface(surface);

   return 1;
}

void Game_FreeFont(GameFont *gamefont) {
   if (gamefont->font != NULL) {
      TTF_CloseFont(gamefont->font);
   }
   if (gamefont->texture != NULL) {
      SDL_DestroyTexture(gamefont->texture);
   }

   free(gamefont);
}
