/**
 * @file error.h
 * @author DargoDargonyx
 * @date 04/08/2026
 * @brief Handles the logic for error handling.
 */

#ifndef ERROR_H
#define ERROR_H

// Here for now because I plan on redoing the error system
typedef enum {
    NONE,
    ANIMATION,
    ENGINE,
    FONT,
    MAIN,
    RENDER,
    SCENE,
    WIDGET,
    WINDOW
} ErrorType;

#define ERR_CONTAINER_INIT_CAP 15

// error and main
#define ESTAT_MAIN_NONE 0x0
#define ESTAT_MAIN_LOAD 0x1
#define ESTAT_ERR_CONTAINER_CREATE 0x2
#define ESTAT_ERR_CONTAINER_DESTROY 0x3
#define ESTAT_ERR_CONTAINER_ADD 0x4

// animation
#define ESTAT_ANIM_SEQ_ADD_FRAME 0x10
#define ESTAT_ANIM_MANAGER_ADD_SEQ 0x11
#define ESTAT_ANIM_LOAD_IMG 0x12

// window
#define ESTAT_WINDOW_INIT 0x20
#define ESTAT_WINDOW_MANAGER_CREATE 0x21
#define ESTAT_WINDOW_MANAGER_DESTROY 0x22
#define ESTAT_WINDOW_SCENE_CLEAR 0x23

// engine
#define ESTAT_ENGINE_START_LOOP 0x30

// render
#define ESTAT_RENDER_LOAD_IMG 0x40
#define ESTAT_RENDER_SCENE_DRAW 0x41
#define ESTAT_RENDER_BTN_SPRITE 0x42

// scene
#define ESTAT_SCENE_CREATE 0x50
#define ESTAT_SCENE_DESTROY 0x51
#define ESTAT_SCENE_ADD_BTN 0x52

// font
#define ESTAT_FONT_CREATE 0x60
#define ESTAT_FONT_DESTROY 0x61

// widget
#define ESTAT_WIDGET_BTN_CREATE 0x70
#define ESTAT_WIDGET_BTN_DESTROY 0x71

typedef struct {
    ErrorType type;
    int statusNum;
    const char* msg;
} Error;

typedef struct {
    int errCap;
    int errCount;
    Error* errs;
} ErrorContainer;

Error createError(int statusNum, const char* msg);
char* getErrorStatusDesc(Error* err);

ErrorContainer* createErrorContainer();
Error destroyErrorContainer(ErrorContainer* self);
Error addErrorToContainer(ErrorContainer* container, Error err);

#endif
