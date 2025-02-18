/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Danyyil Shykerynets
 * @version 7
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#include "../include/game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Game data structure
*/

struct _Game{
  Player *player;             /*!< Puntero a la estructura del jugador de la partida*/
  Object *object;             /*!< Puntero a la estructura del objeto de la partida*/
  Space *spaces[MAX_SPACES];  /*!< Array estático de un número limitado de espacios*/
  int n_spaces;               /*!< Número de espacios*/
  Command *last_cmd;          /*!< Puntero al comando*/
  Bool finished;              /*!< Valor de TRUE o FALSE*/
};

/**
   Game interface implementation
*/

Game* game_create() {
  int i;
  Game* game = NULL;

  if( !(game = (Game*)calloc(1, sizeof(Game))) )
    return NULL;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  if( !(game->player = player_create()) ) { return ERROR; }
  if( !(game->object = object_create(OBJECT_ID)) ) { return ERROR; }

  game->n_spaces = 0;
  game->last_cmd = command_create();
  game->finished = FALSE;

  return game;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  player_destroy(game->player);
  object_destroy(game->object);
  command_destroy(game->last_cmd);

  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;
  
  return OK;
}

Player* game_get_player(Game *game){
  if(!game)
    return NULL;

  return game->player;
} 

Object* game_get_object(Game *game){
  if(!game)
    return NULL;

  return game->object;
}

int game_get_n_space(Game* game){
  if(!game)
    return -1;

  return game->n_spaces;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;
  
  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }
  
  return space_get_id(game->spaces[position]);
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: ");
  object_print(game->object);
  printf("=> Player location: ");
  player_print(game->player);
}
