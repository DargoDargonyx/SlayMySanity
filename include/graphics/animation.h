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
#include <time.h>

#define ANIM_SEQ_FRAMES_INIT_CAP 15
#define ANIM_MANAGER_SEQ_INIT_CAP 7

#define ANIM_PLAYER_IDLE_ORDER 0
#define ANIM_PLAYER_LEFT_ORDER 1
#define ANIM_PLAYER_RIGHT_ORDER 2
#define ANIM_PLAYER_UP_ORDER 3
#define ANIM_PLAYER_DOWN_ORDER 4

typedef enum {
    PLAYER_IDLE,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_UP,
    PLAYER_DOWN
} AnimationState;

typedef enum {
    PLAYER_FACING_LEFT,
    PLAYER_FACING_RIGHT,
    PLAYER_FACING_UP,
    PLAYER_FACING_DOWN
} FacingDirection;

typedef struct {
    int type;
    int order;
    clock_t length;
    Size size;
} AnimationFrame;

typedef struct {
    int frameCount;
    int frameCap;
    clock_t lastTime;
    AnimationFrame currentFrame;
    AnimationFrame* frames;
} AnimationSeq;

typedef struct {
    AnimationState currentState;
    SDL_Texture* spriteTexture;
    Size textureSize;
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

AnimationManager* createAnimationManager(ErrorContainer* errContainer,
                                         SDL_Renderer* renderer,
                                         const char* spritesheetPath);
Error destroyAnimationManager(AnimationManager* self);
Error addSeqToAnimationManager(AnimationManager* manager, AnimationSeq* seq);

#endif
