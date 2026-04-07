#include <raylib.h>

#include "data/colors.h"
#include "game/game_data.h"
#include "render/render_generic.h"

void render_menu_main(const Menu *menu, const Fonts *fonts) {
    // menu title
    const Vector2 menu_title_size = MeasureTextEx(fonts->main,"Speed Painters", 320.0f, 0.0f);
    DrawTextEx(
        fonts->main,
        "Speed Painters",
        (Vector2){(GAME_WIDTH - menu_title_size.x) * 0.5f, 64.0f},
        320.0f,
        0.0f,
        C_DARKGRAY
    );

    // buttons
    render_button(&menu->buttons[MENU_M_SP], &fonts->main);
    render_button(&menu->buttons[MENU_M_MP], &fonts->main);
    render_button(&menu->buttons[MENU_M_EXIT], &fonts->main);
}

void render_menu_pause(const Menu *menu, const Fonts *fonts) {
    // pause background rectangle
    const Rectangle rec = {
        (GAME_WIDTH - 960.0f) * 0.5f,
        (GAME_HEIGHT - 960.0f) * 0.5f,
        960,
        960
    };
    DrawRectangleRounded(
        rec,
        0.1f,
        32,
        C_GRAY
    );
    DrawRectangleRoundedLinesEx(
        rec,
        0.1f,
        32,
        24.0f,
        C_DARKGRAY
    );

    // pause title
    const Vector2 menu_title_size = MeasureTextEx(fonts->main,"Paused", 256.0f, 0.0f);
    DrawTextEx(
        fonts->main,
        "Paused",
        (Vector2){(GAME_WIDTH - menu_title_size.x) * 0.5f, 260.0f},
        256.0f,
        0.0f,
        C_DARKGRAY
    );

    // buttons
    render_button(&menu->buttons[MENU_P_RESUME], &fonts->main);
    render_button(&menu->buttons[MENU_P_MENU], &fonts->main);
    render_button(&menu->buttons[MENU_P_EXIT], &fonts->main);
}

void render_menu_end(const Menu *menu, const float completion, const Fonts *fonts) {
    // end title
    const char *end_title = (completion < 1.0f) ? "GAME OVER" : "YOU WIN";
    const Vector2 end_title_size = MeasureTextEx(fonts->main, end_title, 320.0f, 0.0f);
    DrawTextEx(
        fonts->main,
        end_title,
        (Vector2){(GAME_WIDTH - end_title_size.x) * 0.5f, 64.0f},
        320.0f,
        0.0f,
        C_DARKGRAY
    );

    // end subtitle
    const char *end_subtitle = TextFormat(
        "You managed to score %.02f%%!",
        completion * 100.0f
    );
    const Vector2 end_subtitle_size = MeasureTextEx(fonts->main, end_subtitle, 128.0f, 0.0f);
    DrawTextEx(
        fonts->main,
        end_subtitle,
        (Vector2){(GAME_WIDTH - end_subtitle_size.x) * 0.5f, 96.0f + end_title_size.y},
        128.0f,
        0.0f,
        C_DARKGRAY
    );

    // buttons
    render_button(&menu->buttons[MENU_E_NEW], &fonts->main);
    render_button(&menu->buttons[MENU_E_MENU], &fonts->main);
    render_button(&menu->buttons[MENU_E_EXIT], &fonts->main);
}