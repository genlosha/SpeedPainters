#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game/game_data.h"
#include "data/levels.h"

void load_fonts(Fonts *fonts) {
    fonts->main = LoadFontEx("assets/Go_Mono_Bold.ttf", 512, nullptr, 0);
}

void load_renderer(Renderer *renderer) {
    renderer->target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    renderer->scale = fminf(
        (float)GetScreenWidth() / GAME_WIDTH,
        (float)GetScreenHeight() / GAME_HEIGHT
    );
}

void load_menu_main(Menu *menu) {
    menu->size = 3;
    menu->selected = -1;

    menu->buttons = calloc(menu->size, sizeof(Button));

    menu->buttons[MENU_M_SP].rec.x = GAME_WIDTH * 0.5f - 512.0f;
    menu->buttons[MENU_M_SP].rec.y = 512.0f;
    menu->buttons[MENU_M_SP].rec.width = 1024.0f;
    menu->buttons[MENU_M_SP].rec.height = 192.0f;
    menu->buttons[MENU_M_SP].text = "Singleplayer";

    menu->buttons[MENU_M_MP].rec.x = GAME_WIDTH * 0.5f - 512.0f;
    menu->buttons[MENU_M_MP].rec.y = menu->buttons[MENU_M_SP].rec.y + menu->buttons[MENU_M_SP].rec.height + 64.0f;
    menu->buttons[MENU_M_MP].rec.width = 1024.0f;
    menu->buttons[MENU_M_MP].rec.height = 192.0f;
    menu->buttons[MENU_M_MP].text = "Multiplayer";

    menu->buttons[MENU_M_EXIT].rec.x = GAME_WIDTH * 0.5f - 512.0f;
    menu->buttons[MENU_M_EXIT].rec.y = menu->buttons[MENU_M_MP].rec.y + menu->buttons[MENU_M_MP].rec.height + 64.0f;
    menu->buttons[MENU_M_EXIT].rec.width = 1024.0f;
    menu->buttons[MENU_M_EXIT].rec.height = 192.0f;
    menu->buttons[MENU_M_EXIT].text = "Exit";
}

void load_menu_pause(Menu *menu) {
    menu->size = 3;
    menu->selected = -1;

    menu->buttons = calloc(menu->size, sizeof(Button));

    menu->buttons[MENU_P_RESUME].rec.x = GAME_WIDTH * 0.5f - 384.0f;
    menu->buttons[MENU_P_RESUME].rec.y = 576.0f;
    menu->buttons[MENU_P_RESUME].rec.width = 768.0f;
    menu->buttons[MENU_P_RESUME].rec.height = 128.0f;
    menu->buttons[MENU_P_RESUME].text = "Resume";

    menu->buttons[MENU_P_MENU].rec.x = GAME_WIDTH * 0.5f - 384.0f;
    menu->buttons[MENU_P_MENU].rec.y = menu->buttons[MENU_P_RESUME].rec.y + menu->buttons[MENU_P_RESUME].rec.height + 64.0f;
    menu->buttons[MENU_P_MENU].rec.width = 768.0f;
    menu->buttons[MENU_P_MENU].rec.height = 128.0f;
    menu->buttons[MENU_P_MENU].text = "Main Menu";

    menu->buttons[MENU_P_EXIT].rec.x = GAME_WIDTH * 0.5f - 384.0f;
    menu->buttons[MENU_P_EXIT].rec.y = menu->buttons[MENU_P_MENU].rec.y + menu->buttons[MENU_P_MENU].rec.height + 64.0f;
    menu->buttons[MENU_P_EXIT].rec.width = 768.0f;
    menu->buttons[MENU_P_EXIT].rec.height = 128.0f;
    menu->buttons[MENU_P_EXIT].text = "Exit";
}

void load_menu_end(Menu *menu) {
    menu->size = 3;
    menu->selected = -1;

    menu->buttons = calloc(menu->size, sizeof(Button));

    menu->buttons[MENU_E_NEW].rec.x = GAME_WIDTH * 0.5f - 512.0f;
    menu->buttons[MENU_E_NEW].rec.y = 640.0f;
    menu->buttons[MENU_E_NEW].rec.width = 1024.0f;
    menu->buttons[MENU_E_NEW].rec.height = 192.0f;
    menu->buttons[MENU_E_NEW].text = "New Game";

    menu->buttons[MENU_E_MENU].rec.x = GAME_WIDTH * 0.5f - 512.0f;
    menu->buttons[MENU_E_MENU].rec.y = menu->buttons[MENU_E_NEW].rec.y + menu->buttons[MENU_E_NEW].rec.height + 64.0f;
    menu->buttons[MENU_E_MENU].rec.width = 1024.0f;
    menu->buttons[MENU_E_MENU].rec.height = 192.0f;
    menu->buttons[MENU_E_MENU].text = "Main Menu";

    menu->buttons[MENU_E_EXIT].rec.x = GAME_WIDTH * 0.5f - 512.0f;
    menu->buttons[MENU_E_EXIT].rec.y = menu->buttons[MENU_E_MENU].rec.y + menu->buttons[MENU_E_MENU].rec.height + 64.0f;
    menu->buttons[MENU_E_EXIT].rec.width = 1024.0f;
    menu->buttons[MENU_E_EXIT].rec.height = 192.0f;
    menu->buttons[MENU_E_EXIT].text = "Exit";
}

static void load_hotbar(Hotbar *hotbar, const LevelData *level_data) {
    hotbar->size = level_data->hotbar_size;

    hotbar->color = calloc(hotbar->size, sizeof(Color));
    for (int i = 0; i < hotbar->size; i++) {
        hotbar->color[i] = level_data->hotbar_color[i];
    }

    hotbar->rec.width = 96.0f;
    hotbar->rec.height = 96.0f;
    hotbar->outline = 8.0f;
    hotbar->spacing = 12.0f;

    const float slot_total_width = hotbar->rec.width + hotbar->outline * 2.0f + hotbar->spacing;
    const float hotbar_total_width = (float)hotbar->size * slot_total_width - hotbar->spacing - 2.0f * hotbar->outline;

    hotbar->rec.x = (GAME_WIDTH - hotbar_total_width) * 0.5f;
    hotbar->rec.y = GAME_HEIGHT - hotbar->rec.height - hotbar->outline - hotbar->spacing;
}

static void load_grid(Grid *grid, const LevelData *level_data) {
    grid->size = level_data->grid_size;

    grid->color = calloc(grid->size, sizeof(Color *));
    for (int i = 0; i < grid->size; i++) {
        grid->color[i] = calloc(grid->size, sizeof(Color));
    }

    grid->color_solution = calloc(grid->size, sizeof(Color *));
    for (int i = 0; i < grid->size; i++) {
        grid->color_solution[i] = calloc(grid->size, sizeof(Color));
    }

    grid->color_correct = calloc(grid->size, sizeof(Color *));
    for (int i = 0; i < grid->size; i++) {
        grid->color_correct[i] = calloc(grid->size, sizeof(Color));
    }
    for (int x = 0; x < grid->size; x++) {
        for (int y = 0; y < grid->size; y++) {
            grid->color_correct[x][y] = level_data->grid_color[y * grid->size + x];
        }
    }

    const float grid_size = (float)grid->size;

    grid->rec.width = 1024.0f / grid_size;
    grid->rec.height = 1024.0f / grid_size;
    grid->outline = 64.0f / (grid_size + 1);

    const float grid_total_width = grid_size * (grid->rec.width + grid->outline) + grid->outline;
    const float grid_total_height = grid_size * (grid->rec.height + grid->outline) + grid->outline;

    grid->rec.x = (GAME_WIDTH - grid_total_width) * 0.5f;
    grid->rec.y = (GAME_HEIGHT - grid_total_height) * 0.5f;
}

void load_level(Level *level) {
    // select random level
    const LevelData *level_data = &levels[GetRandomValue(0, levels_count - 1)];

    // select fixed random (for testing)
    //const LevelData *level_data = &levels[3];

    load_hotbar(&level->hotbar, level_data);
    load_grid(&level->grid, level_data);

    level->title = malloc(strlen(level_data->title) * sizeof(char));
    strcpy(level->title, level_data->title);

    level->time_start = time(nullptr) + 5;
    level->time_end = level->time_start + level_data->time;
    level->time_solution = level->time_start;
}
