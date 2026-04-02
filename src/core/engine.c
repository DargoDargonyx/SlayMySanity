/**
 * @file engine.c
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for the game engine.
 */

#include "core/engine.h"
#include "core/render.h"

#include <SDL2/SDL_image.h>


/**
 * @author DargoDargonyx
 * @date 03/25/26
 * @brief Handles teh logic for the main game loop.
 *
 * @param event : SDL_Event pointer
 * @return An Error struct describing whether or not the
 * game loop ran without issue
 */
Error runGameLoop(WindowManager* wManager) {
    SDL_Event event;
    int running = 1;
    
    Error err;
    StartMenuScene startMenuScene;
    err = createStartMenuScene(wManager, &startMenuScene);
    if (err.statusNum != ESTAT_NONE) {
        destroyStartMenuScene(&startMenuScene);
        return err;
    }

    while (running) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) running = 0;
   
        err = drawStartMenu(wManager, &startMenuScene);
        if (err.statusNum != ESTAT_NONE) {
            IMG_Quit();
            return err;
        }
        SDL_RenderPresent(wManager->renderer);
    }
    
    destroyStartMenuScene(&startMenuScene);
    IMG_Quit();
    return createError(ESTAT_NONE, NULL);
}


/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for drawing the game start menu.
 *
 * @param wManager : WindowManager struct pointer
 * @return An error struct describing whether or not the
 * menu was created without issue
 */
Error drawStartMenu(WindowManager* wManager, StartMenuScene* scene) {
    SDL_RenderClear(wManager->renderer);
    SDL_RenderCopy(wManager->renderer, scene->bgTexture, NULL, NULL);

    SDL_RenderCopy(
        wManager->renderer, 
        scene->sbTexture, 
        NULL, 
        &scene->sButton.rect
    );
    int txtW, txtH;
    SDL_QueryTexture(scene->sButton.texture, NULL, NULL, &txtW, &txtH);
    SDL_Rect sbTxtRect = {
        scene->sButton.rect.x + (scene->sButton.rect.w - txtW) / 2,
        scene->sButton.rect.y + (scene->sButton.rect.h - txtH) / 2,
        txtW,
        txtH
    };
    SDL_RenderCopy(wManager->renderer, scene->sButton.texture, NULL, &sbTxtRect);

    SDL_RenderCopy(
        wManager->renderer, 
        scene->obTexture, 
        NULL, 
        &scene->oButton.rect
    );
    int obTxtW, obTxtH;
    SDL_QueryTexture(scene->oButton.texture, NULL, NULL, &obTxtW, &obTxtH);
    SDL_Rect obTxtRect = {
        scene->oButton.rect.x + (scene->oButton.rect.w - obTxtW) / 2,
        scene->oButton.rect.y + (scene->oButton.rect.h - obTxtH) / 2,
        obTxtW,
        obTxtH
    };
    SDL_RenderCopy(wManager->renderer, scene->oButton.texture, NULL, &obTxtRect);

    return createError(ESTAT_NONE, NULL);
}
