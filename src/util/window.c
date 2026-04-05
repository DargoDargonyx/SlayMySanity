/**
 * @file window.c
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for the window pop up.
 */

#include "util/window.h"
#include "core/engine.h"
#include "util/error.h"
#include "util/helper.h"

#include <stdio.h>

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Creates a WindowManager struct.
 *
 * @param name : c-style string constant
 * @param wSize : Size struct
 * @return A pointer to the created WindowManager struct
 */
WindowManager* createWindowManager(const char* name, Size wSize) {
    WindowManager* wManager = (WindowManager*) malloc(sizeof(WindowManager));
    wManager->running = 1;
    wManager->name = name;
    wManager->wSize = wSize;
    wManager->currentScene = NULL;
    wManager->errContainer = createErrorContainer();
    return wManager;
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for destroying a WindowManager struct.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct describing whether or not the
 * WindowManager struct in question was successfully destroyed
 */
Error destroyWindowManager(WindowManager* wManager) {
    if (wManager->window)
        SDL_DestroyWindow(wManager->window);
    if (wManager->renderer)
        SDL_DestroyRenderer(wManager->renderer);

    Error err = createError(ESTAT_MAIN_NONE, NULL);
    if (wManager->errContainer) {
        err = destroyErrorContainer(wManager->errContainer);
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for clearing the current scene
 * from a WindowManager struct.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct describing whether or not the
 * current scene from the WindowManager struct was
 * successfully cleared
 */
Error clearCurrentScene(WindowManager* wManager) {
    if (!wManager)
        return createError(
            ESTAT_WINDOW_SCENE_CLEAR,
            "Could not clear the scenes from a NULL window manager");

    if (wManager->currentScene) {
        wManager->currentScene->destroy(wManager->currentScene);
        wManager->currentScene = NULL;
    }
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Checks whether or not SDL initialized correctly.
 *
 * @return An Error struct describing whether or not SDL
 * was initialized properly
 */
Error checkSDLInit() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        createError(ESTAT_WINDOW_INIT, "Couldn't initialize SDL_VIDEO");
    if (TTF_Init() != 0)
        createError(ESTAT_WINDOW_INIT, "Couldn't initialize TTF");

    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Creates an SDL window for a window manager.
 *
 * @param wManager: WindowManager struct pointer
 * @return An Error struct describing whether or not the
 * window was successfully created
 */
Error createWindow(WindowManager* wManager) {
    SDL_Window* window;
    window = SDL_CreateWindow(wManager->name, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, wManager->wSize.w,
                              wManager->wSize.h, 0);

    if (!window)
        return createError(ESTAT_WINDOW_INIT, "Couldn't create SDL window");

    wManager->window = window;
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
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
        return createError(ESTAT_WINDOW_INIT, "Couldn't create SDL renderer");

    wManager->renderer = renderer;
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Initializes the main game window.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct describing whether or not the
 * initialization of the game window was successful
 */
Error initGameWindow(WindowManager* wManager) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    err = checkSDLInit();
    if (err.statusNum != ESTAT_MAIN_NONE)
        return err;

    err = createWindow(wManager);
    if (err.statusNum != ESTAT_MAIN_NONE)
        return err;

    err = createRenderer(wManager);
    if (err.statusNum != ESTAT_MAIN_NONE)
        return err;

    printf("Successfully initilized the game window.\n");
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Runs the game window loop.
 *
 * @param name : c-style string constant
 * @param wSize : Size struct
 * @return An Error struct describing whether or not the
 * window loop ran into an issue
 */
Error runGameWindow(const char* name, Size wSize) {
    WindowManager* wManager = createWindowManager(name, wSize);
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    err = initGameWindow(wManager);
    if (err.statusNum != ESTAT_MAIN_NONE) {
        destroyWindowManager(wManager);
        free(wManager);
        return err;
    }

    err = runGameLoop(wManager);
    if (err.statusNum != ESTAT_MAIN_NONE) {
        destroyWindowManager(wManager);
        free(wManager);
        return err;
    }

    err = destroyWindowManager(wManager);
    free(wManager);
    SDL_Quit();
    return err;
}
