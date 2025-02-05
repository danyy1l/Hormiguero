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
#include "space.h"
#include "types.h"

#define MAX_SPACES 100

typedef struct _Game {
  Id player_location;
  Id object_location;
  Space *spaces[MAX_SPACES];
  int n_spaces;
  Command *last_cmd;
  Bool finished;
} Game;

Status game_create(Game *game);

Status game_destroy(Game *game);

Command* game_get_last_command(Game *game);

Status game_set_last_command(Game *game, Command *command);

Bool game_get_finished(Game *game);

Status game_set_finished(Game *game, Bool finished);

void game_print(Game *game);

#endif
