/**
 * @file error.h
 * @author DargoDargonyx
 * @date 04/03/2026
 * @brief Handles the logic for error handling.
 */

#ifndef ERROR_H
#define ERROR_H

#define ERR_CONTAINER_INIT_CAP 15

// error and main
#define ESTAT_MAIN_NONE 0x0
#define ESTAT_MAIN_LOAD 0x1
#define ESTAT_ERR_CONTAINER_CREATE 0x2
#define ESTAT_ERR_CONTAINER_DESTROY 0x3
#define ESTAT_ERR_CONTAINER_ADD 0x4

// window
#define ESTAT_WINDOW_INIT 0x10
#define ESTAT_WINDOW_MANAGER_CREATE 0x11
#define ESTAT_WINDOW_MANAGER_DESTROY 0x12

// engine
#define ESTAT_ENGINE_START_LOOP 0x20

// render
#define ESTAT_RENDER_LOAD_IMG 0x30
#define ESTAT_RENDER_SCENE_DRAW 0x31

// scene
#define ESTAT_SCENE_CREATE 0x40
#define ESTAT_SCENE_DESTROY 0x41
#define ESTAT_SCENE_ADD_BTN 0x42

// font
#define ESTAT_FONT_CREATE 0x50
#define ESTAT_FONT_DESTROY 0x51

// widget
#define ESTAT_WIDGET_BTN_CREATE 0x60
#define ESTAT_WIDGET_BTN_DESTROY 0x61

typedef struct {
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
