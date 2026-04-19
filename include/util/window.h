/**
 * @file window.h
 * @author DargoDargonyx
 * @date 04/19/2026
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
    Size wSize;
    Scene* currentScene;
    SDL_Window* window;
    SDL_Renderer* renderer;
    ErrorContainer* errCont;
} WindowManager;

WindowManager* createWindowManager(const char*, Size);
Error* destroyWindowManager(WindowManager*);
Error* clearCurrentScene(WindowManager*);

Error* checkSDLInit();
Error* createWindow(WindowManager*);
Error* createRenderer(WindowManager*);

Error* initGameWindow(WindowManager*);
Error* runGameWindow(const char*, Size);

#endif
