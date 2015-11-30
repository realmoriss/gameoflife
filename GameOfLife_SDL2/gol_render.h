#ifndef __GOL_RENDER_H_INCLUDED__
#define __GOL_RENDER_H_INCLUDED__

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_init(GameVars *game_vars);

/** \brief
 *
 * \param void
 * \return void
 *
 */
void render_destroy(void);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_grid(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_main(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_load(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_new(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_sim_menu(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_settings(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_menu_save(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_sim_paused(GameVars* game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void render_sim_running(GameVars* game_vars);

#endif // __GOL_RENDER_H_INCLUDED__
