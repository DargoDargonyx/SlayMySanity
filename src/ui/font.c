/**
 * @file font.c
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for fonts.
 */

#include "ui/font.h"

#include <SDL2/SDL_ttf.h>

/**
 * @author DargoDargonyx
 * @date 04/05/2026
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
 * @param type : FontType enum
 * @param size : integer
 * @param color : SDL_Color
 * @return The newly created Font struct
 */
Font createFont(FontType type, int size, SDL_Color color) {
    Font font;
    font.size = size;
    const char* filename;
    switch (type) {
        case JETBRAINS_MONO:
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
