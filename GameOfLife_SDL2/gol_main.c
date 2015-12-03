#include <SDL_image.h>
#include <time.h>
#include "gol_main.h"
#include "gol_grid.h"
#include "gol_file.h"
#include "gol_font.h"
#include "gol_events.h"
#include "gol_render.h"

static const char GAME_FONT_PATH[] = "assets/fonts/opensans.ttf";
static const int GAME_FONT_SIZE = 20;
static const int SCREEN_INIT_W = 800;
static const int SCREEN_INIT_H = 600;
static const int CELL_INIT_SIZE = 16;
static const char FILENAME_SETTINGS[] = "saves/settings.sav";

GameState Game_StateMachine(GameVars *game_vars) {
	switch (game_vars->state) {
	case STATE_INIT:
		if (!Game_Init_All(game_vars, "Game of Life")) {
#ifdef NDEBUG
			fprintf(stderr, "Init hiba, kilepes...\n");
#endif // NDEBUG
			return STATE_EXIT;
		}
		return STATE_MAIN_MENU;
	case STATE_EXIT:
		file_save_settings(FILENAME_SETTINGS, game_vars);
		Game_Destroy_All(game_vars);
		SDL_Quit();
		return STATE_INVALID;
	case STATE_MAIN_MENU:
		render_menu_main(game_vars);
		return events_menu_main(game_vars);
	case STATE_LOAD_MENU:
		render_menu_load(game_vars);
		return events_menu_load(game_vars);
	case STATE_NEW_MENU:
		render_menu_new(game_vars);
		return events_menu_new(game_vars);
	case STATE_SIM_MENU:
		render_menu_sim_menu(game_vars);
		return events_menu_sim_menu(game_vars);
	case STATE_SIM_SETTINGS:
		render_menu_settings(game_vars);
		return events_menu_settings(game_vars);
	case STATE_SIM_SAVE:
		render_menu_save(game_vars);
		return events_menu_save(game_vars);
	case STATE_SIM_SAVE_CONF:
		render_menu_save_conf(game_vars);
		return events_menu_save(game_vars);
	case STATE_SIM_PAUSED:
		render_sim_paused(game_vars);
		return events_sim_paused(game_vars);
	case STATE_SIM_RUNNING:
		grid_logic(game_vars->grid);
		render_sim_running(game_vars);
		return events_sim_running(game_vars);
	default:
		return STATE_EXIT;
	}
}

int Game_Init_All(GameVars *game_vars, const char *title) {
	game_vars->window = NULL;
	game_vars->screen = NULL;
	game_vars->renderer = NULL;
	game_vars->game_font = NULL;
	game_vars->grid = NULL;
	game_vars->state = STATE_INIT;
	if (file_load_settings(FILENAME_SETTINGS, game_vars) != 0) {
		game_vars->settings.cell_size = CELL_INIT_SIZE;
		game_vars->settings.save_modified = time(NULL);
		game_vars->settings.save_name[0] = '\0';
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
#ifdef NDEBUG
		fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
#endif // NDEBUG
		return 0;
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" )) {
#ifdef NDEBUG
		fprintf(stderr, "SDL figyelmeztetes: a linearis textura szures nem lett aktivalva\n");
#endif // NDEBUG
	}
#ifdef NDEBUG
	game_vars->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_INIT_W, SCREEN_INIT_H, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
#else
	game_vars->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_INIT_W, SCREEN_INIT_H, SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);
#endif // NDEBUG
	if (game_vars->window == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
#endif // NDEBUG
		return 0;
	}
	SDL_GetWindowSize(game_vars->window, &game_vars->window_size.w, &game_vars->window_size.h);
	game_vars->renderer = SDL_CreateRenderer(game_vars->window, -1, SDL_RENDERER_ACCELERATED);
	if (game_vars->renderer == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
#endif // NDEBUG
		return 0;
	}
	//Initialize renderer color
	SDL_SetRenderDrawColor(game_vars->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!( IMG_Init( imgFlags ) & imgFlags )) {
#ifdef NDEBUG
		fprintf(stderr, "SDL_image hiba: %s\n", IMG_GetError());
#endif // NDEBUG
		return 0;
	}
	if (TTF_Init() == -1) {
#ifdef NDEBUG
		fprintf(stderr, "SDL_ttf hiba: %s\n", TTF_GetError());
#endif // NDEBUG
		return 0;
	}
	game_vars->game_font = Game_LoadFont(game_vars->renderer, GAME_FONT_PATH, "FONT LOADED", (SDL_Color) {0xFF, 0xFF, 0xFF, 0xFF}, GAME_FONT_SIZE);
	if (game_vars->game_font == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "SDL_ttf hiba: %s\n", TTF_GetError());
#endif // NDEBUG
		return 0;

	}

	game_vars->screen = SDL_GetWindowSurface(game_vars->window);
	render_init(game_vars);
	return 1;
}

void Game_Destroy_All(GameVars *game_vars) {
	if (game_vars->renderer != NULL) {
		SDL_DestroyRenderer(game_vars->renderer);
		game_vars->renderer = NULL;
	}
	if (game_vars->window != NULL) {
		SDL_DestroyWindow(game_vars->window);
		game_vars->window = NULL;
	}
	if (game_vars->game_font != NULL) {
		Game_FreeFont(game_vars->game_font);
		game_vars->game_font = NULL;
	}
	if (game_vars->grid != NULL) {
		grid_free(game_vars->grid);
		game_vars->grid = NULL;
	}
	render_destroy();
}

SDL_Texture *Game_Load_Texture(const char *path, SDL_Renderer *renderer) {
	SDL_Texture *texture = NULL;
	SDL_Surface *imgSurface = IMG_Load(path);
	if (imgSurface == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "SDL_image Error: %s\n", IMG_GetError());
#endif // NDEBUG
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
		if (texture == NULL) {
#ifdef NDEBUG
			fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
#endif // NDEBUG
		}
		SDL_FreeSurface(imgSurface);
	}

	return texture;
}
