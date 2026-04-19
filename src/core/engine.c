/**
 * @file engine.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for the game engine.
 */

#include "core/engine.h"
#include "core/scene.h"
#include "graphics/render.h"
#include "ui/input.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/19/26
 * @brief Handles the logic for running the main game loop.
 *
 * @param wManager : WindowManager struct pointer
 * @return A pointer to an Error struct that describes
 * whether or not the game loop ran successfully
 */
Error* runGameLoop(WindowManager* wManager) {
    SDL_Event event;
    Error* err = NULL;
    float targetFrameTime = 1000.0f / TARGET_FPS;

    // Initializing the current scene to the start menu
    loadStartMenuScene((void*) wManager);
    Uint64 last = SDL_GetPerformanceCounter();
    while (wManager->running) {
        Uint64 now = SDL_GetPerformanceCounter();
        float dt = (float) (now - last) / SDL_GetPerformanceFrequency();
        last = now;
        if (dt < targetFrameTime) {
            SDL_Delay(targetFrameTime - dt);
            dt = targetFrameTime;
        }
        dt /= 1000.0f;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) wManager->running = 0;

            for (int i = 0; i < wManager->currentScene->btnCount; i++) {
                handleButtonEvent(wManager->currentScene->btns[i], &event);
            }
        }

        if (wManager->currentScene->type == PLAY) {
            PlayScene* scene = (PlayScene*) wManager->currentScene;
            err = handlePlayerEvent(scene->player, dt);
            if (err) return err;
            err = handleCameraMovement(scene->cam, scene->map->worldSize, dt);
            if (err) return err;
        }

        if (wManager->errCont->count > 0) {
            Error* tmpErr = clearCurrentScene(wManager);
            if (tmpErr) return tmpErr;
            return wManager->errCont->errs[0];
        }

        err = drawCurrentScene(wManager);
        if (err) {
            IMG_Quit();
            return err;
        }
        SDL_RenderPresent(wManager->renderer);
    }

    err = clearCurrentScene(wManager);
    IMG_Quit();
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Helper function to handle loading the start menu.
 *
 * @note The window manager is passed as a void pointer because
 * this function is usually called from the scene.c file where
 * window is not within scope.
 *
 * @param wManager : void pointer
 */
void loadStartMenuScene(void* wManager) {
    WindowManager* manager = (WindowManager*) wManager;
    clearCurrentScene(manager);
    manager->currentScene = (Scene*) createStartMenuScene(
        wManager, manager->errCont, manager->renderer, manager->wSize);
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Helper function to handle loading the main options menu.
 *
 * @note The window manager is passed as a void pointer because
 * this function is usually called from the scene.c file where
 * window is not within scope.
 *
 * @param wManager : void pointer
 */
void loadOptionsMenuScene(void* wManager) {
    WindowManager* manager = (WindowManager*) wManager;
    clearCurrentScene(manager);
    manager->currentScene = (Scene*) createOptionsMenuScene(
        wManager, manager->errCont, manager->renderer, manager->wSize);
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Helper function to handle loading the playing scene.
 *
 * @note The window manager is passed as a void pointer because
 * this function is usually called from the scene.c file where
 * window is not within scope.
 *
 * @param wManager : void pointer
 */
void loadPlayScene(void* wManager) {
    WindowManager* manager = (WindowManager*) wManager;
    clearCurrentScene(manager);
    manager->currentScene = (Scene*) createPlayScene(
        wManager, manager->errCont, manager->renderer, manager->wSize);
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Helper function to handle quitting the game.
 *
 * @note The window manager is passed as a void pointer because
 * this function is usually called from the scene.c file where
 * window is not within scope.
 * @param wManager : void pointer
 */
void exitGameLoop(void* wManager) {
    WindowManager* manager = (WindowManager*) wManager;
    manager->running = 0;
}
