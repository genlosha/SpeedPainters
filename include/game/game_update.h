#ifndef GAME_UPDATE_H
#define GAME_UPDATE_H

#include "game/game_data.h"

void update_start(Level *level, GameState *game_state);
void update_level(Level *level, GameState *game_state);
void update_over(GameState *game_state, time_t time_end);

#endif // GAME_UPDATE_H
