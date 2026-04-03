/**
 * @file widget.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for UI widgets.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include "core/ui/font.h"
#include "util/error.h"

#include <SDL2/SDL.h>

#define BTN_TYPE_IMG 1
#define BTN_TYPE_TXT 2

typedef struct Button Button;
struct Button {
    int type;
    Error (*destroy)(Button* btn);
    int x;
    int y;
    int w;
    int h;
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

IMG_Button* createImgButton(ErrorContainer* errContainer,
                            SDL_Renderer* renderer, const char* bgImagePath,
                            int x, int y);
Error destroyImgButton(Button* self);

TXT_Button* createTxtButton(ErrorContainer* errContainer,
                            SDL_Renderer* renderer, const char* bgImagePath,
                            int x, int y, const char* txt, Font* font);
Error destroyTxtButton(Button* self);

#endif
