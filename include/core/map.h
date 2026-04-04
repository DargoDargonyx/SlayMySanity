/**
 * @file map.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for maps and tiles.
 */

#ifndef MAP_H
#define MAP_H

#define MAP_TYPE_TEST 1

#define TILE_TYPE_GRASS 0
#define TILE_TYPE_STONE 1
#define TILE_TYPE_DARKSTONE 2
#define TILE_TYPE_SAND 3
#define TILE_TYPE_SANDSTONE 4
#define TILE_TYPE_WATER 5
#define TILE_TYPE_DARKWATER 6
#define TILE_TYPE_LAVA 7

typedef struct {
    int w;
    int h;
    int rows;
    int cols;
    int* tileArr;
} Tileset;

typedef struct Map Map;
struct Map {
    int type;
    int x;
    int y;
    Tileset* tiles;
};

typedef struct {
    Map base;
} TestMap;

#endif
