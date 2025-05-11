/**
 * @brief Implementacion de las Game Rules
 * 
 * @file game_rules.c
 * @author Danyyil Shykerynets
 * @version 1
 * @date 20-04-2025
 * @copyright GNU Copyright License
 */

#include "../include/game_rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "../include/game.h"

#define BOSS_ID 15

/**
 * GAME RULES DECLARATION
 */

/**
 * @brief Si hay un enemigo en la habitacion, recibes daño ante cualquier comando distinto de attack
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @param command Puntero al comando
 * @return OK en caso de exito, ERROR en caso contrario o que se incumpla la norma
 */
Status game_rule_enemies(Game *game, Command *command);

/**
 * @brief Cuando muera el boss, abre las puertas
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 */
void game_rule_final_boss(Game *game);

/**
 * @brief El personaje vecinoarriba actua en funcion del objeto que se le entregue
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @param last_cmd Puntero al ultimo comando ejecutado
 */
void game_rules_witch_orbs(Game* game, Command *last_cmd);

/**
 * @brief Termina la partida cuando un jugador pierda la vida
 * @author Danyyil Shykerynets
 * @param game
 */
void game_rules_end_game(Game* game);

/**
 * @brief Evita que se reclute a un NPC
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @param last_cmd Ultimo comando
 * @return OK en caso de que no se incumpla la regla
 */
Status game_rules_cant_recruit_vecino(Game* game, Command* last_cmd);

/**
 * @brief Define la victoria de la partida
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @param last_cmd Ultimo comando
 * @return Status
 */
Status game_rules_win(Game* game, Command* last_cmd);

/**
 * GAME RULES IMPLEMENTATION
 */

/*TO DO: gamerule revisar vida de jugador para morir*/

Status game_rules_update(Game* game, Command *last_cmd){ 
  if( !game_rule_enemies(game, last_cmd)) return ERROR;
  game_rule_final_boss(game);
  game_rules_witch_orbs(game, last_cmd);
  game_rules_end_game(game);
  if( !game_rules_cant_recruit_vecino(game, last_cmd)) return ERROR;
  if( !game_rules_win(game, last_cmd)) return ERROR;

  return OK;
}

Status game_rule_enemies(Game *game, Command *last_cmd){
  Player* player = game_get_player(game);
  CommandCode code = command_get_code(last_cmd);
  Character* enemy = NULL;
  int i;

  for( i=0; i<=game_get_n_characters(game); i++){
    enemy = game_get_character_at(game, i);
    
    if( character_get_friendly(enemy) == FALSE && ( player_get_location(player) == character_get_location(enemy) ) ){
      /*Si el comando no es attack, recibo daño*/
      if( code != ATTACK ) {
        player_set_health(player, player_get_health(player) - character_get_strength(enemy));
      }
      /*Si intentas salir no te deja*/
      if( code == MOVE ){
        command_set_output(last_cmd, ERROR);
        return ERROR;
      }
    }
  }

  return OK;
}

void game_rule_final_boss(Game *game){
  Player* player = game_get_player(game);
  Character* boss = game_get_character(game, BOSS_ID);

  if( player_get_location(player) == 612 ){
    if( !boss ){
      link_set_open(game_get_link(game, 612, 611), TRUE);
      link_set_open(game_get_link(game, 612, 613), TRUE);
      object_set_movable(game_get_object(game, 21), TRUE);
    }
  }
}


void game_rules_witch_orbs(Game* game, Command *last_cmd){
  Character *witch = game_get_character(game, 6);
  Object *white = NULL, *black = NULL;

  if( command_get_code(last_cmd) == USE && !strcasecmp(command_get_arguments2(last_cmd), "VecinoArriba") ){
    if( !strcmp(command_get_arguments(last_cmd), "manzana") ){
      character_set_message(witch, "Decision correcta");
      character_set_friendly(witch, TRUE);
      white = object_create(20);
      object_set_name(white, "Cuchillo");
      object_set_location(white, 513);
      object_set_description(white, "Parece un arma fuerte");
      object_set_health(white, 10);
      object_set_strength(white, 7);
      object_set_movable(white, TRUE);
      game_add_object(game, white);
      space_add_object(game_get_space(game, 513), 20);
      inventory_del_object(player_get_objects(game_get_player(game)), 16);
      game_remove_object(game, object_get_id(game_get_object_by_name(game, "Manzana")));
    }else if( !strcmp(command_get_arguments(last_cmd), "platano") ){
      character_set_following(witch, 0);
      if( character_get_following(witch) == player_get_id(game_get_player(game)) ){
        set_del_value(player_get_followers(game_get_player(game)), 6);
        space_add_character(game_get_space(game, player_get_location(game_get_player(game))), 6);
      }
      character_set_message(witch, "Grave error");
      character_set_friendly(witch, FALSE);
      black = object_create(15);
      object_set_name(black, "Aguja");
      object_set_location(black, 513);
      object_set_description(black, "Ouch!");
      object_set_health(black, -10);
      object_set_movable(black, FALSE);
      game_add_object(game, black);
      space_add_object(game_get_space(game, 513), 15);
      game_remove_object(game, object_get_id(game_get_object_by_name(game, "Platano")));
    }
  }
}

void game_rules_end_game(Game* game){
  int i;
  Player* dummy = NULL;

  for(i=0; i<game_get_n_players(game)+1; i++){
    if( !(dummy = game_players(game)[i]) ) continue;

    if( player_get_health(dummy) <= 0 ) game_set_finished(game, TRUE);
  }
}

Status game_rules_cant_recruit_vecino(Game* game, Command* last_cmd){
  if( command_get_code(last_cmd) == RECRUIT && !strcasecmp(command_get_arguments(last_cmd), "VecinoArriba") ){
    command_set_output(last_cmd, ERROR);
    return ERROR;
  }
  
  return OK;
}

Status game_rules_win(Game* game, Command* last_cmd){
  if( command_get_code(last_cmd) == USE && !strcasecmp(command_get_arguments(last_cmd), "BotonVerde")  ) {
    game_set_finished(game, TRUE);
  }
  return OK;
}
