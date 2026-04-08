#ifndef LEVELS_H
#define LEVELS_H

#include <raylib.h>
#include <math.h>

#include "data/colors.h"

typedef struct {
    const char *title;
    const time_t time;

    const int hotbar_size;
    const Color *hotbar_color;

    const int grid_size;
    const Color *grid_color;
} LevelData;

const Color level0_hotbar[] = {
    C_BLACK,
    C_RED
};
const Color level0_grid[] = {
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, C_BLACK, C_BLACK, {0}, {0}, {0}, C_BLACK, C_BLACK, {0}, {0},
    {0}, C_BLACK, C_RED, C_RED, C_BLACK, {0}, C_BLACK, C_RED, C_RED, C_BLACK, {0},
    C_BLACK, C_RED, C_RED, C_RED, C_RED, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_BLACK,
    C_BLACK, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK,
    {0}, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK, {0},
    {0}, {0}, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK, {0}, {0},
    {0}, {0}, {0}, C_BLACK, C_RED, C_RED, C_RED, C_BLACK, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, C_BLACK, C_RED, C_BLACK, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, C_BLACK, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
};

const Color level1_hotbar[] = {
    C_BLACK,
    C_LIGHTGRAY
};
const Color level1_grid[] = {
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, C_BLACK, C_BLACK, {0}, {0}, {0}, {0}, {0}, {0}, {0}, C_BLACK, C_BLACK, {0},
    C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_BLACK, C_BLACK, C_BLACK,
    C_BLACK, C_BLACK, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_BLACK, C_BLACK,
    C_BLACK, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_BLACK,
    {0}, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, {0},
    {0}, C_LIGHTGRAY, C_BLACK, C_BLACK, C_LIGHTGRAY, C_BLACK, C_LIGHTGRAY, C_BLACK, C_LIGHTGRAY, C_BLACK, C_BLACK, C_LIGHTGRAY, {0},
    {0}, C_LIGHTGRAY, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_LIGHTGRAY, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_LIGHTGRAY, {0},
    {0}, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, {0},
    {0}, {0}, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_BLACK, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, {0}, {0},
    {0}, {0}, {0}, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, C_LIGHTGRAY, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}
};

const Color level2_hotbar[] = {
    C_BLACK,
    C_ORANGE
};
const Color level2_grid[] = {
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, {0}, {0},
    {0}, C_BLACK, {0}, {0}, {0}, {0}, {0}, C_BLACK, {0},
    {0}, C_BLACK, {0}, C_BLACK, {0}, C_BLACK, {0}, C_BLACK, {0},
    C_BLACK, C_BLACK, {0}, {0}, C_ORANGE, {0}, {0}, C_BLACK, C_BLACK,
    {0}, C_BLACK, {0}, {0}, {0}, {0}, {0}, C_BLACK, {0},
    {0}, C_BLACK, {0}, {0}, {0}, {0}, {0}, C_BLACK, {0},
    {0}, {0}, C_BLACK, C_ORANGE, C_BLACK, C_ORANGE, C_BLACK, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},

};

const Color level3_hotbar[] = {
    C_BLACK,
    C_RED
};
const Color level3_grid[] = {
    {0}, {0}, {0}, {0}, C_BLACK, C_BLACK, C_BLACK, C_BLACK, {0}, {0}, {0}, {0},
    {0}, {0}, C_BLACK, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_BLACK, C_BLACK, {0}, {0},
    {0}, C_BLACK, C_RED, C_RED, {0}, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK, {0},
    {0}, C_BLACK, C_RED, {0}, {0}, {0}, C_RED, C_RED, C_RED, C_RED, C_BLACK, {0},
    C_BLACK, C_RED, C_RED, C_RED, {0}, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK,
    C_BLACK, C_RED, C_RED, C_RED, C_RED, C_BLACK, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_BLACK,
    C_BLACK, C_BLACK, C_RED, C_RED, C_BLACK, {0}, {0}, C_BLACK, C_RED, C_RED, C_BLACK, C_BLACK,
    C_BLACK, {0}, C_BLACK, C_BLACK, C_BLACK, {0}, {0}, C_BLACK, C_BLACK, C_BLACK, {0}, C_BLACK,
    {0}, C_BLACK, {0}, {0}, {0}, C_BLACK, C_BLACK, {0}, {0}, {0}, C_BLACK, {0},
    {0}, C_BLACK, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, C_BLACK, {0},
    {0}, {0}, C_BLACK, C_BLACK, {0}, {0}, {0}, {0}, C_BLACK, C_BLACK, {0}, {0},
    {0}, {0}, {0}, {0}, C_BLACK, C_BLACK, C_BLACK, C_BLACK, {0}, {0}, {0}, {0}
};

const Color level4_hotbar[] = {
    C_BLACK,
    C_YELLOW,
    C_LIGHTBLUE
};
const Color level4_grid[] = {
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, C_BLACK, C_BLACK, {0}, C_BLACK, C_BLACK, {0}, {0}, {0},
    {0}, {0}, C_BLACK, C_LIGHTBLUE, C_LIGHTBLUE, C_BLACK, C_LIGHTBLUE, C_LIGHTBLUE, C_BLACK, {0}, {0},
    {0}, {0}, {0}, C_BLACK, C_LIGHTBLUE, C_LIGHTBLUE, C_BLACK, C_LIGHTBLUE, C_BLACK, {0}, {0},
    {0}, {0}, {0}, {0}, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, {0}, {0},
    {0}, {0}, {0}, C_BLACK, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_YELLOW, C_BLACK, {0},
    {0}, {0}, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_YELLOW, C_YELLOW, C_BLACK,
    C_BLACK, C_BLACK, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_BLACK,
    {0}, {0}, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_YELLOW, C_YELLOW, C_BLACK,
    {0}, {0}, {0}, C_BLACK, C_BLACK, C_YELLOW, C_BLACK, C_YELLOW, C_YELLOW, C_BLACK, {0},
    {0}, {0}, {0}, {0}, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, {0}, {0}
};

const Color level5_hotbar[] = {
    C_BLACK,
    C_RED,
    C_GREEN,
    C_LIGHTGREEN,
    C_LIGHTGRAY
};
const Color level5_grid[] = {
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, C_BLACK, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, C_BLACK, C_BLACK, C_GREEN, C_BLACK, C_BLACK, {0}, {0}, {0},
    {0}, {0}, C_BLACK, C_LIGHTGREEN, C_LIGHTGREEN, C_GREEN, C_LIGHTGREEN, C_LIGHTGREEN, C_BLACK, {0}, {0},
    {0}, C_BLACK, C_RED, C_RED, C_LIGHTGREEN, C_LIGHTGREEN, C_LIGHTGREEN, C_RED, C_RED, C_BLACK, {0},
    {0}, C_BLACK, C_RED, C_LIGHTGRAY, C_RED, C_LIGHTGREEN, C_RED, C_RED, C_RED, C_BLACK, {0},
    {0}, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK, {0},
    {0}, {0}, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK, {0}, {0},
    {0}, {0}, C_BLACK, C_RED, C_RED, C_RED, C_RED, C_RED, C_BLACK, {0}, {0},
    {0}, {0}, {0}, C_BLACK, C_RED, C_RED, C_RED, C_BLACK, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, C_BLACK, C_BLACK, C_BLACK, {0}, {0}, {0}, {0}
};

const Color level6_hotbar[] = {
    C_BLACK,
    C_RED
};
const Color level6_grid[] = {
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, {0}, {0},
    {0}, C_BLACK, {0}, {0}, {0}, {0}, {0}, C_BLACK, {0},
    C_BLACK, {0}, C_BLACK, {0}, {0}, {0}, C_BLACK, {0}, C_BLACK,
    C_BLACK, {0}, C_BLACK, {0}, C_BLACK, {0}, C_BLACK, {0}, C_BLACK,
    C_BLACK, C_RED, {0}, {0}, {0}, {0}, {0}, C_RED, C_BLACK,
    {0}, C_BLACK, {0}, C_BLACK, {0}, C_BLACK, {0}, C_BLACK, {0},
    {0}, {0}, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}
};

const LevelData levels[] = {
    {"Heart", 240, 2, level0_hotbar, 11, level0_grid},
    {"Panda", 300, 2, level1_hotbar, 13, level1_grid},
    {"Bird", 120, 2, level2_hotbar, 9, level2_grid},
    {"Pokeball", 300, 2, level3_hotbar, 12, level3_grid},
    {"Bee", 300, 3, level4_hotbar, 11, level4_grid},
    {"Strawberry", 240, 5, level5_hotbar, 11, level5_grid},
    {"Skull", 120, 2, level6_hotbar, 9, level6_grid}
};

constexpr int levels_count = sizeof(levels) / sizeof(LevelData);

#endif // LEVELS_H