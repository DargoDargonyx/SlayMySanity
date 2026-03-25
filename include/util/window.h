/**
 * @file window.h
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for the window pop up.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "util/error.h"

#include "core/ui/font.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    char* name;
    int wWidth;
    int wHeight;
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
} WindowManager;


WindowManager* createWindowManager(char* name, int wWidth, int wHeight);
void cleanWindowManager(WindowManager* wManager);

Error checkSDLInit();
Error createTTFFont(WindowManager* wManager, Font* font);
Error createWindow(WindowManager* wManager);
Error createRenderer(WindowManager* wManager);

Error initGameWindow(WindowManager* manager);
Error runGameWindow(char* name, int wWidth, int wHeight);


#endif
