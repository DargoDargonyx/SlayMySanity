/**
 * @file engine.c
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for the game engine.
 */

#include "core/engine.h"
#include "core/scene.h"
#include "graphics/render.h"
#include "ui/widget.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/05/26
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
        err = drawCurrentScene(wManager);
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
 * @date 04/05/2026
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

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Helper function to handle button events.
 *
 * @param btn : Button struct pointer
 * @param e : SDL_Event pointer
 */
void handleButtonEvent(Button* btn, SDL_Event* e) {
    Pos pos;

    if (e->type == SDL_MOUSEMOTION) {
        pos.x = e->motion.x;
        pos.y = e->motion.y;
        if (pointInRect(pos, &btn->rect))
            btn->state = BTN_HOVER;
        else
            btn->state = BTN_IDLE;
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (pointInRect(pos, &btn->rect))
            btn->state = BTN_PRESSED;
    }

    if (e->type == SDL_MOUSEBUTTONUP) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (btn->state == BTN_PRESSED && pointInRect(pos, &btn->rect)) {
            if (btn->onClick)
                btn->onClick(btn->userData);
            btn->state = BTN_HOVER;
        }
    }
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
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
        wManager, manager->errContainer, manager->renderer, manager->wSize);
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
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
        wManager, manager->errContainer, manager->renderer, manager->wSize);
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
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
        wManager, manager->errContainer, manager->renderer, manager->wSize);
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
