/**
 * @file widget.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for UI widgets.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include "ui/font.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

// Orderered vertically such that,
// { IDLE }
// { HOVER }
// { PRESSED }
#define BTN_SPRITESHEET_SIZE 3

typedef enum { IMG, TXT } ButtonType;
typedef enum { BTN_IDLE, BTN_HOVER, BTN_PRESSED } ButtonState;

typedef struct Button Button;
struct Button {
    ButtonType type;
    Error* (*destroy)(Button*);
    ButtonState state;
    void (*onClick)(void*);
    void* userData;
    SDL_Texture* bgTexture;
    SDL_Rect rect;
};

typedef struct {
    Button base;
} IMG_Button;

typedef struct {
    Button base;
    const char* txt;
    Font* font;
    SDL_Texture* txtTexture;
    SDL_Rect txtRect;
} TXT_Button;

IMG_Button* createImgButton(ErrorContainer*, SDL_Renderer*, const char*, Pos,
                            int);
Error* destroyImgButton(Button*);

TXT_Button* createTxtButton(ErrorContainer*, SDL_Renderer*, const char*, Pos,
                            int, const char*, Font*);
Error* destroyTxtButton(Button*);

#endif
