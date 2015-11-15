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

/** \brief A felhasznalo altal generalt esemenyek
 */
typedef enum t_game_event {
   EV_EXIT,             /**< Kilepesi esemeny */
   EV_MOUSE_L_D,        /**< Bal egergomb lenyomasa */
   EV_MOUSE_L_U,        /**< Bal egergomb felengedese */
   EV_MOUSE_R_D,        /**< Jobb egergomb lenyomasa */
   EV_MOUSE_R_U,        /**< Jobb egergomb felengedese */
   EV_MOUSE_MOTION,     /**< Eger mozgatasa */
   EV_KEY_ESC,          /**< ESCAPE gomb megnyomasa */
   EV_KEY_SPACE,        /**< Szokoz megnyomasa */
   EV_KEY_UP,           /**< Fel gomb megnyomasa */
   EV_KEY_DOWN,         /**< Le gomb megnyomasa */
   EV_KEY_LEFT,         /**< Balra gomb megnyomasa */
   EV_KEY_RIGHT,        /**< Jobbra gomb megnyomasa */
   EV_KEY_Q,            /**< Q billentyu megnyomasa */
   EV_INVALID           /**< Ervenytelen esemeny */
} GameEvent;

/** \brief 2 dimenzios vektor struktura
 */
typedef struct vec_2d {
    double x;  /**< X koordinata */
    double y;  /**< Y koordinata */
} Vec2D;

/** \brief Betutipus struktura az SDL_TTF pluginhez
 */
typedef struct t_game_font {
    TTF_Font *font;           /**< A fontra mutato pointer */
    SDL_Renderer *renderer;   /**< A rendererre mutato pointer */
    SDL_Texture *texture;     /**< A font texturaja */
    Vec2D texture_size;       /**< A textura merete */
    SDL_Color color;          /**< A font szine */
} GameFont;

/** \brief A cella allapotai
 */
typedef enum t_cell_state {
    dead = 0,     /**< Halott cella */
    alive = 1     /**< Elo cella */
} CellState;

/** \brief A cella allapotat tarolo struktura
 */
typedef struct t_cell {
    CellState state;       /**< A cella aktualis allapota */
    CellState next_state;  /**< A cella kovetkezo allapota */
    CellState was_alive;   /**< A cella elt-e mar */
} Cell;

/** \brief A cella texturajat tarolo struktura
 */
typedef struct t_cell_texture {
    SDL_Texture* texture;  /**< A texturara mutato pointer */
    Vec2D texture_size;    /**< A textura merete */
} CellTexture;

/** \brief A gridet tarolo struktura
 */
typedef struct t_grid {
    int size_x;                     /**< A grid szelessege */
    int size_y;                     /**< A grid magassaga */
    int cap_x;                      /**< A grid maximalis szelessege */
    int cap_y;                      /**< A grid maximalis magassaga */
    Cell **cells;                   /**< A cellakat tarolo matrix */
    int cell_size;                  /**< A cellak merete pixelben */
    CellTexture cell_texture;       /**< Az elo cellak texturaja */
    CellTexture deadcell_texture;   /**< A halott cellak texturaja */
} Grid;

/** \brief A jatek fo valtozoi
 */
typedef struct t_game_vars {
   SDL_Window *window;        /**< Az ablakra mutato pointer */
   SDL_Surface *screen;       /**< Az ablak surface-re mutato poitner */
   SDL_Renderer *renderer;    /**< A rendererre mutato pointer */
   GameFont *game_font;       /**< A jatekban hasznalt betutipusra mutato pointer */
   Grid *grid;                /**< A gridre mutato pointer */
   GameState state;           /**< A jatek aktualis allapota */
} GameVars;

/** \brief Feldolgozza az SDL_Event-et es visszaadja az esemeny azonositojat
 *
 * \param ev SDL_Event Az esemeny valtozo
 * \return GameEvent Az esemenyazonosito
 *
 */
GameEvent Game_ParseEvent(SDL_Event ev);

/** \brief A jatekot vezerlo allapotgep
 *
 * \param game_vars GameVars* A fo jatekvaltozokra mutato pointer
 * \return GameState A jatek kovetkezo allapota
 *
 */
GameState Game_StateMachine(GameVars *game_vars);

/** \brief A fo valtozok inicializalasa
 *
 * \param game_vars GameVars* A fo valtozokra mutato pointer
 * \param title const char* Az ablak cime
 * \return int Hibakod
 *
 */
int Game_Init_All(GameVars *game_vars, const char *title);

/** \brief A fo valtozok felszabaditasa
 *
 * \param game_vars GameVars* A fo valtozokra mutato pointer
 * \return void
 *
 */
void Game_Destroy_All(GameVars *game_vars);

/** \brief Betolti a parameterkent megadott helyrol a PNG formatumu kepet egy texturaba
 *
 * \param path const char* A kep eleresi utvonala
 * \param renderer SDL_Renderer* A rendererre mutato pointer amin a textura megjelenik
 * \return SDL_Texture* A texturara mutato pointer
 *
 */
SDL_Texture* Game_Load_Texture(const char *path, SDL_Renderer *renderer);

/** \brief Betolti a parameterkent megadott helyrol a TTF formatumu fontot
 *
 * \param renderer SDL_Renderer* A rendererre mutato poitner amin a font megjelenik
 * \param path const char* A font eleresi utvonala
 * \param init_str const char* A font szovegenek kezdoerteke (UTF-8 kodolassal)
 * \param color const SDL_Color A font szine
 * \param text_size const int A font merete pontban
 * \return GameFont* A fontra mutato pointer
 *
 */
GameFont *Game_LoadFont(SDL_Renderer *renderer, const char *path, const char *init_str, const SDL_Color color, const int text_size);

/** \brief A fontot rendereli a megadott koordinatakon (UTF-8 kodolassal)
 *
 * \param game_font GameFont* A fontra mutato pointer
 * \param x int Az x koordinata
 * \param y int Az y koordinata
 * \return void
 *
 */
void Game_RenderFont(GameFont *game_font, int x, int y);

/** \brief Beallitja egy font szoveget
 *
 * \param gamefont GameFont* A fontra mutato pointer
 * \param str const char* A beallitando szoveg (UTF-8 kodolassal)
 * \return int
 *
 */
int Game_SetFontText(GameFont *gamefont, const char* str);

/** \brief Felszabaditja a fontot
 *
 * \param gamefont GameFont* A fontra mutato pointer
 * \return void
 *
 */
void Game_FreeFont(GameFont *gamefont);

#endif // GOL_MAIN_H_INCLUDED
