#include <raylib.h>
#include <math.h>

#include "data/colors.h"
#include "game/game_data.h"

static void render_level_title(const char* title, const Font *font) {
    const Vector2 level_title_size = MeasureTextEx(*font, title, 128.0f, 0.0f);
    DrawTextEx(
        *font,
        title,
        (Vector2){(GAME_WIDTH - level_title_size.x) * 0.5f, 32.0f},
        128.0f,
        0.0f,
        C_DARKGRAY
    );
}

static void render_grid(const Grid *grid, const bool level_started) {
    // fill grid with whitegray background
    DrawRectangleRounded(
    (Rectangle){grid->rec.x, grid->rec.y, 1024 + 64, 1024 + 64},
    0.0f,
    32,
    C_WHITEGRAY
    );

    // fill grid
    for (int x = 0; x < grid->size; x++) {
        for (int y = 0; y < grid->size; y++) {
            const Rectangle rec = {
                grid->rec.x + grid->outline + (float)x * (grid->rec.width + grid->outline),
                grid->rec.y + grid->outline + (float)y * (grid->rec.height + grid->outline),
                grid->rec.width,
                grid->rec.height
            };
            DrawRectangleRec(rec, level_started ? grid->color[x][y] : grid->color_correct[x][y]);
            DrawRectangleRoundedLinesEx(rec, 0.0f, 32, grid->outline, C_GRAY);
        }
    }

    // selected tile
    if (level_started && grid->selected_x != -1 && grid->selected_y != -1) {
        DrawRectangleRoundedLinesEx(
            (Rectangle){
                grid->rec.x + grid->outline + (float)grid->selected_x * (grid->rec.width + grid->outline),
                grid->rec.y + grid->outline + (float)grid->selected_y * (grid->rec.height + grid->outline),
                grid->rec.width,
                grid->rec.height
            },
            0.0f,
            0,
            grid->outline,
            C_DARKGRAY
        );
    }
}

static void render_countdown(const int time_left, const Font *font) {
    const char *countdown_text = TextFormat("%d", time_left);
    const Vector2 countdown_size = MeasureTextEx(*font, countdown_text, 512.0f, 0.0f);
    DrawTextEx(
        *font,
        countdown_text,
        (Vector2){
            (GAME_WIDTH - countdown_size.x) * 0.5f,
            (GAME_HEIGHT - countdown_size.y) * 0.5f
        },
        512.0f,
        0.0f,
        C_TRANSPARENTGRAY
    );
}

static void render_hotbar(const Hotbar *hotbar, const Font *font) {
    for (int i = 0; i < hotbar->size; i++) {
        const Rectangle rec = {
            hotbar->rec.x + (float)i * (hotbar->rec.width + 2.0f * hotbar->outline + hotbar->spacing),
            hotbar->rec.y - ((hotbar->selected == i) ? hotbar->spacing * 2.0f : 0.0f),
            hotbar->rec.width,
            hotbar->rec.height
        };
        const Rectangle rec_in = {
            rec.x + hotbar->rec.width * 0.25f,
            rec.y + hotbar->rec.height * 0.25f,
            hotbar->rec.width * 0.5f,
            hotbar->rec.height * 0.5f
        };

        // hotbar slots
        DrawRectangleRounded(rec, 0.3f, 32, C_GRAY);
        DrawRectangleRoundedLinesEx(rec, 0.3f, 32, hotbar->outline, C_DARKGRAY);
        DrawRectangleRounded(rec_in, 0.3f, 32, hotbar->color[i]);
        DrawRectangleRoundedLinesEx(rec_in, 0.3f, 32, hotbar->outline * 0.5f, C_DARKGRAY);

        // hotbar numbers
        DrawTextEx(
            *font,
            TextFormat("%d", (i + 1) % 10),
            (Vector2){rec.x + 4.0f, rec.y + 4.0f},
            hotbar->rec.width * 0.25f,
            0.0f,
            C_DARKGRAY
        );
    }
}

static void render_controls(const Font *font) {
    // background rectangle for controls
    const Rectangle rec = {
        1874.0f,
        172.0f,
        640.0f,
        1096.0f
    };
    DrawRectangleRounded(
        rec,
        64.0f / fminf(rec.width, rec.height),
        32,
        C_GRAY
    );
    DrawRectangleRoundedLinesEx(
        rec,
        64.0f / fminf(rec.width, rec.height),
        32,
        8.0f,
        C_DARKGRAY
    );

    const Vector2 controls_title_size = MeasureTextEx(*font, "Controls", 64.0f, 0.0f);

    // controls title
    DrawTextEx(
        *font,
        "Controls",
        (Vector2){rec.x + (rec.width - controls_title_size.x) * 0.5f,rec.y + 32.0f},
        64.0f,
        0.0f,
        C_DARKGRAY
    );

    constexpr char controls[] =
        "Hotbar:\n"
        " [1-9, 0]          Select hotbar slot\n"
        " [Mouse Wheel]     Cycle hotbar slots\n"
        "\n"
        "Grid Movement:\n"
        " [W/A/S/D]         Select grid tile\n"
        " [Arrow Keys]      Select grid tile\n"
        "\n"
        "Painting (Mouse):\n"
        " [LMB]             Paint hovered tile\n"
        " [RMB]             Erase hovered tile\n"
        "\n"
        "Painting (Keyboard):\n"
        " [Space]           Paint selected tile\n"
        " [F / LShift]      Erase selected tile\n"
        "\n"
        "Clear:\n"
        " [R / Delete]      Clear grid (hold)\n"
        "\n"
        "Game:\n"
        " [Alt + Enter]     Toggle Fullscreen\n"
        " [Esc]             Pause Game";

    // controls text
    DrawTextEx(
        *font,
        controls,
        (Vector2){1906.0f, 300.0f},
        29.0f,
        0.0f,
        C_DARKGRAY
    );
}

static void render_info(const int time_left, const float completion, const Grid *grid, const Font *font) {
    // timer
    const Vector2 timer_title_size = MeasureTextEx(*font, "Time left", 64.0f, 0.0f);
    const int min_left = time_left / 60;
    const int sec_left = time_left % 60;
    const char *timer_text = TextFormat("%02d:%02d", min_left, sec_left);
    const Vector2 timer_time_size = MeasureTextEx(*font, timer_text, 64.0f, 0.0f);

    // background rectangle for timer
    const Rectangle rec_timer = {
        46.0f,
        172.0f,
        640.0f,
        80.0f + timer_title_size.y + timer_time_size.y
    };
    DrawRectangleRounded(
        rec_timer,
        64.0f / fminf(rec_timer.width, rec_timer.height),
        32,
        C_GRAY
    );
    DrawRectangleRoundedLinesEx(
        rec_timer,
        64.0f / fminf(rec_timer.width, rec_timer.height),
        32,
        8.0f,
        C_DARKGRAY
    );

    // timer title
    DrawTextEx(
        *font,
        "Time left",
        (Vector2){
            rec_timer.x + (rec_timer.width - timer_title_size.x) * 0.5f,
            rec_timer.y + 32.0f
        },
        64.0f,
        0.0f,
        C_DARKGRAY
    );

    // timer time
    DrawTextEx(
        *font,
        timer_text,
        (Vector2){
            rec_timer.x + (rec_timer.width - timer_time_size.x) * 0.5f,
            rec_timer.y + 32.0f + timer_title_size.y + 16.0f
        },
        64.0f,
        0.0f,
        C_DARKGRAY
    );

    // completion
    const Vector2 completion_title_size = MeasureTextEx(*font, "Completion", 64.0f, 0.0f);
    const char *completion_text = TextFormat("%.2f%%", completion * 100.0f);
    const Vector2 completion_text_size = MeasureTextEx(*font, completion_text, 64.0f, 0.0f);

    // background rectangle for completion
    const Rectangle rec_completion = {
        46.0f,
        rec_timer.y + rec_timer.height + 32.0f,
        640.0f,
        80.0f + completion_title_size.y + completion_text_size.y
    };
    DrawRectangleRounded(
        rec_completion,
        64.0f / fminf(rec_completion.width, rec_completion.height),
        32,
        C_GRAY
    );
    DrawRectangleRoundedLinesEx(
        rec_completion,
        64.0f / fminf(rec_completion.width, rec_completion.height),
        32,
        8.0f,
        C_DARKGRAY
    );

    // completion title
    DrawTextEx(
        *font,
        "Completion",
        (Vector2){
            rec_completion.x + (rec_completion.width - completion_title_size.x) * 0.5f,
            rec_completion.y + 32.0f
        },
        64.0f,
        0.0f,
        C_DARKGRAY
    );

    // completion text
    DrawTextEx(
        *font,
        completion_text,
        (Vector2){
            rec_completion.x + (rec_completion.width - completion_text_size.x) * 0.5f,
            rec_completion.y + 32.0f + completion_title_size.y + 16.0f
        },
        64.0f,
        0.0f,
        C_DARKGRAY
    );

    // solution
    const Vector2 solution_title_size = MeasureTextEx(*font, "Solution", 64.0f, 0.0f);

    // background rectangle for solution
    const Rectangle rec_solution = {
        46.0f,
        rec_completion.y + rec_completion.height + 32.0f,
        640.0f,
        1096.0f + 172.0f - (rec_completion.y + rec_completion.height + 32.0f)
    };
    DrawRectangleRounded(
        rec_solution,
        64.0f / fminf(rec_solution.width, rec_solution.height),
        32,
        C_GRAY
    );
    DrawRectangleRoundedLinesEx(
        rec_solution,
        64.0f / fminf(rec_solution.width, rec_solution.height),
        32,
        8.0f,
        C_DARKGRAY
    );

    // solution title
    DrawTextEx(
        *font,
        "Solution",
        (Vector2){
            rec_solution.x + (rec_solution.width - solution_title_size.x) * 0.5f,
            rec_solution.y + 32.0f
        },
        64.0f,
        0.0f,
        C_DARKGRAY
    );

    // whitegray background for solution grid
    const Rectangle rec_solution_grid = {
        rec_solution.x + (rec_solution.width - (1024.0f + 64.0f) * 0.375f) * 0.5f,
        rec_solution.y + solution_title_size.y + 64.0f,
        (1024.0f + 64.0f) * 0.375f,
        (1024.0f + 64.0f) * 0.375f
    };

    DrawRectangleRounded(
    rec_solution_grid,
    0.0f,
    32,
    C_WHITEGRAY
    );

    // solution grid
    for (int x = 0; x < grid->size; x++) {
        for (int y = 0; y < grid->size; y++) {
            const Rectangle rec = {
                rec_solution_grid.x + 0.375f * (grid->outline + (float)x * (grid->rec.width + grid->outline)),
                rec_solution_grid.y + 0.375f * (grid->outline + (float)y * (grid->rec.height + grid->outline)),
                grid->rec.width * 0.375f,
                grid->rec.height * 0.375f
            };
            DrawRectangleRec(rec, grid->color_solution[x][y]);
            DrawRectangleRoundedLinesEx(rec, 0.0f, 32, grid->outline * 0.375f, C_GRAY);
        }
    }
}

void render_start(const Level *level, const Fonts *fonts) {
    render_level_title(level->title, &fonts->main);
    render_grid(&level->grid, false);
    render_countdown(level->time_left, &fonts->main);
}

void render_level(const Level *level, const Fonts *fonts) {
    render_level_title(level->title, &fonts->main);
    render_grid(&level->grid, true);
    render_hotbar(&level->hotbar, &fonts->main);
    render_controls(&fonts->main);
    render_info(level->time_left, level->completion, &level->grid, &fonts->main);
}