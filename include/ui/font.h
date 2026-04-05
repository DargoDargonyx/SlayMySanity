/**
 * @file font.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for fonts.
 */

#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

typedef enum { JETBRAINS_MONO } FontType;

typedef struct {
    TTF_Font* font;
    SDL_Color color;
    int size;
} Font;

Font createFont(FontType type, int size, SDL_Color color);

#endif
