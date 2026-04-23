/**
 * @file widget.h
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for UI widgets.
 */

#ifndef UI_H
#define UI_H

#include "ui/font.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

#define UI_MANAGER_WIDGETS_INIT_CAP 31

typedef enum { BUTTON } WidgetType;

typedef struct Widget Widget;
struct Widget {
    WidgetType type;
    Error* (*destroy)(Widget*);
};

typedef struct {
    int widgetCap;
    int widgetCount;
    Widget** widgets;
    ErrorContainer* errCont;
} UIManager;

UIManager* createUIManager();
Error* destroyUIManager(UIManager*);

// Orderered vertically such that,
// { IDLE }
// { HOVER }
// { PRESSED }
#define BTN_SPRITESHEET_SIZE 3

typedef enum { IMG, TXT } ButtonType;
typedef enum { BTN_IDLE, BTN_HOVER, BTN_PRESSED } ButtonState;

typedef struct Button Button;
struct Button {
    Widget base;
    ButtonType type;
    ButtonState state;
    void (*onClick)(void*);
    void* userData;
    SDL_Texture* bgTexture;
    SDL_Rect rect;
};

typedef struct {
    Button base;
} IMG_Button;

typedef struct {
    Button base;
    const char* txt;
    Font* font;
    SDL_Texture* txtTexture;
    SDL_Rect txtRect;
} TXT_Button;

typedef struct {
    void* wManager;
    void (*startMenu)(void*);
    void (*optionsMenu)(void*);
    void (*playScene)(void*);
    void (*exit)(void*);
} SceneLoader;

IMG_Button* createImgButton(UIManager*, SDL_Renderer*, const char*, Pos, int);
Error* destroyImgButton(Widget*);
TXT_Button* createTxtButton(UIManager*, SDL_Renderer*, const char*, Pos, int, const char*, Font*);
Error* destroyTxtButton(Widget*);

Error* addWidgetToManager(UIManager*, Widget*);

Error* createStartMenuUI(UIManager*, SceneLoader*, SDL_Renderer*, Size);
Error* createOptionsMenuUI(UIManager*, SceneLoader*, SDL_Renderer*, Size);
Error* createPlaySceneUI(UIManager*, SceneLoader*, SDL_Renderer*, Size);

#endif
