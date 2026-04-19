/**
 * @file animaion.h
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Handles the logic for animations.
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include "graphics/sprite.h"
#include "util/error.h"
#include "util/helper.h"

#define ANIM_SEQ_FRAMES_INIT_CAP 15
#define ANIM_MANAGER_SEQ_INIT_CAP 7

#define ANIM_PLAYER_EAST_IDLE_ORDER 0
#define ANIM_PLAYER_WEST_IDLE_ORDER 1
#define ANIM_PLAYER_NORTH_EAST_ORDER 2
#define ANIM_PLAYER_NORTH_WEST_ORDER 3
#define ANIM_PLAYER_SOUTH_EAST_ORDER 4
#define ANIM_PLAYER_SOUTH_WEST_ORDER 5

typedef struct {
    int order;
    Pos spritePos;
    Uint32 length;
    Size size;
} AnimationFrame;

typedef struct {
    int frameCount;
    int frameCap;
    int currentFrameIdx;
    AnimationFrame* frames;
    Uint32 lastTime;
} AnimationSeq;

typedef struct {
    Spritesheet* spritesheet;
    SDL_Rect spriteRect;
    int seqCount;
    int seqCap;
    AnimationSeq** seq;
    AnimationSeq* currentSeq;
} AnimationManager;

AnimationSeq* createAnimationSeq();
Error destroyAnimationSeq(AnimationSeq* self);
Error addFrameToAnimationSeq(AnimationSeq* seq, AnimationFrame frame);

Error iterateSeq(AnimationSeq* seq);
Error animateSeq(AnimationManager* aManager, SDL_Rect* src);
Error switchAnimationSeq(AnimationManager* aManager, int animationOrder);

AnimationManager* createAnimationManager(Spritesheet* spritesheet);
Error destroyAnimationManager(AnimationManager* self);
Error addSeqToAnimationManager(AnimationManager* manager, AnimationSeq* seq);

#endif
