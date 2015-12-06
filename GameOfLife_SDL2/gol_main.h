/**********************************
 * Project:         Game of Life
 * Filename:        gol_main.h
 * Description:     A jatek fobb tipusai es fontosabb fuggvenyei
 *
 * Copyright Telek Istvan 2015
 *
 **********************************/
#ifndef __GOL_MAIN_H_INCLUDED__
#define __GOL_MAIN_H_INCLUDED__
#include <SDL.h>
#include <SDL_ttf.h>

/*! \mainpage Game Of Life dokumentáció főoldal
*
* \section intro_sec Bemutatkozás
*
* Ez a dokumentum a Programozás alapjai 1 tantárgy nagy házi feladatnak a dokumentációja. \n
* A programot készítette: Telek István 2015
*
*
* \section documents_sec Segédletek
*
* A honlapokról letölthetőek a program fordításához szükséges könyvtárak és a futtatáshoz szükséges binárisok. \n
* A készítéshez használt könyvtárak es segédletek listája:
*
* \subsection debugmalloc debugmalloc
* Forrás: https://infoc.eet.bme.hu/debugmalloc/ \n
* Licensz: InfoC licensz (https://infoc.eet.bme.hu/elerhetoseg/)
*
* \subsection sdl2 SDL2
* Forrás: https://www.libsdl.org/download-2.0.php \n
* Licensz: zlib licensz (https://www.libsdl.org/license.php)
*
* \subsection sdl2_image SDL_image 2.0
* Forrás: https://www.libsdl.org/projects/SDL_image/ \n
* Licensz: zlib licensz (https://www.libsdl.org/license.php)
*
* \subsection sdl_ttf SDL_TTF 2.0
* Forrás: https://www.libsdl.org/projects/SDL_ttf/ \n
* Licensz: zlib licensz (https://www.libsdl.org/license.php)
*
* \subsection opensans_font OpenSans font
* Forrás: https://www.google.com/fonts/specimen/Open+Sans \n
* Licensz: Apache licensz (http://www.apache.org/licenses/LICENSE-2.0.html)
*
* \section jotudni_sec Jó tudni
*
* A program Microsoft Windows 10 x64 alatt MinGW fordítóval lett tesztelve, CodeBlocks fejlesztőkörnyezetben. \n
* A program forráskódja hivatalosan megtekinthető itt: https://github.com/moriss/gameoflife \n
*
* \section license Licensz
*
* A program forráskódja az MIT licensz használatával lett kiadva. \n
* \n
* The MIT License (MIT) \n
* Copyright (c) 2015 Istvan Telek \n
* \n
* Permission is hereby granted, free of charge, to any person obtaining a copy \n
* of this software and associated documentation files (the "Software"), to deal \n
* in the Software without restriction, including without limitation the rights \n
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell \n
* copies of the Software, and to permit persons to whom the Software is \n
* furnished to do so, subject to the following conditions: \n
* \n
* The above copyright notice and this permission notice shall be included in all \n
* copies or substantial portions of the Software. \n
* \n
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \n
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \n
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE \n
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \n
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, \n
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE \n
* SOFTWARE. \n
*/

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
    STATE_SIM_SAVE_CONF,    /**< A grid mentese megerosites menu */
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

/** \brief A beallitasokat tartalmazo struktura
 */
typedef struct t_settings {
    int cell_size;                      /**< A cella merete pixelekben */
    time_t save_modified;               /**< Az utolso mentes datuma */
    char save_name[SAVENAME_LENGTH];    /**< A mentes neve */
} Settings;

/** \brief Az ablak meretet tarolo struktura
 */
typedef struct t_window_size {
    int w;      /**< Az ablak szelessege */
    int h;      /**< Az ablak magassaga */
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
    Settings settings;         /**< A jatek beallitasai */
    WindowSize window_size;     /**< A jatek ablakanak merete */
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
