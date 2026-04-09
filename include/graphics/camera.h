/**
 * @file camera.h
 * @author DargoDargonyx
 * @date 04/09/2026
 * @brief Handles the logic for the scene viewing.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "util/error.h"
#include "util/helper.h"
#include "world/player.h"

typedef struct {
    PosFloat worldPos;
    Pos pixelPos;
    SizeFloat worldSize;
    Size pixelSize;
    float zoom;
    Size scale;
    Player* player;
} Cam;

Cam* createCamera(PosFloat worldPos, Size pixelSize, float zoom, Size scale);
Error destroyCamera(Cam* self);
Error addPlayerToCamera(Cam* self, Player* player);

Error refreshPixelPos(Cam* self);
Error refreshWorldPos(Cam* self);

#endif
