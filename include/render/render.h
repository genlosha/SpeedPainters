#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>

#include "game/game_data.h"

void render_menu_main(const Menu *menu, const Fonts *fonts);
void render_menu_pause(const Menu *menu, const Fonts *fonts);
void render_menu_end(const Menu *menu, float completion, const Fonts *fonts);
void render_load(const Font *font);
void render_start(const Level *level, const Fonts *fonts);
void render_level(const Level *level, const Fonts *fonts);

#endif // RENDER_H