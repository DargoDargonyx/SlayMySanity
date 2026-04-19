/**
 * @file player.h
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Handles the logic for the main player.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "graphics/animation.h"
#include "util/error.h"
#include "world/physics.h"

#include <SDL2/SDL.h>

#define PLAYER_SPRITESHEET_SPRITE_COUNT 44
#define PLAYER_SPRITESHEET_WIDTH 11
#define PLAYER_SPRITESHEET_HEIGHT 4

typedef struct {
    Coord coord;
    float speed;
    AnimationManager* aManager;
    ActionState currentAction;
    Direction facingDir;
} Player;

Player* createPlayer(ErrorContainer* errContainer, SDL_Renderer* renderer,
                     const char* spritesheetPath, Coord initCoord, float speed);
Error destroyPlayer(Player* self);

Error movePlayerNorth(Player* self, float dist);
Error movePlayerNorthEast(Player* self, float dist);
Error movePlayerEast(Player* self, float dist);
Error movePlayerSouthEast(Player* self, float dist);
Error movePlayerSouth(Player* self, float dist);
Error movePlayerSouthWest(Player* self, float dist);
Error movePlayerWest(Player* self, float dist);
Error movePlayerNorthWest(Player* self, float dist);

Error initPlayerAnimation(Player* self);
Error createPlayerSouthEastIdleAnim(Player* self);
Error createPlayerSouthWestIdleAnim(Player* self);
Error createPlayerMoveNorthEastAnim(Player* self);
Error createPlayerMoveNorthWestAnim(Player* self);
Error createPlayerMoveSouthEastAnim(Player* self);
Error createPlayerMoveSouthWestAnim(Player* self);

#endif
