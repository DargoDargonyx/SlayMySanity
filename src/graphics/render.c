/**
 * @file render.c
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for rendering the game.
 */

#include "graphics/render.h"
#include "core/scene.h"
#include "ui/widget.h"
#include "util/error.h"
#include "world/physics.h"

#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/04/2026
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
        case SCENE_TYPE_OPTIONS_MENU:
            return drawOptionsMenuScene(
                wManager, (OptionsMenuScene*) wManager->currentScene);
        case SCENE_TYPE_PLAY:
            return drawPlayScene(wManager, (PlayScene*) wManager->currentScene);
        default:
            return createError(ESTAT_RENDER_SCENE_DRAW,
                               "Could not draw an uknown scene");
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
        err = renderBtnSprite(wManager->renderer, btn);
        if (err.statusNum != ESTAT_MAIN_NONE)
            return err;

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
 * @date 04/04/2026
 * @brief Handles the logic for drawing the options menu.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : OptionsMenuScene struct pointer
 * @return An Error struct that describes whether or not the
 * options menu was successfully drawn
 */
Error drawOptionsMenuScene(WindowManager* wManager, OptionsMenuScene* scene) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    SDL_RenderClear(wManager->renderer);
    SDL_RenderCopy(wManager->renderer, scene->base.bgTexture, NULL, NULL);

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err.statusNum != ESTAT_MAIN_NONE)
            return err;

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
 * @date 04/04/2026
 * @brief Handles the logic for drawing the playing scene.
 *
 * @param wManager : WindowManager struct pointer
 * @param scene : PlayScene struct pointer
 * @return An Error struct that describes whether or not the
 * playing scene was successfully drawn
 */
Error drawPlayScene(WindowManager* wManager, PlayScene* scene) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    SDL_RenderClear(wManager->renderer);
    SDL_RenderCopy(wManager->renderer, scene->base.bgTexture, NULL, NULL);
    err = drawMap(wManager->renderer, scene->map);
    if (err.statusNum != ESTAT_MAIN_NONE)
        return err;

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err.statusNum != ESTAT_MAIN_NONE)
            return err;

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
 * @date 04/04/2026
 * @brief Handles the logic for drawing a map in the playing scene.
 *
 * @param renderer : SDL_Renderer pointer
 * @param map : Map struct pointer
 * @return An Error struct that describes whether or not the
 * button sprite was successfully rendered
 */
Error drawMap(SDL_Renderer* renderer, Map* map) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    for (int y = 0; y < map->h; y++) {
        for (int x = 0; x < map->w; x++) {
            int sX = (int) (x * map->tileset->tW * SCALE);
            int sY = (int) (y * map->tileset->tH * SCALE);
            int index = (y * map->w) + x;
            int tileId = map->tiles[index];
            err = drawTile(renderer, map->tileset, tileId, (Pos){sX, sY});
            if (err.statusNum != ESTAT_MAIN_NONE)
                return err;
        }
    }

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for drawing a tile in the playing scene
 * when given a tileset, tileId, and position.
 *
 * @param renderer : SDL_Renderer pointer
 * @param tileset : Tileset struct pointer
 * @param id : integer
 * @param pos : Pos struct
 * @return An Error struct that describes whether or not the
 * button sprite was successfully rendered
 */
Error drawTile(SDL_Renderer* renderer, Tileset* tileset, int id, Pos pos) {
    SDL_Rect tile;
    tile.x = (id % tileset->cols) * tileset->tW;
    tile.y = (id / tileset->cols) * tileset->tH;
    tile.w = tileset->tW;
    tile.h = tileset->tH;

    SDL_Rect dst = {pos.x, pos.y, tile.w * SCALE, tile.h * SCALE};
    SDL_RenderCopy(renderer, tileset->texture, &tile, &dst);
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for rendering the sprite for a button.
 *
 * @param renderer : SDL_Renderer pointer
 * @param btn : Button struct pointer
 * @return An Error struct that describes whether or not the
 * button sprite was successfully rendered
 */
Error renderBtnSprite(SDL_Renderer* renderer, Button* btn) {
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
