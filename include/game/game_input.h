#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include "game/game_data.h"

void input_fullscreen();
void input_menu_main(Menu *menu, GameState *game_state, bool *running, const Renderer *renderer);
void input_menu_pause(Menu *menu, GameState *game_state, bool *running, const Renderer *renderer);
void input_menu_end(Menu *menu, GameState *game_state, bool *running, const Renderer *renderer);
void input_level(Level *level, GameState *game_state, const Renderer *renderer);

#endif // GAME_INPUT_H