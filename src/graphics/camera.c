/**
 * @file camera.c
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for the scene viewing.
 */

#include "graphics/camera.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for creating a new Cam struct.
 *
 * @param origPos : Pos struct
 * @param viewWidth : integer
 * @param viewHeight : integer
 * @return An Error struct that describes whether or not the
 * Cam struct was successfully created
 */
Cam* createCamera(Pos origPos, int viewWidth, int viewHeight) {
    Cam* cam = (Cam*) malloc(sizeof(Cam));
    cam->pos = origPos;
    cam->viewWidth = viewWidth;
    cam->viewHeight = viewHeight;
    return cam;
}

/**
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for destroying a Cam struct.
 *
 * @param self : Cam struct pointer
 * @return An Error struct that describes whether or not the
 * Cam struct in question was successfully destroyed
 */
Error destroyCamera(Cam* self) {
    free(self);
    return createError(ESTAT_MAIN_NONE, NULL);
}
