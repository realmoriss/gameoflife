#include "gol_main.h"
#include "gol_grid.h"

int main(int argc, char *argv[]) {
#ifdef NDEBUG
	debugmalloc_naplofajl("debug_gol.txt");
#endif // NDEBUG

	// A jatek fobb valtozoit tartalmazo struktura
	GameVars game_vars;
	game_vars.state = STATE_INIT;

	int quit = 0;
	while (!quit) {
		// Allapotgep vezerlese
		game_vars.state = Game_StateMachine(&game_vars);
		// Kilepes, ha elertuk a vegallapotot
		if (game_vars.state == STATE_INVALID) {
			quit = 1;
		}
	}
#ifdef NDEBUG
	debugmalloc_dump();
#endif // NDEBUG
	return 0;
}
