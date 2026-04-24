/**
 * @file font.c
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for fonts.
 */

#include "ui/font.h"
#include "util/error.h"

#include <SDL2/SDL_ttf.h>

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for creating a FontContainer struct.
 *
 * @return A pointer to the newly created FontContainer struct
 */
FontContainer* createFontContainer() {
    FontContainer* container = (FontContainer*) malloc(sizeof(FontContainer));
    container->count = 0;
    container->cap = FONT_CONTAINER_INIT_CAP;
    container->fonts = (Font**) calloc(container->cap, sizeof(Font*));
    return container;
}

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for destroying a FontContainer struct.
 *
 * @param self : FontContainer struct pointer
 * @return A pointer to an Error struct that describes whether or not
 * the FontContainer struct in question was successfully destroyed
 */
Error* destroyFontContainer(FontContainer* self) {
    if (!self) return createError(FONT, "Could not destroy a NULL FontContainer");

    Error* err = NULL;
    for (int i = 0; i < self->count; i++) {
        err = destroyFont(self->fonts[i]);
        if (err) return err;
    }
    free(self->fonts);
    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for adding a Font struct to a FontContainer
 * struct.
 *
 * @param container : FontContainer struct pointer
 * @param font : Font struct pointer
 * @return A pointer to an Error struct that describes whether or not
 * the FontContainer struct in question was successfully destroyed
 */
Error* addFontToContainer(FontContainer* container, Font* font) {
    if (!container) return createError(FONT, "Could not add a Font to a NULL FontContainer");
    if (!font) return createError(FONT, "Could not add a NULL font to a FontContainer");

    if (container->count == container->cap) {
        container->cap = (container->count + 1) * 2;
        Font** orig = container->fonts;
        Font** temp = (Font**) calloc(container->cap, sizeof(Font*));
        if (!temp) return createError(FONT, "Could not reallocate a larger Font array field");

        for (int i = 0; i < container->count; i++) { temp[i] = orig[i]; }
        free(orig);
        container->fonts = temp;
    }

    container->fonts[container->count++] = font;
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for creating a Font struct.
 *
 * @note The font will default to my favorite one if the
 * function doesn't recognize the type given.
 *
 * @param container : FontContainer struct pointer
 * @param type : FontType enum
 * @param size : integer
 * @param color : SDL_Color
 * @return A pointer to the newly created Font struct
 */
Error* createFont(FontContainer* container, FontType type, int size, SDL_Color color) {
    Font* font = (Font*) malloc(sizeof(Font));
    font->size = size;
    font->type = type;
    const char* filename;
    switch (type) {
        case JETBRAINS_MONO:
            filename = "../assets/fonts/JetBrainsMono-Regular.ttf";
            break;
        default:
            filename = "../assets/fonts/JetBrainsMono-Regular.ttf";
            break;
    }
    font->font = TTF_OpenFont(filename, font->size);
    font->color = color;
    Error* err = addFontToContainer(container, font);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for destroying a Font struct.
 *
 * @param self : Font struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Font struct in question was successfully destroyed
 */
Error* destroyFont(Font* self) {
    if (!self) return createError(FONT, "Could not destroy a NULL font");
    if (self->font) TTF_CloseFont(self->font);
    free(self);
    return NULL;
}
