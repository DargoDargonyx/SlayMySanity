/**
 * @file engine.c
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for the game engine.
 */

#include "core/engine.h"


/**
 * @author DargoDargonyx
 * @date 03/25/26
 * @brief Handles teh logic for the main game loop.
 *
 * @param event : SDL_Event pointer
 * @return An Error struct describing whether or not the
 * game loop ran without issue
 */
Error runGameLoop(WindowManager* wManager) {
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) running = 0;
    }
    return createError(ESTAT_NONE, NULL);
}
