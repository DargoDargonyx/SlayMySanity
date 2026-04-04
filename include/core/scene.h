/**
 * @file scene.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for scenes.
 */

#ifndef SCENE_H
#define SCENE_H

#include "core/ui/widget.h"
#include "util/error.h"

#include <SDL2/SDL.h>

#define SCENE_TYPE_START_MENU 1
#define SCENE_TYPE_OPTIONS_MENU 2

#define SCENE_BTN_INIT_CAP 15

typedef struct Scene Scene;
struct Scene {
    int type;
    Error (*destroy)(Scene* scene);
    int w;
    int h;
    SDL_Texture* bgTexture;
    int btnCount;
    int btnCap;
    Button** btns;
};

typedef struct {
    Scene base;
} StartMenuScene;

typedef struct {
    Scene base;
} OptionsMenuScene;

Error addBtnToScene(Scene* scene, Button* btn);

StartMenuScene* createStartMenuScene(void* wManager,
                                     ErrorContainer* errContainer,
                                     SDL_Renderer* renderer, int w, int h);
Error destroyStartMenuScene(Scene* self);

OptionsMenuScene* createOptionsMenuScene(void* wManager,
                                         ErrorContainer* errContainer,
                                         SDL_Renderer* renderer, int w, int h);
Error destroyOptionsMenuScene(Scene* self);

#endif
