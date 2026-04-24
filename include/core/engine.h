/**
 * @file engine.h
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for the game engine.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "util/error.h"
#include "util/window.h"

#include <SDL2/SDL.h>

#define TARGET_FPS 60

Error* runGameLoop(WindowManager*);
void exitGameLoop(void*);

SceneLoader* createSceneLoader(WindowManager* wManager);

#endif
