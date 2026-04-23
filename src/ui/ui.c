/*
 * @file ui.c
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for UI.
 */

#include "ui/ui.h"
#include "core/scene.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for creating a UIManager struct.
 *
 * @return A pointer to the newly created UIManager struct
 */
UIManager* createUIManager() {
    UIManager* manager = (UIManager*) malloc(sizeof(UIManager));
    manager->widgetCount = 0;
    manager->widgetCap = UI_MANAGER_WIDGETS_INIT_CAP;
    manager->widgets = (Widget**) calloc(manager->widgetCap, sizeof(Widget*));
    manager->errCont = createErrorContainer(15);
    return manager;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for destroying a UIManager struct.
 *
 * @param self : UIManager struct pointer
 * @return A pointer to an Error struct that describes whether or not the
 * UIManager struct was successfully destroyed
 */
Error* destroyUIManager(UIManager* self) {
    if (!self) return createError(UI, "Could not destroy a NULL UIManager");

    Error* err = destroyErrorContainer(self->errCont);
    if (err) return err;
    for (int i = 0; i < self->widgetCount; i++) {
        err = self->widgets[i]->destroy(self->widgets[i]);
        if (err) return err;
    }
    free(self->widgets);

    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for creating an IMG_Button struct.
 *
 * @note The position of the x and y is assumed to be the center of
 * the button and is adjust to be the top left point of the button.
 *
 * @param uManager : UIManager struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param bgImagePath : c-style string literal
 * @param pos : Pos struct
 * @return A pointer to the newly created IMG_Button struct
 */
IMG_Button* createImgButton(UIManager* uManager, SDL_Renderer* renderer, const char* bgImagePath,
                            Pos pos, int spriteNum) {

    IMG_Button* btn = (IMG_Button*) malloc(sizeof(IMG_Button));
    btn->base.base.type = BUTTON;
    btn->base.base.destroy = destroyImgButton;
    btn->base.type = IMG;
    btn->base.onClick = NULL;
    btn->base.state = BTN_IDLE;

    SDL_Surface* bgSurface = IMG_Load(bgImagePath);
    if (!bgSurface)
        addErrorToContainer(uManager->errCont,
                            createError(RENDER, "Could not load button background image"));

    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    Size size;
    SDL_QueryTexture(bgTexture, NULL, NULL, &size.w, &size.h);

    btn->base.bgTexture = bgTexture;
    btn->base.rect.x = (int) (pos.x - (bgSurface->w / 2));
    btn->base.rect.y = (int) (pos.y - (bgSurface->h / (2 * spriteNum)));
    btn->base.rect.w = size.w;
    btn->base.rect.h = (int) (size.h / spriteNum);

    return btn;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for destroying an IMG_Button struct.
 *
 * @param self : Widget struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the IMG_Button struct was in question successfully
 * destroyed
 */
Error* destroyImgButton(Widget* self) {
    if (!self) return createError(UI, "Could not destroy a NULL Image Button");

    TXT_Button* btn = (TXT_Button*) self;
    SDL_DestroyTexture(btn->base.bgTexture);
    free(btn);
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for creating a TXT_Button struct.
 *
 * @note The position of the x and y is assumed to be the center of
 * the button and is adjust to be the top left point of the button.
 *
 * @param uManager : UIManager struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param bgImagePath : c-style string literal
 * @param pos : Pos struct
 * @param txt : c-style string literal
 * @param font : Font struct pointer
 * @return A pointer to the newly created TXT_Button struct
 */
TXT_Button* createTxtButton(UIManager* uManager, SDL_Renderer* renderer, const char* bgImagePath,
                            Pos pos, int spriteNum, const char* txt, Font* font) {

    TXT_Button* btn = (TXT_Button*) malloc(sizeof(TXT_Button));
    btn->base.base.type = BUTTON;
    btn->base.base.destroy = destroyTxtButton;
    btn->base.type = TXT;
    btn->base.onClick = NULL;
    btn->base.state = BTN_IDLE;

    SDL_Surface* bgSurface = IMG_Load(bgImagePath);
    if (!bgSurface)
        addErrorToContainer(uManager->errCont,
                            createError(RENDER, "Couldn't load button background image"));
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    Size size;
    SDL_QueryTexture(bgTexture, NULL, NULL, &size.w, &size.h);

    btn->base.bgTexture = bgTexture;
    btn->base.rect.x = (int) (pos.x - (bgSurface->w / 2));
    btn->base.rect.y = (int) (pos.y - (bgSurface->h / (2 * spriteNum)));
    btn->base.rect.w = size.w;
    btn->base.rect.h = (int) (size.h / spriteNum);
    SDL_FreeSurface(bgSurface);

    btn->font = font;
    btn->txt = txt;
    SDL_Surface* txtSurface = TTF_RenderText_Blended(font->font, txt, font->color);
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
 * @date 04/20/2026
 * @brief Handles the logic for destroying a TXT_Button struct.
 *
 * @param self : Widget struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the TXT_Button struct in question was successfully
 * destroyed
 */
Error* destroyTxtButton(Widget* self) {
    if (!self) return createError(UI, "Could not destroy a NULL Text Button");

    TXT_Button* btn = (TXT_Button*) self;
    SDL_DestroyTexture(btn->base.bgTexture);
    SDL_DestroyTexture(btn->txtTexture);
    free(btn);
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Handles the logic for adding a Widget struct to a
 * UIManager struct.
 *
 * @param uManager : UIManager struct pointer
 * @param widget : Widget struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Widget struct was successfully added to the UIManager
 * struct
 */
Error* addWidgetToManager(UIManager* uManager, Widget* widget) {
    if (!uManager) return createError(UI, "Could not add a widget to a NULL UIManager");
    if (!widget) return createError(UI, "Could not add a NULL widget to a UIManager");

    if (uManager->widgetCount == uManager->widgetCap) {
        uManager->widgetCap = (uManager->widgetCount + 1) * 2;
        Widget** orig = uManager->widgets;
        Widget** temp = (Widget**) calloc(uManager->widgetCap, sizeof(Widget*));
        if (!temp) return createError(ERROR, "Could not reallocate a larger Error array field");

        for (int i = 0; i < uManager->widgetCount; i++) { temp[i] = orig[i]; }
        free(orig);
        uManager->widgets = temp;
    }

    uManager->widgets[uManager->widgetCount++] = widget;
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Helper function to handle the logic for creating the UI
 * elements for the start menu.
 *
 * @param uManager : UIManager struct pointer
 * @param loader : SceneLoader pointer
 * @param renderer : SDL_Renderer pointer
 * @param screenSize : Size struct
 * @return A pointer to an Error struct that describes whether
 * or not the UI elements were successfully created
 */
Error* createStartMenuUI(UIManager* uManager, SceneLoader* loader, SDL_Renderer* renderer,
                         Size screenSize) {

    Error* err = NULL;
    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(JETBRAINS_MONO, 36, white);

    // Start Button
    const char* sbImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    const char* sbText = "Start Game";
    int sbVertSpacing = -35;
    Pos sbPos = {screenSize.w / 2, (screenSize.h / 2) + sbVertSpacing};
    TXT_Button* sButton =
        createTxtButton(uManager, renderer, sbImgPath, sbPos, BTN_SPRITESHEET_SIZE, sbText, &font);
    sButton->base.onClick = loadPlayScene;
    sButton->base.userData = loader->wManager;
    err = addWidgetToManager(uManager, (Widget*) sButton);
    if (err) return err;

    // Options Button
    const char* obImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    const char* obText = "Options";
    int obVertSpacing = 65;
    Pos obPos = {screenSize.w / 2, (screenSize.h / 2) + obVertSpacing};
    TXT_Button* oButton =
        createTxtButton(uManager, renderer, obImgPath, obPos, BTN_SPRITESHEET_SIZE, obText, &font);
    oButton->base.onClick = loadOptionsMenuScene;
    oButton->base.userData = loader->wManager;
    err = addWidgetToManager(uManager, (Widget*) oButton);
    if (err) return err;

    // Exit Button
    const char* ebImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    const char* ebText = "Exit";
    int ebVertSpacing = 165;
    Pos ebPos = {screenSize.w / 2, (screenSize.h / 2) + ebVertSpacing};
    TXT_Button* exitButton =
        createTxtButton(uManager, renderer, ebImgPath, ebPos, BTN_SPRITESHEET_SIZE, ebText, &font);
    exitButton->base.onClick = loader->exit;
    exitButton->base.userData = loader->wManager;
    err = addWidgetToManager(uManager, (Widget*) exitButton);
    if (err) return err;

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Helper function to handle the logic for creating the UI
 * elements for the options menu.
 *
 * @param uManager : UIManager struct pointer
 * @param loader : SceneLoader pointer
 * @param renderer : SDL_Renderer pointer
 * @param screenSize : Size struct
 * @return A pointer to an Error struct that describes whether
 * or not the UI elements were successfully created
 */
Error* createOptionsMenuUI(UIManager* uManager, SceneLoader* loader, SDL_Renderer* renderer,
                           Size screenSize) {

    Error* err = NULL;

    SDL_Color white = {255, 255, 255, 255};
    Font font = createFont(JETBRAINS_MONO, 36, white);

    // Return button
    const char* rbImgPath = "../assets/sprites/ui/options_menu/main_button.png";
    const char* rbText = "Return";
    Pos rbPos = {screenSize.w / 2, screenSize.h / 2};
    TXT_Button* rButton =
        createTxtButton(uManager, renderer, rbImgPath, rbPos, BTN_SPRITESHEET_SIZE, rbText, &font);
    rButton->base.onClick = loadStartMenuScene;
    rButton->base.userData = loader->wManager;
    err = addWidgetToManager(uManager, (Widget*) rButton);
    if (err) return err;

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/20/2026
 * @brief Helper function to handle the logic for creating the UI
 * elements for the playing scene.
 *
 * @param uManager : UIManager struct pointer
 * @param loader : SceneLoader pointer
 * @param renderer : SDL_Renderer pointer
 * @param screenSize : Size struct
 * @return A pointer to an Error struct that describes whether
 * or not the UI elements were successfully created
 */
Error* createPlaySceneUI(UIManager* uManager, SceneLoader* loader, SDL_Renderer* renderer,
                         Size screenSize) {

    Error* err = NULL;

    // Back button
    Pos disPos = {40, 40};
    const char* backButtonImgPath = "../assets/sprites/ui/play_scene/back_button.png";
    IMG_Button* backButton =
        createImgButton(uManager, renderer, backButtonImgPath, disPos, BTN_SPRITESHEET_SIZE);
    backButton->base.onClick = loadStartMenuScene;
    backButton->base.userData = loader->wManager;
    err = addWidgetToManager(uManager, (Widget*) backButton);
    if (err) return err;

    return err;
}
