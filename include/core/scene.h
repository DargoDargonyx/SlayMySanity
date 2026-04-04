/**
 * @file scene.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for scenes.
 */

#ifndef SCENE_H
#define SCENE_H

#include "core/ui/widget.h"
#include "util/error.h"
#include <SDL2/SDL.h>

#define SCENE_TYPE_NONE 0
#define SCENE_TYPE_START_MENU 1

#define SCENE_BTN_INIT_CAP 15

typedef struct Scene Scene;
struct Scene {
    int type;
    Error (*destroy)(Scene* scene);
    int w;
    int h;
    SDL_Texture* bgTexture;
    ErrorContainer* errContainer;
    int btnCount;
    int btnCap;
    Button** btns;
};

typedef struct {
    Scene base;
} StartMenuScene;

Error destroyStartMenuScene(Scene* self);

Error addBtnToScene(Scene* scene, Button* btn);

#endif
