#ifndef GOL_MENU_H_INCLUDED
#define GOL_MENU_H_INCLUDED

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void menu_init(GameVars *game_vars);

/** \brief
 *
 * \param void
 * \return void
 *
 */
void menu_destroy(void);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void menu_render_main(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void menu_render_load(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void menu_render_new(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void menu_render_sim_menu(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void menu_render_settings(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
void menu_render_save(GameVars *game_vars);

#endif // GOL_MENU_H_INCLUDED
