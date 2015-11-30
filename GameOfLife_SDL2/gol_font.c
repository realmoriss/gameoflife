#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gol_main.h"
#include "gol_font.h"

#define __DEBUG__

#ifdef __DEBUG__
#include "debugmalloc.h"
#endif // __DEBUG__

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
