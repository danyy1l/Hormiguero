/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Danyyil Shykerynets
 * @version 0
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "player.h"
#include "object.h"
#include "space.h"
#include "types.h"

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


Status game_destroy(Game *game);


Command* game_get_last_command(Game *game);


Status game_set_last_command(Game *game, Command *command);


Bool game_get_finished(Game *game);


Status game_set_finished(Game *game, Bool finished);


void game_print(Game *game);

#endif
