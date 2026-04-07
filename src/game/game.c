#include <raylib.h>

#include "game/game_data.h"
#include "game/game_input.h"
#include "game/game_load.h"
#include "game/game_unload.h"
#include "game/game_update.h"

void init_game(GameData *game_data) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Speed Painters");
    SetWindowIcon(LoadImage("assets/icon.png"));
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    game_data->running = true;

    load_fonts(&game_data->fonts);
    load_renderer(&game_data->renderer);
    load_menu_main(&game_data->menu_main);
    load_menu_pause(&game_data->menu_pause);
    load_menu_end(&game_data->menu_end);
}

void close_game(const GameData *game_data) {
    unload_menu(&game_data->menu_main);
    unload_menu(&game_data->menu_pause);
    unload_menu(&game_data->menu_end);

    UnloadFont(game_data->fonts.main);

    UnloadRenderTexture(game_data->renderer.target);

    CloseWindow();
}

void update_game(GameData *game_data) {
    input_fullscreen();

    switch (game_data->state) {
        case GAME_MENU:
            input_menu_main(&game_data->menu_main, &game_data->state, &game_data->running, &game_data->renderer);
            break;
        case GAME_LOAD:
            load_level(&game_data->level);
            game_data->state = GAME_START;
            break;
        case GAME_START:
            update_start(&game_data->level, &game_data->state);
            break;
        case GAME_RUN:
            input_level(&game_data->level, &game_data->state, &game_data->renderer);
            update_level(&game_data->level, &game_data->state);
            break;
        case GAME_PAUSE:
            input_menu_pause(&game_data->menu_pause, &game_data->state, &game_data->running, &game_data->renderer);
            if (game_data->state == GAME_MENU) {
                unload_level(&game_data->level);
            }
            break;
        case GAME_OVER:
            update_over(&game_data->state, game_data->level.time_end);
            if (game_data->state == GAME_END) {
                unload_level(&game_data->level);
            }
            break;
        case GAME_END:
            input_menu_end(&game_data->menu_end, &game_data->state, &game_data->running, &game_data->renderer);
            break;
    }
}