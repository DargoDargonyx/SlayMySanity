/**
 * @file helper.c
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Generic helper functions and structs for random
 * logic needed throughout the program.
 */

#include "util/helper.h"

#include <SDL2/SDL.h>

/**
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Helper function to check whether or not a point in the scene
 * in inside of a given SDL_Rect.
 *
 * @param pos : Pos struct
 * @param rect : SDL_Rect pointer
 * @return An integer representation of a boolean for whether or not
 * the given point is inside of the SDL_Rect in question
 */
int pointInRect(Pos pos, SDL_Rect* rect) {
    return (pos.x >= rect->x) && (pos.x <= rect->x + rect->w) &&
           (pos.y >= rect->y) && (pos.y <= rect->y + rect->h);
}
