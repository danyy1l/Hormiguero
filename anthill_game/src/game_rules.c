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

#include "../include/game.h"

/**
 * @brief Si hay un enemigo en la habitacion, no puedes salir
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @param command Puntero al comando
 * @return OK en caso de exito, ERROR en caso contrario o que se incumpla la norma
 */
Status game_rule_enemies(Game *game, Command *command);

Status game_rules_update(Game* game, Command *last_cmd){ 
  Status output = OK;

  output = game_rule_enemies(game, last_cmd);

  return output;
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
      /*Si intentas salir no te deja
      if( code == MOVE ){
        command_set_output(last_cmd, ERROR);
        return ERROR;
      }*/
    }
  }

  return OK;
}