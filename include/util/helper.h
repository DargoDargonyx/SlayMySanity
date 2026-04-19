/**
 * @file helper.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Generic helper functions and structs for random
 * logic needed throughout the program.
 */

#ifndef HELPER_H
#define HELPER_H

#include <SDL2/SDL.h>

typedef struct {
    int x;
    int y;
} Pos;

typedef struct {
    float x;
    float y;
} PosFloat;

typedef struct {
    int w;
    int h;
} Size;

typedef struct {
    float w;
    float h;
} SizeFloat;

typedef enum {
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST
} Direction;

int pointInRect(Pos, SDL_Rect*);

#endif
