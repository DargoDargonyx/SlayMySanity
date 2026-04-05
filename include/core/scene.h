/**
 * @file scene.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for scenes.
 */

#ifndef SCENE_H
#define SCENE_H

#include "graphics/camera.h"
#include "ui/widget.h"
#include "util/error.h"
#include "util/helper.h"
#include "world/map.h"

#include <SDL2/SDL.h>

typedef enum { START_MENU, OPTIONS_MENU, PLAY } SceneType;

#define SCENE_BTN_INIT_CAP 15

typedef struct Scene Scene;
struct Scene {
    SceneType type;
    Error (*destroy)(Scene* self);
    Size size;
    int btnCount;
    int btnCap;
    Button** btns;
};

typedef struct {
    Scene base;
    SDL_Texture* bgTexture;
} StartMenuScene;

typedef struct {
    Scene base;
    SDL_Texture* bgTexture;
} OptionsMenuScene;

typedef struct {
    Scene base;
    Cam* cam;
    Map* map;
} PlayScene;

Error addBtnToScene(Scene* scene, Button* btn);

StartMenuScene* createStartMenuScene(void* wManager,
                                     ErrorContainer* errContainer,
                                     SDL_Renderer* renderer, Size size);
Error destroyStartMenuScene(Scene* self);

OptionsMenuScene* createOptionsMenuScene(void* wManager,
                                         ErrorContainer* errContainer,
                                         SDL_Renderer* renderer, Size size);
Error destroyOptionsMenuScene(Scene* self);

PlayScene* createPlayScene(void* wManager, ErrorContainer* errContainer,
                           SDL_Renderer* renderer, Size size);
Error destroyPlayScene(Scene* self);

#endif
