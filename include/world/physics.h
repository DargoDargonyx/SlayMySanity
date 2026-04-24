/**
 * @file physics.h
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for world physics.
 */

#ifndef PHYSICS_H
#define PHYSICS_H

// The size of each coordinate spot in the world
// in terms of pixels on the screen
#define WORLD_COORD_WIDTH 32
#define WORLD_COORD_HEIGHT 32

typedef enum {
    // Entities
    IDLE,
    MOVING_NORTH,
    MOVING_NORTH_EAST,
    MOVING_EAST,
    MOVING_SOUTH_EAST,
    MOVING_SOUTH,
    MOVING_SOUTH_WEST,
    MOVING_WEST,
    MOVING_NORTH_WEST,
} ActionState;

// World coordinates where (0, 0) is the top left
// of the world map
typedef struct {
    float x;
    float y;
} Coord;

#endif
