/**
 * @file render.c
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for rendering the game.
 */

#include "core/render.h"
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
    scene->base.btnCount = 0;
    scene->base.btnCap = SCENE_BTN_INIT_CAP;

    scene->base.errContainer = createErrorContainer();
    if (!scene->base.errContainer)
        return createError(
            ESTAT_ERR_CONTAINER_CREATE,
            "Failed to create an Error Container for the Start Menu Scene");

    scene->base.w = wManager->wWidth;
    scene->base.h = wManager->wHeight;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(F_JETBRAINS_MONO, 36, white);

    SDL_Surface* bgSurface = IMG_Load("../assets/sprites/MiniStartMenu.png");
    if (!bgSurface)
        return createError(ESTAT_RENDER_LOAD_IMG,
                           "Failed to load mini start menu image");
    SDL_Texture* bgTexture =
        SDL_CreateTextureFromSurface(wManager->renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->base.bgTexture = bgTexture;

    const char* sbImgPath = "../assets/sprites/MiniStartMenu_PlayButton.png";
    const char* sbText = "Start Game";
    TXT_Button* sButton =
        createTxtButton(scene->base.errContainer, wManager->renderer, sbImgPath,
                        scene->base.w / 2, scene->base.h / 2, sbText, &font);
    addBtnToStartMenuScene(scene, (Button*) sButton);

    const char* obImgPath = "../assets/sprites/MiniStartMenu_PlayButton.png";
    const char* obText = "Options";
    int obVertSpacing = 100;
    TXT_Button* oButton = createTxtButton(
        scene->base.errContainer, wManager->renderer, obImgPath,
        scene->base.w / 2, (scene->base.h / 2) + obVertSpacing, obText, &font);
    addBtnToStartMenuScene(scene, (Button*) oButton);

    // If an error happened along the way, return the
    // first one to occur
    if (scene->base.errContainer->errCount > 0)
        return scene->base.errContainer->errs[0];
    destroyFont(&font);
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/03/26
 * @brief Handles the logic for destroying a StartMenuScene struct.
 *
 * @param self : Scene struct pointer
 * @return An Error struct that describes whether or not the
 * StartMenuScene struct in question was successfully destroyed
 */
Error destroyStartMenuScene(Scene* self) {
    if (!self)
        return createError(ESTAT_RENDER_SCENE_DESTROY,
                           "Could not destroy a NULL scene");

    Error err = createError(ESTAT_MAIN_NONE, NULL);
    StartMenuScene* scene = (StartMenuScene*) self;
    SDL_DestroyTexture(scene->base.bgTexture);

    err = destroyErrorContainer(scene->base.errContainer);
    if (err.statusNum != ESTAT_MAIN_NONE)
        return err;
    for (int i = 0; i < scene->base.btnCount; i++) {
        err = scene->base.btns[i]->destroy(scene->base.btns[i]);
        return err;
    }

    free(scene->base.btns);
    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/03/26
 * @brief Handles the logic for adding a Button struct to a
 * StartMenuScene struct.
 *
 * @param scene : StartMenuScene struct pointer
 * @param btn : Button struct pointer
 * @return An Error struct that describes whether or not the
 * Button struct was successfully added to the StartMenuScene
 */
Error addBtnToStartMenuScene(StartMenuScene* scene, Button* btn) {
    if (!scene)
        return createError(ESTAT_RENDER_SCENE_ADD_BTN,
                           "Could not add a Button to a NULL scene");
    if (!btn)
        return createError(ESTAT_RENDER_SCENE_ADD_BTN,
                           "Could not add a NULL button to a scene");

    if (scene->base.btnCount == scene->base.btnCap) {
        scene->base.btnCap = (scene->base.btnCount + 1) * 2;
        Button** orig = scene->base.btns;
        Button** temp = (Button**) calloc(scene->base.btnCap, sizeof(Button*));
        if (!temp)
            return createError(
                ESTAT_RENDER_SCENE_ADD_BTN,
                "Could not reallocate a larger Button array field");

        for (int i = 0; i < scene->base.btnCount; i++) {
            temp[i] = orig[i];
        }
        free(orig);
        scene->base.btns = temp;
    }

    scene->base.btns[scene->base.btnCount] = btn;
    scene->base.btnCount++;
    return createError(ESTAT_MAIN_NONE, NULL);
}
