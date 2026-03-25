/**
 * @file error.c
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Handles the logic for error handling.
 */

#include "util/error.h"

#include <stdio.h>


/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Creates a new Error strcut.
 *
 * @param statusNum : integer
 * @param msg : string pointer
 * @return The new Error struct
 */
Error createError(int statusNum, char* msg) {
    Error err;
    err.statusNum = statusNum;
    err.msg = msg;
    return err;
}


/**
 * @author DargoDargonyx
 * @date 03/25/2026
 * @brief Gets a quick description of an error.
 *
 * This function gets a quick description of an error
 * when given an Error struct depending on the status
 * number relating to the error.
 *
 * @note Status numbers are defined in the header file.
 * @param err : Error struct
 * @return The description of the error as a string pointer
 */
char* getErrorStatusDesc(Error* err) {
    static char str[20];
    switch(err->statusNum) {
        case ESTAT_NONE:
            sprintf(str, "No status");
            break;
        case ESTAT_WINDOW:
            sprintf(str, "Window Error");
            break;
        default:
            break;
    }
    return str;
}
