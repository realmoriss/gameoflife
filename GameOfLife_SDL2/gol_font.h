#ifndef __GOL_FONT_H_INCLUDED__
#define __GOL_FONT_H_INCLUDED__

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

#endif // __GOL_FONT_H_INCLUDED__
