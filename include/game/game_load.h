#ifndef GAME_LOAD_H
#define GAME_LOAD_H

#include "game/game_data.h"

void load_fonts(Fonts *fonts);
void load_renderer(Renderer *renderer);
void load_menu_main(Menu *menu);
void load_menu_pause(Menu *menu);
void load_menu_end(Menu *menu);
void load_level(Level *level);

#endif // GAME_LOAD_H