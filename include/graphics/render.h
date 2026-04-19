/**
 * @file render.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for rendering the game.
 */

#ifndef RENDER_H
#define RENDER_H

#include "core/scene.h"
#include "graphics/camera.h"
#include "util/error.h"
#include "util/window.h"

Error* drawCurrentScene(WindowManager*);
Error* drawStartMenuScene(WindowManager*, StartMenuScene*);
Error* drawOptionsMenuScene(WindowManager*, OptionsMenuScene*);
Error* drawPlayScene(WindowManager*, PlayScene*);

Error* drawMap(SDL_Renderer*, Cam*, Map*);

Error* renderBtnSprite(SDL_Renderer*, Button*);
Error* renderPlayerSprite(SDL_Renderer*, Cam*);

#endif
