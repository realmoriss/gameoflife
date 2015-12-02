#include <stdio.h>
#include <time.h>
#include "gol_main.h"
#include "gol_grid.h"

int file_load_settings(const char *filename, GameVars *game_vars) {
	FILE *fp;
	fp = fopen(filename, "rb");
	int hiba = 0;
	if (fp == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "Hiba a beallitas fajl megnyitasa kozben: %s", filename);
#endif // NDEBUG
		return 1;
	}
	if (fread(&(game_vars->settings), sizeof(Settings), 1, fp) != 1) {
#ifdef NDEBUG
		fprintf(stderr, "Hiba a beallitas fajl olvasasa kozben: %s", filename);
#endif // NDEBUG
		hiba = 1;
	}
	fclose(fp);
	return hiba;
}

void file_load_grid(const char *filename, GameVars *game_vars) {
	FILE *fp;
	fp = fopen(filename, "rt");
	if (fp == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "Hiba a grid fajl megnyitasa kozben: %s", filename);
#endif // NDEBUG
		return;
	}
	int i,j,state;
	while (fscanf(fp, "%d;%d;%d", &i, &j, &state) != EOF) {
		grid_set(game_vars->grid, i, j, (Cell) {state?alive:dead, dead, alive});
	}
	fclose(fp);
}

void file_save_settings(const char *filename, GameVars *game_vars) {
	FILE *fp;
	fp = fopen(filename, "wb");
	if (fp == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "Hiba a beallitas fajl mentese kozben: %s", filename);
#endif // NDEBUG
		return;
	}
	fwrite(&(game_vars->settings), sizeof(Settings), 1, fp);
	fclose(fp);
}

void file_save_grid(const char *filename, GameVars *game_vars) {
	FILE *fp;
	fp = fopen(filename, "wt");
	if (fp == NULL) {
#ifdef NDEBUG
		fprintf(stderr, "Hiba a grid fajl mentese kozben: %s", filename);
#endif // NDEBUG
		return;
	}
	int i,j;
	Cell tmpcell;
	for (i=game_vars->grid->size_x-1; i>=0; i--) {
		for (j=game_vars->grid->size_y-1; j>=0; j--) {
			tmpcell = grid_get(game_vars->grid, i, j);
			if (tmpcell.state == alive || tmpcell.was_alive == alive) {
				fprintf(fp, "%d;%d;%d\n", i, j, tmpcell.state);
			}
		}
	}
	fclose(fp);
}
