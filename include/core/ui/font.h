/**
 * @file font.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for fonts.
 */

#ifndef FONT_H
#define FONT_H

#include "util/error.h"

#include <SDL2/SDL_ttf.h>

#define F_JETBRAINS_MONO 1

typedef struct {
    TTF_Font* font;
    SDL_Color color;
    int size;
} Font;

Font createFont(int fontNum, int size, SDL_Color color);

#endif
