#include <raylib.h>
#include <math.h>

#include "data/colors.h"
#include "game/game_data.h"
#include "render/render.h"

static void render_scale(Renderer *renderer) {

    const float screen_w = (float)GetScreenWidth();
    const float screen_h = (float)GetScreenHeight();

    renderer->scale = fminf(
        screen_w / GAME_WIDTH,
        screen_h / GAME_HEIGHT
    );

    renderer->offset.x = (screen_w - GAME_WIDTH * renderer->scale) * 0.5f;
    renderer->offset.y = (screen_h - GAME_HEIGHT * renderer->scale) * 0.5f;
}

static void render_texture(const Renderer *renderer) {
    BeginDrawing();
    ClearBackground(C_LIGHTGRAY);

    DrawTexturePro(
        renderer->target.texture,
        (Rectangle){0.0f, 0.0f, GAME_WIDTH, -GAME_HEIGHT},
        (Rectangle){
            renderer->offset.x,
            renderer->offset.y,
            GAME_WIDTH * renderer->scale,
            GAME_HEIGHT * renderer->scale
        },
        (Vector2){0.0f, 0.0f},
        0.0f,
        WHITE
    );

    EndDrawing();
}

static void render_fps() {
    DrawFPS(12, 12);
}

void render_game(GameData *game_data) {
    // change scale when window resized
    if (IsWindowResized()) {
        render_scale(&game_data->renderer);
    }

    // draw everything into one texture
    BeginTextureMode(game_data->renderer.target);
    ClearBackground(C_LIGHTGRAY);

    switch (game_data->state) {
        case GAME_MENU:
            render_menu_main(&game_data->menu_main, &game_data->fonts);
            break;
        case GAME_LOAD:
            render_load(&game_data->fonts.main);
            break;
        case GAME_START:
            render_start(&game_data->level, &game_data->fonts);
            break;
        case GAME_RUN:
            render_level(&game_data->level, &game_data->fonts);
            break;
        case GAME_PAUSE:
            render_level(&game_data->level, &game_data->fonts);
            render_menu_pause(&game_data->menu_pause, &game_data->fonts);
            break;
        case GAME_OVER:
            render_level(&game_data->level, &game_data->fonts);
            break;
        case GAME_END:
            render_menu_end(&game_data->menu_end, game_data->level.completion, &game_data->fonts);
            break;
    }

    render_fps();

    EndTextureMode();

    // draw the texture scaled to the screen
    render_texture(&game_data->renderer);

}