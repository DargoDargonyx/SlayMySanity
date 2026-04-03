/**
 * @file main.c
 * @author DargoDargonyx
 * @date 03/25/2026
 */

#include "util/error.h"
#include "util/window.h"

#include <stdio.h>

#define W_WIDTH 800
#define W_HEIGHT 600

char GAME_NAME[] = "SlayMySanity";

/**
 * @author DargoDargonyx
 * @date 03/25/2026
 */
int main() {
    Error err = runGameWindow(GAME_NAME, W_WIDTH, W_HEIGHT);

    if (err.statusNum != ESTAT_NONE)
        printf("ERROR {%s}: %s.\n", getErrorStatusDesc(&err), err.msg);
    return err.statusNum;
}
