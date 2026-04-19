/**
 * @file engine.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for the game engine.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "util/error.h"
#include "util/helper.h"
#include "util/window.h"

#include <SDL2/SDL.h>

#define TARGET_FPS 60

Error* runGameLoop(WindowManager*);

int pointInRect(Pos, SDL_Rect*);
void handleButtonEvent(Button*, SDL_Event*);
Button** getSceneButtons(Scene*);

void loadStartMenuScene(void*);
void loadOptionsMenuScene(void*);
void loadPlayScene(void*);
void exitGameLoop(void*);

#endif
