/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 7
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    case TAKE:
      game_actions_take(game);
      break;

    case DROP:
      game_actions_drop(game);
      break;

    default:
      break;
  }

  if( player_get_object(game->player) != NO_ID )
    object_set_location(game->object, player_get_location(game->player));

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

void game_actions_take(Game *game){
  if( player_get_object(game->player) == NO_ID && player_get_location(game->player) == object_get_location(game->object)){

    player_set_object(game->player, object_get_id(game->object));
    object_set_location(game->object, player_get_location(game->player));
  }
}

void game_actions_drop(Game *game){
  if( player_get_object(game->player) != NO_ID ){

    player_set_object(game->player, NO_ID);
    object_set_location(game->object, player_get_location(game->player));
  }
}