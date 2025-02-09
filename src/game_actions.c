/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Danyyil Shykerynets 
 * @version 0
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief Realiza la accion al recibir un commando "UNKNOWN"
 * 
 * @param game Estructura de la partida actual
 * No hace nada
 */
void game_actions_unknown(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "EXIT"
 * 
 * @param game Estructura de la partida actual
 * Abandona la partida
 */
void game_actions_exit(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "NORTH"
 * 
 * @param game Estructura de la partida actual
 * Mueve al jugador al sur en caso de que se puede
 */
void game_actions_north(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "SOUTH"
 * 
 * @param game Estructura de la partida actual
 * Mueve al jugador al sur en caso de que sea posible
 */
void game_actions_south(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "EAST"
 * 
 * @param game Estructura de la partida actual
 * Se mueve hacia el este en caso de que sea posible
 */
void game_actions_east(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "WEST"
 * 
 * @param game Estructura de la partida actual
 * Se mueve hacia el oeste en caso posible
 */
void game_actions_west(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NORTH:
      game_actions_north(game);
      break;

    case SOUTH:
      game_actions_south(game);
      break;

    case EAST:
      game_actions_east(game);
      break;

    case WEST:
      game_actions_west(game);
      break;


    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_north(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game->player);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game->player, current_id);
  }

  return;
}

void game_actions_south(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game->player);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game->player, current_id);
  }

  return;
}

void game_actions_east(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game->player);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game->player, current_id);
  }

  return;
}

void game_actions_west(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game->player);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game->player, current_id);
  }

  return;
}
