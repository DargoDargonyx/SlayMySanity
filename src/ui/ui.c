/*
 * @file ui.c
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for UI.
 */

#include "ui/ui.h"
#include "graphics/animation.h"
#include "graphics/sprite.h"
#include "ui/font.h"
#include "util/error.h"
#include "util/helper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for creating a UIManager struct.
 *
 * @return A pointer to the newly created UIManager struct
 */
UIManager* createUIManager() {
    UIManager* manager = (UIManager*) malloc(sizeof(UIManager));
    manager->errCont = createErrorContainer(15);
    manager->fontCont = createFontContainer();
    manager->widgetCount = 0;
    manager->widgetCap = UI_MANAGER_WIDGETS_INIT_CAP;
    manager->widgets = (Widget**) calloc(manager->widgetCap, sizeof(Widget*));
    return manager;
}

/**
 * @author DargoDargonyx
 * @date 04/23/2026
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

    err = destroyFontContainer(self->fontCont);
    if (err) return err;

    free(self);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for adding a Widget struct to a
 * UIManager struct.
 *
 * @param uiManager : UIManager struct pointer
 * @param widget : Widget struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Widget struct was successfully added to the UIManager
 * struct
 */
Error* addWidgetToManager(UIManager* uiManager, Widget* widget) {
    if (!uiManager) return createError(UI, "Could not add a widget to a NULL UIManager");
    if (!widget) return createError(UI, "Could not add a NULL widget to a UIManager");

    if (uiManager->widgetCount == uiManager->widgetCap) {
        uiManager->widgetCap = (uiManager->widgetCount + 1) * 2;
        Widget** orig = uiManager->widgets;
        Widget** temp = (Widget**) calloc(uiManager->widgetCap, sizeof(Widget*));
        if (!temp) return createError(ERROR, "Could not reallocate a larger Error array field");

        for (int i = 0; i < uiManager->widgetCount; i++) { temp[i] = orig[i]; }
        free(orig);
        uiManager->widgets = temp;
    }

    uiManager->widgets[uiManager->widgetCount++] = widget;
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for removing a Widget struct from a
 * UIManager struct.
 *
 * @param uiManager : UIManager struct pointer
 * @param widget : Widget struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Widget struct was successfully rmeoved from the
 * UIManager struct
 */
Error* removeWidgetFromManager(UIManager* uiManager, Widget* widget) {
    int found = 0;
    int index;
    for (int i = 0; i < uiManager->widgetCount; i++) {
        if (uiManager->widgets[i] == widget) {
            index = i;
            found = 1;
            break;
        }
    }

    if (found) {
        for (int i = index; i < uiManager->widgetCount - 1; i++) {
            uiManager->widgets[i] = uiManager->widgets[i + 1];
        }
        uiManager->widgets[uiManager->widgetCount - 1] = NULL;
        uiManager->widgetCount--;
        return NULL;
    } else {
        return createError(
            UI,
            "Could not remove a widget from a UIManager that does not contain it to begin with");
    }
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for finding a specific Font struct inside
 * of a UIManager struct.
 *
 * @param uiManager : UIManager struct pointer
 * @param fontType : FontType enum
 * @return A pointer to the Font struct in question
 */
Font* findFontInManager(UIManager* uiManager, FontType fontType) {
    Font* font = NULL;
    for (int i = 0; i < uiManager->fontCont->count; i++) {
        Font* f = uiManager->fontCont->fonts[i];
        if (!f) continue;
        if (f->type == fontType) {
            font = f;
            break;
        }
    }
    if (!font)
        addErrorToContainer(uiManager->errCont,
                            createError(FONT, "Could not find a specific font in a UIManager"));
    return font;
}

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for creating a TxtBox struct.
 *
 * @param uiManager : UIManager struct pointer
 * @param renderer : SDL_Renderer pointer
 * @param txtBoxType : TxtBoxType enum
 * @param txt : c-style string literal
 * @param fontType : FontType enum
 * @param pos : Pos struct
 * @param size : Size struct
 * @return A pointer to the newly created TxtBox struct
 */
TxtBox* createTxtBox(UIManager* uiManager, SDL_Renderer* renderer, TxtBoxType txtBoxType,
                     const char* txt, FontType fontType, Pos pos, Size size) {

    TxtBox* txtBox = (TxtBox*) malloc(sizeof(TxtBox));
    txtBox->base.destroy = destroyTxtBox;
    txtBox->type = txtBoxType;
    txtBox->txt = txt;

    Font* font = findFontInManager(uiManager, fontType);
    if (uiManager->errCont->count > 0) return txtBox;
    SDL_Surface* txtSurface = TTF_RenderText_Blended(font->font, txt, font->color);
    if (!txtSurface) {
        txtBox->texture = NULL;
        addErrorToContainer(
            uiManager->errCont,
            createError(UI, "Could not create a txt surface when creating a TxtBox"));
        return txtBox;
    }
    txtBox->texture = SDL_CreateTextureFromSurface(renderer, txtSurface);

    switch (txtBox->type) {
        case TXT_BOX_SOLID:
            txtBox->inner.x = pos.x;
            txtBox->inner.y = pos.y;
            txtBox->inner.w = size.w;
            txtBox->inner.h = size.h;
            break;
        case TXT_BOX_FILL:
            // empty for now, just didnt want to exclude a single case
            break;
        case TXT_BOX_MINIMAL:
            txtBox->inner.x = pos.x;
            txtBox->inner.y = pos.y;
            txtBox->inner.w = txtSurface->w;
            txtBox->inner.h = txtSurface->h;
            break;
        default:
            addErrorToContainer(
                uiManager->errCont,
                createError(UI, "Could not create a TxtBox with an unknown TxtBox type"));
            return txtBox;
            break;
    }
    txtBox->outer = txtBox->inner;

    SDL_FreeSurface(txtSurface);
    return txtBox;
}

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for destroying a TxtBox struct.
 *
 * @param self : Widget struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the TxtBox struct in question was successfully
 * destroyed
 */
Error* destroyTxtBox(Widget* self) {
    if (!self) return createError(UI, "Could not destroy a NULL TxtBox");

    TxtBox* txtBox = (TxtBox*) self;
    SDL_DestroyTexture(txtBox->texture);
    free(txtBox);
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for padding a TxtBox struct.
 *
 * @param self : TxtBox struct pointer
 * @param pad : Size struct
 * @return A pointer to an Error struct that describes whether
 * or not the TxtBox struct in question was successfully padded
 */
Error* padTxtBox(TxtBox* self, Size pad) {
    self->inner.x += pad.w;
    self->inner.y += pad.h;
    self->inner.w -= pad.w * 2;
    self->inner.h -= pad.h * 2;
    if (self->inner.w < 0) self->inner.w = 0;
    if (self->inner.h < 0) self->inner.h = 0;
    return NULL;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Handles the logic for creating an IMG_Button struct.
 *
 * @param uiManager : UIManager struct pointer
 * @param spritesheet : Spritesheet struct pointer
 * @param pos : Pos struct
 * @param txtBox : TxtBox struct pointer
 * @return A pointer to the newly created IMG_Button struct
 */
Button* createButton(Spritesheet* spritesheet, Pos pos, TxtBox* txtBox) {
    Button* btn = (Button*) malloc(sizeof(Button));
    btn->base.type = BUTTON;
    btn->base.destroy = destroyButton;
    btn->onClick = NULL;
    btn->currentState = BTN_IDLE;
    btn->aManager = createAnimationManager(spritesheet);
    btn->rect.x = pos.x - (int) (btn->aManager->spritesheet->spriteSize.w / 2);
    btn->rect.y = pos.y - (int) (btn->aManager->spritesheet->spriteSize.h / 2);
    btn->rect.w = btn->aManager->spritesheet->spriteSize.w;
    btn->rect.h = btn->aManager->spritesheet->spriteSize.h;

    btn->txtBox = txtBox;
    if (btn->txtBox && btn->txtBox->type == TXT_BOX_FILL) {
        int diffX = btn->txtBox->outer.x - btn->txtBox->inner.x;
        int diffY = btn->txtBox->outer.y - btn->txtBox->inner.y;
        int diffW = btn->txtBox->outer.w - btn->txtBox->inner.w;
        int diffH = btn->txtBox->outer.h - btn->txtBox->inner.h;
        float ratX, ratY, ratW, ratH;
        if (diffX != 0) ratX = (float) btn->txtBox->outer.x / diffX;
        else ratX = 0;
        if (diffY != 0) ratY = (float) btn->txtBox->outer.y / diffY;
        else ratY = 0;
        if (diffW != 0) ratW = (float) btn->txtBox->outer.w / diffW;
        else ratW = 0;
        if (diffH != 0) ratH = (float) btn->txtBox->outer.h / diffH;
        else ratH = 0;
        btn->txtBox->outer = btn->rect;
        btn->txtBox->inner.x = btn->txtBox->outer.x + (int) (ratX * btn->txtBox->outer.x);
        btn->txtBox->inner.y = btn->txtBox->outer.y + (int) (ratY * btn->txtBox->outer.y);
        btn->txtBox->inner.w = btn->txtBox->outer.w + (int) (ratW * btn->txtBox->outer.w);
        btn->txtBox->inner.h = btn->txtBox->outer.h + (int) (ratH * btn->txtBox->outer.h);
    }

    return btn;
}

/**
 * @author DargoDargonyx
 * @date 04/23/2026
 * @brief Handles the logic for destroying a Button struct.
 *
 * @param self : Widget struct pointer
 * @return A pointer to an Error struct that describes whether
 * or not the Button struct in question was successfully
 * destroyed
 */
Error* destroyButton(Widget* self) {
    if (!self) return createError(UI, "Could not destroy a NULL Image Button");

    Button* btn = (Button*) self;
    Error* err = destroyAnimationManager(btn->aManager);
    if (err) return err;
    if (btn->txtBox) err = btn->txtBox->base.destroy((Widget*) btn->txtBox);

    free(btn);
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Helper function to handle the logic for creating the UI
 * elements for the start menu.
 *
 * @param uiManager : UIManager struct pointer
 * @param loader : SceneLoader pointer
 * @param renderer : SDL_Renderer pointer
 * @param screenSize : Size struct
 * @return A pointer to an Error struct that describes whether
 * or not the UI elements were successfully created
 */
Error* createStartMenuUI(UIManager* uiManager, SceneLoader* loader, SDL_Renderer* renderer,
                         Size screenSize) {

    Error* err = NULL;
    Size btnSpritesheetSize = (Size){BTN_SPRITESHEET_WIDTH, BTN_SPRITESHEET_HEIGHT};
    Size nullSize = (Size){0, 0};

    // Start Button
    const char* sbImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    Spritesheet* sbSpritesheet = createSpritesheet(uiManager->errCont, renderer, sbImgPath,
                                                   btnSpritesheetSize, BTN_SPRITESHEET_COUNT);
    const char* sbText = "Start Game";
    int sbVertSpacing = -35;
    Pos sbPos = {screenSize.w / 2, (screenSize.h / 2) + sbVertSpacing};
    TxtBox* sbTxtBox =
        createTxtBox(uiManager, renderer, TXT_BOX_FILL, sbText, JETBRAINS_MONO, sbPos, nullSize);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    Button* sBtn = createButton(sbSpritesheet, sbPos, sbTxtBox);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    err = addWidgetToManager(uiManager, (Widget*) sBtn);
    if (err) return err;

    sBtn->onClick = (void*) loader->playScene;
    sBtn->userData = loader;

    // Options Button
    const char* obImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    Spritesheet* obSpritesheet = createSpritesheet(uiManager->errCont, renderer, obImgPath,
                                                   btnSpritesheetSize, BTN_SPRITESHEET_COUNT);
    const char* obText = "Options";
    int obVertSpacing = 65;
    Pos obPos = {screenSize.w / 2, (screenSize.h / 2) + obVertSpacing};
    TxtBox* obTxtBox =
        createTxtBox(uiManager, renderer, TXT_BOX_FILL, obText, JETBRAINS_MONO, obPos, nullSize);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    Button* oBtn = createButton(obSpritesheet, obPos, obTxtBox);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    oBtn->onClick = (void*) loader->optionsMenu;
    oBtn->userData = loader;
    err = addWidgetToManager(uiManager, (Widget*) oBtn);
    if (err) return err;

    // Exit Button
    const char* ebImgPath = "../assets/sprites/ui/start_menu/main_button.png";
    Spritesheet* ebSpritesheet = createSpritesheet(uiManager->errCont, renderer, ebImgPath,
                                                   btnSpritesheetSize, BTN_SPRITESHEET_COUNT);
    const char* ebText = "Exit";
    int ebVertSpacing = 165;
    Pos ebPos = {screenSize.w / 2, (screenSize.h / 2) + ebVertSpacing};
    TxtBox* ebTxtBox =
        createTxtBox(uiManager, renderer, TXT_BOX_FILL, ebText, JETBRAINS_MONO, ebPos, nullSize);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    Button* eBtn = createButton(ebSpritesheet, ebPos, ebTxtBox);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    eBtn->onClick = (void*) loader->exit;
    eBtn->userData = loader;
    err = addWidgetToManager(uiManager, (Widget*) eBtn);

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Helper function to handle the logic for creating the UI
 * elements for the options menu.
 *
 * @param uiManager : UIManager struct pointer
 * @param loader : SceneLoader pointer
 * @param renderer : SDL_Renderer pointer
 * @param screenSize : Size struct
 * @return A pointer to an Error struct that describes whether
 * or not the UI elements were successfully created
 */
Error* createOptionsMenuUI(UIManager* uiManager, SceneLoader* loader, SDL_Renderer* renderer,
                           Size screenSize) {

    Error* err = NULL;
    Size btnSpritesheetSize = (Size){BTN_SPRITESHEET_WIDTH, BTN_SPRITESHEET_HEIGHT};
    Size nullSize = (Size){0, 0};

    // Return button
    const char* rbImgPath = "../assets/sprites/ui/options_menu/main_button.png";
    Spritesheet* rbSpritesheet = createSpritesheet(uiManager->errCont, renderer, rbImgPath,
                                                   btnSpritesheetSize, BTN_SPRITESHEET_COUNT);
    const char* rbText = "Return";
    Pos rbPos = {screenSize.w / 2, screenSize.h / 2};
    TxtBox* rbTxtBox =
        createTxtBox(uiManager, renderer, TXT_BOX_FILL, rbText, JETBRAINS_MONO, rbPos, nullSize);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    Button* rBtn = createButton(rbSpritesheet, rbPos, rbTxtBox);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    rBtn->onClick = (void*) loader->startMenu;
    rBtn->userData = loader;
    err = addWidgetToManager(uiManager, (Widget*) rBtn);

    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/24/2026
 * @brief Helper function to handle the logic for creating the UI
 * elements for the playing scene.
 *
 * @param uiManager : UIManager struct pointer
 * @param loader : SceneLoader pointer
 * @param renderer : SDL_Renderer pointer
 * @return A pointer to an Error struct that describes whether
 * or not the UI elements were successfully created
 */
Error* createPlaySceneUI(UIManager* uiManager, SceneLoader* loader, SDL_Renderer* renderer) {
    Error* err = NULL;
    Size btnSpritesheetSize = (Size){BTN_SPRITESHEET_WIDTH, BTN_SPRITESHEET_HEIGHT};

    // Back button
    const char* backBtnImgPath = "../assets/sprites/ui/play_scene/back_button.png";
    Spritesheet* backBtnSpritesheet = createSpritesheet(
        uiManager->errCont, renderer, backBtnImgPath, btnSpritesheetSize, BTN_SPRITESHEET_COUNT);
    Pos backBtnPos = {40, 40};
    Button* backBtn = createButton(backBtnSpritesheet, backBtnPos, NULL);
    if (uiManager->errCont->count > 0) return uiManager->errCont->errs[0];
    backBtn->onClick = (void*) loader->startMenu;
    backBtn->userData = loader;
    err = addWidgetToManager(uiManager, (Widget*) backBtn);

    return err;
}
