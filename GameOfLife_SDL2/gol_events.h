#ifndef __GOL_EVENTS_H_INCLUDED__
#define __GOL_EVENTS_H_INCLUDED__

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
   EV_MWHEELUP,         /**< Egergorgo felfele gorgetese */
   EV_MWHEELDOWN,       /**< Egergorgo lefele gorgetese */
   EV_INVALID           /**< Ervenytelen esemeny */
} GameEvent;

/** \brief
 */
typedef enum t_mouse_state {
   MOUSESTATE_LEFT_DOWN,     /**<  */
   MOUSESTATE_RIGHT_DOWN,    /**<  */
   MOUSESTATE_BOTH_DOWN,     /**<  */
   MOUSESTATE_BOTH_UP        /**<  */
} MouseState;

/** \brief Feldolgozza az SDL_Event-et es visszaadja az esemeny azonositojat
 *
 * \param ev SDL_Event* Az esemeny valtozora mutato pointer
 * \return GameEvent Az esemenyazonosito
 *
 */
GameEvent events_parse(SDL_Event *ev);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_menu_main(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_menu_load(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_menu_new(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_menu_sim_menu(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_menu_settings(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_menu_save(GameVars *game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_sim_paused(GameVars* game_vars);

/** \brief
 *
 * \param game_vars GameVars*
 * \return void
 *
 */
GameState events_sim_running(GameVars* game_vars);

#endif // __GOL_EVENTS_H_INCLUDED__
