/**
 * @file scene.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for scenes.
 */

#ifndef SCENE_H
#define SCENE_H

#include "graphics/camera.h"
#include "ui/widget.h"
#include "util/error.h"
#include "util/helper.h"
#include "world/map.h"
#include "world/player.h"

#include <SDL2/SDL.h>

typedef enum { START_MENU, OPTIONS_MENU, PLAY } SceneType;

#define SCENE_BTN_INIT_CAP 15

typedef struct Scene Scene;
struct Scene {
    SceneType type;
    Error* (*destroy)(Scene* self);
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
    Player* player;
    Map* map;
} PlayScene;

Error* addBtnToScene(Scene*, Button*);

StartMenuScene* createStartMenuScene(void*, ErrorContainer*, SDL_Renderer*,
                                     Size);
Error* destroyStartMenuScene(Scene*);

OptionsMenuScene* createOptionsMenuScene(void*, ErrorContainer*, SDL_Renderer*,
                                         Size);
Error* destroyOptionsMenuScene(Scene*);

PlayScene* createPlayScene(void*, ErrorContainer*, SDL_Renderer*, Size);
Error* destroyPlayScene(Scene*);

#endif
