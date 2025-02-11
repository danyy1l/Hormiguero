/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Danyyil Shykerynets
 * @version 7
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "../classes/player.h"
#include "../classes/object.h"
#include "../classes/space.h"
#include "../classes/types.h"
#include "command.h"

#define MAX_SPACES 100

typedef struct _Game {
  Player *player;             /*!< Número id de localización del jugador*/
  Object *object;             /*!< Número id de localización del objeto*/
  Space *spaces[MAX_SPACES];  /*!< Array estático de un número limitado de espacios*/
  int n_spaces;               /*!< Número de espacios*/
  Command *last_cmd;          /*!< Puntero al comando*/
  Bool finished;              /*!< Valor de TRUE o FALSE*/
} Game;

/**
 * @brief Crea el juego reservando la memoria 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_create(Game *game);

/**
 * @brief Destruye el juego liberando la memoria reservada
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_destroy(Game *game);

/**
 * @brief El juego obtiene el último comando utilizado
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return Un puntero a Command
 */
Command* game_get_last_command(Game *game);

/**
 * @brief El juego define el último comando utilizado
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief El juego define el último comando utilizado
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Bool game_get_finished(Game *game);

/**
 * @brief Se define el fin del juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @param finished EL valor TRUE o FALSE
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Imprime el juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 */
void game_print(Game *game);

#endif