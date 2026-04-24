/**
 * @file widget.h
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for UI widgets.
 */

#ifndef UI_H
#define UI_H

#include "graphics/animation.h"
#include "ui/font.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>

#define UI_MANAGER_WIDGETS_INIT_CAP 31
#define UI_MANAGER_FONTS_INIT_CAP 7

typedef enum { TXT_BOX, BUTTON } WidgetType;

typedef struct Widget Widget;
struct Widget {
    WidgetType type;
    Error* (*destroy)(Widget*);
};

typedef struct {
    // Errors
    ErrorContainer* errCont;
    // Fonts
    FontContainer* fontCont;
    // Widgets
    int widgetCap;
    int widgetCount;
    Widget** widgets;
} UIManager;

UIManager* createUIManager();
Error* destroyUIManager(UIManager*);

typedef enum { TXT_BOX_SOLID, TXT_BOX_FILL, TXT_BOX_MINIMAL } TxtBoxType;

// Buttons orderered vertically such that,
// { IDLE }
// { HOVER }
// { PRESSED }
#define BTN_SPRITESHEET_COUNT 3
#define BTN_SPRITESHEET_WIDTH 1
#define BTN_SPRITESHEET_HEIGHT 3
typedef enum { BTN_IDLE, BTN_HOVER, BTN_PRESSED } BtnState;

typedef struct {
    TxtBoxType type;
    Widget base;
    SDL_Rect outer;
    SDL_Rect inner;
    const char* txt;
    SDL_Texture* texture;
} TxtBox;

typedef struct {
    Widget base;
    SDL_Rect rect;
    BtnState currentState;
    AnimationManager* aManager;
    TxtBox* txtBox;
    void (*onClick)(void*);
    void* userData;
} Button;

typedef struct {
    void* wManager;
    void (*startMenu)(void*);
    void (*optionsMenu)(void*);
    void (*playScene)(void*);
    void (*exit)(void*);
} SceneLoader;

Error* addWidgetToManager(UIManager*, Widget*);
Error* removeWidgetFromManager(UIManager*, Widget*);
Error* addFontToManager(UIManager*, Font*);
Font* findFontInManager(UIManager*, FontType);

TxtBox* createTxtBox(UIManager*, SDL_Renderer*, TxtBoxType, const char*, FontType, Pos, Size);
Error* destroyTxtBox(Widget*);
Error* padTxtBox(TxtBox*, Size);

Button* createButton(Spritesheet*, Pos, TxtBox*);
Error* destroyButton(Widget*);

Error* createStartMenuUI(UIManager*, SceneLoader*, SDL_Renderer*, Size);
Error* createOptionsMenuUI(UIManager*, SceneLoader*, SDL_Renderer*, Size);
Error* createPlaySceneUI(UIManager*, SceneLoader*, SDL_Renderer*);

#endif
