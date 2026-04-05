/**
 * @file player.h
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for the main player.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "util/error.h"
#include "util/helper.h"

typedef struct {
    Pos pos;
    float speed;
} Player;

Player* createPlayer(Pos origPos, float speed);
Error destroyPlayer(Player* self);

#endif
