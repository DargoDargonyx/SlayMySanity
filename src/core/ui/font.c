/**
 * @file font.c
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for fonts.
 */

#include "core/ui/font.h"


/**
 * @author DargoDargonyx
 * @date 03/25/2026
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
 * @param fontNum : integer
 * @return The created Font struct
 */
Font createFont(int fontNum, int size) {
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
    return font;
}


/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Destroys the fields of a Font struct.
 *
 * @param font : Font struct pointer
 */
void destroyFont(Font* font) {
    if (!font) return;
    if (font->font) {
        TTF_CloseFont(font->font);
        font->font = NULL;
    }
}
