/**
 * @brief It implements the game reading functionality
 *
 * @file game_reader.c
 * @author Danyyil Shykerynets
 * @version 7
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#include "../include/game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/space.h"
#include "../include/player.h"
#include "../include/object.h"

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

Game* game_create_from_file(char *filename) {
  Game* game = NULL;
  if (!(game = game_create())) {
    return ERROR;
  }

  if (game_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  player_set_location(game_get_player(game), game_get_space_id_at(game, 0));
  object_set_location(game_get_object(game), game_get_space_id_at(game, 9));

  return game;
}

char *game_object_check(char *objs, Game *game){
  
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID;
  Space *space_act = NULL;
  
  if( (id_act = player_get_location(game_get_player(game))) != NO_ID ){
    space_act = game_get_space(game, id_act);
    id_north = space_get_north(space_act);
    id_south = space_get_south(space_act);
    id_east = space_get_east(space_act);
    id_west = space_get_west(space_act);
    
    if (object_get_location(game_get_object(game)) == id_act && player_get_object(game_get_player(game)) == NO_ID)
    objs[0] = '*';
    else
    objs[0] = ' ';

    if (object_get_location(game_get_object(game)) == id_north && player_get_object(game_get_player(game)) == NO_ID)
      objs[1] = '*';
    else
      objs[1] = ' ';


    if (object_get_location(game_get_object(game)) == id_south && player_get_object(game_get_player(game)) == NO_ID)
      objs[3] = '*';
    else
      objs[3] = ' ';


    if (object_get_location(game_get_object(game)) == id_east && player_get_object(game_get_player(game)) == NO_ID)
      objs[2] = '*';
    else
      objs[2] = ' ';


    if (object_get_location(game_get_object(game)) == id_west && player_get_object(game_get_player(game)) == NO_ID)
      objs[4] = '*';
    else
      objs[4] = ' ';

  }

  return objs;
}