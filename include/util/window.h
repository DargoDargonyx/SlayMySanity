/**
 * @file window.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for the window pop up.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "util/error.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    const char* name;
    int wWidth;
    int wHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
} WindowManager;

WindowManager* createWindowManager(const char* name, int wWidth, int wHeight);
void destroyWindowManager(WindowManager* wManager);

Error checkSDLInit();
Error createWindow(WindowManager* wManager);
Error createRenderer(WindowManager* wManager);

Error initGameWindow(WindowManager* manager);
Error runGameWindow(const char* name, int wWidth, int wHeight);

#endif
