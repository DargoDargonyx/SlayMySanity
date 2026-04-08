/**
 * @file animaion.h
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for animations.
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

#define ANIM_SEQ_FRAMES_INIT_CAP 15
#define ANIM_MANAGER_SEQ_INIT_CAP 7

typedef struct {
    int type;
    float length;
    Size size;
} AnimationFrame;

typedef struct {
    int frameCount;
    int frameCap;
    AnimationFrame* frames;
} AnimationSeq;

typedef struct {
    SDL_Texture* spriteTexture;
    int seqCount;
    int seqCap;
    AnimationSeq** seq;
} AnimationManager;

AnimationSeq* createAnimationSeq();
Error destroyAnimationSeq(AnimationSeq* self);
Error addFrameToAnimationSeq(AnimationSeq* seq, AnimationFrame frame);

AnimationManager* createAnimationManager(ErrorContainer* errContainer,
                                         SDL_Renderer* renderer,
                                         const char* spritesheetPath);
Error destroyAnimationManager(AnimationManager* self);
Error addSeqToAnimationManager(AnimationManager* manager, AnimationSeq* seq);

#endif
