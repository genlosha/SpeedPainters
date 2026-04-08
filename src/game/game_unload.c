#include <stdlib.h>

#include "game/game_data.h"

void unload_level(const Level *level) {
    for (int i = 0; i < level->grid.size; i++) {
        free(level->grid.color[i]);
        free(level->grid.color_solution[i]);
        free(level->grid.color_correct[i]);
    }
    free(level->grid.color);
    free(level->grid.color_solution);
    free(level->grid.color_correct);
    free(level->hotbar.color);
    free(level->title);
}

void unload_menu(const Menu *menu) {
    free(menu->buttons);
}