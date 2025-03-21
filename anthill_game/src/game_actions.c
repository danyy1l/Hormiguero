/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Anthony Eduardo Alvarado Carbajal
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

    case QUIT:
      game_actions_quit(game);
      break;

    case NORTH:
      if( game_actions_north(game) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case SOUTH:
      if( game_actions_south(game) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case EAST:
      if( game_actions_east(game) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case WEST:
      if( game_actions_west(game) == ERROR )
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

    default:
      break;
  }

  if( player_get_object(game_get_player(game)))
    object_set_location(game_get_object(game, object_get_id( player_get_object(game_get_player(game)))), player_get_location(game_get_player(game)));

  return OK;
}

/**
   Calls implementation for each action
*/

Status game_actions_unknown(Game *game) { return ERROR; }

void game_actions_quit(Game *game) {}

Status game_actions_north(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));

  if (NO_ID == space_id) {
    return ERROR;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game_get_player(game), current_id);
  }else
    return ERROR;

  return OK;
}

Status game_actions_south(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));

  if (NO_ID == space_id) {
    return ERROR;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game_get_player(game), current_id);
  }else
    return ERROR;

  return OK;
}

Status game_actions_east(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));

  if (NO_ID == space_id) {
    return ERROR;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game_get_player(game), current_id);
  }else
    return ERROR;

  return OK;
}

Status game_actions_west(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));

  if (NO_ID == space_id) {
    return ERROR;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    player_set_location(game_get_player(game), current_id);
  }else
    return ERROR;

  return OK;
}

Status game_actions_take(Game *game, Command *command){
  Object* object = game_get_object_by_name(game, command_get_arguments(command));
  Space* current_space = game_get_space(game, player_get_location(game_get_player(game)));
  Player* player=game_get_player(game);
  Inventory* backpack=player_get_objects(player);

  if( !command )
    return ERROR;

  if( inventory_is_full(backpack)==FALSE && object_get_location(object) == player_get_location(game_get_player(game)) ){
    player_add_object(player, object);

    /*TODO: esto cause core dump*/
    space_del_object(current_space, object_get_id(object));
    return OK;
  }
  
  return ERROR;
}

Status game_actions_drop(Game *game, Command *command){
  
  Player *player=game_get_player(game);
  Object *object=game_get_object_by_name(game, command_get_arguments(command));
  Space* current_space = game_get_space(game, player_get_location(game_get_player(game)));
  
  if (!game || !command) {
    return ERROR;
  }

  if (player_find_object(player, object)==FALSE) {
    return ERROR;
  }
  
  space_add_object(current_space, object_get_id(object));
  player_del_object(player, object);

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
    printf("You died!\n");
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

  if( (player_get_location(player) == character_get_location(character)) && (character_get_friendly( character )) ){
    return OK;
  }

  return ERROR;
}