/**
 * @file engine.c
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for the game engine.
 */

#include "core/engine.h"
#include "core/render.h"
#include "core/scene.h"
#include "core/ui/widget.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/04/26
 * @brief Handles the logic for running the main game loop.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct that describes whether or not the
 * game loop ran successfully
 */
Error runGameLoop(WindowManager* wManager) {
    SDL_Event event;
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    // Initializing the current scene to the start menu
    loadStartMenuScene((void*) wManager);
    while (wManager->running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                wManager->running = 0;

            for (int i = 0; i < wManager->currentScene->btnCount; i++) {
                handleButtonEvent(wManager->currentScene->btns[i], &event);
            }
        }

        if (wManager->errContainer->errCount > 0) {
            Error tmpErr = clearCurrentScene(wManager);
            if (tmpErr.statusNum != ESTAT_MAIN_NONE)
                return tmpErr;
            return wManager->errContainer->errs[0];
        }
        err = drawScene(wManager);
        if (err.statusNum != ESTAT_MAIN_NONE) {
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
 * @date 04/03/2026
 * @brief Helper function to check whether or not a point in the scene
 * in inside of a given SDL_Rect.
 *
 * @param x : integer
 * @param y : integer
 * @param r : SDL_Rect pointer
 * @return An integer representation of a boolean for whether or not
 * the given point is inside of the SDL_Rect in question
 */
int pointInRect(int x, int y, SDL_Rect* r) {
    return x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h;
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Helper function to handle button events.
 *
 * @param btn : Button struct pointer
 * @param e : SDL_Event pointer
 */
void handleButtonEvent(Button* btn, SDL_Event* e) {
    int x, y;

    if (e->type == SDL_MOUSEMOTION) {
        x = e->motion.x;
        y = e->motion.y;
        if (pointInRect(x, y, &btn->rect))
            btn->state = BTN_HOVER;
        else
            btn->state = BTN_IDLE;
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        x = e->button.x;
        y = e->button.y;
        if (pointInRect(x, y, &btn->rect))
            btn->state = BTN_PRESSED;
    }

    if (e->type == SDL_MOUSEBUTTONUP) {
        x = e->button.x;
        y = e->button.y;
        if (btn->state == BTN_PRESSED && pointInRect(x, y, &btn->rect)) {
            if (btn->onClick)
                btn->onClick(btn->userData);
            btn->state = BTN_HOVER;
        }
    }
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
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
        wManager, manager->errContainer, manager->renderer, manager->wWidth,
        manager->wHeight);
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
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
        wManager, manager->errContainer, manager->renderer, manager->wWidth,
        manager->wHeight);
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
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
        wManager, manager->errContainer, manager->renderer, manager->wWidth,
        manager->wHeight);
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
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
