/**
 * @file sprite.h
 * @author DargoDargonyx
 * @date 04/17/2026
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

Spritesheet* createSpritesheet(ErrorContainer* errContainer,
                               SDL_Renderer* renderer, const char* filepath,
                               Size sheetSize, int spriteCount);
Error destroySpritesheet(Spritesheet* self);
Error scaleSpritesheet(Spritesheet* spritesheet, Size scaledPixelSize);

#endif
