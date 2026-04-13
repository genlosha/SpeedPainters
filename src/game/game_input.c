#include <raylib.h>

#include "game/game_data.h"

// helper function to handle delay when selecting with KEYBOARD
static bool input_key_repeat(float *timer, const int key_one, const int key_two, const float delta_time) {
    if (IsKeyPressed(key_one) || IsKeyPressed(key_two)) {
        *timer = 0;
        return true;
    }
    if (IsKeyDown(key_one) || IsKeyDown(key_two)) {
        *timer += delta_time;
        if (*timer > 0.2f) {
            if (*timer > 0.3f) {
                *timer = 0.2f;
                return true;
            }
        }
    }
    return false;
}

void input_fullscreen() {
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
        ToggleBorderlessWindowed();
    }
}

// function for generic menus with buttons
static int input_menu(Menu *menu, const Renderer *renderer) {
    int selected_new = menu->selected;
    int pressed = -1;

    const float delta_time = GetFrameTime();

    // WASD and ARROW keys for menu select and hide cursor
    if (input_key_repeat(&menu->select_timer[0], KEY_S, KEY_DOWN, delta_time)) {
        if (selected_new == -1) {
            selected_new = 0;
        }
        else {
            selected_new++;
        }
        HideCursor();
    }
    if (input_key_repeat(&menu->select_timer[1], KEY_W, KEY_UP, delta_time)) {
        if (selected_new == -1) {
            selected_new = 0;
        }
        else {
            selected_new--;
        }
        HideCursor();
    }

    // only change when new selected slot within menu size
    if (selected_new >= 0 && selected_new < menu->size) {
        menu->buttons[menu->selected].selected = false;
        menu->buttons[menu->selected].pressed = false;
        menu->selected = selected_new;
        menu->buttons[selected_new].selected = true;
    }

    if (IsCursorHidden()) {
        if (IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_SPACE)) {
            menu->buttons[menu->selected].pressed = true;
        }

        if (IsKeyReleased(KEY_ENTER) || IsKeyReleased(KEY_SPACE)) {
            pressed = menu->selected;
        }

        // show cursor in selected button when mouse moved
        if (GetMouseDelta().x || GetMouseDelta().y) {
            const int mouse_pos_x = (int)(
                (menu->buttons[menu->selected].rec.x + menu->buttons[menu->selected].rec.width * 0.5f) *
                renderer->scale + renderer->offset.x
            );
            const int mouse_pos_y = (int)(
                (menu->buttons[menu->selected].rec.y + menu->buttons[menu->selected].rec.height * 0.5f) *
                renderer->scale + renderer->offset.y
            );
            SetMousePosition(mouse_pos_x, mouse_pos_y);
            ShowCursor();
        }
    }

    // menu input with MOUSE
    else {
        Vector2 mouse_pos = GetMousePosition();
        mouse_pos.x = mouse_pos.x / renderer->scale - renderer->offset.x;
        mouse_pos.y = mouse_pos.y / renderer->scale - renderer->offset.y;
        for (int i = 0; i < menu->size; i++) {
            menu->buttons[i].selected = CheckCollisionPointRec(mouse_pos, menu->buttons[i].rec);
            if (menu->buttons[i].selected) {
                menu->selected = i;
                menu->buttons[i].pressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    pressed = i;
                    break;
                }
            }
            else {
                menu->buttons[i].pressed = false;
            }
            pressed = -1;
        }
    }

    return pressed;
}

void input_menu_main(Menu *menu, GameState *game_state, bool *running, const Renderer *renderer) {
    // get pressed button and trigger action for it
    switch (input_menu(menu, renderer)) {
        case MENU_M_SP:
            *game_state = GAME_LOAD;
            break;
        case MENU_M_MP:
            menu->buttons[MENU_M_MP].text = "COMING SOON";
            break;
        case MENU_M_EXIT:
            *running = false;
        default:
            break;
    }
}

void input_menu_pause(Menu *menu, GameState *game_state, bool *running, const Renderer *renderer) {
    // unpause with ESCAPE
    if (IsKeyPressed(KEY_ESCAPE)) {
        *game_state = GAME_RUN;
        if (IsCursorHidden()) {
            ShowCursor();
        }
    }

    // get pressed button and trigger action for it
    switch (input_menu(menu, renderer)) {
        case MENU_P_RESUME:
            *game_state = GAME_RUN;
            break;
        case MENU_P_MENU:
            *game_state = GAME_MENU;
            break;
        case MENU_P_EXIT:
            *running = false;
        default:
            break;
    }
}

void input_menu_end(Menu *menu, GameState *game_state, bool *running, const Renderer *renderer) {
    // get pressed button and trigger action for it
    switch (input_menu(menu, renderer)) {
        case MENU_E_NEW:
            *game_state = GAME_LOAD;
            break;
        case MENU_E_MENU:
            *game_state = GAME_MENU;
            break;
        case MENU_E_EXIT:
            *running = false;
        default:
            break;
    }
}

static void input_hotbar(Hotbar *hotbar) {
    int selected_new = hotbar->selected;

    // NUMBER keys hotbar select
    const int pressed_key = GetKeyPressed();
    if (pressed_key == KEY_ZERO) {
        selected_new = 9;
    }
    else if (pressed_key >= KEY_ONE && pressed_key <= KEY_NINE) {
        selected_new = pressed_key - KEY_ONE;
    }

    // MOUSE WHEEL hotbar select
    selected_new -= (int)GetMouseWheelMove();

    // only change when new selected slot within hotbar size
    if (selected_new >= 0 && selected_new < hotbar->size) {
        hotbar->selected = selected_new;
    }
}

static void input_grid(Grid *grid, const Hotbar *hotbar, const Renderer *renderer) {
    int selected_new_x = grid->selected_x;
    int selected_new_y = grid->selected_y;

    const float delta_time = GetFrameTime();

    // WASD and ARROW keys for grid select and hide cursor
    if (input_key_repeat(&grid->select_timer[0], KEY_W, KEY_UP, delta_time)) {
        if (selected_new_x == -1) {
            selected_new_x = 0;
            selected_new_y = 0;
        }
        else {
            selected_new_y--;
        }
        HideCursor();
    }
    if (input_key_repeat(&grid->select_timer[1], KEY_S, KEY_DOWN, delta_time)) {
        if (selected_new_x == -1) {
            selected_new_x = 0;
            selected_new_y = 0;
        }
        else {
            selected_new_y++;
        }
        HideCursor();
    }
    if (input_key_repeat(&grid->select_timer[2], KEY_A, KEY_LEFT, delta_time)) {
        if (selected_new_x == -1) {
            selected_new_x = 0;
            selected_new_y = 0;
        }
        else {
            selected_new_x--;
        }
        HideCursor();
    }
    if (input_key_repeat(&grid->select_timer[3], KEY_D, KEY_RIGHT, delta_time)) {
        if (selected_new_x == -1) {
            selected_new_x = 0;
            selected_new_y = 0;
        }
        else {
            selected_new_x++;
        }
        HideCursor();
    }

    // only change when new selected slot within grid size
    if (selected_new_x >= 0 && selected_new_x < grid->size) {
        grid->selected_x = selected_new_x;
    }
    if (selected_new_y >= 0 && selected_new_y < grid->size) {
        grid->selected_y = selected_new_y;
    }

    // fully clear with holding R or DELETE
    if (IsKeyPressedRepeat(KEY_R) || IsKeyPressedRepeat(KEY_DELETE)) {
        for (int x = 0; x < grid->size; x++) {
            for (int y = 0; y < grid->size; y++) {
                grid->color[x][y].a = 0;
            }
        }
    }

    if (IsCursorHidden()) {
        // paint with SPACE (only when cursor hidden)
        if (IsKeyDown(KEY_SPACE)) {
            if (hotbar->color[hotbar->selected].a) {
                grid->color[grid->selected_x][grid->selected_y] = hotbar->color[hotbar->selected];
            }
        }

        // erase with F or LEFT SHIFT (only when cursor hidden)
        if (IsKeyDown(KEY_F) || IsKeyDown(KEY_LEFT_SHIFT)) {
            grid->color[grid->selected_x][grid->selected_y].a = 0;
        }

        // show cursor in selected tile when mouse moved
        if (GetMouseDelta().x || GetMouseDelta().y) {
            const int mouse_pos_x = (int)(
                (grid->rec.x + grid->outline * 0.5f +
                    ((float)grid->selected_x + 0.5f) * (grid->rec.width + grid->outline)) *
                renderer->scale + renderer->offset.x
            );
            const int mouse_pos_y = (int)(
                (grid->rec.y + grid->outline * 0.5f +
                    ((float)grid->selected_y + 0.5f) * (grid->rec.height + grid->outline)) *
                renderer->scale + renderer->offset.y
            );
            SetMousePosition(mouse_pos_x, mouse_pos_y);
            ShowCursor();
        }
    }

    // paint and erase with MOUSE
    else {
        const float grid_size = (float)grid->size;
        Vector2 mouse_pos = GetMousePosition();
        mouse_pos.x = (mouse_pos.x - renderer->offset.x) / renderer->scale ;
        mouse_pos.y = (mouse_pos.y - renderer->offset.y) / renderer->scale;
        const float tile_x = (mouse_pos.x - grid->rec.x - grid->outline * 0.5f) / (grid->rec.width + grid->outline);
        const float tile_y = (mouse_pos.y - grid->rec.y - grid->outline * 0.5f) / (grid->rec.height + grid->outline);
        if (tile_x >= 0.0f && tile_x < grid_size && tile_y >= 0.0f && tile_y < grid_size) {
            grid->selected_x = (int)tile_x;
            grid->selected_y = (int)tile_y;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                grid->color[(int)tile_x][(int)tile_y] = hotbar->color[hotbar->selected];
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                grid->color[(int)tile_x][(int)tile_y].a = 0;
            }
        }
        else {
            grid->selected_x = -1;
            grid->selected_x = -1;
        }
    }
}

void input_level(Level *level, GameState *game_state, const Renderer *renderer) {
    input_hotbar(&level->hotbar);
    input_grid(&level->grid, &level->hotbar, renderer);

    // pause with ESCAPE
    if (IsKeyPressed(KEY_ESCAPE)) {
        *game_state = GAME_PAUSE;
        if (IsCursorHidden()) {
            ShowCursor();
        }
    }
}