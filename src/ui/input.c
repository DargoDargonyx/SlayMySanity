/**
 * @file input.c
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for user input.
 */

#include "ui/input.h"
#include "graphics/camera.h"
#include "ui/widget.h"
#include "util/helper.h"
#include "world/player.h"

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
 * @date 04/08/2026
 * @brief Handles the logic for player events.
 *
 * @param player : Player struct pointer
 * @param dt : float
 */
void handlePlayerEvent(Player* player, float dt) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    float distance = 10.0f * dt * player->speed;

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
        player->worldPos.y -= distance;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
        player->worldPos.y += distance;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
        player->worldPos.x -= distance;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
        player->worldPos.x += distance;
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
        if (pointInRect(pos, &btn->rect)) btn->state = BTN_HOVER;
        else btn->state = BTN_IDLE;
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (pointInRect(pos, &btn->rect)) btn->state = BTN_PRESSED;
    }

    if (e->type == SDL_MOUSEBUTTONUP) {
        pos.x = e->button.x;
        pos.y = e->button.y;
        if (btn->state == BTN_PRESSED && pointInRect(pos, &btn->rect)) {
            if (btn->onClick) btn->onClick(btn->userData);
            btn->state = BTN_HOVER;
        }
    }
}

/**
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for checking whether or not
 * the user inputted a key to move the camera.
 *
 * @param cam : Camera struct pointer
 * @param maxBounds : Size struct
 * @param dt : float
 */
void handleCameraMovement(Cam* cam, Size maxWorldBounds, float dt) {
    float movement = (500.0f * dt) / cam->zoom;

    if (cam->player) {
        float distX = cam->player->worldPos.x - cam->worldPos.x;
        float distY = cam->player->worldPos.y - cam->worldPos.y;
        if (distX < 0) {
            if (0 - distX < movement) cam->worldPos.x += distX;
            else cam->worldPos.x -= movement;
        }
        if (distX > 0) {
            if (distX < movement) cam->worldPos.x += distX;
            else cam->worldPos.x -= movement;
        }
        if (distY < 0) {
            if (0 - distY < movement) cam->worldPos.y += distY;
            else cam->worldPos.y -= movement;
        }
        if (distY > 0) {
            if (distY < movement) cam->worldPos.y += distY;
            else cam->worldPos.y -= movement;
        }
    }

    if (cam->worldPos.x < 0) cam->worldPos.x = 0;
    if (cam->worldPos.y < 0) cam->worldPos.y = 0;
    if (cam->worldPos.x > (maxWorldBounds.w - cam->worldSize.w))
        cam->worldPos.x = maxWorldBounds.w - cam->worldSize.w;
    if (cam->worldPos.y > (maxWorldBounds.h - ((float) cam->worldSize.h / 2)))
        cam->worldPos.y = maxWorldBounds.h - ((float) cam->worldSize.h / 2);

    Error err = refreshPixelPos(cam);
}
