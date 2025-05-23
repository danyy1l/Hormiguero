/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Danyyil Shykerynets
 * @version 22
 * @date 24-04-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "types.h"
#include "command.h"
#include "game.h"

/**
 * @brief Actualiza las acciones del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param command Un puntero a Command
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_actions_update(Game *game, Command *command);

#endif
