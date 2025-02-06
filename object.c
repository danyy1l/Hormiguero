/**
 * @brief Implementacion de la funcionalidad del modulo Object
 *
 * @file object.c
 * @author Danyyil Shykerynets
 * @version 0
 * @date 06-02-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "game_reader.h"

struct _Object{

  Id id;
  char icon;
  char name[WORD_SIZE+1];

};

Object *object_create(Id id, char icon, char *name){

  Object *output = NULL;
  
  if(!name || id == NO_ID ){ return NULL; }

  if( !(output = (Object*)calloc(1, sizeof(Object))) )
    return NULL;

  output->id = id;
  output->icon = icon;
  strcpy(output->name, name);

  return output;

}

void object_destroy(Object *object){

  if( object ){
    free(object);
    object = NULL;
  }

}

Status object_set_location(Game *game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  game->object_location = id;
  space_set_object(game_get_space(game, id), TRUE);

  return OK;
}

Id object_get_location(Game *game) { return game->object_location; }

void object_print(Object *object){

  if( object ){
    printf("Object ID: %ld\nObject name: %s\nObject icon: %c", object->id, object->name, object->icon);
  }

}

char *game_object_check(char *objs, Game *game){
  
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID;
  Space *space_act = NULL;

  if( (id_act = player_get_location(game)) != NO_ID ){
    space_act = game_get_space(game, id_act);
    id_north = space_get_north(space_act);
    id_south = space_get_south(space_act);
    id_east = space_get_east(space_act);
    id_west = space_get_west(space_act);

    if (object_get_location(game) == id_act)
      objs[0] = '*';
    else
      objs[0] = ' ';

    if (object_get_location(game) == id_north)
      objs[1] = '*';
    else
      objs[1] = ' ';


    if (object_get_location(game) == id_south)
      objs[3] = '*';
    else
      objs[3] = ' ';


    if (object_get_location(game) == id_east)
      objs[2] = '*';
    else
      objs[2] = ' ';


    if (object_get_location(game) == id_west)
      objs[4] = '*';
    else
      objs[4] = ' ';

  }

  return objs;
}
