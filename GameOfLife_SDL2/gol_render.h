/**********************************
 * Project:         Game of Life
 * Filename:        gol_render.h
 * Description:     A jatek megjelenitesevel kapcsolatos fuggvenyek
 *
 * Copyright Telek Istvan 2015
 *
 **********************************/
#ifndef __GOL_RENDER_H_INCLUDED__
#define __GOL_RENDER_H_INCLUDED__

/** \brief A renderhez tartozo valtozok inicializalasa
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_init(GameVars *game_vars);

/** \brief A renderhez tartozo valtozok felszabaditasa
 *
 * \return void
 *
 */
void render_destroy(void);

/** \brief Az eletter renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_grid(GameVars *game_vars);

/** \brief A fomenu renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_main(GameVars *game_vars);

/** \brief A betoltes menu renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_load(GameVars *game_vars);

/** \brief Az uj jatek menu renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_new(GameVars *game_vars);

/** \brief A szimulacio menu renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_sim_menu(GameVars *game_vars);

/** \brief A szimulacio beallitasai menu renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_settings(GameVars *game_vars);

/** \brief A mentes menu renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_save(GameVars *game_vars);

/** \brief A mentes megerositese menu renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_save_conf(GameVars *game_vars);

/** \brief A szuneteltetett szimualcio renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_sim_paused(GameVars *game_vars);

/** \brief A futo szimulacio renderelese
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_sim_running(GameVars *game_vars);

#endif // __GOL_RENDER_H_INCLUDED__
