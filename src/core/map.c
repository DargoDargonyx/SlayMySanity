/**
 * @file map.c
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for maps and tiles.
 */

#include "core/map.h"
#include "util/error.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for creating a Map struct.
 *
 * @param renderer : SDL_Renderer pointer
 * @return A pointer to the Map struct in question
 */
Map* createTestMap(SDL_Renderer* renderer) {
    Map* map = (Map*) malloc(sizeof(Map));
    map->type = MAP_TYPE_TEST;
    map->w = 10;
    map->h = 10;
    map->tiles = (int*) calloc(map->w * map->h, sizeof(int));

    for (int y = 0; y < map->h; y++) {
        for (int x = 0; x < map->w; x++) {
            int index = (y * map->w) + x;
            map->tiles[index] = TILE_TYPE_GRASS;
        }
    }

    const char* spritesheetPath = "../assets/sprites/tiles/test_tiles.png";
    map->tileset =
        createTileset(renderer, spritesheetPath, TEST_TILE_W, TEST_TILE_H,
                      TEST_TILESET_ROWS, TEST_TILESET_COLS);

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
 * @date 04/04/2026
 * @brief Handles the logic for creating a Tileset struct.
 *
 * @param renderer : SDL_Renderer pointer
 * @param spritesheetPath : c-style string literal
 * @param iW : integer
 * @param iH : integer
 * @param r : integer
 * @param c : integer
 * @return A pointer to the newly created Tileset struct
 */
Tileset* createTileset(SDL_Renderer* renderer, const char* spritesheetPath,
                       int tW, int tH, int r, int c) {

    Tileset* tileset = (Tileset*) malloc(sizeof(Tileset));
    SDL_Surface* surface = IMG_Load(spritesheetPath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    tileset->texture = texture;
    tileset->tW = tW;
    tileset->tH = tH;
    tileset->rows = r;
    tileset->cols = c;

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
