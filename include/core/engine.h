/**
 * @file engine.h
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for the game engine.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "util/error.h"
#include "util/window.h"

#include "core/render.h"

#include <SDL2/SDL.h>

Error runGameLoop(WindowManager *wManager);

Error drawStartMenu(WindowManager *wManager, StartMenuScene *scene);

#endif
