/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Danyyil Shykerynets
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "player.h"
#include "object.h"

/**
 * Private functions
 */

Status game_load_spaces(Game *game, char *filename);

Status game_add_space(Game *game, Space *space);

Id game_get_space_id_at(Game *game, int position);

/**
 * Game Implementation
 */

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Status game_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  player_set_location(game, game_get_space_id_at(game, 0));
  object_set_location(game, game_get_space_id_at(game, 9));

  return OK;
}

/**
 * Implementation of private functions
 */


Status game_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}