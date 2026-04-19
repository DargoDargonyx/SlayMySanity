/**
 * @file sprite.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for sprites and spritesheets.
 */

#include "graphics/sprite.h"
#include "SDL_render.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating a new Spritesheet struct.
 *
 * @param errContainer : ErrorContainer struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param filepath : c-style string literal
 * @param sheetSize : Size struct
 * @param spriteCount : integer
 * @return A pointer to the newly created Spritesheet struct
 */
Spritesheet* createSpritesheet(ErrorContainer* errCont, SDL_Renderer* renderer,
                               const char* filepath, Size sheetSize,
                               int spriteCount) {

    Spritesheet* sheet = (Spritesheet*) malloc(sizeof(Spritesheet));
    sheet->size = sheetSize;
    sheet->spriteCount = spriteCount;

    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface) {
        addErrorToContainer(
            errCont,
            createError(SPRITE, "Could not load the sritesheet image file"));
    } else {
        sheet->texture = SDL_CreateTextureFromSurface(renderer, surface);
        sheet->pixelSize = (Size){surface->w, surface->h};
        SDL_FreeSurface(surface);
    }

    sheet->spriteSize.w = (int) (sheet->pixelSize.w / sheet->size.w);
    sheet->spriteSize.h = (int) (sheet->pixelSize.h / sheet->size.h);
    return sheet;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying a Spritesheet struct.
 *
 * @param sheet : Spritesheet struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Spritesheet struct in question was successfully
 * destroyed
 */
Error* destroySpritesheet(Spritesheet* self) {
    SDL_DestroyTexture(self->texture);
    free(self);
    return NULL;
}
