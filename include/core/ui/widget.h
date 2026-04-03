/**
 * @file widget.h
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for widgets.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include "core/ui/font.h"

#include <SDL2/SDL.h>

typedef struct {
  char *txt;
  Font *font;
  int x;
  int y;
  int w;
  int h;
  SDL_Texture *bgTexture;
  SDL_Texture *texture;
  SDL_Rect rect;
} Button;

Button createButton(SDL_Renderer *renderer, SDL_Texture *bgTexture,
                    const char *text, TTF_Font *font, SDL_Color color, int x,
                    int y);

void destroyButton(Button *button);

#endif
