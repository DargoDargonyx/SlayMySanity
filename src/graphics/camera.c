/**
 * @file camera.c
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Handles the logic for the scene viewing.
 */

#include "graphics/camera.h"
#include "util/error.h"
#include "world/physics.h"
#include "world/player.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Handles the logic for creating a new Cam struct.
 *
 * @param worldPos : PosFloat struct
 * @param pixelSize : Size struct
 * @param zoom : float
 * @return An Error struct that describes whether or not the
 * Cam struct was successfully created
 */
Cam* createCamera(Coord coord, Size pixelSize, float zoom) {

    Cam* cam = (Cam*) malloc(sizeof(Cam));
    cam->scale = (Size){WORLD_COORD_WIDTH, WORLD_COORD_HEIGHT};
    cam->player = NULL;
    cam->coord = coord;
    cam->pixelPos =
        (Pos){cam->coord.x * cam->scale.w, cam->coord.y * cam->scale.h};
    cam->pixelSize = pixelSize;
    cam->worldSize = (SizeFloat){cam->pixelSize.w / (float) cam->scale.w,
                                 cam->pixelSize.h / (float) cam->scale.h};
    cam->zoom = zoom;
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
 * @date 04/17/2026
 * @brief Handles the logic for updating the pixel position
 * of a Cam struct based on it's world position.
 *
 * @param self : Cam struct pointer
 * @return An Error struct that describes whether or not the
 * Cam struct was successfully updated
 */
Error refreshCamPixelPos(Cam* self) {
    if (!self)
        return createError(
            ESTAT_CAM_REFRESH,
            "Could not refresh the pixel position for a NULL camera");
    self->pixelPos = (Pos){(int) (self->coord.x * self->scale.w),
                           (int) (self->coord.y * self->scale.h)};
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Handles the logic for checking whether or not
 * the camera needs to be moved.
 *
 * @param cam : Camera struct pointer
 * @param maxBounds : SizeFloat struct
 * @param dt : float
 * @return An Error struct that describes whether or not there was an
 * issue when determining camera movement
 */
Error handleCameraMovement(Cam* cam, SizeFloat maxWorldBounds, float dt) {
    float movement = (500.0f * dt) / cam->zoom;

    if (cam->player) {
        float distX = cam->player->coord.x - cam->coord.x;
        float distY = cam->player->coord.y - cam->coord.y;
        if (distX < 0) {
            if (0 - distX < movement) cam->coord.x += distX;
            else cam->coord.x -= movement;
        }
        if (distX > 0) {
            if (distX < movement) cam->coord.x += distX;
            else cam->coord.x += movement;
        }
        if (distY < 0) {
            if (0 - distY < movement) cam->coord.y += distY;
            else cam->coord.y -= movement;
        }
        if (distY > 0) {
            if (distY < movement) cam->coord.y += distY;
            else cam->coord.y += movement;
        }
    }

    float halfX = cam->worldSize.w / 2;
    float halfY = cam->worldSize.h / 2;
    if (cam->coord.x < halfX) cam->coord.x = halfX;
    if (cam->coord.y < halfY) cam->coord.y = halfY;
    if (cam->coord.x > (maxWorldBounds.w - halfX))
        cam->coord.x = maxWorldBounds.w - halfX;
    if (cam->coord.y > (maxWorldBounds.h - halfY))
        cam->coord.y = maxWorldBounds.h - halfY;

    Error err = refreshCamPixelPos(cam);
    return err;
}
