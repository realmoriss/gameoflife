#include <stdio.h>
#include <SDL.h>
#include <SDL_TTF.h>
#include "gol_main.h"
#include "gol_grid.h"

//#define __DEBUG__

#ifdef __DEBUG__
#include "debugmalloc.h"
#endif // __DEBUG__

static char buf[128];
static SDL_Texture *menubg = NULL;
static const char MENU_BG_TEXTURE_PATH[] = "assets/texture/menualpha.png";

void menu_init(GameVars *game_vars) {
   menubg = Game_Load_Texture(MENU_BG_TEXTURE_PATH, game_vars->renderer);
}

void menu_destroy(void) {
   if (menubg != NULL) {
      SDL_DestroyTexture(menubg);
      menubg = NULL;
   }
}

void menu_render_main(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Főmenü");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Kilépés, SPACE: Új élettér, LE: Élettér betöltése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}

void menu_render_load(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Élettér betöltése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Főmenü, SPACE: Élettér betöltése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}

void menu_render_new(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Új élettér");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Főmenü, SPACE: Szimuláció indítása");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   Game_SetFontText(game_vars->game_font, "BAL/JOBB: Grid szélessége, FEL/LE: Grid magassága");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-32);
   sprintf(buf, "Szélesség: %g", game_vars->grid_size.x);
   Game_SetFontText(game_vars->game_font, buf);
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h/2-game_vars->game_font->texture_size.y/2);
   sprintf(buf, "Magasság: %g",  game_vars->grid_size.y);
   Game_SetFontText(game_vars->game_font, buf);
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h/2+game_vars->game_font->texture_size.y/2);
   SDL_RenderPresent(game_vars->renderer);
}

void menu_render_sim_menu(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   grid_render(game_vars->renderer, game_vars->grid);
   SDL_Rect itemrect = {0, 0, game_vars->screen->w, game_vars->screen->h};
   SDL_RenderCopy(game_vars->renderer, menubg, NULL, &itemrect);
   Game_SetFontText(game_vars->game_font, "Szimuláció menü");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "Q: Kilépés a főmenübe, ESC: Vissza a szimulációhoz");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   Game_SetFontText(game_vars->game_font, "LE: Szimuláció mentése, FEL: Szimuláció beállításai");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-32);
   SDL_RenderPresent(game_vars->renderer);
}

void menu_render_settings(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Szimuláció beállításai");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Vissza a Szimuláció menübe");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}

void menu_render_save(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Szimuláció mentése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Vissza a Szimuláció menübe");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}
