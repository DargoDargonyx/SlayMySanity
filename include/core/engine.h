/**
 * @file engine.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for the game engine.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "core/render.h"
#include "util/error.h"
#include "util/window.h"

#include <SDL2/SDL.h>

Error runGameLoop(WindowManager* wManager);

Error drawStartMenu(WindowManager* wManager, StartMenuScene* scene);

#endif
