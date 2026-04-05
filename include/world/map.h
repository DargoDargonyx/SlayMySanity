/**
 * @file map.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for maps and tiles.
 */

#ifndef MAP_H
#define MAP_H

#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

#define TEST_TILE_W 32
#define TEST_TILE_H 32
#define TEST_TILESET_ROWS 1
#define TEST_TILESET_COLS 8

#define TILE_TYPE_GRASS 0
#define TILE_TYPE_STONE 1
#define TILE_TYPE_DARKSTONE 2
#define TILE_TYPE_SAND 3
#define TILE_TYPE_SANDSTONE 4
#define TILE_TYPE_WATER 5
#define TILE_TYPE_DARKWATER 6
#define TILE_TYPE_LAVA 7

typedef struct {
    Size tileSize;
    Size sheetSize;
    SDL_Texture* texture;
} Tileset;

typedef struct {
    Size size;
    Tileset* tileset;
    int* tiles;
} Map;

Map* createTestMap(SDL_Renderer* renderer);
Error destroyMap(Map* self);

Tileset* createTileset(SDL_Renderer* renderer, const char* spritesheetPath,
                       Size tileSize, Size sheetSize);
Error destroyTileset(Tileset* self);

#endif
