/**
 * @file camera.h
 * @author DargoDargonyx
 * @date 04/04/2026
 * @brief Handles the logic for the scene viewing.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "util/error.h"
#include "util/helper.h"

typedef struct {
    Pos pos;
    Size size;
    int zoom;
} Cam;

Cam* createCamera(Pos origPos, Size size, int zoom);
Error destroyCamera(Cam* self);

#endif
