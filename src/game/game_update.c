#include <raylib.h>
#include <string.h>
#include <time.h>

#include "game/game_data.h"

void update_start(Level *level, GameState *game_state) {
    // update timer
    level->time_left = (int)difftime(level->time_start, time(nullptr));
    if (level->time_left <= 0) {
        *game_state = GAME_RUN;
    }
}

void update_level(Level *level, GameState *game_state) {
    // update timer
    level->time_left = (int)difftime(level->time_end, time(nullptr));

    // update level completion
    float tile_count = 0.0f;
    float tile_correct_count = 0.0f;
    for (int x = 0; x < level->grid.size; x++) {
        for (int y = 0; y < level->grid.size; y++) {
            if (level->grid.color[x][y].a || level->grid.color_goal[x][y].a) {
                tile_count++;
                if (!memcmp(&level->grid.color[x][y], &level->grid.color_goal[x][y], sizeof(Color))) {
                    tile_correct_count++;
                }
            }
        }
    }
    level->completion = tile_correct_count / tile_count;

    // game over when timer or completion
    if (level->time_left <= 0 || level->completion >= 1.0f) {
        level->time_end = time(nullptr) + 2;
        *game_state = GAME_OVER;
    }
}

void update_over(GameState *game_state, const time_t time_end) {
    // show level for 2 more seconds before switching to end screen
    if (difftime(time_end, time(nullptr)) <= 0) {
        *game_state = GAME_END;
    }
}

