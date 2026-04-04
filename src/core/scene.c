/**
 * @file scene.c
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for scenes.
 */

#include "core/scene.h"
#include "core/ui/widget.h"
#include "util/error.h"

#include <SDL2/SDL.h>

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

    err = destroyErrorContainer(scene->base.errContainer);
    if (err.statusNum != ESTAT_MAIN_NONE)
        return err;
    for (int i = 0; i < scene->base.btnCount; i++) {
        err = scene->base.btns[i]->destroy(scene->base.btns[i]);
        return err;
    }

    free(scene->base.btns);
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
