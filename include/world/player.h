/**
 * @file player.h
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for the main player.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "graphics/animation.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

typedef struct {
    PosFloat worldPos;
    float speed;
    AnimationManager* aManager;
} Player;

Player* createPlayer(ErrorContainer* errContainer, SDL_Renderer* renderer,
                     const char* spritesheetPath, PosFloat origPos,
                     float speed);
Error destroyPlayer(Player* self);

Error createPlayerIdleAnimation(Player* self);
Error createPlayerWalkLeftAnimation(Player* self);
Error createPlayerWalkRightAnimation(Player* self);
Error createPlayerWalkUpAnimation(Player* self);
Error createPlayerWalkDownAnimation(Player* self);

#endif
