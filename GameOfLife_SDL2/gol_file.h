#ifndef __GOL_FILE_H_INCLUDED__
#define __GOL_FILE_H_INCLUDED__

int file_load_settings(const char *filename, GameVars *game_vars);
void file_load_grid(const char *filename, GameVars *game_vars);

void file_save_settings(const char *filename, GameVars *game_vars);
void file_save_grid(const char *filename, GameVars *game_vars);

#endif // __GOL_FILE_H_INCLUDED__
