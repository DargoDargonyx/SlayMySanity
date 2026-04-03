/**
 * @file widget.c
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for widgets.
 */

#include "core/ui/widget.h"

#include <stdlib.h>
#include <string.h>

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Creates a Button struct.
 *
 * @param txt : string pointer
 * @param x : integer
 * @param y : integer
 * @param w : integer
 * @param h : integer
 * @param texture : SDL_Texture pointer
 * @return The Button struct created
 */
Button createButton(SDL_Renderer* renderer,
                    SDL_Texture* bgTexture,
                    const char* text,
                    TTF_Font* font,
                    SDL_Color color,
                    int x,
                    int y) {

    Button btn;
    btn.bgTexture = bgTexture;
    int w, h;
    SDL_QueryTexture(bgTexture, NULL, NULL, &w, &h);
    btn.rect.x = x;
    btn.rect.y = y;
    btn.rect.w = w;
    btn.rect.h = h;

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    if (!textSurface) {
        btn.texture = NULL;
        return btn;
    }
    btn.texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return btn;
}

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Destroys the fields of a Button struct.
 *
 * @param button : Button struct pointer
 */
void destroyButton(Button* button) {
    if (!button) return;

    if (button->texture) {
        SDL_DestroyTexture(button->texture);
        button->texture = NULL;
    }
}
