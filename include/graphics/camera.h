/**
 * @file camera.h
 * @author DargoDargonyx
 * @date 04/19/2026
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

Cam* createCamera(Coord, Size, float);
Error* destroyCamera(Cam*);
Error* addPlayerToCamera(Cam*, Player*);

Error* handleCameraMovement(Cam*, SizeFloat, float);
Error* refreshCamPixelPos(Cam*);

#endif
