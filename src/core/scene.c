/**
 * @file scene.c
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for scenes.
 */

#include "core/scene.h"
#include "core/engine.h"
#include "core/ui/widget.h"
#include "util/error.h"
#include "util/window.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
Error addBtnToScene(Scene* scene, Button* btn) {
    if (!scene)
        return createError(ESTAT_SCENE_ADD_BTN,
                           "Could not add a Button to a NULL scene");
    if (!btn)
        return createError(ESTAT_SCENE_ADD_BTN,
                           "Could not add a NULL button to a scene");

    if (scene->btnCount == scene->btnCap) {
        scene->btnCap = (scene->btnCount + 1) * 2;
        Button** orig = scene->btns;
        Button** temp = (Button**) calloc(scene->btnCap, sizeof(Button*));
        if (!temp)
            return createError(
                ESTAT_SCENE_ADD_BTN,
                "Could not reallocate a larger Button array field");

        for (int i = 0; i < scene->btnCount; i++) {
            temp[i] = orig[i];
        }
        free(orig);
        scene->btns = temp;
    }

    scene->btns[scene->btnCount] = btn;
    scene->btnCount++;
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/04/26
 * @brief Handles the logic for creating a StartMenuScene struct.
 *
 * @note The void pointer is passed so that there are no errors for
 * overlapping includes
 * @param wManager : void pointer
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param w : integer
 * @param h : integer
 * @return An Error struct that describes whether or not the
 * StartMenuScene struct in question was successfully created
 */
StartMenuScene* createStartMenuScene(void* wManager,
                                     ErrorContainer* errContainer,
                                     SDL_Renderer* renderer, int w, int h) {

    StartMenuScene* scene = (StartMenuScene*) malloc(sizeof(StartMenuScene));
    scene->base.type = SCENE_TYPE_START_MENU;
    scene->base.destroy = destroyStartMenuScene;
    scene->base.btnCount = 0;
    scene->base.btnCap = SCENE_BTN_INIT_CAP;
    scene->base.btns = (Button**) calloc(scene->base.btnCap, sizeof(Button*));

    scene->base.w = w;
    scene->base.h = h;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(F_JETBRAINS_MONO, 36, white);
    int menuButtonSpriteNum = 3;

    // Background
    SDL_Surface* bgSurface = IMG_Load("../assets/sprites/start_menu/bgImg.png");
    if (!bgSurface)
        addErrorToContainer(
            errContainer,
            createError(ESTAT_RENDER_LOAD_IMG,
                        "Failed to load start menu background image"));
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->base.bgTexture = bgTexture;

    // Start Button
    const char* sbImgPath = "../assets/sprites/start_menu/MainButton.png";
    const char* sbText = "Start Game";
    int sbVertSpacing = -35;
    TXT_Button* sButton =
        createTxtButton(errContainer, renderer, sbImgPath, scene->base.w / 2,
                        (scene->base.h / 2) + sbVertSpacing,
                        menuButtonSpriteNum, sbText, &font);
    sButton->base.onClick = testStartButton;
    addBtnToScene(&scene->base, (Button*) sButton);

    // Options Button
    const char* obImgPath = "../assets/sprites/start_menu/MainButton.png";
    const char* obText = "Options";
    int obVertSpacing = 65;
    TXT_Button* oButton =
        createTxtButton(errContainer, renderer, obImgPath, scene->base.w / 2,
                        (scene->base.h / 2) + obVertSpacing,
                        menuButtonSpriteNum, obText, &font);
    oButton->base.onClick = loadOptionsMenuScene;
    oButton->base.userData = wManager;
    addBtnToScene(&scene->base, (Button*) oButton);

    // Exit Button
    const char* exitImgPath = "../assets/sprites/start_menu/MainButton.png";
    const char* exitText = "Exit";
    int exitVertSpacing = 165;
    TXT_Button* exitButton =
        createTxtButton(errContainer, renderer, exitImgPath, scene->base.w / 2,
                        (scene->base.h / 2) + exitVertSpacing,
                        menuButtonSpriteNum, exitText, &font);
    exitButton->base.onClick = exitGameLoop;
    exitButton->base.userData = wManager;
    addBtnToScene(&scene->base, (Button*) exitButton);

    return scene;
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
        return createError(ESTAT_SCENE_DESTROY,
                           "Could not destroy a NULL scene");

    Error err = createError(ESTAT_MAIN_NONE, NULL);
    StartMenuScene* scene = (StartMenuScene*) self;
    SDL_DestroyTexture(scene->base.bgTexture);

    for (int i = 0; i < scene->base.btnCount; i++) {
        err = scene->base.btns[i]->destroy(scene->base.btns[i]);
        if (err.statusNum != ESTAT_MAIN_NONE)
            return err;
    }

    free(scene->base.btns);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/04/26
 * @brief Handles the logic for creating an OptionsMenuScene struct.
 *
 * @note The void pointer is passed so that there are no errors for
 * overlapping includes
 * @param wManager : void pointer
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param w : integer
 * @param h : integer
 * @return An Error struct that describes whether or not the
 * OptionsMenuScene struct in question was successfully created
 */
OptionsMenuScene* createOptionsMenuScene(void* wManager,
                                         ErrorContainer* errContainer,
                                         SDL_Renderer* renderer, int w, int h) {

    OptionsMenuScene* scene =
        (OptionsMenuScene*) malloc(sizeof(OptionsMenuScene));
    scene->base.type = SCENE_TYPE_OPTIONS_MENU;
    scene->base.destroy = destroyOptionsMenuScene;
    scene->base.btnCount = 0;
    scene->base.btnCap = SCENE_BTN_INIT_CAP;
    scene->base.btns = (Button**) calloc(scene->base.btnCap, sizeof(Button*));

    scene->base.w = w;
    scene->base.h = h;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(F_JETBRAINS_MONO, 36, white);
    int menuButtonSpriteNum = 3;

    // Background
    SDL_Surface* bgSurface =
        IMG_Load("../assets/sprites/options_menu/bgImg.png");
    if (!bgSurface)
        addErrorToContainer(
            errContainer,
            createError(ESTAT_RENDER_LOAD_IMG,
                        "Failed to load start menu background image"));
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->base.bgTexture = bgTexture;

    // Return button
    const char* retButtonImgPath =
        "../assets/sprites/options_menu/MainButton.png";
    const char* retText = "Return";
    TXT_Button* retButton = createTxtButton(
        errContainer, renderer, retButtonImgPath, scene->base.w / 2,
        scene->base.h / 2, menuButtonSpriteNum, retText, &font);
    retButton->base.onClick = loadStartMenuScene;
    retButton->base.userData = wManager;
    addBtnToScene(&scene->base, (Button*) retButton);

    return scene;
}

/**
 * @author DargoDargonyx
 * @date 04/04/26
 * @brief Handles the logic for destroying an OptionsMenuScene struct.
 *
 * @param self : Scene struct pointer
 * @return An Error struct that describes whether or not the
 * OptionsMenuScene struct in question was successfully destroyed
 */
Error destroyOptionsMenuScene(Scene* self) {
    if (!self)
        return createError(ESTAT_SCENE_DESTROY,
                           "Could not destroy a NULL scene");

    Error err = createError(ESTAT_MAIN_NONE, NULL);
    StartMenuScene* scene = (StartMenuScene*) self;
    SDL_DestroyTexture(scene->base.bgTexture);

    for (int i = 0; i < scene->base.btnCount; i++) {
        err = scene->base.btns[i]->destroy(scene->base.btns[i]);
        if (err.statusNum != ESTAT_MAIN_NONE)
            return err;
    }

    free(scene->base.btns);
    return err;
}
