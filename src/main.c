#include <raylib.h>

#include "game/game.h"
#include "game/game_data.h"

int main() {
    GameData game_data = {0};

    init_game(&game_data);

    while (!WindowShouldClose() && game_data.running) {
        update_game(&game_data);
        render_game(&game_data);
    }

    close_game(&game_data);

    return 0;
}
