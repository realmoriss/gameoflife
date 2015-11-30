#include "gol_main.h"
#include "gol_grid.h"
#include "gol_font.h"

static const char CELL_TEXTURE_ALIVE_PATH[] = "assets/texture/cell_rect.png";
static SDL_Texture *cell_texture_alive = NULL;

static const char CELL_TEXTURE_DEAD_PATH[] = "assets/texture/cell_rect_dead.png";
static SDL_Texture *cell_texture_dead = NULL;

static const char MENU_BG_TEXTURE_PATH[] = "assets/texture/menualpha.png";
static SDL_Texture *menubg = NULL;

static char buf[128];

void render_init(GameVars *game_vars) {
   cell_texture_alive = Game_Load_Texture(CELL_TEXTURE_ALIVE_PATH, game_vars->renderer);
   cell_texture_dead = Game_Load_Texture(CELL_TEXTURE_DEAD_PATH, game_vars->renderer);
   menubg = Game_Load_Texture(MENU_BG_TEXTURE_PATH, game_vars->renderer);
}

void render_destroy(void) {
   if (cell_texture_alive != NULL) {
      SDL_DestroyTexture(cell_texture_alive);
      cell_texture_alive = NULL;
   }
   if (cell_texture_dead != NULL) {
      SDL_DestroyTexture(cell_texture_dead);
      cell_texture_dead = NULL;
   }
   if (menubg != NULL) {
      SDL_DestroyTexture(menubg);
      menubg = NULL;
   }
}

void render_grid(GameVars *game_vars) {
   int i,j;
   SDL_Rect itemrect;
   // Az elso ervenyes elem az 1. indexu - a szegely miatt
   for (i=0; i<game_vars->grid->size_x-1; i++) {
      for (j=0; j<game_vars->grid->size_y-1; j++) {
         Cell tmpcell = game_vars->grid->cells[i+1][j+1];
         if (tmpcell.state) {
            itemrect = (SDL_Rect){game_vars->cell_size*i, game_vars->cell_size*j, game_vars->cell_size, game_vars->cell_size};
            SDL_RenderCopy(game_vars->renderer, cell_texture_alive, NULL, &itemrect);
         } else if (tmpcell.was_alive) {
            itemrect = (SDL_Rect){game_vars->cell_size*i, game_vars->cell_size*j, game_vars->cell_size, game_vars->cell_size};
            SDL_RenderCopy(game_vars->renderer, cell_texture_dead, NULL, &itemrect);
         }
      }
   }
}

void render_menu_main(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Főmenü");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Kilépés, SPACE: Új élettér, LE: Élettér betöltése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}

void render_menu_load(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Élettér betöltése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Főmenü, SPACE: Élettér betöltése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}

void render_menu_new(GameVars *game_vars) {
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

void render_menu_sim_menu(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   render_grid(game_vars);
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

void render_menu_settings(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Szimuláció beállításai");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Vissza a Szimuláció menübe");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}

void render_menu_save(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   Game_SetFontText(game_vars->game_font, "Szimuláció mentése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Vissza a Szimuláció menübe");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   SDL_RenderPresent(game_vars->renderer);
}

void render_sim_paused(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   render_grid(game_vars);
   Game_SetFontText(game_vars->game_font, "Szimuláció (szünetel)");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Szimuláció menü, SPACE: Szimuláció futtatása");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   Game_SetFontText(game_vars->game_font, "Bal egér: Cella felélesztése, Jobb egér: Cella megölése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-32);
   SDL_RenderPresent(game_vars->renderer);

}

void render_sim_running(GameVars *game_vars) {
   SDL_SetRenderDrawColor(game_vars->renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(game_vars->renderer);
   render_grid(game_vars);
   Game_SetFontText(game_vars->game_font, "Szimuláció (fut)");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, 8);
   Game_SetFontText(game_vars->game_font, "ESC: Szimuláció menü, SPACE: Szimuláció szüneteltetése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-8);
   Game_SetFontText(game_vars->game_font, "Bal egér: Cella felélesztése, Jobb egér: Cella megölése");
   Game_RenderFont(game_vars->game_font, game_vars->screen->w/2-game_vars->game_font->texture_size.x/2, game_vars->screen->h-game_vars->game_font->texture_size.y-32);
   SDL_RenderPresent(game_vars->renderer);

}
