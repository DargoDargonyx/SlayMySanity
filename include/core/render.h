#ifndef RENDER_H
#define RENDER_H

#include "util/error.h"
#include "util/window.h"

#include "core/ui/widget.h"

#include <SDL2/SDL.h>

typedef struct {
    int w;
    int h;
    SDL_Texture* bgTexture;
    Button sButton;
    SDL_Texture* sbTexture;
    Button oButton;
    SDL_Texture* obTexture;
} StartMenuScene;


Error createStartMenuScene(WindowManager* wManager, StartMenuScene* scene);
void destroyStartMenuScene(StartMenuScene* scene);


#endif
