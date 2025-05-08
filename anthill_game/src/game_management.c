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
  Bool discovered, create;
  int i, num_objects, num_characters;
  Space **spaces=game_get_spaces(game);

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
      
      create=TRUE;
      for (i=0;i<game_get_n_spaces(game);i++) {
        if (id==space_get_id(spaces[i])) {
          create=FALSE;
          break;
        }
      }

      if (create==TRUE) {
        if( !(space = space_create(id)))
        return ERROR;
      } else if (create==FALSE) {
        space=game_get_space(game, id);
      }
      
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      for(i=0; i<GDESC_MAX; i++){
        toks = strtok(NULL, "|");
        space_set_gdesc(space, toks, i);
      }
      toks = strtok(NULL, "|");
      space_set_message1(space, toks);
      toks = strtok(NULL, "|");
      space_set_message2(space, toks);
      toks = strtok(NULL, "|");
      discovered = atoi(toks);
      space_set_discovered(space, discovered);
      if (!(toks = strtok(NULL, "|"))) {
        num_objects=0;
      } else {
        num_objects=atoi(toks);
      }
      set_set_nids(space_get_set_objects(space), num_objects);
      if (!(toks = strtok(NULL, "|"))) {
        num_characters=0;
      } else {
        num_characters=atoi(toks);
      }
      set_set_nids(space_get_set_characters(space), num_characters);
      #ifdef DEBUG
      printf("Leido: %ld|%s|\n", id, name);
      #endif
      space_set_name(space, name);
      if (create==TRUE) {
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

Status game_load_links(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  Id id = NO_ID, origin = NO_ID, destination = NO_ID;
  Direction direction;
  Bool open, create;
  char *toks = NULL;
  int i;

  Link *link = NULL, **links=game_get_links(game);
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

      create=TRUE;
      for (i=0;i<game_get_n_links(game);i++) {
        if (id==link_get_id(links[i])) {
          create=FALSE;
          break;
        }
      }

      if (create==TRUE) {
        if( !(link = link_create()) ){ return ERROR; }
      } else if (create==FALSE) {
        link=game_get_link_by_id(game, id);
      }

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
      link_set_id(link, id);
      link_set_name(link, name);
      link_set_origin(link, origin);
      link_set_destination(link, destination);
      link_set_direction(link, direction);
      link_set_open(link, open);

      if (create==TRUE) {
        game_add_link(game, link);
      }
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
  int health, strength, bag_max, n_objects, i;
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID, object_id = NO_ID;
  Player* player = NULL;
  Status status = OK;
  Object *object=NULL;
  Bool create;
  Player **players=game_get_players(game);

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

      create=TRUE;
      for (i=0;i<game_get_n_players(game);i++) {
        if (id==player_get_id(players[i])) {
          create=FALSE;
          break;
        }
      }

      if (create==TRUE) {
        if( !(player = player_create()) ) return ERROR;
      } else if (create==FALSE) {
        player=game_get_player_by_id(game, id);
      }

      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      strength = atoi(toks);
      toks = strtok(NULL, "|");
      bag_max = atoi(toks);
      if (!(toks = strtok(NULL, "|"))) {
        n_objects=0;
      } else {
        n_objects = atoi(toks);
      }
      for (i=0;i<n_objects;i++) {
        toks = strtok(NULL, "|");
        object_id = atol(toks);
        object=game_get_object(game, object_id);
        player_add_object(player, object);
      }
  #ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, location);
  #endif
      player_set_id(player, id);
      player_set_name(player, name);
      player_set_gdesc(player, gdesc);
      player_set_location(player, location);
      player_set_health(player, health);
      player_set_strength(player, strength);
      inventory_set_max_objects(player_get_objects(player), bag_max);
      set_set_nids(inventory_get_objects(player_get_objects(player)), n_objects);
      if (create==TRUE) {
        game_add_player(game, player);
        space_player_arrive(game_get_space(game, location));
      }
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
  int health, strength, i;
  Bool movable, taken, create;
  Object **objects=game_get_objects(game);

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

      create=TRUE;
      for (i=0;i<game_get_n_objects(game);i++) {
        if (id==object_get_id(objects[i])) {
          create=FALSE;
          break;
        }
      }

      if (create==TRUE) {
        if( !(object = object_create(id))) return ERROR;
      } else if (create==FALSE) {
        object=game_get_object(game, id);
      }

      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      strength = atoi(toks);
      toks = strtok(NULL, "|");
      movable = atoi(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      taken = atoi(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s|%d|%d|%ld|%ld|%d|\n", id, name, location, description, health, strength, movable, dependency, open);
  #endif
      object_set_name(object, name);
      object_set_location(object, location);
      object_set_description(object, description);
      object_set_health(object, health);
      object_set_strength(object, strength);
      object_set_movable(object, movable);
      object_set_dependency(object, dependency);
      object_set_open(object, open);
      object_set_taken(object, taken);
      if (create==TRUE) {
        game_add_object(game, object);
        space_add_object(game_get_space(game, location), id);
      }
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
  int health, strength, i;
  Bool friendly, create;
  Id id = NO_ID, location = NO_ID, following = NO_ID;
  Character **characters=game_get_characters(game);
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

      create=TRUE;
      for (i=0;i<game_get_n_characters(game);i++) {
        if (id==character_get_id(characters[i])) {
          create=FALSE;
          break;
        }
      }

      if (create==TRUE) {
        if( !(character = character_create()) ){ return ERROR; }
      } else if (create==FALSE) {
        character=game_get_character(game, id);
      }

      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      strength = atoi(toks);
      toks = strtok(NULL, "|");
      friendly = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);
      toks =strtok(NULL,"|");
      following =atol(toks);
  #ifdef DEBUG
      printf("Leido: %ld|%s|%s|%d|%d|%s|%ld|%ld\n", id, name, gdesc, health, friendly, message, location,following);
  #endif
      character_set_id(character, id);
      character_set_location(character, location);
      character_set_name(character, name);
      character_set_gdesc(character, gdesc);
      character_set_health(character, health);
      character_set_strength(character, strength);
      character_set_friendly(character, friendly);
      character_set_message(character, message);
      character_set_following(character,following);

      if (create==TRUE) {
        game_add_character(game, character);
        space_add_character(game_get_space(game, location), id);
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
  char *gdesc = NULL;

  if (!game || !filename || !(f=fopen(filename, "w"))) {
    return ERROR;
  }

  fprintf(f, "#ns:%d|\n", game_get_n_spaces(game));

  fprintf(f, "#np:%d|\n", game_get_n_players(game));

  fprintf(f, "#nc:%d|\n", game_get_n_characters(game));

  fprintf(f, "#nl:%d|\n", game_get_n_links(game));

  fprintf(f, "#no:%d|\n", game_get_n_objects(game));

  fprintf(f, "#lc:%d|%d|", command_get_code(command), command_get_output(command));

  if (command_get_arguments(command)==NULL || strlen(command_get_arguments(command))==0) {
    fprintf(f, " |");
  } else {
    fprintf(f, "%s|", command_get_arguments(command));
  }

  if (command_get_arguments1(command)==NULL || strlen(command_get_arguments1(command))==0) {
    fprintf(f, " |");
  } else {
    fprintf(f, "%s|", command_get_arguments1(command));
  }

  if (command_get_arguments2(command)==NULL || strlen(command_get_arguments2(command))==0) {
    fprintf(f, " |\n");
  } else {
    fprintf(f, "%s|\n", command_get_arguments2(command));
  }

  fprintf(f, "#t:%d|\n\n", game_get_turn(game));

  for (i=0;i<game_get_n_spaces(game);i++) {
    space=spaces[i];
    fprintf(f, "#s:%ld|%s|", space_get_id(space), space_get_name(space));
    for (j=0; j<GDESC_MAX; j++) {
      gdesc=space_get_gdesc(space, j);
      if (gdesc == NULL || strlen(gdesc) == 0) {
          fprintf(f, " |");
      } else {
          fprintf(f, "%s|", gdesc);
      }
    }
    fprintf(f, "%s|%s|%d|%d|%d|", space_get_message1(space), space_get_message2(space), space_get_discovered(space), set_get_nids(space_get_set_objects(space)), set_get_nids(space_get_set_characters(space)));
    fprintf(f, "\n");
  }

  fprintf(f, "\n");

  for (i=0;i<game_get_n_players(game);i++) {
    game_next_turn(game, i);
    fprintf(f, "#p:%ld|%s|%s|%ld|%d|%d|%d|%d|", player_get_id(game_get_player(game)), player_get_name(game_get_player(game)), player_get_gdesc(game_get_player(game)), player_get_location(game_get_player(game)), player_get_health(game_get_player(game)), player_get_strength(game_get_player(game)), inventory_get_max_objects(player_get_objects(game_get_player(game))), set_get_nids(inventory_get_objects(player_get_objects(game_get_player(game)))));
    ids=set_id_object(inventory_get_objects(player_get_objects(game_get_player(game))));
    for (j=0;j<set_get_nids(inventory_get_objects(player_get_objects(game_get_player(game))));j++) {
      fprintf(f, "%ld|", ids[j]);
    }
    fprintf(f, "\n");
  }

  fprintf(f, "\n");

  for (i=0;i<game_get_n_characters(game);i++) {
    character=characters[i];
    fprintf(f, "#c:%ld|%s|%s|%ld|%d|%d|%d|%s|%ld|\n", character_get_id(character), character_get_name(character), character_get_gdesc(character), character_get_location(character), character_get_health(character), character_get_strength(character), character_get_friendly(character), character_get_message(character), character_get_following(character));
  }

  fprintf(f, "\n");

  for (i=0;i<game_get_n_links(game);i++) {
    link=links[i];
    fprintf(f, "#l:%ld|%s|%ld|%ld|%d|%d|\n", link_get_id(link), link_get_name(link), link_get_origin(link), link_get_destination(link), link_get_direction(link), link_get_open(link));
  }

  fprintf(f, "\n");

  for (i=0;i<game_get_n_objects(game);i++) {
    object=objects[i];
    fprintf(f, "#o:%ld|%s|%ld|%s|%d|%d|%d|%ld|%ld|%d|\n", object_get_id(object), object_get_name(object), object_get_location(object), object_get_description(object), object_get_health(object), object_get_strength(object), object_get_movable(object), object_get_dependency(object), object_get_open(object), object_get_taken(object));
  }

  fclose(f);

  return OK;
}

Status game_management_load(Game *game, char *filename) {
  FILE *f=NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  int ns = 0, np = 0, nc = 0, nl = 0, no = 0, t = 0;
  char arguments[WORD_SIZE] = "", arguments1[WORD_SIZE] = "", arguments2[WORD_SIZE] = "";
  CommandCode code;
  Status output;
  Command *cmd=game_get_last_command(game);

  if (!game || !filename || !(f=fopen(filename, "r"))) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, f)) {
    if (strncmp("#ns:", line, 4) == 0) {
      ns = atoi(line + 4);
    } else if (strncmp("#np:", line, 4) == 0) {
      np = atoi(line + 4);
    } else if (strncmp("#nc:", line, 4) == 0) {
      nc = atoi(line + 4);
    } else if (strncmp("#nl:", line, 4) == 0) {
      nl = atoi(line + 4);
    } else if (strncmp("#no:", line, 4) == 0) {
      no = atoi(line + 4);
    } else if (strncmp("#lc:", line, 4) == 0) {
      toks = strtok(line + 3, "|");
      if (toks) code = atoi(toks);
      command_set_code(cmd, code);
      toks = strtok(NULL, "|");
      if (toks) output = atoi(toks);
      command_set_output(cmd, output);
      toks = strtok(NULL, "|");
      if (toks) strcpy(arguments, toks);
      command_set_arguments(cmd, arguments);
      toks = strtok(NULL, "|");
      if (toks) strcpy(arguments1, toks);
      command_set_arguments1(cmd, arguments1);
      toks = strtok(NULL, "|");
      if (toks) strcpy(arguments2, toks);
      command_set_arguments2(cmd, arguments2);
    } else if (strncmp("#t:", line, 3) == 0) {
      t = atoi(line + 3);
    } else if (line[0] == '#' && line[1] == 's' && line[2] == ':') {
      break;
    }
  }

  game_set_n_spaces(game, ns);
  game_set_n_players(game, np);
  game_set_n_characters(game, nc);
  game_set_n_links(game, nl);
  game_set_n_objects(game, no);

  game_set_turn(game, t);

  fclose(f);

  game_load_objects(game, filename);
  game_load_players(game, filename);
  game_load_characters(game, filename);
  game_load_links(game, filename);
  game_load_spaces(game, filename);

  return OK;
}
