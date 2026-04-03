/**
 * @file window.c
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for the window pop up.
 */

#include "util/window.h"

#include "core/engine.h"

#include <stdio.h>

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Creates a WindowManager struct.
 *
 * @param name : string pointer
 * @param width : integer
 * @return A pointer to the created WindowManager struct
 */
WindowManager* createWindowManager(char* name, int wWidth, int wHeight) {
    WindowManager* wManager = (WindowManager*) malloc(sizeof(WindowManager));
    wManager->name = name;
    wManager->wWidth = wWidth;
    wManager->wHeight = wHeight;
    return wManager;
}

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Cleans up a WindowManager struct.
 *
 * @param wManager : WindowManager struct pointer
 */
void destroyWindowManager(WindowManager* wManager) {
    if (wManager->window) SDL_DestroyWindow(wManager->window);
    if (wManager->renderer) SDL_DestroyRenderer(wManager->renderer);
}

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Checks whether or not SDL initialized correctly.
 *
 * @return An Error struct describing whether or not SDL
 * was initialized properly
 */
Error checkSDLInit() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        createError(ESTAT_WINDOW, "Couldn't initialize SDL_VIDEO");
    if (TTF_Init() != 0) createError(ESTAT_WINDOW, "Couldn't initialize TTF");

    return createError(ESTAT_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Creates an SDL window for a window manager.
 *
 * @param wManager: WindowManager struct pointer
 * @return An Error struct describing whether or not the
 * window was successfully created
 */
Error createWindow(WindowManager* wManager) {
    SDL_Window* window;
    window = SDL_CreateWindow(wManager->name,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              wManager->wWidth,
                              wManager->wHeight,
                              0);

    if (!window) return createError(ESTAT_WINDOW, "Couldn't create SDL window");

    wManager->window = window;
    return createError(ESTAT_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Creates an SDL renderer for a window manager.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct describing whether or not the
 * renderer was successfully created
 */
Error createRenderer(WindowManager* wManager) {
    SDL_Renderer* renderer;
    renderer =
        SDL_CreateRenderer(wManager->window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
        return createError(ESTAT_WINDOW, "Couldn't create SDL renderer");

    wManager->renderer = renderer;
    return createError(ESTAT_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Initializes the main game window.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct describing whether or not the
 * initialization of the game window was successful
 */
Error initGameWindow(WindowManager* wManager) {
    Error err;
    err = checkSDLInit();
    if (err.statusNum != ESTAT_NONE) return err;

    err = createWindow(wManager);
    if (err.statusNum != ESTAT_NONE) return err;

    err = createRenderer(wManager);
    if (err.statusNum != ESTAT_NONE) return err;

    printf("Successfully initilized the game window.\n");
    return createError(ESTAT_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Runs the game window loop.
 *
 * @param name : string pointer
 * @param wWidth : integer
 * @param wHeight : integer
 * @return An Error struct describing whether or not the
 * window loop ran into an issue
 */
Error runGameWindow(char* name, int wWidth, int wHeight) {
    WindowManager* wManager = createWindowManager(name, wWidth, wHeight);
    Error err;

    err = initGameWindow(wManager);
    if (err.statusNum != ESTAT_NONE) {
        destroyWindowManager(wManager);
        free(wManager);
        return err;
    }

    err = runGameLoop(wManager);
    if (err.statusNum != ESTAT_NONE) {
        destroyWindowManager(wManager);
        free(wManager);
        return err;
    }

    destroyWindowManager(wManager);
    free(wManager);
    SDL_Quit();
    return createError(ESTAT_NONE, NULL);
}
