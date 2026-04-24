/**
 * @file font.h
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for fonts.
 */

#ifndef FONT_H
#define FONT_H

#include "util/error.h"

#include <SDL2/SDL_ttf.h>

#define FONT_CONTAINER_INIT_CAP 7

typedef enum { JETBRAINS_MONO } FontType;

typedef struct {
    FontType type;
    TTF_Font* font;
    SDL_Color color;
    int size;
} Font;

typedef struct {
    int count;
    int cap;
    Font** fonts;
} FontContainer;

FontContainer* createFontContainer();
Error* destroyFontContainer(FontContainer*);
Error* addFontToContainer(FontContainer*, Font*);

Error* createFont(FontContainer*, FontType, int, SDL_Color);
Error* destroyFont(Font*);

#endif
