/**
 * @file render.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for rendering the game.
 */

#ifndef RENDER_H
#define RENDER_H

#include "core/scene.h"
#include "util/error.h"
#include "util/window.h"

Error drawScene(WindowManager* wManager);
Error drawStartMenuScene(WindowManager* wManager, StartMenuScene* scene);
Error drawOptionsMenuScene(WindowManager* wManager, OptionsMenuScene* scene);

Error renderMainButtonSprite(SDL_Renderer* renderer, Button* btn);

#endif
