/**
 * @file animaion.c
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for animations.
 */

#include "graphics/animation.h"
#include "util/error.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for creating a new AnimationSeq struct.
 *
 * @return A pointer to a newly created AnimationSeq struct
 */
AnimationSeq* createAnimationSeq() {
    AnimationSeq* seq = (AnimationSeq*) malloc(sizeof(AnimationSeq));
    seq->frameCount = 0;
    seq->frameCap = ANIM_SEQ_FRAMES_INIT_CAP;
    seq->frames =
        (AnimationFrame*) calloc(seq->frameCap, sizeof(AnimationFrame));

    return seq;
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for destroying an AnimationSeq struct.
 *
 * @param self : AnimationSeq struct pointer
 * @return An Error struct that describes whether or not the
 * AnimationSeq struct in question was successfully destroyed
 */
Error destroyAnimationSeq(AnimationSeq* self) {
    free(self->frames);
    free(self);
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for destroying an AnimationSeq struct.
 *
 * @param seq : AnimationSeq struct pointer
 * @param frame : AnimationFrame struct
 * @return An Error struct that describes whether or not
 * the AnimationFrame struct was successfully added to the
 * AnimationSeq struct
 */
Error addFrameToAnimationSeq(AnimationSeq* seq, AnimationFrame frame) {
    if (!seq)
        return createError(
            ESTAT_ANIM_SEQ_ADD_FRAME,
            "Could not add an Animation Frame to a NULL Animation Sequence");

    if (seq->frameCount == seq->frameCap) {
        seq->frameCap = (seq->frameCount + 1) * 2;
        AnimationFrame* orig = seq->frames;
        AnimationFrame* temp =
            (AnimationFrame*) calloc(seq->frameCap, sizeof(AnimationFrame));
        if (!temp)
            return createError(
                ESTAT_ANIM_SEQ_ADD_FRAME,
                "Could not reallocate a larger Animation Frame array field");

        for (int i = 0; i < seq->frameCount; i++) { temp[i] = orig[i]; }
        free(orig);
        seq->frames = temp;
    }

    seq->frames[seq->frameCount++] = frame;
    return createError(ESTAT_MAIN_NONE, NULL);
}

AnimationManager* createAnimationManager(ErrorContainer* errContainer,
                                         SDL_Renderer* renderer,
                                         const char* spritesheetPath) {

    AnimationManager* manager =
        (AnimationManager*) malloc(sizeof(AnimationManager));

    SDL_Surface* surface = IMG_Load(spritesheetPath);
    if (!surface) {
        addErrorToContainer(
            errContainer,
            createError(ESTAT_ANIM_LOAD_IMG,
                        "Could not load a sritesheet image file"));
    } else {
        manager->spriteTexture =
            SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    manager->seqCount = 0;
    manager->seqCap = ANIM_MANAGER_SEQ_INIT_CAP;
    manager->seq =
        (AnimationSeq**) calloc(manager->seqCap, sizeof(AnimationSeq*));

    return manager;
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for destroying an AnimationManager struct.
 *
 * @param self : AnimationManager struct pointer
 * @return An Error struct that describes whether or not the
 * AnimationManager struct in question was successfully destroyed
 */
Error destroyAnimationManager(AnimationManager* self) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    for (int i = 0; i < self->seqCount; i++) {
        err = destroyAnimationSeq(self->seq[i]);
        if (err.statusNum != ESTAT_MAIN_NONE) return err;
    }
    free(self->seq);

    SDL_DestroyTexture(self->spriteTexture);
    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for adding an AnimationSeq struct
 * to an AnimationManager struct.
 *
 * @param manager : AnimationManager struct pointer
 * @param seq : AnimationSeq struct pointer
 * @return An Error struct that describes whether or not the
 * AnimationSeq struct was successfully added to the
 * AnimationManager struct
 */
Error addSeqToAnimationManager(AnimationManager* manager, AnimationSeq* seq) {
    if (!manager)
        return createError(
            ESTAT_ANIM_MANAGER_ADD_SEQ,
            "Could not add an Animation Sequence to a NULL Animation Manager");

    if (manager->seqCount == manager->seqCap) {
        manager->seqCap = (manager->seqCount + 1) * 2;
        AnimationSeq** orig = manager->seq;
        AnimationSeq** temp =
            (AnimationSeq**) calloc(manager->seqCap, sizeof(AnimationSeq*));
        if (!temp)
            return createError(
                ESTAT_ANIM_MANAGER_ADD_SEQ,
                "Could not reallocate a larger Animation Sequence array field");

        for (int i = 0; i < manager->seqCount; i++) { temp[i] = orig[i]; }
        free(orig);
        manager->seq = temp;
    }

    manager->seq[manager->seqCount++] = seq;
    return createError(ESTAT_MAIN_NONE, NULL);
}
