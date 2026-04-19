/**
 * @file player.h
 * @author DargoDargonyx
 * @date 04/19/2026
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

Player* createPlayer(ErrorContainer*, SDL_Renderer*, const char*, Coord, float);
Error* destroyPlayer(Player*);

Error* movePlayerNorth(Player*, float);
Error* movePlayerNorthEast(Player*, float);
Error* movePlayerEast(Player*, float);
Error* movePlayerSouthEast(Player*, float);
Error* movePlayerSouth(Player*, float);
Error* movePlayerSouthWest(Player*, float);
Error* movePlayerWest(Player*, float);
Error* movePlayerNorthWest(Player*, float);

Error* initPlayerAnimation(Player*);
Error* createPlayerSouthEastIdleAnim(Player*);
Error* createPlayerSouthWestIdleAnim(Player*);
Error* createPlayerMoveNorthEastAnim(Player*);
Error* createPlayerMoveNorthWestAnim(Player*);
Error* createPlayerMoveSouthEastAnim(Player*);
Error* createPlayerMoveSouthWestAnim(Player*);

#endif
