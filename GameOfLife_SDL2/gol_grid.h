#ifndef __GOL_GRID_H_INCLUDED__
#define __GOL_GRID_H_INCLUDED__

const int GRID_SIZE_DEFAULT;  /**< A grid alapertelmezett merete */

/** \brief Letrehoz egy uj gridet es visszaadja a ra mutato pointert
 *
 * \param renderer SDL_Renderer*
 * \param size_startx const int a grid szelessege
 * \param size_starty const int a grid magassaga
 * \return Grid* a gridre mutato pointer (Hiba eseten NULL)
 *
 */
Grid *grid_new(const int size_startx, const int size_starty);

/** \brief Felszabaditja a gridet
 *
 * \param grid Grid* a gridre mutato pointer
 * \return void
 *
 */
void grid_free(Grid *grid);

/** \brief Feltolti a gridet ures cellakkal
 *
 * \param grid Grid* a gridre mutato pointer
 * \return void
 *
 */
void grid_init(Grid *grid);

/** \brief Leellenorzi, hogy a grid eleg szeles-e. Szukseg eseten noveli a szelesseget
 *
 * \param grid Grid* a gridre mutato pointer
 * \return void
 *
 */
void grid_set_sizex(Grid *grid);

/** \brief Leellenorzi, hogy a grid eleg magas-e. Szukseg eseten noveli a magassagot
 *
 * \param grid Grid*
 * \return void
 *
 */
void grid_set_sizey(Grid *grid);

/** \brief Beallitja a grid parameterkent megadott koordinatajan levo elemet a parameterben megadott ertekre
 *
 * \param grid Grid* a gridre mutato pointer
 * \param x const int az elem x koordinataja
 * \param y const int az elem y koordinataja
 * \param cell const Cell a tarolni kivant elem
 * \return void
 *
 */
void grid_set(Grid *grid, const int x, const int y, const Cell cell);

/** \brief Visszaadja a parameterkent megadott koordinatan levo elem erteket
 *
 * \param grid Grid* a gridre mutato pointer
 * \param x const int int az elem x koordinataja
 * \param y const int int az elem y koordinataja
 * \return Cell az adott koordinatan levo elem erteke
 *
 */
Cell grid_get(Grid *grid, const int x, const int y);

/** \brief Megallapitja a parameterkent megadott koordinatakon talalhato elem kovetkezo allapotat es tarolja is
 *
 * \param grid Grid* a gridre mutato pointer
 * \param x int az elem x koordinataja
 * \param y int az elem y koordinataja
 * \return void
 *
 */
void grid_cell_next_state(Grid *grid, int x, int y);

/** \brief Vegigmegy a grid elemein es elvegzi a kovetkezo allapotok kiszamolasat
 *
 * \param grid Grid* a gridre mutato pointer
 * \return void
 *
 */
void grid_logic(Grid *grid);

/** \brief Beallitja a parameterkent megadott koordinatakon talalhato elem erteket elore
 *
 * \param grid Grid* a gridre mutato pointer
 * \param x int az elem x koordinataja
 * \param y int az elem y koordinataja
 * \return void
 *
 */
void grid_set_alive(Grid *grid, int x, int y);

/** \brief Beallitja a parameterkent megadott koordinatakon talalhato elem erteket halottra
 *
 * \param grid Grid* a gridre mutato pointer
 * \param x int az elem x koordinataja
 * \param y int az elem y koordinataja
 * \return void
 *
 */
void grid_set_dead(Grid *grid, int x, int y);

#endif // __GOL_GRID_H_INCLUDED__
