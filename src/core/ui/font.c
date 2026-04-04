/**
 * @file font.c
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for fonts.
 */

#include "core/ui/font.h"
#include "util/error.h"

#include <SDL2/SDL_ttf.h>

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Creates a Font struct.
 *
 * This function will take a font identification number and
 * a font size in order to create a Font struct depending
 * on the type of font specified by the indentification number.
 * If an identification number doesn't match any known ones it
 * will default to a JetBrains Mono font.
 *
 * @note The indentification numbers are defined in the
 * header file.
 * @param fontNum : integer
 * @param size : integer
 * @param color : SDL_Color
 * @return The newly created Font struct
 */
Font createFont(int fontNum, int size, SDL_Color color) {
    Font font;
    font.size = size;
    const char* filename;
    switch (fontNum) {
        case F_JETBRAINS_MONO:
            filename = "../assets/fonts/JetBrainsMono-Regular.ttf";
            break;
        default:
            filename = "../assets/fonts/JetBrainsMono-Regular.ttf";
            break;
    }
    font.font = TTF_OpenFont(filename, font.size);
    font.color = color;
    return font;
}

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for destroying the fields of a Font struct.
 *
 * @param self : Font struct pointer
 * @return An Error struct that describes whether or not the Font
 * struct in question was successfully destroyed
 */
Error destroyFont(Font* self) {
    if (!self)
        return createError(ESTAT_FONT_DESTROY, "Could not destroy a NULL font");
    if (self->font) {
        TTF_CloseFont(self->font);
        self->font = NULL;
    }
    return createError(ESTAT_MAIN_NONE, NULL);
}
