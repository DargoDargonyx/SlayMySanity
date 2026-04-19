/**
 * @file input.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for user input.
 */

#include "ui/input.h"
#include "graphics/animation.h"
#include "ui/widget.h"
#include "util/helper.h"
#include "world/player.h"

#include <SDL2/SDL.h>

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for player events when a
 * button is pressed.
 *
 * @param player : Player struct pointer
 * @param dt : float
 * @return A pointer to an Error struct that describes whether
 * or not the player events were handled without issue
 */
Error* handlePlayerEvent(Player* player, float dt) {
    Error* err = NULL;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    float dist = 10.0f * dt * player->speed;

    Uint8 up = keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP];
    Uint8 down = keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN];
    Uint8 left = keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT];
    Uint8 right = keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT];

    if (up && right) {
        movePlayerNorthEast(player, dist);
    } else if (up && left) {
        movePlayerNorthWest(player, dist);
    } else if (down && right) {
        movePlayerSouthEast(player, dist);
    } else if (down && left) {
        movePlayerSouthWest(player, dist);
    } else {
        if (up && down) {
            if (player->currentAction != IDLE) {
                player->currentAction = IDLE;
                err = switchAnimationSeq(player->aManager,
                                         ANIM_PLAYER_EAST_IDLE_ORDER);
            }
        } else if (left && right) {
            if (player->currentAction != IDLE) {
                player->currentAction = IDLE;
                err = switchAnimationSeq(player->aManager,
                                         ANIM_PLAYER_EAST_IDLE_ORDER);
            }
        } else if (up) {
            movePlayerNorth(player, dist);
        } else if (down) {
            movePlayerSouth(player, dist);
        } else if (left) {
            movePlayerWest(player, dist);
        } else if (right) {
            movePlayerEast(player, dist);
        } else {
            if (player->currentAction != IDLE) {
                player->currentAction = IDLE;
                if (player->facingDir == NORTH ||
                    player->facingDir == NORTH_EAST ||
                    player->facingDir == EAST ||
                    player->facingDir == SOUTH_EAST ||
                    player->facingDir == SOUTH) {

                    err = switchAnimationSeq(player->aManager,
                                             ANIM_PLAYER_EAST_IDLE_ORDER);
                    player->facingDir = SOUTH_EAST;
                } else if (player->facingDir == NORTH_WEST ||
                           player->facingDir == WEST ||
                           player->facingDir == SOUTH_WEST) {

                    err = switchAnimationSeq(player->aManager,
                                             ANIM_PLAYER_WEST_IDLE_ORDER);
                    player->facingDir = SOUTH_WEST;
                } else {
                    err = createError(ANIMATION,
                                      "Could not animate a player with an "
                                      "unkown facing direction");
                }
            }
        }
    }

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for button events.
 *
 * @param btn : Button struct pointer
 * @param e : SDL_Event pointer
 */
void handleButtonEvent(Button* btn, SDL_Event* e) {
    Pos pos;

    if (e->type == SDL_MOUSEMOTION) {
        pos.x = e->motion.x;
        pos.y = e->motion.y;
        if (pointInRect(pos, &btn->rect)) btn->state = BTN_HOVER;
        else btn->state = BTN_IDLE;
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (pointInRect(pos, &btn->rect)) btn->state = BTN_PRESSED;
    }

    if (e->type == SDL_MOUSEBUTTONUP) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (btn->state == BTN_PRESSED && pointInRect(pos, &btn->rect)) {
            if (btn->onClick) btn->onClick(btn->userData);
            btn->state = BTN_HOVER;
        }
    }
}
