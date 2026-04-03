/**
 * @file engine.c
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for the game engine.
 */

#include "core/engine.h"
#include "core/render.h"
#include "core/ui/widget.h"

#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/03/26
 * @brief Handles the logic for running the main game loop.
 *
 * @param wManager : WindowManager struct pointer
 * @return An Error struct that describes whether or not the
 * game loop ran successfully
 */
Error runGameLoop(WindowManager* wManager) {
    SDL_Event event;
    int running = 1;

    Error err;
    StartMenuScene startMenuScene;
    err = initStartMenuScene(wManager, &startMenuScene);
    if (err.statusNum != ESTAT_MAIN_NONE) {
        destroyStartMenuScene((Scene*) &startMenuScene);
        return err;
    }

    while (running) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                running = 0;

        err = drawStartMenu(wManager, &startMenuScene);
        if (err.statusNum != ESTAT_MAIN_NONE) {
            IMG_Quit();
            return err;
        }
        SDL_RenderPresent(wManager->renderer);
    }

    destroyStartMenuScene((Scene*) &startMenuScene);
    IMG_Quit();
    return createError(ESTAT_MAIN_NONE, NULL);
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
Error drawStartMenu(WindowManager* wManager, StartMenuScene* scene) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    SDL_RenderClear(wManager->renderer);
    SDL_RenderCopy(wManager->renderer, scene->base.bgTexture, NULL, NULL);

    for (int i = 0; i < scene->base.btnCount; i++) {
        Button* btn = scene->base.btns[i];
        switch (btn->type) {
            case BTN_TYPE_IMG: {
                IMG_Button* imgBtn = (IMG_Button*) btn;
                SDL_RenderCopy(wManager->renderer, imgBtn->base.bgTexture, NULL,
                               &imgBtn->base.rect);
                break;
            }
            case BTN_TYPE_TXT: {
                TXT_Button* txtBtn = (TXT_Button*) btn;
                SDL_RenderCopy(wManager->renderer, txtBtn->base.bgTexture, NULL,
                               &txtBtn->base.rect);

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
