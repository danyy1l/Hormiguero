/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Danyyil Shykerynets
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "object.h"

/**
   Game interface implementation
*/

Status game_create(Game *game) {
  int i;

  if( !game ) { return ERROR; }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  if( !(game->player = player_create()) ) { return ERROR; }
  if( !(game->object = object_create(OBJECT_ID)) ) { return ERROR; }

  game->n_spaces = 0;
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  player_destroy(game->player);
  object_destroy(game->object);
  command_destroy(game->last_cmd);

  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: ");
  object_print(game->object);
  printf("=> Player location: ");
  player_print(game->player);
}
