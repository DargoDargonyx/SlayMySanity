/**
 * @file error.c
 * @author DargoDargonyx
 * @date 04/17/2026
 * @brief Handles the logic for error handling.
 */

#include "util/error.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for creating a new Error struct.
 *
 * @param statusNum : integer
 * @param msg : c-style string literal
 * @return The new Error struct
 */
Error createError(int statusNum, const char* msg) {
    Error err;
    err.statusNum = statusNum;
    err.msg = msg;
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/17/2026
 * @brief Gets a quick description of an error.
 *
 * This function gets a quick description of an error
 * when given an Error struct depending on the status
 * number relating to the error.
 *
 * @note Status numbers are defined in the header file.
 * @param err : Error struct pointer
 * @return The description of the error as a c-style string
 */
char* getErrorStatusDesc(Error* err) {
    static char str[63];

    switch (err->statusNum) {
        // error and main
        case ESTAT_MAIN_NONE:
            sprintf(str, "Null Error");
            break;
        case ESTAT_MAIN_LOAD:
            sprintf(str, "Main Function Load Error");
            break;
        case ESTAT_ERR_CONTAINER_CREATE:
            sprintf(str, "Error Container Creation Error");
            break;
        case ESTAT_ERR_CONTAINER_DESTROY:
            sprintf(str, "Error Container Destruction Error");
            break;
        case ESTAT_ERR_CONTAINER_ADD:
            sprintf(str, "Error Container Addition Error");
            break;
        // animation
        case ESTAT_ANIM_SEQ_ADD_FRAME:
            sprintf(str, "Animation Sequence Addition Error");
            break;
        case ESTAT_ANIM_MANAGER_ADD_SEQ:
            sprintf(str, "Animation Manager Addition Error");
            break;
        case ESTAT_ANIM_LOAD_IMG:
            sprintf(str, "Animation Image Loading Error");
            break;
        case ESTAT_ANIM_ANIMATE_SEQ:
            sprintf(str, "Animation Sequence Animation Error");
            break;
        case ESTAT_ANIM_ITERATE_FRAME:
            sprintf(str, "Animation Sequence Iteration Error");
            break;
        // window
        case ESTAT_WINDOW_INIT:
            sprintf(str, "Window Initialization Error");
            break;
        case ESTAT_WINDOW_MANAGER_CREATE:
            sprintf(str, "Window Manager Creation Error");
            break;
        case ESTAT_WINDOW_MANAGER_DESTROY:
            sprintf(str, "Window Manager Destruction Error");
            break;
        case ESTAT_WINDOW_SCENE_CLEAR:
            sprintf(str, "Window Manager Scene Clearing Error");
            break;
        // engine
        case ESTAT_ENGINE_START_LOOP:
            sprintf(str, "Game Loop Error");
            break;
        // render
        case ESTAT_RENDER_LOAD_IMG:
            sprintf(str, "Image Asset Loading Error");
            break;
        case ESTAT_RENDER_SCENE_DRAW:
            sprintf(str, "Scene Drawing Error");
            break;
        case ESTAT_RENDER_BTN_SPRITE:
            sprintf(str, "Button Sprite Rendering Error");
            break;
        case ESTAT_RENDER_PLAYER_SPRITE:
            sprintf(str, "Player Sprite Rendering Error");
            break;
        // scene
        case ESTAT_SCENE_CREATE:
            sprintf(str, "Scene Creation Error");
            break;
        case ESTAT_SCENE_DESTROY:
            sprintf(str, "Scene Destruction Error");
            break;
        case ESTAT_SCENE_ADD_BTN:
            sprintf(str, "Scene Button Addition Error");
            break;
        // font
        case ESTAT_FONT_CREATE:
            sprintf(str, "Font Creation Error");
            break;
        case ESTAT_FONT_DESTROY:
            sprintf(str, "Font Destruction Error");
            break;
        // widget
        case ESTAT_WIDGET_BTN_CREATE:
            sprintf(str, "Button Creation Error");
            break;
        case ESTAT_WIDGET_BTN_DESTROY:
            sprintf(str, "Button Destruction Error");
            break;
        // camera
        case ESTAT_CAM_REFRESH:
            sprintf(str, "Camera Refreshing Error");
            break;
        case ESTAT_SPRITE_LOAD_IMG:
            sprintf(str, "Sprite Image File Loading Error");
            break;
        // player
        case ESTAT_PLAYER_CREATE:
            sprintf(str, "Player Creation Error");
            break;
        case ESTAT_PLAYER_DESTROY:
            sprintf(str, "Player Destruction Error");
            break;
        case ESTAT_PLAYER_ANIM:
            sprintf(str, "Player Animation Error");
            break;
        default:
            break;
    }
    return str;
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for creating a new Error
 * Container struct.
 *
 * @return A pointer to the newly created ErrorContainer struct
 */
ErrorContainer* createErrorContainer() {
    ErrorContainer* container =
        (ErrorContainer*) malloc(sizeof(ErrorContainer));

    container->errCount = 0;
    container->errCap = ERR_CONTAINER_INIT_CAP;
    container->errs = (Error*) calloc(container->errCap, sizeof(Error));
    return container;
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for destroying an ErrorContainer struct.
 *
 * @return An Error struct that describes whether or not the
 * ErrorContainer struct in question was successfully destroyed
 */
Error destroyErrorContainer(ErrorContainer* self) {
    if (!self)
        return createError(ESTAT_ERR_CONTAINER_DESTROY,
                           "Couldn't destroy a NULL Error Container");

    free(self->errs);
    free(self);
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for adding an Error struct to an
 * Error Container struct.
 *
 * @return An Error struct that describes whether or not the
 * Error struct was successfully added to the ErrorContainer struct.
 */
Error addErrorToContainer(ErrorContainer* container, Error err) {
    if (!container)
        return createError(ESTAT_ERR_CONTAINER_ADD,
                           "Could not add an Error to a NULL Error Container");

    if (container->errCount == container->errCap) {
        container->errCap = (container->errCount + 1) * 2;
        Error* orig = container->errs;
        Error* temp = (Error*) calloc(container->errCap, sizeof(Error));
        if (!temp)
            return createError(
                ESTAT_ERR_CONTAINER_ADD,
                "Could not reallocate a larger Error array field");

        for (int i = 0; i < container->errCount; i++) { temp[i] = orig[i]; }
        free(orig);
        container->errs = temp;
    }

    container->errs[container->errCount++] = err;
    return createError(ESTAT_MAIN_NONE, NULL);
}
