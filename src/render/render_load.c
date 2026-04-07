#include <raylib.h>

#include "data/colors.h"
#include "game/game_data.h"

void render_load(const Font *font) {
    const Vector2 loading_text_size = MeasureTextEx(*font,"Loading", 320.0f, 0.0f);
    const char *loading_text[] = {"Loading", "Loading.", "Loading..", "Loading..."};
    DrawTextEx(
        *font,
        loading_text[(int)(GetTime() * 3.0) % 4],
        (Vector2){(GAME_WIDTH - loading_text_size.x) * 0.5f, (GAME_HEIGHT - loading_text_size.y) * 0.5f},
        320.0f,
        0.0f,
        C_DARKGRAY
    );
}