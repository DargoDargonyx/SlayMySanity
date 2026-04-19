/**
 * @file input.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for user input.
 */

#ifndef INPUT_H
#define INPUT_H

#include "ui/widget.h"
#include "util/error.h"
#include "world/player.h"

#include <SDL2/SDL.h>

Error* handlePlayerEvent(Player*, float);
void handleButtonEvent(Button*, SDL_Event*);

#endif
