/**
 * @file sprite.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for sprites and spritesheets.
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

typedef struct {
    SDL_Texture* texture;
    const char* filepath;
    Size pixelSize;
    Size size;
    Size spriteSize;
    int spriteCount;
} Spritesheet;

Spritesheet* createSpritesheet(ErrorContainer*, SDL_Renderer*, const char*, Size, int);
Error* destroySpritesheet(Spritesheet*);
Error* scaleSpritesheet(Spritesheet*, Size);

#endif
