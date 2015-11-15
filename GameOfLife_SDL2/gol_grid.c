#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "gol_grid.h"
#include "sdl_helpers.h"

//#define __DEBUG__

#ifdef __DEBUG__
#include "debugmalloc.h"
#endif // __DEBUG__

static const int GRID_CAP_OVERHEAD = 32;
static const int GRID_CELL_SIZE = 16;

const int GRID_SIZE_DEFAULT = 255;

static const char CELL_TEXTURE_PATH[] = "assets/texture/cell_rect.png";
static const char DEADCELL_TEXTURE_PATH[] = "assets/texture/cell_rect_dead.png";

Grid *grid_new(SDL_Renderer *renderer, const int size_startx, const int size_starty) {
    // Lefoglaljuk a grid valtozot
    Grid *grid = malloc(sizeof(Grid));

    if (grid == NULL) {
        #ifdef __DEBUG__
        fprintf(stderr, "Malloc hiba a grid letrehozasanal.\n");
        #endif // __DEBUG__
        return NULL;
    }

    // Ha valamelyik meret parameter erteke kisebb mint nulla, akkor alapertelmezett mereture allitjuk a gridet
    if (size_startx < 0) {
        grid->cap_x = GRID_SIZE_DEFAULT + GRID_CAP_OVERHEAD;
        grid->size_x = GRID_SIZE_DEFAULT;
        #ifdef __DEBUG__
        fprintf(stderr, "Figyelmeztetes: Ervenytelen x meretet adtal meg a grid letrehozasanal! Alapertelmezes hasznalata...\n");
        #endif // __DEBUG__
    } else {
        grid->cap_x = size_startx + GRID_CAP_OVERHEAD;
        grid->size_x = size_startx;
    }
    if (size_starty < 0) {
        grid->cap_y = GRID_SIZE_DEFAULT + GRID_CAP_OVERHEAD;
        grid->size_y = GRID_SIZE_DEFAULT;
        #ifdef __DEBUG__
        fprintf(stderr, "Figyelmeztetes: Ervenytelen y meretet adtal meg a grid letrehozasanal! Alapertelmezes hasznalata...\n");
        #endif // __DEBUG__
    } else {
        grid->cap_y = size_starty + GRID_CAP_OVERHEAD;
        grid->size_y = size_starty;
    }

    grid->cells = malloc(sizeof(Cell *)*grid->cap_x);
    int i;
    for (i=0; i<grid->cap_x; i++) {
        grid->cells[i] = malloc(sizeof(Cell)*grid->cap_y);
    }

    // Cella merete (pixelekben)
    grid->cell_size = GRID_CELL_SIZE;
    grid->cell_texture.texture = Game_Load_Texture(CELL_TEXTURE_PATH, renderer);
    grid->cell_texture.texture_size = (Vec2D){GRID_CELL_SIZE, GRID_CELL_SIZE};
    grid->deadcell_texture.texture = Game_Load_Texture(DEADCELL_TEXTURE_PATH, renderer);
    grid->deadcell_texture.texture_size = (Vec2D){GRID_CELL_SIZE, GRID_CELL_SIZE};

    return grid;
}

void grid_free(Grid *grid) {
    // Fel kell szabaditani minden oszlopot, utana pedig a sort
    int i;
    for (i=0; i<grid->cap_x; i++) {
        free(grid->cells[i]);
    }
    free(grid->cells);

    SDL_DestroyTexture(grid->cell_texture.texture);
    SDL_DestroyTexture(grid->deadcell_texture.texture);

    // Felszabaditjuk a valtozot is
    free(grid);
}

void grid_init(Grid *grid) {
    // Grid kitoltese halott cellakkal
    int i,j;
    Cell new_cell = {dead, dead, dead};
    for (i=0; i<grid->size_x; i++) {
        for (j=0; j<grid->size_y; j++) {
            grid->cells[i][j] = new_cell;
        }
    }
}

void grid_set_sizex(Grid *grid) {
    int i, old_cap;
    // A +2 amiatt kell, hogy a grid korben halott cellakbol alljon - elkerulve a tulindexeles vizsgalatat.
    while (grid->cap_x < grid->size_x+2) {
        old_cap = grid->cap_x;
        grid->cap_x += GRID_CAP_OVERHEAD;
        grid->cells = realloc(grid->cells, sizeof(Cell *)*grid->cap_x);
        for (i=old_cap; i<grid->cap_x; i++) {
            grid->cells[i] = malloc(sizeof(Cell)*grid->cap_y);
        }
    }
}

void grid_set_sizey(Grid *grid) {
    int i;
    // A +2 amiatt kell, hogy a grid korben halott cellakbol alljon - elkerulve a tulindexeles vizsgalatat.
    while (grid->cap_y < grid->size_y+2) {
        grid->cap_y += GRID_CAP_OVERHEAD;
        for (i=0; i<grid->cap_x; i++) {
            grid->cells[i] = realloc(grid->cells[i], sizeof(Cell)*grid->cap_y);
        }
    }
}

void grid_set(Grid *grid, const int x, const int y, const Cell cell) {
    int i, j, old_size;
    Cell new_cell = {dead, dead, dead};
    // Ellenorizzuk le, hogy a tomb szelessege elegendo-e
    // Bele kell fernie a keretnek is.
    if (grid->size_x <= x+2) {
        old_size = grid->size_x;
        grid->size_x = x+2;
        grid_set_sizex(grid);
        // Az uj elemeket allitsuk alapertelmezett ertekure
        for (i=old_size; i<=grid->size_x; i++) {
            for (j=0; j<=grid->size_y; j++) {
                grid->cells[i][j] = new_cell;
            }
        }
    }
    // Ellenorizzuk le, hogy a tomb magassaga elegendo-e
    // Bele kell fernie a keretnek is.
    if (grid->size_y <= y+2) {
        old_size = grid->size_y;
        grid->size_y = y+2;
        grid_set_sizey(grid);
        // Az uj elemeket allitsuk alapertelmezett ertekure
        for (i=0; i<grid->cap_x; i++) {
            for (j=old_size; j<=grid->size_y; j++) {
                grid->cells[i][j] = new_cell;
            }
        }
    }
    grid->cells[x+1][y+1] = cell;
}

Cell grid_get(Grid *grid, const int x, const int y) {
    //
    if (x >= grid->size_x || y >= grid->size_y || x<0 || y<0) {
        fprintf(stderr, "Figyelmeztetes (grid_get): rossz indexet adtal meg! A fuggveny ures cellaval ter vissza!");
        return (Cell){dead, dead, dead};
    }
    return grid->cells[x+1][y+1];
}

void grid_cell_next_state(Grid *grid, int x, int y) {
    int count = 0;
    count+=grid->cells[x-1][y-1].state;
    count+=grid->cells[x-1][y].state;
    count+=grid->cells[x-1][y+1].state;
    count+=grid->cells[x][y-1].state;
    count+=grid->cells[x][y+1].state;
    count+=grid->cells[x+1][y-1].state;
    count+=grid->cells[x+1][y].state;
    count+=grid->cells[x+1][y+1].state;
    if (count < 2 || count > 3) {
        grid->cells[x][y].next_state = dead;
    } else if (grid->cells[x][y].state == alive || count == 3) {
        grid->cells[x][y].next_state = alive;
        grid->cells[x][y].was_alive = alive;
    }
}

void grid_logic(Grid *grid) {
    int i,j;
    for (i=1; i<=grid->size_x; i++) {
        for (j=1; j<=grid->size_y; j++) {
            grid_cell_next_state(grid, i, j);
        }
    }
    for (i=1; i<=grid->size_x; i++) {
        for (j=1; j<=grid->size_y; j++) {
            grid->cells[i][j].state = grid->cells[i][j].next_state;
        }
    }
}

void grid_render(SDL_Renderer *renderer, Grid *grid) {
    int i,j;
    SDL_Rect itemrect;
    // Az elso ervenyes elem az 1. indexu - a szegely miatt
    for (i=0; i<grid->size_x; i++) {
        for (j=0; j<grid->size_y; j++) {
            Cell tmpcell = grid->cells[i+1][j+1];
            if (tmpcell.state) {
                itemrect = (SDL_Rect){grid->cell_size*i, grid->cell_size*j, grid->cell_texture.texture_size.x, grid->cell_texture.texture_size.y};
                SDL_RenderCopy(renderer, grid->cell_texture.texture, NULL, &itemrect);
            } else if (tmpcell.was_alive) {
                itemrect = (SDL_Rect){grid->cell_size*i, grid->cell_size*j, grid->cell_texture.texture_size.x, grid->cell_texture.texture_size.y};
                SDL_RenderCopy(renderer, grid->deadcell_texture.texture, NULL, &itemrect);
            }
        }
    }
}

void grid_set_alive(Grid *grid, int x, int y) {
   Cell tmpcell;
   tmpcell = grid_get(grid, x, y);
   tmpcell.state = alive;
   tmpcell.was_alive = alive;
   grid_set(grid, x, y, tmpcell);
}

void grid_set_dead(Grid *grid, int x, int y) {
   Cell tmpcell;
   tmpcell = grid_get(grid, x, y);
   tmpcell.state = dead;
   grid_set(grid, x, y, tmpcell);
}
