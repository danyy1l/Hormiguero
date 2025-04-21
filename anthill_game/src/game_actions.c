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
 * @author Hugo Martín
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
 * @param command Ultimo comando
 * Ataca al personaje que haya en la misma casilla
 */
Status game_actions_attack(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "CHAT"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param command Ultimo comando de la partida
 * Imprime el mensaje del personaje al que nos dirijamos si estamos en el mismo espacio
 */
Status game_actions_chat(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "LOOK"
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * Imprime la informacion del espacio en el que nos encontremos
 */
Status game_actions_look(Game *game);

/**
 * @brief Realiza la accion al recibir un commando "INSPECT"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Imprime la descripción del objeto de la casilla en la que nos encontremos, en caso de que lo haya, o de la mochila
 */
Status game_actions_inspect(Game *game, Command *command);

/**
 * @brief Realiza la accion al recibir un commando "USE"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Usa el objeto al que se esté refiriendo, y luego el objeto desaparece
 */
Status game_actions_use(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "OPEN"
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * Abre un enlace con un obeto y luego este desaparece
 */
Status game_actions_open(Game *game, Command* command);

/**
 * @brief Realiza la accion al recibir un commando "RECRUIT"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * @param command puntero a command
 * Recluta a un amigo que se encuentre en la misma casilla
 */
Status game_actions_recruit(Game* game, Command *command);

/**
 * @brief Realiza la accion al recibir un commando "ABANDON"
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Estructura de la partida actual
 * @param command puntero a command
 * Abandona a un amigo que se encuentre en la misma casilla
 */
Status game_actions_abandon(Game* game, Command* command);

/**
   Game actions implementation
*/
 
Status game_actions_update(Game *game, Command *command) {
  int i;
  Player *player=game_get_player(game);                                  /*Jugador del game*/
  Inventory *inventory=player_get_objects(player);                       /*Inventario del jugador del game*/
  Set* player_bag = inventory_get_objects(player_get_objects(player));   /*Set con objetos de la mochila*/
  int n_ids=set_get_nids(player_bag);                                    /*Numero de objetos que porta el jugador*/
  int n_followers = set_get_nids(player_get_followers(player));
  Object *object=NULL;
  Character* character = NULL;
  CommandCode cmd;

  cmd = command_get_code(command);
  game_set_prev_player_location(game, player_get_location(game_get_player(game)));

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
      if( game_actions_attack(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;

    case CHAT:
      if( game_actions_chat(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;
    
    case LOOK:
      if( game_actions_look(game) == ERROR )
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

     case RECRUIT:
      if( game_actions_recruit(game, command) == ERROR )
        command_set_output(command, ERROR);
      else
        command_set_output(command, OK);
      break;
    
    case ABANDON:
      if( game_actions_abandon(game, command) == ERROR )
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
  
  for(i=0; i<n_followers; i++){
    character=game_get_character(game, set_id_object(player_get_followers(player))[i]);
    character_set_location(character, player_get_location(player));
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

Status game_actions_attack(Game *game, Command *command) {
  if (!game || !command) {
    return ERROR;
  }

  const char *target_name = command_get_arguments(command);
  if (!target_name) {
    return ERROR;
  }

  Player *player = game_get_player(game);
  Id player_loc = player_get_location(player);
  Id player_id = player_get_id(player);
  int num_chars = game_get_n_characters(game);
  int n_followers = 0, num, damage, n_attackers, attacker;
  Character *followers[num_chars], *hit_follower = NULL, *target = NULL, *character = NULL, *follower = NULL; 

  for (int i = 0; i < num_chars; i++) {
    character = game_get_character_at(game, i);
    if (!character) continue;

    if (strcasecmp(character_get_name(character), target_name) == 0) {
      target = character;
    }

    if (character_get_following(character) == player_id && character_get_location(character) == player_loc) {
      followers[n_followers++] = character;
    }
  }

  if (!target || character_get_location(target) != player_loc || character_get_friendly(target)) {
    return ERROR;
  }

  num = rand() % 10;

  if (num > 5) {
    damage = 1 + n_followers;  
    character_set_health(target, character_get_health(target) - damage);
  } else {
    n_attackers = 1 + n_followers;  
    attacker = rand() % n_attackers;

    if (attacker == 0) {
      player_set_health(player, player_get_health(player) - 1);
    } else {
      hit_follower = followers[attacker - 1];
      character_set_health(hit_follower, character_get_health(hit_follower) - 1);
    }
  }

  if (player_get_health(player) <= 0) {
    game_set_finished(game, TRUE);
  }

  if (character_get_health(target) <= 0) {
    game_remove_character(game, character_get_id(target));
  }

  for (int i = 0; i < n_followers; i++) {
    follower = followers[i];
    if (character_get_health(follower) <= 0) {
      game_remove_character(game, character_get_id(follower));
    }
  }
  return OK;
}


Status game_actions_chat(Game *game, Command* command){
  if( !command || !game ) return ERROR;
  
  Player* player = game_get_player(game);
  Character* character;
  char str[WORD_SIZE], *char_name;
  int n_chars = game_get_n_characters(game);

  char_name = command_get_arguments(command);

  for(int i=0; i<n_chars; i++){
    character = game_get_character_at(game, i);

    if (!character) 
      continue;

    if (strcasecmp(character_get_name(character), char_name) != 0) {
      continue;
    }

    if (character_get_location(character) != player_get_location(player) || !character_get_friendly(character)) return ERROR;
    
    sprintf(str, "%s: %s", character_get_name(character), character_get_message(character));
    game_set_message(game, str);
    return OK;
  }

  return ERROR;
}

Status game_actions_look(Game *game){
  if( !game || !game_get_space(game, player_get_location(game_get_player(game))) ) return ERROR;
  return OK;
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

Status game_actions_recruit(Game* game, Command *command){
  if (!game || !command) {
    return ERROR;
  }

  const char *char_name = command_get_arguments(command);
  if (!char_name) {
    return ERROR;
  }

  Player *player = game_get_player(game);
  Id player_loc = player_get_location(player);
  int num_chars = game_get_n_characters(game);
  Character *character = NULL;

  for (int i = 0; i < num_chars; i++) {
    character = game_get_character_at(game, i);

    if (!character) 
      continue;

    if (strcasecmp(character_get_name(character), char_name) != 0) {
      continue;
    }


    if (character_get_location(character) != player_loc || !character_get_friendly(character) || character_get_following(character) != NO_ID) {
      return ERROR;
    }

    character_set_following(character, player_get_id(player));
    set_add_value(player_get_followers(player), character_get_id(character));
    space_del_character(game_get_space(game, player_loc), character_get_id(character));
    return OK;
  }

  return ERROR; 
}

Status game_actions_abandon(Game* game, Command *command){
  if (!game || !command) {
    return ERROR;
  }

  Player *player = game_get_player(game);
  Id player_id = player_get_id(player);
  Id player_loc = player_get_location(player);

  int num_chars = set_get_nids(player_get_followers(player));
  Character *character = NULL;

  const char *char_name = command_get_arguments(command);
  if (!char_name) {
    return ERROR;
  }

  for (int i = 0; i < num_chars; i++) {
    character = game_get_character(game, set_id_object(player_get_followers(player))[i]);

    if (!character) 
      continue;

    if (strcasecmp(character_get_name(character), char_name) != 0) {
      continue;
    }

    if (character_get_location(character) != player_loc || !character_get_friendly(character) || character_get_following(character) != player_id) {
      return ERROR;
    }

    character_set_following(character, NO_ID);
    set_del_value(player_get_followers(player), character_get_id(character));
    space_add_character(game_get_space(game, player_loc), character_get_id(character));

    return OK;
  }

  return ERROR;
}
