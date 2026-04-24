/**
 * @file render.h
 * @author DargoDargonyx
 * @date 04/21/2026
 * @brief Handles the logic for rendering the game.
 */

#ifndef RENDER_H
#define RENDER_H

#include "core/scene.h"
#include "graphics/camera.h"
#include "util/error.h"
#include "util/window.h"

Error* drawCurrentScene(WindowManager*);
Error* drawMenuScene(SDL_Renderer*, MenuScene*);
Error* drawPlayScene(SDL_Renderer*, PlayScene*);

Error* drawWidgets(SDL_Renderer*, UIManager*);
Error* drawTxtBox(SDL_Renderer*, TxtBox*);
Error* drawButton(SDL_Renderer*, Button*);

Error* drawMap(SDL_Renderer*, Cam*, Map*);
Error* drawPlayer(SDL_Renderer*, Cam*);

#endif
