/**
 * @file window.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for the window pop up.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "core/scene.h"
#include "util/error.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct Scene Scene;

typedef struct {
    int running;
    const char* name;
    int wWidth;
    int wHeight;
    Scene* currentScene;
    SDL_Window* window;
    SDL_Renderer* renderer;
    ErrorContainer* errContainer;
} WindowManager;

WindowManager* createWindowManager(const char* name, int wWidth, int wHeight);
Error destroyWindowManager(WindowManager* wManager);
Error clearCurrentScene(WindowManager* wManager);

Error checkSDLInit();
Error createWindow(WindowManager* wManager);
Error createRenderer(WindowManager* wManager);

Error initGameWindow(WindowManager* manager);
Error runGameWindow(const char* name, int wWidth, int wHeight);

#endif
