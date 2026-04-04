/**
 * @file render.c
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for rendering the game.
 */

#include "core/render.h"
#include "core/engine.h"
#include "core/scene.h"
#include "core/ui/font.h"
#include "core/ui/widget.h"
#include "util/error.h"

#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/03/26
 * @brief Handles the logic for initializing a StartMenuScene struct.
 *
 * @note The intention for the use of this function is to create
 * an empty struct elsewhere and pass a reference to it through
 * this function in order to initialize it.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : StartMenuScene struct pointer
 * @return An Error struct that describes whether or not the
 * StartMenuScene struct in question was successfully initialized
 */
Error initStartMenuScene(WindowManager* wManager, StartMenuScene* scene) {
    scene->base.type = SCENE_TYPE_START_MENU;
    scene->base.destroy = destroyStartMenuScene;
    scene->base.btnCount = 0;
    scene->base.btnCap = SCENE_BTN_INIT_CAP;
    scene->base.btns = (Button**) calloc(scene->base.btnCap, sizeof(Button*));

    scene->base.errContainer = createErrorContainer();
    if (!scene->base.errContainer)
        return createError(
            ESTAT_ERR_CONTAINER_CREATE,
            "Failed to create an Error Container for the Start Menu Scene");

    scene->base.w = wManager->wWidth;
    scene->base.h = wManager->wHeight;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(F_JETBRAINS_MONO, 36, white);
    int menuButtonSpriteNum = 3;

    SDL_Surface* bgSurface = IMG_Load("../assets/sprites/start_menu/bgImg.png");
    if (!bgSurface)
        return createError(ESTAT_RENDER_LOAD_IMG,
                           "Failed to load mini start menu image");
    SDL_Texture* bgTexture =
        SDL_CreateTextureFromSurface(wManager->renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->base.bgTexture = bgTexture;

    const char* sbImgPath = "../assets/sprites/start_menu/MainButton.png";
    const char* sbText = "Start Game";
    TXT_Button* sButton =
        createTxtButton(scene->base.errContainer, wManager->renderer, sbImgPath,
                        scene->base.w / 2, scene->base.h / 2,
                        menuButtonSpriteNum, sbText, &font);
    sButton->base.onClick = testStartButton;
    addBtnToScene(&scene->base, (Button*) sButton);

    const char* obImgPath = "../assets/sprites/start_menu/MainButton.png";
    const char* obText = "Options";
    int obVertSpacing = 100;
    TXT_Button* oButton =
        createTxtButton(scene->base.errContainer, wManager->renderer, obImgPath,
                        scene->base.w / 2, (scene->base.h / 2) + obVertSpacing,
                        menuButtonSpriteNum, obText, &font);
    oButton->base.onClick = testOptionButton;
    addBtnToScene(&scene->base, (Button*) oButton);

    // If an error happened along the way, return the
    // first one to occur
    if (scene->base.errContainer->errCount > 0)
        return scene->base.errContainer->errs[0];
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Intermediary helper function to draw scenes.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : StartMenuScene struct pointer
 * @return An Error struct that describes whether or not the
 * scene was successfully drawn
 */
Error drawScene(WindowManager* wManager) {
    switch (wManager->currentScene->type) {
        case SCENE_TYPE_START_MENU:
            return drawStartMenuScene(wManager,
                                      (StartMenuScene*) wManager->currentScene);
            break;
        default:
            return createError(ESTAT_RENDER_SCENE_DRAW,
                               "Could not draw a NULL scene");
            break;
    }
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for drawing the game start menu.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : StartMenuScene struct pointer
 * @return An Error struct that describes whether or not the
 * start menu was successfully drawn
 */
Error drawStartMenuScene(WindowManager* wManager, StartMenuScene* scene) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    SDL_RenderClear(wManager->renderer);
    SDL_RenderCopy(wManager->renderer, scene->base.bgTexture, NULL, NULL);

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderMainButtonSprite(wManager->renderer, btn);
        switch (btn->type) {
            case BTN_TYPE_IMG: {
                break;
            }
            case BTN_TYPE_TXT: {
                TXT_Button* txtBtn = (TXT_Button*) btn;
                int txtW, txtH;
                SDL_QueryTexture(txtBtn->txtTexture, NULL, NULL, &txtW, &txtH);
                SDL_Rect txtDest;
                txtDest.x = txtBtn->txtRect.x + (txtBtn->txtRect.w - txtW) / 2;
                txtDest.y = txtBtn->txtRect.y + (txtBtn->txtRect.h - txtH) / 2;
                txtDest.w = txtW;
                txtDest.h = txtH;
                SDL_RenderCopy(wManager->renderer, txtBtn->txtTexture, NULL,
                               &txtDest);

                break;
            }
            default:
                break;
        }
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for drawing the game start menu.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : StartMenuScene struct pointer
 * @return An Error struct that describes whether or not the
 * start menu was successfully drawn
 */
Error renderMainButtonSprite(SDL_Renderer* renderer, Button* btn) {
    SDL_Rect src = {0, 0, btn->rect.w, btn->rect.h};
    switch (btn->state) {
        case BTN_IDLE:
            src.y = 0;
            break;
        case BTN_HOVER:
            src.y = btn->rect.h;
            break;
        case BTN_PRESSED:
            src.y = 2 * btn->rect.h;
            break;
        default:
            return createError(ESTAT_RENDER_BTN_SPRITE, "Unknown button state");
            break;
    }
    SDL_RenderCopy(renderer, btn->bgTexture, &src, &btn->rect);
    return createError(ESTAT_MAIN_NONE, NULL);
}
