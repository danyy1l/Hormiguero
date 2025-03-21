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
#include <strings.h>

/*
  Game data structure
*/

struct _Game{
  Player *player;                         /*!< Puntero a la estructura del jugador de la partida*/
  Object *objects[MAX_OBJECTS];            /*!< Puntero a array de objetos de la partida*/
  int n_objects;                          /*!< Almacena el numero de objetos en la partida*/
  Character *characters[MAX_CHARACTERS];  /*!< Puntero a array de personajes en la partida*/
  int n_characters;                       /*!< Almacena el numero de personajes*/
  Space *spaces[MAX_SPACES];              /*!< Array estático de un número limitado de espacios*/
  int n_spaces;                           /*!< Número de espacios*/
  Command *last_cmd;                      /*!< Puntero al comando*/
  Bool finished;                          /*!< Valor de TRUE o FALSE*/
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

  game->n_objects = 0;
  game->n_characters = 0;
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

  for(i=0; i<game->n_objects; i++)
    object_destroy(game->objects[i]);

  for(i=0; i<game->n_characters; i++){
    character_destroy(game->characters[i]);
  }

  player_destroy(game->player);
  command_destroy(game->last_cmd);

  free(game);
  game = NULL;

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

Status game_add_object(Game *game, Object* object){
  if( !game || !object)
    return ERROR;

  game->objects[ game->n_objects ] = object;
  game->n_objects++;
  return OK;
}

Object* game_get_object(Game *game, Id id){
  int i;
  if(!game)
    return NULL;

  for(i=0; i<game->n_objects; i++){
    if( object_get_id(game->objects[i]) == id )
      return game->objects[i];
  }

  return NULL;
}

Object* game_get_object_by_name(Game *game, char* name){
  int i;
  if( !game )
    return NULL; 

  for(i=0; i<game->n_objects; i++){
    if( !strcasecmp(object_get_name(game->objects[i]), name) )
      return game->objects[i];
  }

  return NULL;
}

int game_get_n_objects(Game* game){
  if( !game )
    return -1;

  return game->n_objects;
}

Status game_set_n_objects(Game* game, int n_objects){
  if(!game)
    return ERROR;

  game->n_objects = n_objects;

  return OK;
}

Status game_add_character(Game *game, Character* character){
  if( !game || !character)
    return ERROR;

  game->characters[ game->n_characters ] = character;
  game->n_characters++;
  return OK;
}

Status game_remove_character(Game *game, Id character_id){
  if( !game )
    return ERROR;

  character_set_id( game_get_character(game, character_id), NO_ID );
  space_set_character( game_get_space(game, player_get_location(game_get_player(game))), NO_ID );
  game->n_characters--;
  
  return OK;
}

Character* game_get_character(Game *game, Id id){
  int i;
  if( !game )
  return NULL;
  
  for(i=0; i<game->n_characters; i++){
    if( character_get_id(game->characters[i]) == id )
    return game->characters[i];
  }
  
  return NULL;
}

int game_get_n_characters(Game* game){
  if( !game )
    return -1;

  return game->n_characters;
}

Status game_set_n_characters(Game* game, int n_characters){
  if(!game)
    return ERROR;

  game->n_characters = n_characters;

  return OK;
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
  object_print(game->objects[0]);
  printf("=> Player location: ");
  player_print(game->player);
}
