/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Hugo Martín
 * @version 7
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "../include/game.h"
#include "../include/game_actions.h"
#include "../include/game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
 
/**
   Game actions implementation
*/
 
Status game_actions_update(Game *game, Command *command) {
  int i;
  Player *player=game_get_player(game);                                  /*Jugador del game*/
  Inventory *inventory=player_get_objects(player);                       /*Inventario del jugador del game*/
  Set* player_bag = inventory_get_objects(player_get_objects(player));   /*Set con objetos de la mochila*/
  int n_ids=set_get_nids(player_bag);                                    /*Numero de objetos que porta el jugador*/
  Object *object=NULL;
  CommandCode cmd;

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case QUIT:
      game_actions_quit(game);
      break;

    case MOVE:
      if( game_actions_move(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case TAKE:
      if( game_actions_take(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case DROP:
      if( game_actions_drop(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case ATTACK:
      if( game_actions_attack(game) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case CHAT:
      if( game_actions_chat(game) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;
    
    case INSPECT:
      if( game_actions_inspect(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case USE:
      if( game_actions_use(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case OPEN:
      if( game_actions_open(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    default: 
      break;
  } 

  /*Update position of objects in player backpack*/
  if( !inventory_is_empty(inventory)) {
    for (i=0;i<n_ids;i++) {
      object=game_get_object(game, set_id_object(player_bag)[i]);       /*Cada uno de los objetos de la mochila del jugador*/
      object_set_location(object, player_get_location(player));         /*Actualiza la ubicación de cada uno de los objetos*/
    }
  }

  return OK;
}

/**
   Calls implementation for each action
*/

Status game_actions_unknown(Game *game) { return ERROR; }

void game_actions_quit(Game *game) {}

Status game_actions_move(Game *game, Command *command) {
  Id space_id = NO_ID;
  char dir[WORD_SIZE];
  Direction direction = U;

  space_id = player_get_location(game_get_player(game));
  strcpy(dir, command_get_arguments(command));

  if( !strcasecmp("North", dir) || !strcasecmp("N", dir) )
    direction = N;
  else if( !strcasecmp("East", dir) || !strcasecmp("E", dir) )
    direction = E;
  else if( !strcasecmp("South", dir) || !strcasecmp("S", dir) )
    direction = S;
  else if( !strcasecmp("West", dir) || !strcasecmp("W", dir) )
    direction = W; 
  else
    direction = U;

  if (game_connection_is_open(game, space_id, direction)) {
    player_set_location(game_get_player(game), game_get_connection(game, space_id, direction));
  }else
    return ERROR;

  return OK;
}

Status game_actions_take(Game *game, Command *command){
  Object* object = game_get_object_by_name(game, command_get_arguments(command));
  Space* current_space = game_get_space(game, player_get_location(game_get_player(game)));
  Player* player=game_get_player(game);
  Inventory* backpack=player_get_objects(player);
  Id dependency=object_get_dependency(object);
  Object *object2=game_get_object(game, dependency);

  if(!game || !command )
    return ERROR;

  if( inventory_is_full(backpack)==FALSE && (object_get_location(object) == player_get_location(game_get_player(game))) && object_get_taken(object) == FALSE && object_get_movable(object)==TRUE && (dependency==NO_ID || player_find_object(player, object2)==TRUE)){
    player_add_object(player, object);
    space_del_object(current_space, object_get_id(object));
    object_set_taken(object, TRUE);
    return OK;
  }

  return ERROR;
}

Status game_actions_drop(Game *game, Command *command){
  Player *player=game_get_player(game);
  Object *object=game_get_object_by_name(game, command_get_arguments(command)), *object2=NULL;
  Space* current_space = game_get_space(game, player_get_location(game_get_player(game)));
  int i, n_ids=set_get_nids(inventory_get_objects(player_get_objects(player)));
  Id *ids=set_id_object(inventory_get_objects(player_get_objects(player)));

  if (!game || !command_get_arguments(command) ) {
    return ERROR;
  }

  if (!object || player_find_object(player, object)==FALSE || inventory_is_empty(player_get_objects(player))) {
    return ERROR;
  }
  
  for (i=0;i<n_ids;i++) {
    object2=game_get_object(game, ids[i]);
    if (object_get_id(object)==object_get_dependency(object2)) {
      space_add_object(current_space, object_get_id(object2));
      player_del_object(player, object2);
      object_set_taken(object2, FALSE);
    }
  }
  
  space_add_object(current_space, object_get_id(object));
  player_del_object(player, object);
  object_set_taken(object, FALSE);

  return OK;
}

Status game_actions_attack(Game *game){
  Player* player = game_get_player(game);
  Space *current_space = game_get_space(game, player_get_location(player));
  Character* character = game_get_character(game, space_get_character_id(current_space));
  int num;

  if( !character )
    return ERROR;

  if( (player_get_location(player) == character_get_location(character)) && !(character_get_friendly( character )) ){
    num = rand() % 10;
    if( num < 5 )
      player_set_health(player, player_get_health(player) - 1);
    else
      character_set_health(character, character_get_health(character) - 1);
  }else
    return ERROR;

  if( player_get_health(player) == 0 ){
    game_set_finished(game, TRUE);
  }
  
  if( character_get_health(character) == 0 ){
    game_remove_character(game, character_get_id(character));
  }
  return OK;
}

Status game_actions_chat(Game *game){
  Player* player = game_get_player(game);
  Space *current_space = game_get_space(game, player_get_location(player));
  Character* character = game_get_character(game, space_get_character_id(current_space));
  char str[WORD_SIZE];

  if( (player_get_location(player) == character_get_location(character)) && (character_get_friendly( character )) ){
    sprintf(str, "%s: %s", character_get_name(character), character_get_message(character));
    game_set_message(game, str);
    return OK;
  }

  return ERROR;
}

Status game_actions_inspect(Game *game, Command *command) {
  if (!game || !command) {
    return ERROR;
  }

  Player *player=game_get_player(game);
  Inventory *backpack=player_get_objects(player);
  Object *object=game_get_object_by_name(game, command_get_arguments(command));

  if (player_get_location(player)!=object_get_location(object) && inventory_find_object(backpack, object_get_id(object))==FALSE) {
    return ERROR;
  } else {
    return OK;
  }

  return ERROR;
}

Status game_actions_use(Game *game, Command *command) {
  Player *player=game_get_player(game);
  Object *object=game_get_object_by_name(game, command_get_arguments(command));
  Space *current_space = game_get_space(game, player_get_location(player));
  int p_health=player_get_health(player), health=object_get_health(object), t_health;

  if (!game || !command || health==0 || space_get_id(current_space)!=object_get_location(object)) {
    return ERROR;
  }

  t_health=p_health+health;
  player_set_health(player, t_health);
  if (player_get_health(player)>10) {
    player_set_health(player, 10);
  }
  if (player_get_health(player)<0) {
    player_set_health(player, 0);
  }

  object_set_location(object, 99);

  return OK;
}

Status game_actions_open(Game *game, Command* command) {
  Player *player=game_get_player(game);
  Object *object=game_get_object_by_name(game, command_get_arguments2(command));
  Space *current_space = game_get_space(game, player_get_location(player));
  Id s_id=space_get_id(current_space);
  Link *link=game_get_link_by_name(game, command_get_arguments(command));

  if (!game || !command || object_get_open(object)!=link_get_id(link) || s_id!=object_get_location(object) || s_id!=link_get_origin(link) || strcasecmp(command_get_arguments1(command), "with")!=0) {
    return ERROR;
  }

  link_set_open(link, TRUE);

  return OK;
}
