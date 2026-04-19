/**
 * @file camera.h
 * @author DargoDargonyx
 * @date 04/18/2026
 * @brief Handles the logic for the scene viewing.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "util/error.h"
#include "util/helper.h"
#include "world/physics.h"
#include "world/player.h"

typedef struct {
    Coord coord;
    Pos pixelPos;
    SizeFloat worldSize;
    Size pixelSize;
    float zoom;
    Size scale;
    Player* player;
} Cam;

Cam* createCamera(Coord coord, Size pixelSize, float zoom);
Error destroyCamera(Cam* self);
Error addPlayerToCamera(Cam* self, Player* player);

Error handleCameraMovement(Cam* cam, SizeFloat maxBounds, float dt);
Error refreshCamPixelPos(Cam* self);

#endif
