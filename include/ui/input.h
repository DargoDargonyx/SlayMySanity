/**
 * @file input.h
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for user input.
 */

#ifndef INPUT_H
#define INPUT_H

#include "graphics/camera.h"
#include "ui/widget.h"
#include "util/helper.h"
#include "world/player.h"

#include <SDL2/SDL.h>

int pointInRect(Pos pos, SDL_Rect* rect);

void handlePlayerEvent(Player* player, float dt);
void handleButtonEvent(Button* btn, SDL_Event* e);
void handleCameraMovement(Cam* cam, Size maxBounds, float dt);

#endif
