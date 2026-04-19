/**
 * @file error.c
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for error handling.
 */

#include "util/error.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating a new Error struct.
 *
 * @param type : ErrorType enum
 * @param msg : c-style string literal
 * @return A pointer to the new Error struct in question
 */
Error* createError(ErrorType type, const char* msg) {
    Error* err = (Error*) malloc(sizeof(Error));
    err->type = type;
    err->msg = msg;
    return err;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying an Error struct.
 *
 * @param err : Error struct pointer
 */
void destroyError(Error* err) { free(err); }

const char* getErrorTypeDesc(ErrorType type) {
    switch (type) {
        case NONE:
            return "Null Error";
            break;
        case CAMERA:
            return "Camera Error";
            break;
        case ENGINE:
            return "Game Engine Error";
            break;
        case ERROR:
            return "Error Handling Error";
            break;
        case FONT:
            return "Font Error";
            break;
        case INPUT:
            return "Input Error";
            break;
        case MAIN:
            return "Main Function Error";
            break;
        case MAP:
            return "Map Error";
            break;
        case PHYSICS:
            return "Game Physics Error";
            break;
        case PLAYER:
            return "Player Error";
            break;
        case RENDER:
            return "Rendering Error";
            break;
        case SCENE:
            return "Scene Error";
            break;
        case SPRITE:
            return "Sprite Error";
            break;
        case UI:
            return "UI Error";
            break;
        case WINDOW:
            return "Window Error";
            break;
        default:
            return "Unknown Error";
            break;
    }
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for printing an Error message
 * when given an Error struct pointer
 *
 * @param err : Error struct pointer
 */
void printErrorMsg(Error* err) {
    const char* typeDesc = getErrorTypeDesc(err->type);
    printf("{%s} %s", typeDesc, err->msg);
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for creating a new Error
 * Container struct.
 *
 * @param initCap : integer
 * @return A pointer to the newly created ErrorContainer struct
 */
ErrorContainer* createErrorContainer(int initCap) {
    ErrorContainer* container =
        (ErrorContainer*) malloc(sizeof(ErrorContainer));

    container->count = 0;
    container->cap = initCap;
    container->errs = (Error**) calloc(container->cap, sizeof(Error*));
    return container;
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for destroying an ErrorContainer struct.
 *
 * @return A pointer to an Error struct that describes whether
 * or not the ErrorContainer struct in question was successfully
 * destroyed
 */
Error* destroyErrorContainer(ErrorContainer* self) {
    if (!self)
        return createError(ERROR, "Could not destroy a NULL Error Container");

    free(self->errs);
    free(self);
    return createError(NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 04/19/2026
 * @brief Handles the logic for adding an Error struct to an
 * Error Container struct.
 *
 * @param container : ErrorContainer struct pointer
 * @return An Error struct that describes whether or not the
 * Error struct was successfully added to the ErrorContainer struct.
 */
Error* addErrorToContainer(ErrorContainer* errCont, Error* err) {
    if (!errCont)
        return createError(ERROR,
                           "Could not add an Error to a NULL Error Container");

    if (errCont->count == errCont->cap) {
        errCont->cap = (errCont->count + 1) * 2;
        Error** orig = errCont->errs;
        Error** temp = (Error**) calloc(errCont->cap, sizeof(Error*));
        if (!temp)
            return createError(
                ERROR, "Could not reallocate a larger Error array field");

        for (int i = 0; i < errCont->count; i++) { temp[i] = orig[i]; }
        free(orig);
        errCont->errs = temp;
    }

    errCont->errs[errCont->count++] = err;
    return createError(NONE, NULL);
}
