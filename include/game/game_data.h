#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <raylib.h>
#include <time.h>

constexpr int GAME_WIDTH = 2560;
constexpr int GAME_HEIGHT = 1440;

typedef enum {
    GAME_MENU,
    GAME_LOAD,
    GAME_START,
    GAME_RUN,
    GAME_PAUSE,
    GAME_OVER,
    GAME_END,
} GameState;

typedef enum {
    MENU_M_SP,
    MENU_M_MP,
    MENU_M_EXIT
} MenuMainButton;

typedef enum {
    MENU_P_RESUME,
    MENU_P_MENU,
    MENU_P_EXIT
} MenuPauseButton;

typedef enum {
    MENU_E_NEW,
    MENU_E_MENU,
    MENU_E_EXIT
} MenuEndButton;

typedef struct {
    Font main;
} Fonts;

typedef struct {
    RenderTexture2D target;
    float scale;
    Vector2 offset;
} Renderer;

typedef struct {
    Rectangle rec;
    char *text;
    bool selected;
    bool pressed;
} Button;

typedef struct {
    Button *buttons;
    int size;
    int selected;
    float select_timer[2];
} Menu;

typedef struct {
    int size;
    int selected;
    Rectangle rec;
    float outline;
    float spacing;
    Color *color;
} Hotbar;

typedef struct {
    int size;
    int selected_x;
    int selected_y;
    float select_timer[4];
    Rectangle rec;
    float outline;
    Color **color;
    Color **color_solution;
    Color **color_correct;
} Grid;

typedef struct {
    Hotbar hotbar;
    Grid grid;
    char *title;
    float completion;
    int time_left;
    time_t time_start;
    time_t time_end;
    time_t time_solution;
} Level;

typedef struct {
    bool running;
    GameState state;
    Fonts fonts;
    Renderer renderer;
    Menu menu_main;
    Menu menu_pause;
    Menu menu_end;
    Level level;
} GameData;

#endif // GAME_DATA_H