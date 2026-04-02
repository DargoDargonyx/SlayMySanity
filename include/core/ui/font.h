/**
 * @file font.h
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for fonts.
 */

#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

#define F_JETBRAINS_MONO 1

typedef struct {
    TTF_Font* font;
    int size;
} Font;


Font createFont(int fontNum, int size);
void destroyFont(Font* font);


#endif
