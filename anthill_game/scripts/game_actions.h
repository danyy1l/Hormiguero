/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 7
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "../classes/types.h"
#include "command.h"
#include "game.h"

/**
 * @brief Actualiza las acciones del juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @param cmd Un puntero a Command
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_actions_update(Game *game, Command *cmd);

#endif
