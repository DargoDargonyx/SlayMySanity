/**
 * @file render.c
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for rendering the game.
 */

#include "graphics/render.h"
#include "core/scene.h"
#include "ui/ui.h"
#include "util/error.h"
#include "util/helper.h"
#include "world/physics.h"

#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/21/2026
 * @brief Handles the logic for determining the ucrrent scene and drawing
 * it draw the current scene.
 *
 * @param wManager : WindowManager struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the scene was successfully drawn
 */
Error* drawCurrentScene(WindowManager* wManager) {
    Error* err = NULL;
    switch (wManager->currentScene->type) {
        case MENU:
            err = drawMenuScene(wManager->renderer, (MenuScene*) wManager->currentScene);
            break;
        case PLAY:
            err = drawPlayScene(wManager->renderer, (PlayScene*) wManager->currentScene);
            break;
        default:
            err = createError(RENDER, "Could not draw a scene with an unknown type");
            break;
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for drawing all the widgets inside of
 * a UIManager struct.
 *
 * @param renderer : SDL_Renderer pointer
 * @param uManager : UIManager struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the button sprite in question was successfully drawn
 */
Error* drawWidgets(SDL_Renderer* renderer, UIManager* uManager) {
    if (!renderer) return createError(RENDER, "Could not draw widgets for a NULL SDL_Renderer");
    if (!uManager) return createError(RENDER, "Could not draw widgets for a NULL UIManager");
    Error* err = NULL;
    for (int i = 0; i < uManager->widgetCount; i++) {
        Widget* widget = uManager->widgets[i];
        switch (widget->type) {
            case TXT_BOX:
                err = drawTxtBox(renderer, (TxtBox*) widget);
                break;
            case BUTTON:
                err = drawButton(renderer, (Button*) widget);
                break;
            default:
                err = createError(RENDER, "Could not draw a widget with an unknown type");
                break;
        }
        if (err) return err;
    }
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for drawing the sprite for a text box.
 *
 * @param renderer : SDL_Renderer pointer
 * @param txtBox : TxtBox struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the text box sprite in question was successfully drawn
 */
Error* drawTxtBox(SDL_Renderer* renderer, TxtBox* txtBox) {
    if (!renderer) return createError(RENDER, "Could not draw a text box with a NULL SDL_Renderer");
    if (!txtBox) return createError(RENDER, "Could not draw a NULL text box");

    int txtW, txtH;
    SDL_QueryTexture(txtBox->texture, NULL, NULL, &txtW, &txtH);
    SDL_Rect txtDest;
    txtDest.x = txtBox->outer.x + (txtBox->outer.w - txtW) / 2;
    txtDest.y = txtBox->outer.y + (txtBox->outer.h - txtH) / 2;
    txtDest.w = txtW;
    txtDest.h = txtH;
    SDL_RenderCopy(renderer, txtBox->texture, NULL, &txtDest);

    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for drawing the sprite for a button.
 *
 * @param renderer : SDL_Renderer pointer
 * @param btn : Button struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the button sprite in question was successfully drawn
 */
Error* drawButton(SDL_Renderer* renderer, Button* btn) {
    if (!renderer) return createError(RENDER, "Could not draw a button with a NULL SDL_Renderer");
    if (!btn) return createError(RENDER, "Could not draw a NULL button");

    SDL_Rect src = {0, 0, btn->rect.w, btn->rect.h};

    switch (btn->currentState) {
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
    SDL_RenderCopy(renderer, btn->aManager->spritesheet->texture, &src, &btn->rect);

    Error* err = NULL;
    if (btn->txtBox) err = drawTxtBox(renderer, btn->txtBox);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for drawing a Menu Scene.
 *
 * @param renderer : SDL_Renderer pointer
 * @param scene : MenuScene struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Menu Scene in question was successfully drawn
 */
Error* drawMenuScene(SDL_Renderer* renderer, MenuScene* scene) {
    if (!renderer)
        return createError(RENDER, "Could not draw a Menu Scene with a NULL SDL_Renderer");
    if (!scene)
        return createError(RENDER, "Could not draw a Menu Scene with a NULL StartMenuScene struct");
    Error* err = NULL;
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, scene->bgTexture, NULL, NULL);
    err = drawWidgets(renderer, scene->base.uiManager);

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for drawing the Playing Scene.
 *
 * @param renderer : SDL_Renderer pointer
 * @param scene : PlayScene struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Playing Scene in question was successfully drawn
 */
Error* drawPlayScene(SDL_Renderer* renderer, PlayScene* scene) {
    if (!renderer)
        return createError(RENDER, "Could not draw the Playing Scene with a NULL SDL_Renderer");
    if (!scene)
        return createError(RENDER, "Could not draw the Playing Scene with a NULL PlayScene struct");
    Error* err = NULL;
    SDL_RenderClear(renderer);

    err = drawMap(renderer, scene->cam, scene->map);
    if (err) return err;
    err = drawWidgets(renderer, scene->base.uiManager);
    if (err) return err;
    err = drawPlayer(renderer, scene->cam);
    if (err) return err;

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/21/2026
 * @brief Handles the logic for drawing a map in the playing scene.
 *
 * @param renderer : SDL_Renderer pointer
 * @param cam : Cam struct pointer
 * @param map : Map struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the button sprite was successfully rendered
 */
Error* drawMap(SDL_Renderer* renderer, Cam* cam, Map* map) {
    if (!renderer) return createError(RENDER, "Could not draw a map with a NULL SDL_Renderer");
    if (!cam) return createError(RENDER, "Could not draw a map with a NULL camera");
    if (!map) return createError(RENDER, "Could not draw a NULL map");

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
 * @date 04/21/2026
 * @brief Handles the logic for drawing the sprite for the player.
 *
 * @param renderer : SDL_Renderer pointer
 * @param cam : Cam struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the player sprite was successfully drawn
 */
Error* drawPlayer(SDL_Renderer* renderer, Cam* cam) {
    if (!renderer) return createError(RENDER, "Could not draw a player with a NULL SDL_Renderer");
    if (!cam) return createError(RENDER, "Could not draw a player with a NULL camera");
    if (!cam->player) return createError(RENDER, "Could not draw a NULL player");
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
