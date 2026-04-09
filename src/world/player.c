/**
 * @file player.c
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for the main player.
 */

#include "world/player.h"
#include "graphics/animation.h"
#include "util/error.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for creating a Player struct.
 *
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param spritesheetPath : c-style string literal
 * @param origPos : PosFloat struct
 * @param speed : float
 * @return A pointer to a newly created Player struct
 */
Player* createPlayer(ErrorContainer* errContainer, SDL_Renderer* renderer,
                     const char* spritesheetPath, PosFloat origPos,
                     float speed) {

    Player* player = (Player*) malloc(sizeof(Player));
    player->aManager =
        createAnimationManager(errContainer, renderer, spritesheetPath);
    player->aManager->currentState = PLAYER_IDLE;
    player->worldPos = origPos;
    player->speed = speed;
    return player;
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for destroying a Player struct.
 *
 * @param self : Player struct pointer
 * @return An Error struct describing whether or not the Player
 * struct in question was successfully destroyed
 */
Error destroyPlayer(Player* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    if (!self)
        return createError(ESTAT_PLAYER_DESTROY,
                           "Could not destroy a NULL Player struct");
    err = destroyAnimationManager(self->aManager);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for calculating the pixel size
 * of a Player struct using a given spritesheet.
 *
 * @param self : Player struct pointer
 * @param frameCount : integer
 * @return An Error struct that describes whether or not the
 * pixel size of the Player struct in question was successfully
 * calculated
 */
Error calculatePlayerSize(Player* self, int frameCount) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    self->aManager->spriteRect.w = self->aManager->textureSize.w;
    self->aManager->spriteRect.h =
        (int) (self->aManager->textureSize.h / frameCount);

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for setting up the player animation
 * sequences for the first time.
 *
 * @param self : Player struct pointer
 * @return An Error struct that describes whether or not the
 * animation sequences were successfully setup
 */
Error setupPlayerAnimation(Player* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    err = createPlayerIdleAnimation(self);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    err = createPlayerWalkLeftAnimation(self);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    err = createPlayerWalkRightAnimation(self);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    err = createPlayerWalkUpAnimation(self);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    err = createPlayerWalkDownAnimation(self);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    self->aManager->currentSeq = self->aManager->seq[ANIM_PLAYER_IDLE_ORDER];

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for creating the Idle animation
 * sequence for the player.
 *
 * @param self : Player struct pointer
 * @return An Error struct that describes whether or not the
 * animation sequence was successfully created
 */
Error createPlayerIdleAnimation(Player* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    Uint32 quarterSec = 250.0f;
    Size spriteSize =
        (Size){self->aManager->spriteRect.w, self->aManager->spriteRect.h};
    AnimationSeq* seq = createAnimationSeq();

    AnimationFrame frame1 =
        (AnimationFrame){0, 0, quarterSec + 100.0f, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame2 =
        (AnimationFrame){1, 1, quarterSec + 100.0f, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame3 =
        (AnimationFrame){2, 2, quarterSec - 50.0f, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    seq->currentFrame = frame1;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for creating the WalkLeft animation
 * sequence for the player.
 *
 * @param self : Player struct pointer
 * @return An Error struct that describes whether or not the
 * animation sequence was successfully created
 */
Error createPlayerWalkLeftAnimation(Player* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    Uint32 quarterSec = 250.0f;
    Size spriteSize =
        (Size){self->aManager->spriteRect.w, self->aManager->spriteRect.h};
    AnimationSeq* seq = createAnimationSeq();

    AnimationFrame frame1 = (AnimationFrame){0, 0, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame2 = (AnimationFrame){1, 1, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame3 = (AnimationFrame){2, 2, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    seq->currentFrame = frame1;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for creating the WalkRight animation
 * sequence for the player.
 *
 * @param self : Player struct pointer
 * @return An Error struct that describes whether or not the
 * animation sequence was successfully created
 */
Error createPlayerWalkRightAnimation(Player* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    Uint32 quarterSec = 250.0f;
    Size spriteSize =
        (Size){self->aManager->spriteRect.w, self->aManager->spriteRect.h};
    AnimationSeq* seq = createAnimationSeq();

    AnimationFrame frame1 = (AnimationFrame){0, 0, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame2 = (AnimationFrame){1, 1, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame3 = (AnimationFrame){2, 2, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    seq->currentFrame = frame1;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for creating the WalkUp animation
 * sequence for the player.
 *
 * @param self : Player struct pointer
 * @return An Error struct that describes whether or not the
 * animation sequence was successfully created
 */
Error createPlayerWalkUpAnimation(Player* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    Uint32 quarterSec = 250.0f;
    Size spriteSize =
        (Size){self->aManager->spriteRect.w, self->aManager->spriteRect.h};
    AnimationSeq* seq = createAnimationSeq();

    AnimationFrame frame1 = (AnimationFrame){0, 0, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame2 = (AnimationFrame){1, 1, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame3 = (AnimationFrame){2, 2, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    seq->currentFrame = frame1;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for creating the WalkDown animation
 * sequence for the player.
 *
 * @param self : Player struct pointer
 * @return An Error struct that describes whether or not the
 * animation sequence was successfully created
 */
Error createPlayerWalkDownAnimation(Player* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    Uint32 quarterSec = 250.0f;
    Size spriteSize =
        (Size){self->aManager->spriteRect.w, self->aManager->spriteRect.h};
    AnimationSeq* seq = createAnimationSeq();

    AnimationFrame frame1 = (AnimationFrame){0, 0, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame1);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame2 = (AnimationFrame){1, 1, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame2);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;
    AnimationFrame frame3 = (AnimationFrame){2, 2, quarterSec, spriteSize};
    err = addFrameToAnimationSeq(seq, frame3);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    seq->currentFrame = frame1;
    err = addSeqToAnimationManager(self->aManager, seq);
    return err;
}
