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
      game_actions_north(game);
      break;

    case SOUTH:
      game_actions_south(game);
      break;

    case EAST:
      game_actions_east(game);
      break;

    case WEST:
      game_actions_west(game);
      break;

    case TAKE:
      game_actions_take(game, command);
      break;

    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;

    case CHAT:
      game_actions_chat(game);
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
  Space *current_space = game_get_space(game, player_get_location(game_get_player(game)));
  /*Object* object;*/

  if( !command )
    return ERROR;

  if( player_get_object(game_get_player(game)) == NULL && space_get_object(current_space) ){
    player_set_object(game_get_player(game), space_get_object(current_space));
    return OK;
  }else
    return ERROR;
}


Status game_actions_drop(Game *game){
  if( player_get_object(game_get_player(game) )){
    player_set_object(game_get_player(game), NULL);
    return OK;
  }else
    return ERROR;
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
  }

  if( player_get_health(player) == 0 ){
    printf("You died!\n");
    game_set_finished(game, TRUE);
  }
  
  if( character_get_health(character) == 0 ){
    printf("You killed the spider!\n");
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