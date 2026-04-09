/**
 * @file camera.c
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for the scene viewing.
 */

#include "graphics/camera.h"
#include "util/error.h"
#include "world/player.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for creating a new Cam struct.
 *
 * @param worldPos : PosFloat struct
 * @param pixelSize : Size struct
 * @param zoom : float
 * @param scale : Size struct
 * @return An Error struct that describes whether or not the
 * Cam struct was successfully created
 */
Cam* createCamera(PosFloat worldPos, Size pixelSize, float zoom, Size scale) {

    Cam* cam = (Cam*) malloc(sizeof(Cam));
    cam->player = NULL;
    cam->worldPos = worldPos;
    cam->pixelPos = (Pos){
        cam->worldPos.x * scale.w,
        cam->worldPos.y * scale.h,
    };
    cam->pixelSize = pixelSize;
    cam->worldSize = (SizeFloat){cam->pixelSize.w / (float) scale.w,
                                 cam->pixelSize.h / (float) scale.h};
    cam->zoom = zoom;
    cam->scale = scale;
    return cam;
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for destroying a Cam struct.
 *
 * @param self : Cam struct pointer
 * @return An Error struct that describes whether or not the
 * Cam struct in question was successfully destroyed
 */
Error destroyCamera(Cam* self) {
    if (self->player) destroyPlayer(self->player);
    free(self);
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for adding a Player struct
 * to a Cam struct.
 *
 * @param self : Cam struct pointer
 * @param player : Player struct pointer
 * @return An Error struct that describes whether or not the
 * Player struct was successfully added to the Camera struct
 */
Error addPlayerToCamera(Cam* self, Player* player) {
    if (self->player) destroyPlayer(self->player);
    self->player = player;
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for updating the pixel position
 * of a Cam struct based on it's world position.
 *
 * @param self : Cam struct pointer
 * @return An Error struct that describes whether or not the
 * Cam struct was successfully updated
 */
Error refreshPixelPos(Cam* self) {
    if (!self)
        return createError(
            ESTAT_CAM_REFRESH,
            "Could not refresh the pixel position for a NULL camera");
    self->pixelPos = (Pos){(int) (self->worldPos.x * self->scale.w),
                           (int) (self->worldPos.y * self->scale.h)};
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for updating the world position
 * of a Cam struct based on it's pixel position.
 *
 * @param self : Cam struct pointer
 * @return An Error struct that describes whether or not the
 * Cam struct was successfully updated
 */
Error refreshWorldPos(Cam* self) {
    if (!self)
        return createError(
            ESTAT_CAM_REFRESH,
            "Could not refresh the world position for a NULL camera");
    self->worldPos = (PosFloat){(float) self->pixelPos.x / self->scale.w,
                                (float) self->pixelPos.y / self->scale.h};
    return createError(ESTAT_MAIN_NONE, NULL);
}
