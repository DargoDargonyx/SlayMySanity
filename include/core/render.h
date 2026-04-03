/**
 * @file render.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for rendering the game.
 */

#ifndef RENDER_H
#define RENDER_H

#include "core/ui/widget.h"
#include "util/error.h"
#include "util/window.h"

#include <SDL2/SDL.h>

#define SCENE_TYPE_START_MENU 1

#define SCENE_BTN_INIT_CAP 15

typedef struct Scene Scene;
struct Scene {
    int type;
    void (*destroy)(Scene* scene);
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

Error initStartMenuScene(WindowManager* wManager, StartMenuScene* scene);
Error destroyStartMenuScene(Scene* self);

Error addBtnToStartMenuScene(StartMenuScene* scene, Button* btn);

#endif
