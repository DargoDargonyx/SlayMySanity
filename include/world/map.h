/**
 * @file map.h
 * @author DargoDargonyx
 * @date 04/18/2026
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

Map* createTestMap(ErrorContainer* errCont, SDL_Renderer* renderer);
Error destroyMap(Map* self);

Error createMapTexture(Map* map, SDL_Renderer* renderer, const char* filepath);

#endif
