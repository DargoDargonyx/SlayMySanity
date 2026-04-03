#include "core/render.h"

#include "core/ui/font.h"
#include "core/ui/widget.h"

#include <SDL2/SDL_image.h>

Error createStartMenuScene(WindowManager* wManager, StartMenuScene* scene) {
    scene->w = wManager->wWidth;
    scene->h = wManager->wHeight;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(F_JETBRAINS_MONO, 36);

    SDL_Surface* bgSurface = IMG_Load("../assets/sprites/MiniStartMenu.png");
    if (!bgSurface)
        return createError(ESTAT_LOAD_IMG,
                           "Failed to load mini start menu image");
    SDL_Texture* bgTexture =
        SDL_CreateTextureFromSurface(wManager->renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    scene->bgTexture = bgTexture;

    SDL_Surface* sbSurface =
        IMG_Load("../assets/sprites/MiniStartMenu_PlayButton.png");
    if (!sbSurface)
        return createError(ESTAT_LOAD_IMG,
                           "Failed to load start menu start button image");
    SDL_Texture* sbTexture =
        SDL_CreateTextureFromSurface(wManager->renderer, sbSurface);
    scene->sbTexture = sbTexture;

    char sbText[15] = "Start Game";
    Button sButton =
        createButton(wManager->renderer, sbTexture, sbText, font.font, white,
                     (scene->w / 2) - (sbSurface->w / 2),
                     (scene->h / 2) - (sbSurface->h / 2));

    if (!sButton.texture)
        return createError(ESTAT_CREATE_BUTTON,
                           "Failed to create start menu start button");
    scene->sButton = sButton;
    SDL_FreeSurface(sbSurface);

    SDL_Surface* obSurface =
        IMG_Load("../assets/sprites/MiniStartMenu_PlayButton.png");
    if (!obSurface)
        return createError(ESTAT_LOAD_IMG,
                           "Failed to load start menu option button image");
    SDL_Texture* obTexture =
        SDL_CreateTextureFromSurface(wManager->renderer, obSurface);
    scene->obTexture = obTexture;

    char obText[15] = "Options";
    int spacing = 100;
    Button oButton =
        createButton(wManager->renderer, obTexture, obText, font.font, white,
                     sButton.x, sButton.y + spacing);
    if (!oButton.texture)
        return createError(ESTAT_CREATE_BUTTON,
                           "Failed to create start menu option button");
    scene->oButton = oButton;
    SDL_FreeSurface(obSurface);

    return createError(ESTAT_NONE, NULL);
}

void destroyStartMenuScene(StartMenuScene* scene) {
    if (!scene)
        return;

    if (scene->bgTexture)
        SDL_DestroyTexture(scene->bgTexture);
    if (scene->sbTexture)
        SDL_DestroyTexture(scene->sbTexture);
    if (scene->obTexture)
        SDL_DestroyTexture(scene->obTexture);

    destroyButton(&scene->sButton);
    destroyButton(&scene->oButton);
}
