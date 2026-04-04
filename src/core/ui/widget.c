/**
 * @file widget.c
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for UI widgets.
 */

#include "core/ui/widget.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for creating an IMG_Button struct.
 *
 * @note The position of the x and y is assumed to be the center of
 * the button and is adjust to be the top left point of the button.
 *
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param bgImagePath : c-style string literal
 * @param x : integer
 * @param y : integer
 * @return A pointer to the newly created IMG_Button struct
 */
IMG_Button* createImgButton(ErrorContainer* errContainer,
                            SDL_Renderer* renderer, const char* bgImagePath,
                            int x, int y) {

    IMG_Button* btn = (IMG_Button*) malloc(sizeof(IMG_Button));
    btn->base.type = BTN_TYPE_IMG;
    btn->base.destroy = destroyImgButton;
    btn->base.onClick = NULL;
    btn->base.state = BTN_IDLE;

    SDL_Surface* bgSurface = IMG_Load(bgImagePath);
    if (!bgSurface)
        addErrorToContainer(
            errContainer, createError(ESTAT_RENDER_LOAD_IMG,
                                      "Couldn't load button background image"));

    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    int w, h;
    SDL_QueryTexture(bgTexture, NULL, NULL, &w, &h);

    btn->base.bgTexture = bgTexture;
    btn->base.rect.x = x - (bgSurface->w / 2);
    btn->base.rect.y = y - (bgSurface->h / 2);
    btn->base.rect.w = w;
    btn->base.rect.h = h;

    return btn;
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for destroying an IMG_Button struct.
 *
 * @param self : Button struct pointer
 * @return An Error struct that describes whether or not
 * the IMG_Button struct was in question successfully destroyed
 */
Error destroyImgButton(Button* self) {
    if (!self)
        return createError(ESTAT_WIDGET_BTN_DESTROY,
                           "Could not destroy a NULL Image Button");

    TXT_Button* btn = (TXT_Button*) self;
    SDL_DestroyTexture(btn->base.bgTexture);
    free(btn);
    return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for creating a TXT_Button struct.
 *
 * @note The position of the x and y is assumed to be the center of
 * the button and is adjust to be the top left point of the button.
 *
 * @param errContainer : ErroContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param bgImagePath : c-style string literal
 * @param x : integer
 * @param y : integer
 * @param txt : c-style string literal
 * @param font : Font struct pointer
 * @return A pointer to the newly created TXT_Button struct
 */
TXT_Button* createTxtButton(ErrorContainer* errContainer,
                            SDL_Renderer* renderer, const char* bgImagePath,
                            int x, int y, const char* txt, Font* font) {

    TXT_Button* btn = (TXT_Button*) malloc(sizeof(TXT_Button));
    btn->base.type = BTN_TYPE_TXT;
    btn->base.destroy = destroyTxtButton;
    btn->base.onClick = NULL;
    btn->base.state = BTN_IDLE;

    SDL_Surface* bgSurface = IMG_Load(bgImagePath);
    if (!bgSurface)
        addErrorToContainer(
            errContainer, createError(ESTAT_RENDER_LOAD_IMG,
                                      "Couldn't load button background image"));
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);

    int w, h;
    SDL_QueryTexture(bgTexture, NULL, NULL, &w, &h);
    btn->base.bgTexture = bgTexture;
    btn->base.rect.x = x - (bgSurface->w / 2);
    btn->base.rect.y = y - (bgSurface->h / 2);
    btn->base.rect.w = w;
    btn->base.rect.h = h;
    SDL_FreeSurface(bgSurface);

    SDL_Surface* txtSurface =
        TTF_RenderText_Blended(font->font, txt, font->color);
    if (!txtSurface) {
        btn->txtTexture = NULL;
        return btn;
    }
    btn->txtTexture = SDL_CreateTextureFromSurface(renderer, txtSurface);
    SDL_FreeSurface(txtSurface);
    btn->txtRect.x = btn->base.rect.x + 20;
    btn->txtRect.y = btn->base.rect.y + 20;
    btn->txtRect.w = btn->base.rect.w - 40;
    btn->txtRect.h = btn->base.rect.h - 40;

    return btn;
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for destroying a TXT_Button struct.
 *
 * @param self : Button struct pointer
 * @return An Error struct that describes whether or not
 * the TXT_Button struct in question was successfully destroyed
 */
Error destroyTxtButton(Button* self) {
    if (!self)
        return createError(ESTAT_WIDGET_BTN_DESTROY,
                           "Could not destroy a NULL Text Button");

    Error err = createError(ESTAT_MAIN_NONE, NULL);
    TXT_Button* btn = (TXT_Button*) self;
    SDL_DestroyTexture(btn->base.bgTexture);
    SDL_DestroyTexture(btn->txtTexture);
    err = destroyFont(btn->font);
    free(btn);
    return err;
}
