/**
 * @file player.c
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for the main player.
 */

#include "world/player.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for creating a Player struct.
 *
 * @param origPos : Pos struct
 * @param speed : float
 * @return A pointer to the Player struct in question
 */
Player* createPlayer(Pos origPos, float speed) {
    Player* player = (Player*) malloc(sizeof(Player));
    player->pos = origPos;
    player->speed = speed;
    return player;
}

/**
 * @author DargoDargonyx
 * @date 04/05/2026
 * @brief Handles the logic for creating a Player struct.
 *
 * @note This functin may seeem redundant right now but it's
 * to prepare for future expansions in the code.
 *
 * @param self : Player struct pointer
 * @return An Error struct describing whether or not the Player
 * struct in question was successfully destroyed
 */
Error destroyPlayer(Player* self) {
    free(self);
    return createError(ESTAT_MAIN_NONE, NULL);
}
