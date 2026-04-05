/**
 * @file input.h
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for user input.
 */

#ifndef INPUT_H
#define INPUT_H

#include "graphics/camera.h"
#include "ui/widget.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

int pointInRect(Pos pos, SDL_Rect* rect);

void handleButtonEvent(Button* btn, SDL_Event* e);
void checkCameraMovement(Cam* cam, Pos maxBounds, float deltaTime);

#endif
