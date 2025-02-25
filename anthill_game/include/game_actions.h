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

#include "types.h"
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

/**
 * @brief Realiza la accion al recibir un commando "UNKNOWN"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * No hace nada
 */
void game_actions_unknown(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "QUIT"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * Detiene el bucle de actualizacion del juego, terminando la partida
 */
void game_actions_quit(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "NORTH"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Mueve al jugador al sur en caso de que se puede
 */
void game_actions_north(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "SOUTH"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Mueve al jugador al sur en caso de que sea posible
 */
void game_actions_south(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "EAST"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Se mueve hacia el este en caso de que sea posible
 */
void game_actions_east(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "WEST"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Se mueve hacia el oeste en caso posible
 */
void game_actions_west(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "TAKE"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * Recibe el objeto de la casilla del jugador y lo lleva consigo hasta recibir un DROP
 */
void game_actions_take(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "DROP"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Suelta el objeto del inventario del jugador en caso de haberlo
 */
void game_actions_drop(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "ATTACK"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Ataca al personaje que haya en la misma casilla
 */
void game_actions_attack(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "CHAT"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Recibe el mensaje del personaje de la casilla en la que nos encontremos, en caso de que lo haya
 */
void game_actions_chat(Game *game);

#endif
