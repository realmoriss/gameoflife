#ifndef GOL_MAIN_H_INCLUDED
#define GOL_MAIN_H_INCLUDED

/** \brief A jatek allapotai
 */
typedef enum t_game_state {
   STATE_INIT,          /**< Valtozok inicializalasa */
   STATE_MAIN_MENU,     /**< A fomenu */
   STATE_LOAD_MENU,     /**< A grid betoltese menu */
   STATE_NEW_MENU,      /**< Az uj grid menu */
   STATE_EXIT,          /**< Valtozok felszabaditasa */
   STATE_SIM_PAUSED,    /**< A grid szimulalasa, lepesenkent */
   STATE_SIM_RUNNING,   /**< A grid szimulalasa, folyamatosan */
   STATE_SIM_MENU,      /**< A szimulacio menu */
   STATE_SIM_SETTINGS,  /**< A szimulacio beallitasai menu */
   STATE_SIM_SAVE,      /**< A grid mentese menu */
   STATE_INVALID        /**< A program veget jelzo allapot */
} GameState;

typedef enum t_game_event {
   EV_EXIT,
   EV_MOUSE_L_D,
   EV_MOUSE_L_U,
   EV_MOUSE_R_D,
   EV_MOUSE_R_U,
   EV_MOUSE_MOTION,
   EV_KEY_ESC,
   EV_KEY_SPACE,
   EV_KEY_UP,
   EV_KEY_DOWN,
   EV_KEY_LEFT,
   EV_KEY_RIGHT,
   EV_INVALID
} GameEvent;

typedef struct vec_2d {
    double x;
    double y;
} Vec2D;

typedef struct t_game_font {
    TTF_Font *font;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Vec2D texture_size;
    SDL_Color color;
} GameFont;

typedef enum t_cell_state {
    dead = 0,
    alive = 1
} CellState;

typedef struct t_cell {
    CellState state;
    CellState next_state;
    CellState was_alive;
} Cell;

typedef struct t_cell_texture {
    SDL_Texture* texture;
    Vec2D texture_size;
} CellTexture;

typedef struct t_grid {
    int size_x;
    int size_y;
    int cap_x;
    int cap_y;
    Cell **cells;
    int cell_size;
    CellTexture cell_texture;
    CellTexture deadcell_texture;
} Grid;

typedef struct t_game_vars {
   SDL_Window *window;
   SDL_Surface *screen;
   SDL_Renderer *renderer;
   GameFont *game_font;
   Grid *grid;
   GameState state;
} GameVars;

GameEvent Game_ParseEvent(SDL_Event ev);
GameState Game_StateMachine(GameVars *game_vars);

int Game_Init_All(GameVars *game_vars, const char *title);
void Game_Destroy_All(GameVars *game_vars);

SDL_Texture* Game_Load_Texture(const char *path, SDL_Renderer *renderer);

GameFont *Game_LoadFont(SDL_Renderer *renderer, const char *path, const char *init_str, const SDL_Color color, const int text_size);
void Game_RenderFont(GameFont *game_font, int x, int y);
int Game_SetFontText(GameFont *gamefont, const char* str);
void Game_FreeFont(GameFont *gamefont);

#endif // GOL_MAIN_H_INCLUDED
