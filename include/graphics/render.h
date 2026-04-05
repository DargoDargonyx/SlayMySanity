/**
 * @file render.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for rendering the game.
 */

#ifndef RENDER_H
#define RENDER_H

#include "core/scene.h"
#include "graphics/camera.h"
#include "util/error.h"
#include "util/helper.h"
#include "util/window.h"

Error drawCurrentScene(WindowManager* wManager);
Error drawStartMenuScene(WindowManager* wManager, StartMenuScene* scene);
Error drawOptionsMenuScene(WindowManager* wManager, OptionsMenuScene* scene);
Error drawPlayScene(WindowManager* wManager, PlayScene* scene);

Error drawMap(SDL_Renderer* renderer, Cam* cam, Map* map);
Error drawTile(SDL_Renderer* renderer, Cam* cam, Tileset* tileset, int id,
               Pos pos);
Error renderBtnSprite(SDL_Renderer* renderer, Button* btn);

#endif
