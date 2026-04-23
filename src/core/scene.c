/**
 * @file scene.c
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for scenes.
 */

#include "core/scene.h"
#include "graphics/camera.h"
#include "ui/ui.h"
#include "util/error.h"
#include "util/window.h"
#include "world/map.h"
#include "world/physics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/21/26
 * @brief Handles the logic for creating a MenuScene struct.
 *
 * @param pixelSize : Size struct
 * @return A pointer to a newly created MenuScene struct
 */
MenuScene* createMenuScene(Size pixelSize) {
    MenuScene* scene = (MenuScene*) malloc(sizeof(MenuScene));
    scene->base.type = MENU;
    scene->base.destroy = destroyMenuScene;
    scene->base.uManager = createUIManager();
    scene->base.pixelSize = pixelSize;

    return scene;
}

/**
 * @author DargoDargonyx
 * @date 04/21/26
 * @brief Handles the logic for destroying a MenuScene struct.
 *
 * @param self : Scene struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the MenuScene struct in question was successfully
 * destroyed
 */
Error* destroyMenuScene(Scene* self) {
    if (!self) return createError(SCENE, "Could not destroy a NULL scene");

    Error* err = destroyUIManager(self->uManager);
    MenuScene* scene = (MenuScene*) self;
    SDL_DestroyTexture(scene->bgTexture);

    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/21/26
 * @brief Handles the logic for initializing a MenuScene struct
 * for the Start Menu.
 *
 * @param errCont : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param pixelSize : Size struct
 * @param loader : SceneLoader struct pointer
 * @return A pointer to the newly created StartMenuScene in question
 */
MenuScene* initStartMenuScene(ErrorContainer* errCont, SDL_Renderer* renderer, Size pixelSize,
                              SceneLoader* loader) {

    Error* err = NULL;
    if (!renderer) {
        err = createError(SCENE, "Could not initialize the Start Menu with a NULL SDL_Renderer");
        addErrorToContainer(errCont, err);
        return NULL;
    } else if (!loader) {
        err = createError(SCENE, "Could not initialize the Start Menu with a NULL SceneLoader");
    }

    MenuScene* scene = createMenuScene(pixelSize);
    err = createStartMenuUI(scene->base.uManager, loader, renderer, scene->base.pixelSize);
    if (err) {
        addErrorToContainer(errCont, err);
        return scene;
    }

    // Background
    SDL_Surface* bgSurface = IMG_Load("../assets/sprites/ui/start_menu/bg_img.png");
    if (!bgSurface) {
        err = createError(RENDER, "Could not load the background image for the Start Menu");
        addErrorToContainer(errCont, err);
        return scene;
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->bgTexture = bgTexture;

    return scene;
}

/**
 * @author DargoDargonyx
 * @date 04/21/2026
 * @brief Helper function to handle loading the start menu.
 *
 * @note The window manager is passed as a void pointer because
 * this function is usually called from the scene.c file where
 * window is not within scope.
 *
 * @param wManager : void pointer (Acts like a WindowManager struct pointer)
 */
void loadStartMenuScene(void* wManager) {
    WindowManager* manager = (WindowManager*) wManager;
    clearCurrentScene(manager);
    manager->currentScene = (Scene*) initStartMenuScene(
        manager->errCont, manager->renderer, manager->wSize, (SceneLoader*) manager->sceneLoader);
}

/**
 * @author DargoDargonyx
 * @date 04/21/26
 * @brief Handles the logic for creating an OptionsMenuScene struct.
 *
 * @note The void pointer is passed so that there are no errors for
 * overlapping includes
 *
 * @param errCont : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param pixelSize : Size struct
 * @param loader : SceneLoader struct pointer
 * @return A pointer to the newly created OptionsMenuScene in question
 */
MenuScene* initOptionsMenuScene(ErrorContainer* errCont, SDL_Renderer* renderer, Size pixelSize,
                                SceneLoader* loader) {

    Error* err = NULL;
    if (!renderer) {
        err = createError(SCENE, "Could not initialize the Options Menu with a NULL SDL_Renderer");
        addErrorToContainer(errCont, err);
        return NULL;
    } else if (!loader) {
        err = createError(SCENE, "Could not initialize the Options Menu with a NULL SceneLoader");
        addErrorToContainer(errCont, err);
        return NULL;
    }

    MenuScene* scene = createMenuScene(pixelSize);
    err = createOptionsMenuUI(scene->base.uManager, loader, renderer, scene->base.pixelSize);
    if (err) {
        addErrorToContainer(errCont, err);
        return scene;
    }

    // Background
    SDL_Surface* bgSurface = IMG_Load("../assets/sprites/ui/options_menu/bg_img.png");
    if (!bgSurface) {
        err = createError(SCENE, "Could not load the background image for the Options Menu ");
        addErrorToContainer(errCont, err);
        return scene;
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->bgTexture = bgTexture;

    return scene;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Helper function to handle loading the main options menu.
 *
 * @note The window manager is passed as a void pointer because
 * this function is usually called from the scene.c file where
 * window is not within scope.
 *
 * @param wManager : void pointer
 */
void loadOptionsMenuScene(void* wManager) {
    WindowManager* manager = (WindowManager*) wManager;
    clearCurrentScene(manager);
    manager->currentScene = (Scene*) initOptionsMenuScene(
        manager->errCont, manager->renderer, manager->wSize, (SceneLoader*) manager->sceneLoader);
}

/**
 * @author DargoDargonyx
 * @date 04/21/26
 * @brief Handles the logic for creating a PlayScene struct.
 *
 * @note The void pointer is passed so that there are no errors for
 * overlapping includes
 *
 * @param errCont : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param pixelSize : Size struct
 * @param loader : SceneLoader struct pointer
 * @return A pointer to the newly created PlayScene in question
 */
PlayScene* createPlayScene(ErrorContainer* errCont, SDL_Renderer* renderer, Size pixelSize,
                           SceneLoader* loader) {

    Error* err = NULL;
    if (!renderer) {
        err = createError(SCENE, "Could not create the Play Scene with a NULL SDL_Renderer");
        addErrorToContainer(errCont, err);
        return NULL;
    } else if (!loader) {
        err = createError(SCENE, "Could not create the Play Scene with a NULL SceneLoader");
        addErrorToContainer(errCont, err);
        return NULL;
    }

    PlayScene* scene = (PlayScene*) malloc(sizeof(PlayScene));
    scene->base.type = PLAY;
    scene->base.destroy = destroyPlayScene;
    scene->base.uManager = createUIManager();
    scene->base.pixelSize = pixelSize;

    err = createPlaySceneUI(scene->base.uManager, loader, renderer, scene->base.pixelSize);
    if (err) {
        addErrorToContainer(errCont, err);
        return scene;
    }

    // map
    scene->map = createTestMap(errCont, renderer);
    if (errCont->count > 0) return scene;

    // Player
    const char* playerSpritesheetPath = "../assets/sprites/player/testing_player_spritesheet.png";
    Coord initPlayerCoord;
    initPlayerCoord.x = scene->map->worldSize.w / 2.0f;
    initPlayerCoord.y = scene->map->worldSize.h / 2.0f;
    float initPlayerSpeed = 1.0f;
    scene->player =
        createPlayer(errCont, renderer, playerSpritesheetPath, initPlayerCoord, initPlayerSpeed);
    if (errCont->count > 0) return scene;

    err = initPlayerAnimation(scene->player);
    if (err) {
        addErrorToContainer(errCont, err);
        return scene;
    }

    // Camera
    scene->cam = createCamera(initPlayerCoord, scene->base.pixelSize, 2.0f);
    err = addPlayerToCamera(scene->cam, scene->player);
    if (err) {
        addErrorToContainer(errCont, err);
        return scene;
    }

    return scene;
}

/**
 * @author DargoDargonyx
 * @date 04/20/26
 * @brief Handles the logic for destroying an PlayScene struct.
 *
 * @param self : Scene struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the PlayScene struct in question was successfully
 * destroyed
 */
Error* destroyPlayScene(Scene* self) {
    if (!self) return createError(SCENE, "Could not destroy a NULL scene");

    Error* err = destroyUIManager(self->uManager);
    PlayScene* scene = (PlayScene*) self;
    err = destroyCamera(scene->cam);
    if (err) return err;
    err = destroyMap(scene->map);

    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Helper function to handle loading the playing scene.
 *
 * @note The window manager is passed as a void pointer because
 * this function is usually called from the scene.c file where
 * window is not within scope.
 *
 * @param wManager : void pointer
 */
void loadPlayScene(void* wManager) {
    WindowManager* manager = (WindowManager*) wManager;
    clearCurrentScene(manager);
    manager->currentScene = (Scene*) createPlayScene(
        manager->errCont, manager->renderer, manager->wSize, (SceneLoader*) manager->sceneLoader);
}
