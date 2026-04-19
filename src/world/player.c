/**
 * @file player.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for the main player.
 */

#include "world/player.h"
#include "graphics/animation.h"
#include "util/error.h"
#include "util/helper.h"
#include "world/physics.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating a Player struct.
 *
 * @param errCont : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param spritesheetPath : c-style string literal
 * @param initCoord : Coord struct
 * @param speed : float
 * @return A pointer to a newly created Player struct
 */
Player* createPlayer(ErrorContainer* errCont, SDL_Renderer* renderer,
                     const char* spritesheetPath, Coord initCoord,
                     float speed) {

    Player* player = (Player*) malloc(sizeof(Player));
    player->coord = initCoord;
    player->speed = speed;

    Size spritesheetSize =
        (Size){PLAYER_SPRITESHEET_WIDTH, PLAYER_SPRITESHEET_HEIGHT};
    Spritesheet* spritesheet =
        createSpritesheet(errCont, renderer, spritesheetPath, spritesheetSize,
                          PLAYER_SPRITESHEET_SPRITE_COUNT);
    player->aManager = createAnimationManager(spritesheet);

    return player;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying a Player struct.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct describing whether
 * or not the Player struct in question was successfully
 * destroyed
 */
Error* destroyPlayer(Player* self) {
    Error* err = NULL;
    if (!self)
        return createError(PLAYER, "Could not destroy a NULL Player struct");
    err = destroyAnimationManager(self->aManager);
    free(self);

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player NORTH.
 *
 * @param self : Player struct pointer
 * @param dist : float
 * @return A pointer to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerNorth(Player* self, float dist) {
    Error* err = NULL;
    self->coord.y -= dist;
    if (self->currentAction != MOVING_NORTH) {
        if (self->currentAction != MOVING_NORTH_EAST &&
            self->currentAction != MOVING_NORTH_WEST) {

            if (self->facingDir == WEST || self->facingDir == NORTH_WEST ||
                self->facingDir == SOUTH_WEST) {

                err = switchAnimationSeq(self->aManager,
                                         ANIM_PLAYER_NORTH_WEST_ORDER);
                self->facingDir = NORTH_WEST;
            } else {
                err = switchAnimationSeq(self->aManager,
                                         ANIM_PLAYER_NORTH_EAST_ORDER);
                self->facingDir = NORTH_EAST;
            }
        }
        self->currentAction = MOVING_NORTH;
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player NORTH_EAST.
 *
 * @param self : Player struct pointer
 * @param dist : float
 * @return A pointer to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerNorthEast(Player* self, float dist) {
    Error* err = NULL;
    self->coord.y -= dist;
    self->coord.x += dist;
    if (self->currentAction != MOVING_NORTH_EAST) {
        self->currentAction = MOVING_NORTH_EAST;
        self->facingDir = NORTH_EAST;
        err = switchAnimationSeq(self->aManager, ANIM_PLAYER_NORTH_EAST_ORDER);
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player EAST.
 *
 * @param selfr : Player struct pointer
 * @param dist : float
 * @return A pointer to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerEast(Player* self, float dist) {
    Error* err = NULL;
    self->coord.x += dist;
    if (self->currentAction != MOVING_EAST) {
        if (self->currentAction != MOVING_SOUTH_EAST)
            err = switchAnimationSeq(self->aManager,
                                     ANIM_PLAYER_SOUTH_EAST_ORDER);
        self->facingDir = EAST;
        self->currentAction = MOVING_EAST;
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player SOUTH_EAST.
 *
 * @param self : Player struct pointer
 * @param dist : float
 * @return A pointer to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerSouthEast(Player* self, float dist) {
    Error* err = NULL;
    self->coord.y += dist;
    self->coord.x += dist;
    if (self->currentAction != MOVING_SOUTH_EAST) {
        self->currentAction = MOVING_SOUTH_EAST;
        self->facingDir = SOUTH_EAST;
        err = switchAnimationSeq(self->aManager, ANIM_PLAYER_SOUTH_EAST_ORDER);
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player SOUTH.
 *
 * @param self : Player struct pointer
 * @param dist : float
 * @return A pointer to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerSouth(Player* self, float dist) {
    Error* err = NULL;
    self->coord.y += dist;
    if (self->currentAction != MOVING_SOUTH) {
        if (self->currentAction != MOVING_SOUTH_EAST &&
            self->currentAction != MOVING_SOUTH_WEST) {

            if (self->facingDir == WEST || self->facingDir == NORTH_WEST ||
                self->facingDir == SOUTH_WEST) {

                err = switchAnimationSeq(self->aManager,
                                         ANIM_PLAYER_SOUTH_WEST_ORDER);
                self->facingDir = SOUTH_WEST;
            } else {
                err = switchAnimationSeq(self->aManager,
                                         ANIM_PLAYER_SOUTH_EAST_ORDER);
                self->facingDir = SOUTH_EAST;
            }
        }
        self->currentAction = MOVING_SOUTH;
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player SOUTH_WEST.
 *
 * @param self : Player struct pointer
 * @param dist : float
 * @return A pointer to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerSouthWest(Player* self, float dist) {
    Error* err = NULL;
    self->coord.y += dist;
    self->coord.x -= dist;
    if (self->currentAction != MOVING_SOUTH_WEST) {
        self->currentAction = MOVING_SOUTH_WEST;
        self->facingDir = SOUTH_WEST;
        err = switchAnimationSeq(self->aManager, ANIM_PLAYER_SOUTH_WEST_ORDER);
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player WEST.
 *
 * @param self : Player struct pointer
 * @param dist : float
 * @return A poinyter to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerWest(Player* self, float dist) {
    Error* err = NULL;
    self->coord.x -= dist;
    if (self->currentAction != MOVING_WEST) {
        if (self->currentAction != MOVING_SOUTH_WEST)
            err = switchAnimationSeq(self->aManager,
                                     ANIM_PLAYER_SOUTH_WEST_ORDER);
        self->facingDir = WEST;
        self->currentAction = MOVING_WEST;
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for moving the player NORTH_WEST.
 *
 * @param self : Player struct pointer
 * @param dist : float
 * @return A pointer to an Error struct that describes whether
 * or not the player was successfully moved
 */
Error* movePlayerNorthWest(Player* self, float dist) {
    Error* err = NULL;
    self->coord.y -= dist;
    self->coord.x -= dist;
    if (self->currentAction != MOVING_NORTH_WEST) {
        self->currentAction = MOVING_NORTH_WEST;
        self->facingDir = NORTH_WEST;
        err = switchAnimationSeq(self->aManager, ANIM_PLAYER_NORTH_WEST_ORDER);
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for initializing the player
 * animation sequences.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequences were successfully initialized
 */
Error* initPlayerAnimation(Player* self) {
    Error* err = NULL;

    err = createPlayerSouthEastIdleAnim(self);
    if (err) return err;
    err = createPlayerSouthWestIdleAnim(self);
    if (err) return err;
    err = createPlayerMoveNorthEastAnim(self);
    if (err) return err;
    err = createPlayerMoveNorthWestAnim(self);
    if (err) return err;
    err = createPlayerMoveSouthEastAnim(self);
    if (err) return err;
    err = createPlayerMoveSouthWestAnim(self);
    if (err) return err;

    self->aManager->currentSeq =
        self->aManager->seq[ANIM_PLAYER_EAST_IDLE_ORDER];
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating the South/East Idle
 * animation sequence for the player.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequence was successfully created
 */
Error* createPlayerSouthEastIdleAnim(Player* self) {
    Error* err = NULL;
    Uint32 quarterSec = 250.0f;
    Size spriteSize = self->aManager->spritesheet->spriteSize;
    AnimationSeq* seq = createAnimationSeq();

    Pos frame1Pos = (Pos){0, 1};
    AnimationFrame frame1 =
        (AnimationFrame){0, frame1Pos, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err) return err;

    Pos frame2Pos = (Pos){1, 1};
    AnimationFrame frame2 =
        (AnimationFrame){1, frame2Pos, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err) return err;

    Pos frame3Pos = (Pos){2, 1};
    AnimationFrame frame3 =
        (AnimationFrame){2, frame3Pos, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err) return err;

    seq->currentFrameIdx = 0;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating the South/West Idle
 * animation sequence for the player.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequence was successfully created
 */
Error* createPlayerSouthWestIdleAnim(Player* self) {
    Error* err = NULL;
    Uint32 quarterSec = 250.0f;
    Size spriteSize = self->aManager->spritesheet->spriteSize;
    AnimationSeq* seq = createAnimationSeq();

    Pos frame1Pos = (Pos){0, 2};
    AnimationFrame frame1 =
        (AnimationFrame){0, frame1Pos, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err) return err;

    Pos frame2Pos = (Pos){1, 2};
    AnimationFrame frame2 =
        (AnimationFrame){1, frame2Pos, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err) return err;

    Pos frame3Pos = (Pos){2, 2};
    AnimationFrame frame3 =
        (AnimationFrame){2, frame3Pos, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err) return err;

    seq->currentFrameIdx = 0;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating the moving North/East
 * animation sequence for the player.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequence was successfully created
 */
Error* createPlayerMoveNorthEastAnim(Player* self) {
    Error* err = NULL;
    Uint32 eigthSec = 125.0f;
    Size spriteSize = self->aManager->spritesheet->spriteSize;
    AnimationSeq* seq = createAnimationSeq();

    Pos frame1Pos = (Pos){3, 0};
    AnimationFrame frame1 =
        (AnimationFrame){0, frame1Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err) return err;

    Pos frame2Pos = (Pos){4, 0};
    AnimationFrame frame2 =
        (AnimationFrame){1, frame2Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err) return err;

    Pos frame3Pos = (Pos){5, 0};
    AnimationFrame frame3 =
        (AnimationFrame){2, frame3Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err) return err;

    Pos frame4Pos = (Pos){6, 0};
    AnimationFrame frame4 =
        (AnimationFrame){3, frame4Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame4);
    if (err) return err;

    Pos frame5Pos = (Pos){7, 0};
    AnimationFrame frame5 =
        (AnimationFrame){4, frame5Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame5);
    if (err) return err;

    Pos frame6Pos = (Pos){8, 0};
    AnimationFrame frame6 =
        (AnimationFrame){5, frame6Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame6);
    if (err) return err;

    Pos frame7Pos = (Pos){9, 0};
    AnimationFrame frame7 =
        (AnimationFrame){6, frame7Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame7);
    if (err) return err;

    Pos frame8Pos = (Pos){10, 0};
    AnimationFrame frame8 =
        (AnimationFrame){7, frame8Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame8);
    if (err) return err;

    seq->currentFrameIdx = 0;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating the moving North/West
 * animation sequence for the player.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequence was successfully created
 */
Error* createPlayerMoveNorthWestAnim(Player* self) {
    Error* err = NULL;
    Uint32 eigthSec = 125.0f;
    Size spriteSize = self->aManager->spritesheet->spriteSize;
    AnimationSeq* seq = createAnimationSeq();

    Pos frame1Pos = (Pos){3, 3};
    AnimationFrame frame1 =
        (AnimationFrame){0, frame1Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err) return err;

    Pos frame2Pos = (Pos){4, 3};
    AnimationFrame frame2 =
        (AnimationFrame){1, frame2Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err) return err;

    Pos frame3Pos = (Pos){5, 3};
    AnimationFrame frame3 =
        (AnimationFrame){2, frame3Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err) return err;

    Pos frame4Pos = (Pos){6, 3};
    AnimationFrame frame4 =
        (AnimationFrame){3, frame4Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame4);
    if (err) return err;

    Pos frame5Pos = (Pos){7, 3};
    AnimationFrame frame5 =
        (AnimationFrame){4, frame5Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame5);
    if (err) return err;

    Pos frame6Pos = (Pos){8, 3};
    AnimationFrame frame6 =
        (AnimationFrame){5, frame6Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame6);
    if (err) return err;

    Pos frame7Pos = (Pos){9, 3};
    AnimationFrame frame7 =
        (AnimationFrame){6, frame7Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame7);
    if (err) return err;

    Pos frame8Pos = (Pos){10, 3};
    AnimationFrame frame8 =
        (AnimationFrame){7, frame8Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame8);
    if (err) return err;

    seq->currentFrameIdx = 0;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating the moving South/East
 * animation sequence for the player.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequence was successfully created
 */
Error* createPlayerMoveSouthEastAnim(Player* self) {
    Error* err = NULL;
    Uint32 eigthSec = 125.0f;
    Size spriteSize = self->aManager->spritesheet->spriteSize;
    AnimationSeq* seq = createAnimationSeq();

    Pos frame1Pos = (Pos){3, 1};
    AnimationFrame frame1 =
        (AnimationFrame){0, frame1Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err) return err;

    Pos frame2Pos = (Pos){4, 1};
    AnimationFrame frame2 =
        (AnimationFrame){1, frame2Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err) return err;

    Pos frame3Pos = (Pos){5, 1};
    AnimationFrame frame3 =
        (AnimationFrame){2, frame3Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err) return err;

    Pos frame4Pos = (Pos){6, 1};
    AnimationFrame frame4 =
        (AnimationFrame){3, frame4Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame4);
    if (err) return err;

    Pos frame5Pos = (Pos){7, 1};
    AnimationFrame frame5 =
        (AnimationFrame){4, frame5Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame5);
    if (err) return err;

    Pos frame6Pos = (Pos){8, 1};
    AnimationFrame frame6 =
        (AnimationFrame){5, frame6Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame6);
    if (err) return err;

    Pos frame7Pos = (Pos){9, 1};
    AnimationFrame frame7 =
        (AnimationFrame){6, frame7Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame7);
    if (err) return err;

    Pos frame8Pos = (Pos){10, 1};
    AnimationFrame frame8 =
        (AnimationFrame){7, frame8Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame8);
    if (err) return err;

    seq->currentFrameIdx = 0;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating the moving South/West
 * animation sequence for the player.
 *
 * @param self : Player struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequence was successfully created
 */
Error* createPlayerMoveSouthWestAnim(Player* self) {
    Error* err = NULL;
    Uint32 eigthSec = 125.0f;
    Size spriteSize = self->aManager->spritesheet->spriteSize;
    AnimationSeq* seq = createAnimationSeq();

    Pos frame1Pos = (Pos){3, 2};
    AnimationFrame frame1 =
        (AnimationFrame){0, frame1Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err) return err;

    Pos frame2Pos = (Pos){4, 2};
    AnimationFrame frame2 =
        (AnimationFrame){1, frame2Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err) return err;

    Pos frame3Pos = (Pos){5, 2};
    AnimationFrame frame3 =
        (AnimationFrame){2, frame3Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err) return err;

    Pos frame4Pos = (Pos){6, 2};
    AnimationFrame frame4 =
        (AnimationFrame){3, frame4Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame4);
    if (err) return err;

    Pos frame5Pos = (Pos){7, 2};
    AnimationFrame frame5 =
        (AnimationFrame){4, frame5Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame5);
    if (err) return err;

    Pos frame6Pos = (Pos){8, 2};
    AnimationFrame frame6 =
        (AnimationFrame){5, frame6Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame6);
    if (err) return err;

    Pos frame7Pos = (Pos){9, 2};
    AnimationFrame frame7 =
        (AnimationFrame){6, frame7Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame7);
    if (err) return err;

    Pos frame8Pos = (Pos){10, 2};
    AnimationFrame frame8 =
        (AnimationFrame){7, frame8Pos, eigthSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame8);
    if (err) return err;

    seq->currentFrameIdx = 0;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}
