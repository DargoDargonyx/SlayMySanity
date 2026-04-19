/**
 * @file map.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for maps and tiles.
 */

#ifndef MAP_H
#define MAP_H

#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

typedef struct {
    SDL_Texture* texture;
    SizeFloat worldSize;
    Size pixelSize;
} Map;

Map* createTestMap(ErrorContainer*, SDL_Renderer*);
Error* destroyMap(Map*);

Error* createMapTexture(Map*, SDL_Renderer*, const char*);

#endif
