/**
 * @file error.h
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for error handling.
 */

#ifndef ERROR_H
#define ERROR_H

typedef enum {
    NONE,
    ANIMATION,
    CAMERA,
    ENGINE,
    ERROR,
    FONT,
    INPUT,
    MAIN,
    MAP,
    PHYSICS,
    PLAYER,
    RENDER,
    SCENE,
    SPRITE,
    UI,
    WINDOW
} ErrorType;

typedef struct {
    ErrorType type;
    const char* msg;
} Error;

typedef struct {
    int cap;
    int count;
    Error** errs;
} ErrorContainer;

Error* createError(ErrorType, const char*);
void destroyError(Error*);
const char* getErrorTypeDesc(ErrorType);
void printErrorMsg(Error*);

ErrorContainer* createErrorContainer(int);
Error* destroyErrorContainer(ErrorContainer*);
Error* addErrorToContainer(ErrorContainer*, Error*);

#endif
