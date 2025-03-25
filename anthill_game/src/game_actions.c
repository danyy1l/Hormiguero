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
#include <strings.h>

/**
   Game actions declaration
*/

/**
 * @brief Realiza la accion al recibir un commando "UNKNOWN"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * No hace nada
 */
Status game_actions_unknown(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "QUIT"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * Detiene el bucle de actualizacion del juego, terminando la partida
 */
void game_actions_quit(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "MOVE"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Mueve al jugador en la direccion escrita en caso de que se puede
 */
Status game_actions_move(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "TAKE"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Recibe el objeto de la casilla del jugador y lo lleva consigo hasta recibir un DROP
 */
Status game_actions_take(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "DROP" y un nombre de un objeto
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Suelta el objeto del inventario del jugador en caso de haberlo
 */
Status game_actions_drop(Game *game, Command *command);

/**
 * @brief Realiza la accion al recibir un commando "ATTACK"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Ataca al personaje que haya en la misma casilla
 */
Status game_actions_attack(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "CHAT"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Imprime el mensaje del personaje de la casilla en la que nos encontremos, en caso de que lo haya
 */
Status game_actions_chat(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "INSPECT"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Imprime la descripción del objeto de la casilla en la que nos encontremos, en caso de que lo haya, o de la mochila
 */
Status game_actions_inspect(Game *game, Command *command);

/**
   Game actions implementation
*/
 
Status game_actions_update(Game *game, Command *command) {
  int i;
  Player *player=game_get_player(game, 1);                               /*Jugador del game*/
  Inventory *inventory=player_get_objects(player);                       /*Inventario del jugador del game*/
  Set* player_bag = inventory_get_objects(player_get_objects(player));   /*Set con objetos de la mochila*/
  int n_ids=set_get_nids(player_bag);                                    /*Numero de objetos que porta el jugador*/
  Object *object=NULL;

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
  char dir[__WORDSIZE];
  Direction direction = U;

  space_id = player_get_location(game_get_player(game, 1));
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
    player_set_location(game_get_player(game, 1), game_get_connection(game, space_id, direction));
  }else
    return ERROR;

  return OK;
}

Status game_actions_take(Game *game, Command *command){
  Object* object = game_get_object_by_name(game, command_get_arguments(command));
  Space* current_space = game_get_space(game, player_get_location(game_get_player(game, 1)));
  Player* player=game_get_player(game, 1);
  Inventory* backpack=player_get_objects(player);

  if(!game || !command )
    return ERROR;

  if( inventory_is_full(backpack)==FALSE && (object_get_location(object) == player_get_location(game_get_player(game, 1))) ){
    player_add_object(player, object);
    space_del_object(current_space, object_get_id(object));
    return OK;
  }
  
  return ERROR;
}

Status game_actions_drop(Game *game, Command *command){
  Player *player=game_get_player(game, 1);
  Object *object=game_get_object_by_name(game, command_get_arguments(command));
  Space* current_space = game_get_space(game, player_get_location(game_get_player(game, 1)));

  if (!game || !command_get_arguments(command) ) {
    return ERROR;
  }

  if (!object || player_find_object(player, object)==FALSE || inventory_is_empty(player_get_objects(player))) {
    return ERROR;
  }
  
  space_add_object(current_space, object_get_id(object));
  player_del_object(player, object);

  return OK;
}

Status game_actions_attack(Game *game){
  Player* player = game_get_player(game, 1);
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
  Player* player = game_get_player(game, 1);
  Space *current_space = game_get_space(game, player_get_location(player));
  Character* character = game_get_character(game, space_get_character_id(current_space));

  if( (player_get_location(player) == character_get_location(character)) && (character_get_friendly( character )) ){
    return OK;
  }

  return ERROR;
}

Status game_actions_inspect(Game *game, Command *command) {
  if (!game || !command) {
    return ERROR;
  }

  Player *player=game_get_player(game, 1);
  Inventory *backpack=player_get_objects(player);
  Object *object=game_get_object_by_name(game, command_get_arguments(command));

  if (player_get_location(player)!=object_get_location(object) && inventory_find_object(backpack, object_get_id(object))==FALSE) {
    return ERROR;
  } else {
    return OK;
  }

  return ERROR;
}