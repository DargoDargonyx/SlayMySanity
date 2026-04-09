/**
 * @file render.c
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for rendering the game.
 */

#include "graphics/render.h"
#include "core/scene.h"
#include "ui/widget.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Intermediary helper function to draw the current scene.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct that describes whether or not the
 * scene was successfully drawn
 */
Error drawCurrentScene(WindowManager* wManager) {
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
            return createError(ESTAT_RENDER_SCENE_DRAW,
                               "Could not draw an uknown scene");
            break;
    }
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
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
    SDL_RenderCopy(wManager->renderer, scene->bgTexture, NULL, NULL);

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err.statusNum != ESTAT_MAIN_NONE) return err;

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
 * @date 04/05/2026
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
    SDL_RenderCopy(wManager->renderer, scene->bgTexture, NULL, NULL);

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err.statusNum != ESTAT_MAIN_NONE) return err;

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
 * @date 04/09/2026
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
    err = drawMap(wManager->renderer, scene->cam, scene->map);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        err = renderBtnSprite(wManager->renderer, btn);
        if (err.statusNum != ESTAT_MAIN_NONE) return err;

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

    err = renderPlayerSprite(wManager->renderer, scene->cam, wManager->wSize);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for drawing a map in the playing scene.
 *
 * @param renderer : SDL_Renderer pointer
 * @param cam : Cam struct pointer
 * @param map : Map struct pointer
 * @return An Error struct that describes whether or not the
 * button sprite was successfully rendered
 */
Error drawMap(SDL_Renderer* renderer, Cam* cam, Map* map) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    int tileWidth = map->tileset->tileSize.w;
    int tileHeight = map->tileset->tileSize.h;

    int startCol = (int) cam->worldPos.x;
    int endCol = (int) (cam->worldPos.x + cam->worldSize.w);
    int startRow = (int) cam->worldPos.y;
    int endRow = (int) (cam->worldPos.y + cam->worldSize.h);

    endCol += 1;
    endRow += 1;

    if (startCol < 0) startCol = 0;
    if (startRow < 0) startRow = 0;
    if (endCol > map->size.w) endCol = map->size.w;
    if (endRow > map->size.h) endRow = map->size.h;

    for (int row = startRow; row <= endRow; row++) {
        for (int col = startCol; col <= endCol; col++) {
            Pos pixelPos;
            pixelPos.x = col * tileWidth;
            pixelPos.y = row * tileHeight;
            int index = (row * map->size.w) + col;
            int tileId = map->tiles[index];
            err = drawTile(renderer, cam, map->tileset, tileId, pixelPos);
            if (err.statusNum != ESTAT_MAIN_NONE) return err;
        }
    }

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for drawing a tile in the playing scene
 * when given a tileset, tileId, and position.
 *
 * @param renderer : SDL_Renderer pointer
 * @param cam : Cam struct pointer
 * @param tileset : Tileset struct pointer
 * @param id : integer
 * @param pixelPos : Pos struct
 * @return An Error struct that describes whether or not the
 * button sprite was successfully rendered
 */
Error drawTile(SDL_Renderer* renderer, Cam* cam, Tileset* tileset, int id,
               Pos pixelPos) {

    SDL_Rect tile;
    tile.x = (id % tileset->sheetSize.w) * tileset->tileSize.w;
    tile.y = (id / tileset->sheetSize.w) * tileset->tileSize.h;
    tile.w = tileset->tileSize.w;
    tile.h = tileset->tileSize.h;

    SDL_Rect dst;
    dst.x = (int) ((pixelPos.x - cam->pixelPos.x) * cam->zoom);
    dst.y = (int) ((pixelPos.y - cam->pixelPos.y) * cam->zoom);
    dst.w = (int) (tile.w * cam->zoom);
    dst.h = (int) (tile.h * cam->zoom);

    SDL_RenderCopy(renderer, tileset->texture, &tile, &dst);
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for rendering the sprite for a button.
 *
 * @param renderer : SDL_Renderer pointer
 * @param btn : Button struct pointer
 * @return An Error struct that describes whether or not the
 * button sprite in question was successfully rendered
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

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for rendering the sprite for the player.
 *
 * @param renderer : SDL_Renderer pointer
 * @param player : Player struct pointer
 * @param screenSize : Size struct
 * @return An Error struct that describes whether or not the
 * player sprite was successfully rendered
 */
Error renderPlayerSprite(SDL_Renderer* renderer, Cam* cam, Size screenSize) {

    Error err = createError(ESTAT_MAIN_NONE, NULL);
    SDL_Rect src = {0, 0, cam->player->aManager->textureSize.w,
                    cam->player->aManager->textureSize.h};

    int currentSeqIdx;
    switch (cam->player->aManager->currentState) {
        case PLAYER_IDLE:
            currentSeqIdx = ANIM_PLAYER_IDLE_ORDER;
            break;
        case PLAYER_LEFT:
            currentSeqIdx = ANIM_PLAYER_LEFT_ORDER;
            break;
        case PLAYER_RIGHT:
            currentSeqIdx = ANIM_PLAYER_RIGHT_ORDER;
            break;
        case PLAYER_UP:
            currentSeqIdx = ANIM_PLAYER_UP_ORDER;
            break;
        case PLAYER_DOWN:
            currentSeqIdx = ANIM_PLAYER_DOWN_ORDER;
            break;
        default:
            return createError(ESTAT_RENDER_PLAYER_SPRITE,
                               "Unknown player animation state");
            break;
    }

    if (cam->player->aManager->seqCount <= currentSeqIdx) {
        return createError(
            ESTAT_RENDER_PLAYER_SPRITE,
            "Could not access an animation sequence that hasn't been defined");
    }

    cam->player->aManager->currentSeq =
        cam->player->aManager->seq[currentSeqIdx];
    err = animateSeq(cam->player->aManager, &src);
    if (err.statusNum != ESTAT_MAIN_NONE) return err;

    // @TODO get rid of magic number
    SDL_Rect dst;
    dst.x =
        ((screenSize.w / 2) - (src.w / 2)) - 32; // magic number here for now
    dst.y = ((screenSize.h / 2) - (src.h / 2)) - 32;
    dst.w = (int) (src.w * cam->zoom);
    dst.h = (int) (src.h * cam->zoom);

    SDL_RenderCopy(renderer, cam->player->aManager->spriteTexture, &src, &dst);
    return err;
}
