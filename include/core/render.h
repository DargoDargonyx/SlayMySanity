/**
 * @file render.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for rendering the game.
 */

#ifndef RENDER_H
#define RENDER_H

#include "core/scene.h"
#include "util/error.h"
#include "util/window.h"

Error initStartMenuScene(WindowManager* wManager, StartMenuScene* scene);

Error drawScene(WindowManager* wManager);
Error drawStartMenuScene(WindowManager* wManager, StartMenuScene* scene);

#endif
