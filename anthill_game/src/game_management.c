/**
 * @brief It implements the game reading functionality
 *
 * @file game_management.c
 * @author Hugo Martín
 * @version 7
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#include "../include/game_management.h"

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
  Id id = NO_ID;
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
      for(i=0; i<GDESC_MAX; i++){
        toks = strtok(NULL, "|");
        space_set_gdesc(space, toks, i);
      }
      #ifdef DEBUG
      printf("Leido: %ld|%s|\n", id, name);
      #endif
      space_set_name(space, name);
      game_add_space(game, space);
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}

Status game_load_links(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  Id id = NO_ID, origin = NO_ID, destination = NO_ID;
  Direction direction;
  Bool open;
  char *toks = NULL;

  Link *link = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      origin= atol(toks);
      toks = strtok(NULL, "|");
      destination = atol(toks);
      toks = strtok(NULL, "|");
      direction = atoi(toks);
      toks = strtok(NULL, "|");
      open = atoi(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%d|%d\n", id, name, origin, destination, direction, open);
  #endif
      if( !(link = link_create()) ){ return ERROR; }
      link_set_id(link, id);
      link_set_name(link, name);
      link_set_origin(link, origin);
      link_set_destination(link, destination);
      link_set_direction(link, direction);
      link_set_open(link, open);

      game_add_link(game, link);
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  
  return status;
}

Status game_load_players(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[PLY_GDESC] = "";
  int health, bag_max;
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Player* player = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      bag_max = atoi(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, location);
  #endif
      if( !(player = player_create()) ) return ERROR;
      player_set_id(player, id);
      player_set_name(player, name);
      player_set_gdesc(player, gdesc);
      player_set_location(player, location);
      player_set_health(player, health);
      inventory_set_max_objects(player_get_objects(player), bag_max);
      game_add_player(game, player);
      space_player_arrive(game_get_space(game, location));
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  
  return status;
}

Status game_load_objects(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID, dependency = NO_ID, open = NO_ID; 
  Object *object = NULL;
  Status status = OK;
  int health;
  Bool movable;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) { 
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      movable = atoi(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s|%d|%d|%ld|%ld\n", id, name, location, description, health, movable, dependency, open);
  #endif
      if( !(object = object_create(id))) return ERROR;
      object_set_name(object, name);
      object_set_location(object, location);
      object_set_description(object, description);
      object_set_health(object, health);
      object_set_movable(object, movable);
      object_set_dependency(object, dependency);
      object_set_open(object, open);
      game_add_object(game, object);
      space_add_object(game_get_space(game, location), id);
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  
  return status;
}

Status game_load_characters(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESC_SIZE] = "";
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  int health;
  Bool friendly;
  Id id = NO_ID, location = NO_ID, following = NO_ID;

  Character *character = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      friendly = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);
      toks =strtok(NULL,"|");
      following =atol(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%s|%d|%d|%s|%ld|%ld\n", id, name, gdesc, health, friendly, message, location,following);
  #endif
      if( !(character = character_create()) ){ return ERROR; }
      character_set_id(character, id);
      character_set_location(character, location);
      character_set_name(character, name);
      character_set_gdesc(character, gdesc);
      character_set_health(character, health);
      character_set_friendly(character, friendly);
      character_set_message(character, message);
      character_set_following(character,following);

      game_add_character(game, character);
      space_add_character(game_get_space(game, location), id);
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
  printf("Initialized\n");
  if (!(game = game_create())) {
    return ERROR;
  }
  printf("Game created\n");

  if (game_load_spaces(game, filename) == ERROR) return ERROR;
  printf("Spaces created\n");
  
  if (game_load_links(game, filename) == ERROR) return ERROR;
  printf("Links created\n");

  if( game_load_players(game, filename) == ERROR) return ERROR;
  printf("Players loaded\n");

  if(game_load_objects(game, filename) == ERROR) return ERROR;
  printf("Objects loaded\n");
  
  if(game_load_characters(game, filename) == ERROR) return ERROR;
  printf("Characters loaded\n");

  return game;
}

Status game_management_save(Game *game, char *filename) {
  FILE *f=NULL;
  int i, j;
  Id *ids=NULL;
  Object **objects=game_get_objects(game), *object=NULL;
  Character **characters=game_get_characters(game), *character=NULL;
  Space **spaces=game_get_spaces(game), *space=NULL;
  Link **links=game_get_links(game), *link=NULL;
  Command *command=game_get_last_command(game);

  if (!game || !filename || !(f=fopen(filename, "w"))) {
    return ERROR;
  }

  fprintf(f, "GAME_START\n\n\n");
  fprintf(f, "PLAYERS_START\n");
  fprintf(f, "NUM_PLAYERS=%d\n", game_get_n_players(game));

  for (i=0;i<game_get_n_players(game);i++) {
    game_next_turn(game, i);
    fprintf(f, "\nplayer_id=%ld;name=%s;location=%ld;gdesc=%s;health=%d;num_objects=%d\n", player_get_id(game_get_player(game)), player_get_name(game_get_player(game)), player_get_location(game_get_player(game)), player_get_gdesc(game_get_player(game)), player_get_health(game_get_player(game)), set_get_nids(inventory_get_objects(player_get_objects(game_get_player(game)))));
    fprintf(f, "Objects: ");
    ids=set_id_object(inventory_get_objects(player_get_objects(game_get_player(game))));
    for (j=0;j<set_get_nids(inventory_get_objects(player_get_objects(game_get_player(game))));j++) {
      fprintf(f, "id=%ld;", ids[j]);
    }
  }

  fprintf(f, "\n\nPLAYERS_END\n\n\n");
  fprintf(f, "OBJECTS_START\n");
  fprintf(f, "NUM_OBJECTS=%d\n\n", game_get_n_objects(game));

  for (i=0;i<game_get_n_objects(game);i++) {
    object=objects[i];
    fprintf(f, "object_id=%ld;name=%s;location=%ld;description=%s;taken=%d;health=%d;movable=%d;dependency=%ld;open=%ld\n", object_get_id(object), object_get_name(object), object_get_location(object), object_get_description(object), object_get_taken(object), object_get_health(object), object_get_movable(object), object_get_dependency(object), object_get_open(object));
  }

  fprintf(f, "\nOBJECTS_END\n\n\n");
  fprintf(f, "CHARACTER_START\n");
  fprintf(f, "NUM_CHARACTERS=%d\n\n", game_get_n_characters(game));

  for (i=0;i<game_get_n_characters(game);i++) {
    character=characters[i];
    fprintf(f, "character_id=%ld;name=%s;location=%ld;gdesc=%s;health=%d;friendly=%d;message=%s;following=%ld\n", character_get_id(character), character_get_name(character), character_get_location(character), character_get_gdesc(character), character_get_health(character), character_get_friendly(character), character_get_message(character), character_get_following(character));
  }

  fprintf(f, "\nCHARACTERS_END\n\n\n");
  fprintf(f, "SPACES_START\n");
  fprintf(f, "NUM_SPACES=%d\n", game_get_n_spaces(game));

  for (i=0;i<game_get_n_spaces(game);i++) {
    space=spaces[i];
    fprintf(f, "\nspace_id=%ld;name=%s;discovered=%d;num_objects=%d;num_characters=%d\n", space_get_id(space), space_get_name(space), space_get_discovered(space), set_get_nids(space_get_set_objects(space)), set_get_nids(space_get_set_characters(space)));
    fprintf(f, "Objects: ");
    ids=set_id_object(space_get_set_objects(space));
    for (j=0;j<set_get_nids(space_get_set_objects(space));j++) {
      fprintf(f, "id=%ld;", ids[j]);
    }
    fprintf(f, "\nCharacters: ");
    ids=set_id_object(space_get_set_characters(space));
    for (j=0;j<set_get_nids(space_get_set_characters(space));j++) {
      fprintf(f, "id=%ld;", ids[j]);
    }
  }

  fprintf(f, "\n\nSPACES_END\n\n\n");
  fprintf(f, "LINKS_START\n");
  fprintf(f, "NUM_LINKS=%d\n\n", game_get_n_links(game));

  for (i=0;i<game_get_n_links(game);i++) {
    link=links[i];
    fprintf(f, "link_id=%ld;name=%s;origin=%ld;destination=%ld;dir=%d;open=%d\n", link_get_id(link), link_get_name(link), link_get_origin(link), link_get_destination(link), link_get_direction(link), link_get_open(link));
  }

  fprintf(f, "\nLINKS_END\n\n\n");
  fprintf(f, "LAST_COMMAND\n");
  fprintf(f, "code=%d;output=%d;arguments=%s;argumments1=%s;arguments2=%s\n", command_get_code(command), command_get_output(command), command_get_arguments(command), command_get_arguments1(command), command_get_arguments2(command));

  fprintf(f, "\n\nTURN=%d", game_get_turn(game));

  fprintf(f, "\n\n\nGAME_END");

  fclose(f);

  return OK;
}

Status game_management_load(Game *game, char *filename) {

}
