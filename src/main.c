/**
 * @file main.c
 * @author DargoDargonyx
 * @date 04/03/2026
 */

#include "util/error.h"
#include "util/window.h"

#include <stdio.h>

#define W_WIDTH 800
#define W_HEIGHT 600
#define GAME_NAME "SlayMySanity"

/**
 * @author DargoDargonyx
 * @date 04/03/2026
 */
int main() {
    Error err = runGameWindow(GAME_NAME, W_WIDTH, W_HEIGHT);

    if (err.statusNum != ESTAT_MAIN_NONE)
        printf("ERROR {%s}: %s.\n", getErrorStatusDesc(&err), err.msg);
    return err.statusNum;
}
