/**
 * @brief Declaration of Game Rules
 * 
 * @file game_rules.h
 * @author Danyyil Shykerynets
 * @version 1
 * @date 20-04-2025
 * @copyright GNU Copyright License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"

/**
 * @brief Revisa las reglas del juego y actualiza el comando
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param last_cmd Un puntero al ultimo comando
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_rules_update(Game* game, Command *last_cmd);

#endif