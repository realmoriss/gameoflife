/**********************************
 * Project:         Game of Life
 * Filename:        gol_file.h
 * Description:     A fajlokkal kapcsolatos fuggvenyek
 *
 * Copyright Telek Istvan 2015
 *
 **********************************/
#ifndef __GOL_FILE_H_INCLUDED__
#define __GOL_FILE_H_INCLUDED__

/** \brief A beallitasok mentese fajlba
 *
 * \param filename const char* A beallitasokat tartalmazo fajl eleresi utvonala
 * \param game_vars GameVars* A jatek valtozoira mutato pointer
 * \return int
 *
 */
int file_load_settings(const char *filename, GameVars *game_vars);

/** \brief Az eletter mentese fajlba
 *
 * \param filename const char* Az eletteret tartalmazo fajl eleresi utvonala
 * \param game_vars GameVars* A jatek valtozoira mutato pointer
 * \return void
 *
 */
void file_load_grid(const char *filename, GameVars *game_vars);

/** \brief A beallitasok betoltese fajlbol
 *
 * \param filename const char* A beallitasokat tartalmazo fajl eleresi utvonala
 * \param game_vars GameVars* A jatek valtozoira mutato pointer
 * \return void
 *
 */
void file_save_settings(const char *filename, GameVars *game_vars);

/** \brief Az eletter betoltese fajlbol
 *
 * \param filename const char* Az eletteret tartalmazo fajl eleresi utvonala
 * \param game_vars GameVars* A jatek valtozoira mutato pointer
 * \return void
 *
 */
void file_save_grid(const char *filename, GameVars *game_vars);

#endif // __GOL_FILE_H_INCLUDED__
