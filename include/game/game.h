#ifndef GAME_H
#define GAME_H

#include "game/game_data.h"

void init_game(GameData *game_data);
void update_game(GameData *game_data);
void close_game(GameData *game_data);
void render_game(GameData *game_data);

#endif // GAME_H