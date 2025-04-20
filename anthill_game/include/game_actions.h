/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Danyyil Shykerynets
 * @version 18
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
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param cmd Un puntero a Command
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_actions_update(Game *game, Command *cmd);


/**
   Game actions declaration
*/

/**
 * @brief Realiza la accion al recibir un commando "UNKNOWN"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * No hace nada
 */
Status game_actions_unknown(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "QUIT"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * Detiene el bucle de actualizacion del juego, terminando la partida
 */
void game_actions_quit(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "MOVE"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Mueve al jugador en la direccion escrita en caso de que se puede
 */
Status game_actions_move(Game *game, Command* command);
 
/**
 * @brief Realiza la accion al recibir un commando "TAKE"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Recibe el objeto de la casilla del jugador y lo lleva consigo hasta recibir un DROP
 */
Status game_actions_take(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "DROP" y un nombre de un objeto
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Suelta el objeto del inventario del jugador en caso de haberlo
 */
Status game_actions_drop(Game *game, Command *command);

/**
 * @brief Realiza la accion al recibir un commando "ATTACK"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Ataca al personaje que haya en la misma casilla
 */
Status game_actions_attack(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "CHAT"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Imprime el mensaje del personaje de la casilla en la que nos encontremos, en caso de que lo haya
 */
Status game_actions_chat(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "INSPECT"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Imprime la descripción del objeto de la casilla en la que nos encontremos, en caso de que lo haya, o de la mochila
 */
Status game_actions_inspect(Game *game, Command *command);

/**
 * @brief Realiza la accion al recibir un commando "USE"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Usa el objeto al que se esté refiriendo, y luego el objeto desaparece
 */
Status game_actions_use(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "OPEN"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Abre un enlace con un obeto y luego este desaparece
 */
Status game_actions_open(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "SAVE"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Guarda la partida
 */
Status game_actions_save(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "LOAD"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Carga una partida guardada
 */
Status game_actions_load(Game *game, Command* command);

#endif
