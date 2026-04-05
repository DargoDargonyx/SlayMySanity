/**
 * @file map.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for maps and tiles.
 */

#ifndef MAP_H
#define MAP_H

#include "util/error.h"

#include <SDL2/SDL.h>

#define MAP_TYPE_TEST 1

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
    int tW;
    int tH;
    int rows;
    int cols;
    SDL_Texture* texture;
} Tileset;

typedef struct {
    int type;
    int w;
    int h;
    Tileset* tileset;
    int* tiles;
} Map;

Map* createTestMap(SDL_Renderer* renderer);
Error destroyMap(Map* self);

Tileset* createTileset(SDL_Renderer* renderer, const char* spritesheetPath,
                       int tW, int tH, int r, int c);
Error destroyTileset(Tileset* self);

#endif
