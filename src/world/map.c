/**
 * @file map.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for maps and tiles.
 */

#include "world/map.h"
#include "util/error.h"
#include "util/helper.h"
#include "world/physics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating a Map struct.
 *
 * @param errCont : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @return A pointer to the Map struct in question
 */
Map* createTestMap(ErrorContainer* errCont, SDL_Renderer* renderer) {
    Map* map = (Map*) malloc(sizeof(Map));
    const char* spritePath = "../assets/sprites/map/testing_map.png";
    Error* err = createMapTexture(map, renderer, spritePath);
    if (err) addErrorToContainer(errCont, err);

    return map;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying a Map struct.
 *
 * @param self : Map struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Map struct was successfully destroyed
 */
Error* destroyMap(Map* self) {
    free(self);
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating the SDL texture for a map.
 *
 * @param map : Map struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param filepath : c-style string literal
 * @return A pointer to an Error struct that describes whether
 * or not the SDL texture was successfully created for the map
 * in question
 */
Error* createMapTexture(Map* map, SDL_Renderer* renderer, const char* filepath) {

    Error* err = NULL;
    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface) {
        err = createError(SPRITE, "Could not load the sritesheet image file");
    } else {
        map->texture = SDL_CreateTextureFromSurface(renderer, surface);
        map->pixelSize.w = surface->w;
        map->pixelSize.h = surface->h;
        map->worldSize.w = (float) map->pixelSize.w / WORLD_COORD_WIDTH;
        map->worldSize.h = (float) map->pixelSize.h / WORLD_COORD_HEIGHT;
        SDL_FreeSurface(surface);
    }
    return err;
}
