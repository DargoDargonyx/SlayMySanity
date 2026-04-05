/**
 * @file input.c
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for user input.
 */

#include "ui/input.h"
#include "graphics/camera.h"
#include "ui/widget.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Helper function to check whether or not a point in the scene
 * in inside of a given SDL_Rect.
 *
 * @param pos : Pos struct
 * @param rect : SDL_Rect pointer
 * @return An integer representation of a boolean for whether or not
 * the given point is inside of the SDL_Rect in question
 */
int pointInRect(Pos pos, SDL_Rect* rect) {
    return (pos.x >= rect->x) && (pos.x <= rect->x + rect->w) &&
           (pos.y >= rect->y) && (pos.y <= rect->y + rect->h);
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for button events.
 *
 * @param btn : Button struct pointer
 * @param e : SDL_Event pointer
 */
void handleButtonEvent(Button* btn, SDL_Event* e) {
    Pos pos;

    if (e->type == SDL_MOUSEMOTION) {
        pos.x = e->motion.x;
        pos.y = e->motion.y;
        if (pointInRect(pos, &btn->rect))
            btn->state = BTN_HOVER;
        else
            btn->state = BTN_IDLE;
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (pointInRect(pos, &btn->rect))
            btn->state = BTN_PRESSED;
    }

    if (e->type == SDL_MOUSEBUTTONUP) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (btn->state == BTN_PRESSED && pointInRect(pos, &btn->rect)) {
            if (btn->onClick)
                btn->onClick(btn->userData);
            btn->state = BTN_HOVER;
        }
    }
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for checking whether or not
 * the user inputted a key to move the camera.
 *
 * @param cam : Camera struct pointer
 * @param maxBounds : Pos struct
 * @param deltaTime : float
 */
void checkCameraMovement(Cam* cam, Pos maxBounds, float deltaTime) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    float speed = (500.0f * deltaTime) / cam->zoom;

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
        cam->pos.y -= speed;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
        cam->pos.y += speed;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
        cam->pos.x -= speed;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
        cam->pos.x += speed;

    if (cam->pos.x < 0)
        cam->pos.x = 0;
    if (cam->pos.y < 0)
        cam->pos.y = 0;
    if (cam->pos.x > maxBounds.x)
        cam->pos.x = maxBounds.x;
    if (cam->pos.y > maxBounds.y)
        cam->pos.y = maxBounds.y;
}
