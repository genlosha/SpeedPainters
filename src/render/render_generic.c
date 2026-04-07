#include <raylib.h>

#include "data/colors.h"
#include "game/game_data.h"

void render_button(const Button *button, const Font *font) {
    Rectangle rec = button->rec;

    // bigger button when selected
    if (button->selected) {
        rec.x -= rec.width * 0.025f;
        rec.y -= rec.height * 0.025f;
        rec.width += rec.width * 0.05f;
        rec.height += rec.height * 0.05f;
    }

    // darker color when pressed
    const Color button_color = button->pressed ? C_DIMGRAY : C_GRAY;

    // render button
    DrawRectangleRounded(rec, 0.3f, 32, button_color);
    DrawRectangleRoundedLinesEx(rec, 0.3f, 32, rec.width / 64.0f, C_DARKGRAY);

    // render button text
    const float font_size = rec.width * 0.125f;
    const Vector2 text_size = MeasureTextEx(*font, button->text, font_size, 0.0f);
    DrawTextEx(
        *font,
        button->text,
        (Vector2){
            button->rec.x + (button->rec.width - text_size.x) * 0.5f,
            button->rec.y + (button->rec.height - text_size.y) * 0.5f
        },
        font_size,
        0.0f,
        C_DARKGRAY
    );
}