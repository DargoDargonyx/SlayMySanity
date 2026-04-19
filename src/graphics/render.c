/**
 * @file render.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for rendering the game.
 */

#include "graphics/render.h"
#include "core/scene.h"
#include "ui/widget.h"
#include "util/error.h"
#include "util/helper.h"
#include "world/physics.h"

#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Intermediary helper function to draw the current scene.
 *
 * @param wManager : WindowManager struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the scene was successfully drawn
 */
Error* drawCurrentScene(WindowManager* wManager) {
    switch (wManager->currentScene->type) {
        case START_MENU:
            return drawStartMenuScene(wManager,
                                      (StartMenuScene*) wManager->currentScene);
            break;
        case OPTIONS_MENU:
            return drawOptionsMenuScene(
                wManager, (OptionsMenuScene*) wManager->currentScene);
        case PLAY:
            return drawPlayScene(wManager, (PlayScene*) wManager->currentScene);
        default:
            return createError(RENDER, "Could not draw an uknown scene");
            break;
    }
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for drawing the game start menu.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : StartMenuScene struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the start menu was successfully drawn
 */
Error* drawStartMenuScene(WindowManager* wManager, StartMenuScene* scene) {
    Error* err = NULL;
    SDL_RenderClear(wManager->renderer);
    SDL_RenderCopy(wManager->renderer, scene->bgTexture, NULL, NULL);

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err) return err;

        switch (btn->type) {
            case IMG: {
                break;
            }
            case TXT: {
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
 * @date 04/19/2026
 * @brief Handles the logic for drawing the options menu.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : OptionsMenuScene struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the options menu was successfully drawn
 */
Error* drawOptionsMenuScene(WindowManager* wManager, OptionsMenuScene* scene) {
    Error* err = NULL;
    SDL_RenderClear(wManager->renderer);
    SDL_RenderCopy(wManager->renderer, scene->bgTexture, NULL, NULL);

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err) return err;

        switch (btn->type) {
            case IMG: {
                break;
            }
            case TXT: {
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
 * @date 04/19/2026
 * @brief Handles the logic for drawing the playing scene.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : PlayScene struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the playing scene was successfully drawn
 */
Error* drawPlayScene(WindowManager* wManager, PlayScene* scene) {
    Error* err = NULL;
    if (wManager->errContainer->count > 0)
        return wManager->errContainer->errs[0];

    SDL_RenderClear(wManager->renderer);
    err = drawMap(wManager->renderer, scene->cam, scene->map);
    if (err) return err;

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err) return err;

        switch (btn->type) {
            case IMG: {
                break;
            }
            case TXT: {
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

    err = renderPlayerSprite(wManager->renderer, scene->cam);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for drawing a map in the playing scene.
 *
 * @param renderer : SDL_Renderer pointer
 * @param cam : Cam struct pointer
 * @param map : Map struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the button sprite was successfully rendered
 */
Error* drawMap(SDL_Renderer* renderer, Cam* cam, Map* map) {
    int distX = (float) cam->pixelSize.w / 2;
    int distY = (float) cam->pixelSize.h / 2;
    int startX = (int) (cam->coord.x * WORLD_COORD_WIDTH) - distX;
    int endX = (int) (cam->coord.x * WORLD_COORD_WIDTH) + distX;
    int startY = (int) (cam->coord.y * WORLD_COORD_HEIGHT) - distY;
    int endY = (int) (cam->coord.y * WORLD_COORD_HEIGHT) + distY;

    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > map->pixelSize.w) startX -= map->pixelSize.w - endX;
    if (endY > map->pixelSize.h) startY -= map->pixelSize.h - endY;

    SDL_Rect src;
    src.x = startX;
    src.y = startY;
    src.w = cam->pixelSize.w;
    src.h = cam->pixelSize.h;

    SDL_RenderCopy(renderer, map->texture, &src, NULL);
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for rendering the sprite for a button.
 *
 * @param renderer : SDL_Renderer pointer
 * @param btn : Button struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the button sprite in question was successfully rendered
 */
Error* renderBtnSprite(SDL_Renderer* renderer, Button* btn) {
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
            return createError(RENDER, "Unknown button state");
            break;
    }
    SDL_RenderCopy(renderer, btn->bgTexture, &src, &btn->rect);
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for rendering the sprite for the player.
 *
 * @param renderer : SDL_Renderer pointer
 * @param player : Player struct pointer
 * @param screenSize : Size struct
 * @return A pointer to an Error struct that describes whether
 * or not the player sprite was successfully rendered
 */
Error* renderPlayerSprite(SDL_Renderer* renderer, Cam* cam) {
    Error* err = NULL;
    AnimationManager* manager = cam->player->aManager;

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = manager->spritesheet->spriteSize.w;
    src.h = manager->spritesheet->spriteSize.h;

    err = animateSeq(manager, &src);
    if (err) return err;

    float diffX = cam->coord.x - cam->player->coord.x;
    float diffY = cam->coord.y - cam->player->coord.y;
    int distX = (int) (diffX * WORLD_COORD_WIDTH);
    int distY = (int) (diffY * WORLD_COORD_HEIGHT);

    SDL_Rect dst;
    dst.x = (cam->pixelSize.w / 2) - src.w - distX;
    dst.y = (cam->pixelSize.h / 2) - src.h - distY;
    dst.w = (int) (src.w * cam->zoom);
    dst.h = (int) (src.h * cam->zoom);

    SDL_RenderCopy(renderer, manager->spritesheet->texture, &src, &dst);
    return err;
}
