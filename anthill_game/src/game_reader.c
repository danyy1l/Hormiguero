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
  int i;

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

      if( !(space = space_create(id)))
        return ERROR;

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
      for(i=0; i<GDESC_MAX; i++){
        toks = strtok(NULL, "|");
        space_set_gdesc(space, toks, i);
      }
#ifdef DEBUG
printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space_set_name(space, name);
      space_set_north(space, north);
      space_set_east(space, east);
      space_set_south(space, south);
      space_set_west(space, west);
      game_add_space(game, space);
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  
  return status;
}

Status game_load_objects(Game *game, char *filename){
  int i;
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  i=0;
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, location);
  #endif
      object = object_create(id);
      object_set_name(object, name);
      object_set_location(object, location);
      game_add_object(game, object);
      space_add_object(game_get_space(game, location), id);
      i++;
    }
  }
  
  game_set_n_objects(game, i);

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  
  return status;
}

Status game_load_characters(Game *game, char *filename){
  int i;
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESC_SIZE] = "";
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  int health;
  Bool friendly;
  Id id = NO_ID, location = NO_ID;

  Character *character = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  i=0;
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      friendly = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%s|%d|%d|%s|%ld\n", id, name, gdesc, health, friendly, message, location);
  #endif
      if( !(character = character_create()) ){ return ERROR; }
      character_set_id(character, id);
      character_set_location(character, location);
      character_set_name(character, name);
      character_set_gdesc(character, gdesc);
      character_set_health(character, health);
      character_set_friendly(character, friendly);
      character_set_message(character, message);

      game_add_character(game, character);
      space_set_character(game_get_space(game, location), character_get_id(character));
      i++;
    }
  }
  
  game_set_n_characters(game, i);

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  
  return status;
}

Game* game_create_from_file(char *filename) {
  Game* game = NULL;
  printf("Initialized\n");
  if (!(game = game_create())) {
    return ERROR;
  }
  printf("Game created\n");

  if (game_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }
  printf("Spaces created\n");
  
  if(game_load_objects(game, filename) == ERROR){
    return ERROR;
  }
  printf("Objects loaded\n");
  
  if(game_load_characters(game, filename) == ERROR){
    return ERROR;
  }
  printf("Characters loaded\n");  
  /* The player is located in the first space */
  player_set_location(game_get_player(game), game_get_space_id_at(game, 0));
  player_set_health(game_get_player(game), 10);

  return game;
}