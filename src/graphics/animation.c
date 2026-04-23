/**
 * @file animaion.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for animations.
 */

#include "graphics/animation.h"
#include "graphics/sprite.h"
#include "util/error.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

/**
 * @author DargoDargonyx
 * @date 04/17/2026
 * @brief Handles the logic for creating a new AnimationSeq struct.
 *
 * @return A pointer to a newly created AnimationSeq struct
 */
AnimationSeq* createAnimationSeq() {
    AnimationSeq* seq = (AnimationSeq*) malloc(sizeof(AnimationSeq));
    seq->frameCount = 0;
    seq->frameCap = ANIM_SEQ_FRAMES_INIT_CAP;
    seq->frames = (AnimationFrame*) calloc(seq->frameCap, sizeof(AnimationFrame));
    seq->lastTime = 0;

    return seq;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying an AnimationSeq struct.
 *
 * @param self : AnimationSeq struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the AnimationSeq struct in question was successfully
 * destroyed
 */
Error* destroyAnimationSeq(AnimationSeq* self) {
    free(self->frames);
    free(self);
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying an AnimationSeq struct.
 *
 * @param seq : AnimationSeq struct pointer
 * @param frame : AnimationFrame struct
 * @return A pointer to an Error struct that describes whether
 * or not the AnimationFrame struct was successfully added to
 * the AnimationSeq struct
 */
Error* addFrameToAnimationSeq(AnimationSeq* seq, AnimationFrame frame) {
    if (!seq)
        return createError(ANIMATION,
                           "Could not add an Animation Frame to a NULL Animation Sequence");

    if (seq->frameCount == seq->frameCap) {
        seq->frameCap = (seq->frameCount + 1) * 2;
        AnimationFrame* orig = seq->frames;
        AnimationFrame* temp = (AnimationFrame*) calloc(seq->frameCap, sizeof(AnimationFrame));
        if (!temp)
            return createError(ANIMATION,
                               "Could not reallocate a larger Animation Frame array field");

        for (int i = 0; i < seq->frameCount; i++) { temp[i] = orig[i]; }
        free(orig);
        seq->frames = temp;
    }

    seq->frames[seq->frameCount++] = frame;
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for iterating the current AnimationFrame
 * in an AnimationSeq.
 *
 * @param seq : AnimationSeq struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the current AnimationFrame in the AnimationSeq and
 * SDL_Rect was successfully iterated
 */
Error* iterateSeq(AnimationSeq* seq) {
    if (!seq)
        return createError(ANIMATION, "Could not iterate the animation frame for a NULL "
                                      "AnimationSeq struct");
    if (seq->frameCount == 0)
        return createError(ANIMATION, "Could not iterate the animation frames for an "
                                      "empty AnimationSeq struct");
    if (seq->currentFrameIdx >= seq->frameCount)
        return createError(ANIMATION,
                           "Current animation frame has an order greater than the animation "
                           "frame count for the animation sequence");

    if (seq->currentFrameIdx == seq->frameCount - 1) seq->currentFrameIdx = 0;
    else seq->currentFrameIdx++;

    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for updating the rendered frame for
 * an AnimationSeq, and updating a src SDL_Rect to be rendered.
 *
 * @param aManager : AnimationManager struct pointer
 * @param src : SDL_Rect pointer
 * @return A pointer to an Error struct that describes whether
 * or not the AnimationSeq and SDL_Rect was successfully updated
 */
Error* animateSeq(AnimationManager* aManager, SDL_Rect* src) {
    if (!aManager)
        return createError(ANIMATION, "Could not animate with a NULL AnimationManager struct");
    if (!aManager->spritesheet->texture)
        return createError(ANIMATION, "Could not animate with a NULL spritesheet texture");
    if (aManager->seqCount == 0)
        return createError(ANIMATION, "Could not animate without any animation sequences");

    Error* err = NULL;
    Uint32 now = SDL_GetTicks();
    double timeGap = (now - aManager->currentSeq->lastTime);

    AnimationSeq* currentSeq = aManager->currentSeq;
    AnimationFrame currentFrame = currentSeq->frames[currentSeq->currentFrameIdx];
    if (timeGap >= currentFrame.length) {
        err = iterateSeq(aManager->currentSeq);
        if (err) return err;
        aManager->currentSeq->lastTime = now;
    }
    if (currentFrame.length == 0)
        return createError(ANIMATION, "Could not render an animation frame with 0 length");

    src->w = currentFrame.size.w;
    src->h = currentFrame.size.h;
    src->x = currentFrame.spritePos.x * src->w;
    src->y = currentFrame.spritePos.y * src->h;

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for switching the current animation
 * sequence for an AnimationManager struct.
 *
 * @param aManager : AnimationManager struct pointer
 * @param animationOrder : integer
 * @return A pointer to an Error struct that describes whether
 * or not the animation sequence was able to successfully be
 * switched
 */
Error* switchAnimationSeq(AnimationManager* aManager, int animationOrder) {
    aManager->currentSeq = aManager->seq[animationOrder];
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/17/2026
 * @brief Handles the logic for creating a new AnimationManager struct.
 *
 * @param spritesheet : Spritesheet struct pointer
 * @return A pointer to a newly created AnimationManager struct
 */
AnimationManager* createAnimationManager(Spritesheet* spritesheet) {

    AnimationManager* manager = (AnimationManager*) malloc(sizeof(AnimationManager));

    manager->spritesheet = spritesheet;
    manager->seqCount = 0;
    manager->seqCap = ANIM_MANAGER_SEQ_INIT_CAP;
    manager->seq = (AnimationSeq**) calloc(manager->seqCap, sizeof(AnimationSeq*));

    return manager;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying an AnimationManager struct.
 *
 * @param self : AnimationManager struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the AnimationManager struct in question was successfully
 * destroyed
 */
Error* destroyAnimationManager(AnimationManager* self) {
    Error* err = NULL;
    for (int i = 0; i < self->seqCount; i++) {
        err = destroyAnimationSeq(self->seq[i]);
        if (err) return err;
    }
    free(self->seq);

    destroySpritesheet(self->spritesheet);
    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for adding an AnimationSeq struct
 * to an AnimationManager struct.
 *
 * @param manager : AnimationManager struct pointer
 * @param seq : AnimationSeq struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the AnimationSeq struct was successfully added to the
 * AnimationManager struct
 */
Error* addSeqToAnimationManager(AnimationManager* manager, AnimationSeq* seq) {
    if (!manager)
        return createError(ANIMATION,
                           "Could not add an Animation Sequence to a NULL Animation Manager");

    if (manager->seqCount == manager->seqCap) {
        manager->seqCap = (manager->seqCount + 1) * 2;
        AnimationSeq** orig = manager->seq;
        AnimationSeq** temp = (AnimationSeq**) calloc(manager->seqCap, sizeof(AnimationSeq*));
        if (!temp)
            return createError(ANIMATION,
                               "Could not reallocate a larger Animation Sequence array field");

        for (int i = 0; i < manager->seqCount; i++) { temp[i] = orig[i]; }
        free(orig);
        manager->seq = temp;
    }

    manager->seq[manager->seqCount++] = seq;
    return NULL;
}
