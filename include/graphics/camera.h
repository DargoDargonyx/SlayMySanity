/**
 * @file camera.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for the scene viewing.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "util/error.h"
#include "world/physics.h"

typedef struct {
    Pos pos;
    int viewWidth;
    int viewHeight;
} Cam;

Cam* createCamera(Pos origPos, int viewWidth, int viewHeight);
Error destroyCamera(Cam* self);

#endif
