/**
 * @file map.c
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for maps and tiles.
 */

#include "world/map.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for creating a Map struct.
 *
 * @param renderer : SDL_Renderer pointer
 * @return A pointer to the Map struct in question
 */
Map* createTestMap(SDL_Renderer* renderer) {
    Map* map = (Map*) malloc(sizeof(Map));
    map->size.w = 100;
    map->size.h = 100;
    map->tiles = (int*) calloc(map->size.w * map->size.h, sizeof(int));

    for (int y = 0; y < map->size.h; y++) {
        for (int x = 0; x < map->size.w; x++) {
            int index = (y * map->size.w) + x;
            map->tiles[index] = TILE_TYPE_GRASS;
        }
    }

    const char* spritesheetPath = "../assets/sprites/tiles/test_tiles.png";
    Size tileSize = {TEST_TILE_W, TEST_TILE_H};
    Size sheetSize = {TEST_TILESET_ROWS, TEST_TILESET_COLS};
    map->tileset =
        createTileset(renderer, spritesheetPath, tileSize, sheetSize);

    return map;
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for destroying a Map struct.
 *
 * @param self : Map struct pointer
 * @return An Error struct that describes whether or not the
 * Map struct was successfully destroyed
 */
Error destroyMap(Map* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    err = destroyTileset(self->tileset);
    if (err.statusNum != ESTAT_MAIN_NONE)
        return err;

    free(self->tiles);
    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for creating a Tileset struct.
 *
 * @param renderer : SDL_Renderer pointer
 * @param spritesheetPath : c-style string literal
 * @param tileSize : Size struct
 * @param sheetSize : Size struct
 * @return A pointer to the newly created Tileset struct
 */
Tileset* createTileset(SDL_Renderer* renderer, const char* spritesheetPath,
                       Size tileSize, Size sheetSize) {

    Tileset* tileset = (Tileset*) malloc(sizeof(Tileset));
    SDL_Surface* surface = IMG_Load(spritesheetPath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    tileset->texture = texture;
    tileset->tileSize = tileSize;
    tileset->sheetSize = sheetSize;

    return tileset;
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for destroying a Tileset struct.
 *
 * @param self : Tileset struct pointer
 * @return An Error struct that describes whether or not the
 * Tileset struct was successfully destroyed
 */
Error destroyTileset(Tileset* self) {
    SDL_DestroyTexture(self->texture);
    free(self);
    return createError(ESTAT_MAIN_NONE, NULL);
}
