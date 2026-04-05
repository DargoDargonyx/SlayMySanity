/**
 * @file engine.h
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for the game engine.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "util/error.h"
#include "util/helper.h"
#include "util/window.h"

#include <SDL2/SDL.h>

#define TARGET_FPS 60

Error runGameLoop(WindowManager* wManager);

int pointInRect(Pos pos, SDL_Rect* rect);
void handleButtonEvent(Button* btn, SDL_Event* e);
Button** getSceneButtons(Scene* scene);

void loadStartMenuScene(void* wManager);
void loadOptionsMenuScene(void* wManager);
void loadPlayScene(void* wManager);
void exitGameLoop(void* wManager);

#endif
