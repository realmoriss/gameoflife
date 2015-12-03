#ifndef __GOL_MAIN_H_INCLUDED__
#define __GOL_MAIN_H_INCLUDED__
#include <SDL.h>
#include <SDL_ttf.h>

#ifdef NDEBUG
#include <stdio.h>
#include "debugmalloc.h"
#endif // NDEBUG

#define SAVENAME_LENGTH 128

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
	STATE_SIM_SAVE_CONF,	/**< A grid mentese megerosites menu */
	STATE_INVALID        /**< A program veget jelzo allapot */
} GameState;

/** \brief Ketdimenzios vektor struktura
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

/** \brief A gridet tarolo struktura
 */
typedef struct t_grid {
	int size_x;                     /**< A grid szelessege */
	int size_y;                     /**< A grid magassaga */
	int cap_x;                      /**< A grid maximalis szelessege */
	int cap_y;                      /**< A grid maximalis magassaga */
	Cell **cells;                   /**< A cellakat tarolo matrix */
} Grid;

/** \brief
 */
typedef struct t_settings {
	int cell_size;                      /**<  */
	time_t save_modified;               /**<  */
	char save_name[SAVENAME_LENGTH];    /**<  */
} Settings;

typedef struct t_window_size {
	int w;
	int h;
} WindowSize;

/** \brief A jatek fo valtozoi
 */
typedef struct t_game_vars {
	SDL_Window *window;        /**< Az ablakra mutato pointer */
	SDL_Surface *screen;       /**< Az ablak surface-re mutato poitner */
	SDL_Renderer *renderer;    /**< A rendererre mutato pointer */
	GameFont *game_font;       /**< A jatekban hasznalt betutipusra mutato pointer */
	Grid *grid;                /**< A gridre mutato pointer */
	GameState state;           /**< A jatek aktualis allapota */
	Vec2D grid_size;           /**< A felhasznalo altal beallitott grid meret */
	Settings settings;         /**<  */
	WindowSize window_size;			/**<  */
} GameVars;

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
SDL_Texture *Game_Load_Texture(const char *path, SDL_Renderer *renderer);

#endif // __GOL_MAIN_H_INCLUDED__
