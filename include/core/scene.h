/**
 * @file scene.h
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for scenes.
 */

#ifndef SCENE_H
#define SCENE_H

#include "graphics/camera.h"
#include "ui/ui.h"
#include "util/error.h"
#include "util/helper.h"
#include "world/map.h"
#include "world/player.h"

#include <SDL2/SDL.h>

typedef enum { MENU, PLAY } SceneType;

#define SCENE_BTN_INIT_CAP 15

typedef struct Scene Scene;
struct Scene {
    SceneType type;
    Error* (*destroy)(Scene* self);
    UIManager* uManager;
    Size pixelSize;
};

typedef struct {
    Scene base;
    SDL_Texture* bgTexture;
} MenuScene;

typedef struct {
    Scene base;
    Cam* cam;
    Player* player;
    Map* map;
} PlayScene;

MenuScene* createMenuScene(Size);
Error* destroyMenuScene(Scene*);

MenuScene* initStartMenuScene(ErrorContainer*, SDL_Renderer*, Size, SceneLoader*);
void loadStartMenuScene(void*);
MenuScene* initOptionsMenuScene(ErrorContainer*, SDL_Renderer*, Size, SceneLoader*);
void loadOptionsMenuScene(void*);

PlayScene* createPlayScene(ErrorContainer*, SDL_Renderer*, Size, SceneLoader*);
Error* destroyPlayScene(Scene*);
void loadPlayScene(void*);

#endif
