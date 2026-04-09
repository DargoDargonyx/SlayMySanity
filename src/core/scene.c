/**
 * @file scene.c
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for scenes.
 */

#include "core/scene.h"
#include "core/engine.h"
#include "graphics/camera.h"
#include "ui/widget.h"
#include "util/error.h"
#include "util/window.h"
#include "world/map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/08/26
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

        for (int i = 0; i < scene->btnCount; i++) { temp[i] = orig[i]; }
        free(orig);
        scene->btns = temp;
    }

    scene->btns[scene->btnCount++] = btn;
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/05/26
 * @brief Handles the logic for creating a StartMenuScene struct.
 *
 * @note The void pointer is passed so that there are no errors for
 * overlapping includes
 *
 * @param wManager : void pointer
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param size : Size struct
 * @return An Error struct that describes whether or not the
 * StartMenuScene struct in question was successfully created
 */
StartMenuScene* createStartMenuScene(void* wManager,
                                     ErrorContainer* errContainer,
                                     SDL_Renderer* renderer, Size size) {

    Error err = createError(ESTAT_MAIN_NONE, NULL);

    StartMenuScene* scene = (StartMenuScene*) malloc(sizeof(StartMenuScene));
    scene->base.type = START_MENU;
    scene->base.destroy = destroyStartMenuScene;
    scene->base.btnCount = 0;
    scene->base.btnCap = SCENE_BTN_INIT_CAP;
    scene->base.btns = (Button**) calloc(scene->base.btnCap, sizeof(Button*));

    scene->base.size = size;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(JETBRAINS_MONO, 36, white);

    // Background
    SDL_Surface* bgSurface =
        IMG_Load("../assets/sprites/ui/start_menu/bg_img.png");
    if (!bgSurface)
        addErrorToContainer(
            errContainer,
            createError(ESTAT_RENDER_LOAD_IMG,
                        "Failed to load start menu background image"));
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->bgTexture = bgTexture;

    // Start Button
    const char* sbImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    const char* sbText = "Start Game";
    int sbVertSpacing = -35;
    Pos sbPos = {scene->base.size.w / 2,
                 (scene->base.size.h / 2) + sbVertSpacing};
    TXT_Button* sButton =
        createTxtButton(errContainer, renderer, sbImgPath, sbPos,
                        BTN_SPRITESHEET_SIZE, sbText, &font);
    sButton->base.onClick = loadPlayScene;
    sButton->base.userData = wManager;
    err = addBtnToScene(&scene->base, (Button*) sButton);
    if (err.statusNum != ESTAT_MAIN_NONE)
        addErrorToContainer(errContainer, err);

    // Options Button
    const char* obImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    const char* obText = "Options";
    int obVertSpacing = 65;
    Pos obPos = {scene->base.size.w / 2,
                 (scene->base.size.h / 2) + obVertSpacing};
    TXT_Button* oButton =
        createTxtButton(errContainer, renderer, obImgPath, obPos,
                        BTN_SPRITESHEET_SIZE, obText, &font);
    oButton->base.onClick = loadOptionsMenuScene;
    oButton->base.userData = wManager;
    err = addBtnToScene(&scene->base, (Button*) oButton);
    if (err.statusNum != ESTAT_MAIN_NONE)
        addErrorToContainer(errContainer, err);

    // Exit Button
    const char* ebImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    const char* ebText = "Exit";
    int ebVertSpacing = 165;
    Pos ebPos = {scene->base.size.w / 2,
                 (scene->base.size.h / 2) + ebVertSpacing};
    TXT_Button* exitButton =
        createTxtButton(errContainer, renderer, ebImgPath, ebPos,
                        BTN_SPRITESHEET_SIZE, ebText, &font);
    exitButton->base.onClick = exitGameLoop;
    exitButton->base.userData = wManager;
    err = addBtnToScene(&scene->base, (Button*) exitButton);
    if (err.statusNum != ESTAT_MAIN_NONE)
        addErrorToContainer(errContainer, err);

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
    SDL_DestroyTexture(scene->bgTexture);

    for (int i = 0; i < scene->base.btnCount; i++) {
        err = scene->base.btns[i]->destroy(scene->base.btns[i]);
        if (err.statusNum != ESTAT_MAIN_NONE) return err;
    }

    free(scene->base.btns);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/05/26
 * @brief Handles the logic for creating an OptionsMenuScene struct.
 *
 * @note The void pointer is passed so that there are no errors for
 * overlapping includes
 *
 * @param wManager : void pointer
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param size : Size struct
 * @return An Error struct that describes whether or not the
 * OptionsMenuScene struct in question was successfully created
 */
OptionsMenuScene* createOptionsMenuScene(void* wManager,
                                         ErrorContainer* errContainer,
                                         SDL_Renderer* renderer, Size size) {

    Error err = createError(ESTAT_MAIN_NONE, NULL);

    OptionsMenuScene* scene =
        (OptionsMenuScene*) malloc(sizeof(OptionsMenuScene));
    scene->base.type = OPTIONS_MENU;
    scene->base.destroy = destroyOptionsMenuScene;
    scene->base.btnCount = 0;
    scene->base.btnCap = SCENE_BTN_INIT_CAP;
    scene->base.btns = (Button**) calloc(scene->base.btnCap, sizeof(Button*));

    scene->base.size = size;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(JETBRAINS_MONO, 36, white);

    // Background
    SDL_Surface* bgSurface =
        IMG_Load("../assets/sprites/ui/options_menu/bg_img.png");
    if (!bgSurface)
        addErrorToContainer(
            errContainer,
            createError(ESTAT_RENDER_LOAD_IMG,
                        "Failed to load start menu background image"));
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->bgTexture = bgTexture;

    // Return button
    const char* rbImgPath = "../assets/sprites/ui/options_menu/main_button.png";
    const char* rbText = "Return";
    Pos rbPos = {scene->base.size.w / 2, scene->base.size.h / 2};
    TXT_Button* rButton =
        createTxtButton(errContainer, renderer, rbImgPath, rbPos,
                        BTN_SPRITESHEET_SIZE, rbText, &font);
    rButton->base.onClick = loadStartMenuScene;
    rButton->base.userData = wManager;
    err = addBtnToScene(&scene->base, (Button*) rButton);
    if (err.statusNum != ESTAT_MAIN_NONE)
        addErrorToContainer(errContainer, err);

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
    OptionsMenuScene* scene = (OptionsMenuScene*) self;
    SDL_DestroyTexture(scene->bgTexture);

    for (int i = 0; i < scene->base.btnCount; i++) {
        err = scene->base.btns[i]->destroy(scene->base.btns[i]);
        if (err.statusNum != ESTAT_MAIN_NONE) return err;
    }

    free(scene->base.btns);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/08/26
 * @brief Handles the logic for creating a PlayScene struct.
 *
 * @note The void pointer is passed so that there are no errors for
 * overlapping includes
 *
 * @param wManager : void pointer
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param size : Size struct
 * @return An Error struct that describes whether or not the
 * PlayScene struct in question was successfully created
 */
PlayScene* createPlayScene(void* wManager, ErrorContainer* errContainer,
                           SDL_Renderer* renderer, Size size) {

    Error err = createError(ESTAT_MAIN_NONE, NULL);

    PlayScene* scene = (PlayScene*) malloc(sizeof(PlayScene));
    scene->base.type = PLAY;
    scene->base.destroy = destroyPlayScene;
    scene->base.btnCount = 0;
    scene->base.btnCap = SCENE_BTN_INIT_CAP;
    scene->base.btns = (Button**) calloc(scene->base.btnCap, sizeof(Button*));
    scene->base.size = size;

    // map
    scene->map = createTestMap(renderer);

    // Player
    const char* playerSpritesheetPath =
        "../assets/sprites/player/player_sprite.png";
    PosFloat initPlayerPos;
    initPlayerPos.x = scene->map->size.w / 2.0f;
    initPlayerPos.y = scene->map->size.h / 2.0f;
    float initPlayerSpeed = 1.0f;
    scene->player = createPlayer(errContainer, renderer, playerSpritesheetPath,
                                 initPlayerPos, initPlayerSpeed);
    calculatePlayerSize(scene->player, 3);
    if (err.statusNum != ESTAT_MAIN_NONE) {
        addErrorToContainer(errContainer, err);
        return scene;
    }

    err = setupPlayerAnimation(scene->player);
    if (err.statusNum != ESTAT_MAIN_NONE) {
        addErrorToContainer(errContainer, err);
        return scene;
    }

    // Camera
    scene->cam = createCamera(initPlayerPos, scene->base.size, 2.0f,
                              scene->map->tileset->tileSize);
    err = addPlayerToCamera(scene->cam, scene->player);
    if (err.statusNum != ESTAT_MAIN_NONE) {
        addErrorToContainer(errContainer, err);
        return scene;
    }

    // Back button
    Pos disPos = {40, 40};
    const char* backButtonImgPath =
        "../assets/sprites/ui/play_scene/back_button.png";
    IMG_Button* backButton =
        createImgButton(errContainer, renderer, backButtonImgPath, disPos,
                        BTN_SPRITESHEET_SIZE);
    backButton->base.onClick = loadStartMenuScene;
    backButton->base.userData = wManager;
    err = addBtnToScene(&scene->base, (Button*) backButton);
    if (err.statusNum != ESTAT_MAIN_NONE)
        addErrorToContainer(errContainer, err);

    return scene;
}

/**
 * @author DargoDargonyx
 * @date 04/04/26
 * @brief Handles the logic for destroying an PlayScene struct.
 *
 * @param self : Scene struct pointer
 * @return An Error struct that describes whether or not the
 * PlayScene struct in question was successfully destroyed
 */
Error destroyPlayScene(Scene* self) {
    if (!self)
        return createError(ESTAT_SCENE_DESTROY,
                           "Could not destroy a NULL scene");

    Error err = createError(ESTAT_MAIN_NONE, NULL);
    PlayScene* scene = (PlayScene*) self;

    for (int i = 0; i < scene->base.btnCount; i++) {
        err = scene->base.btns[i]->destroy(scene->base.btns[i]);
        if (err.statusNum != ESTAT_MAIN_NONE) return err;
    }

    destroyCamera(scene->cam);
    destroyMap(scene->map);
    free(scene->base.btns);
    return err;
}
