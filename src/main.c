/**
 * @file main.c
 * @author DargoDargonyx
 * @date 04/05/2026
 */

#include "util/error.h"
#include "util/helper.h"
#include "util/window.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_WIN_WIDTH 1200
#define DEFAULT_WIN_HEIGHT 800
#define GAME_NAME "SlayMySanity"

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Helper function to print an error message.
 *
 * @param err : Error struct
 * @return An integer representation of a boolean for whether
 * or not the error given was valid (not none)
 */
int printErrorMsg(Error err) {
    if (err.statusNum != ESTAT_MAIN_NONE) {
        printf("ERROR {%s}: %s.\n", getErrorStatusDesc(&err), err.msg);
        return 1;
    }
    return 0;
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief The main function for the program.
 *
 * @param argc : integer
 * @param argv : An array of c-style strings
 * @return An integer representation of a boolean for whether
 * or not the program encountered an error.
 */
int main(int argc, char** argv) {
    Error err = createError(ESTAT_MAIN_NONE, NULL);
    Size wSize;

    switch (argc) {
        case 1:
            wSize = (Size){DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT};
            break;
        case 2:
            printf("Usage: ./game <window_width> <window_height>\n");
            err = createError(ESTAT_MAIN_LOAD,
                              "Invalid number of arguments given");
            return printErrorMsg(err);
            break;
        case 3: {
            char* end;
            wSize.w = (int) strtol(argv[1], &end, 10);
            if (*end != '\0') {
                err = createError(ESTAT_MAIN_LOAD, "Invalid number given");
                return printErrorMsg(err);
            }
            wSize.h = (int) strtol(argv[2], &end, 10);
            if (*end != '\0') {
                err = createError(ESTAT_MAIN_LOAD, "Invalid number given");
                return printErrorMsg(err);
            }

            break;
        }
        default:
            printf("Usage: ./game <window_width> <window_height>\n");
            err = createError(ESTAT_MAIN_LOAD,
                              "Invalid number of arguments given");
            return printErrorMsg(err);
            break;
    }

    err = runGameWindow(GAME_NAME, wSize);
    return printErrorMsg(err);
}
