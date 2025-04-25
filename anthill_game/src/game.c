/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Danyyil Shykerynets
 * @version 22
 * @date 22-04-2025
 * @copyright GNU Public License
 */

#include "../include/game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> 

/**
 * @brief Game
 *
 * This struct stores all the information related to the game.
 */
struct _Game{
  Player *players[MAX_PLAYERS];           /*!< Puntero a la estructura del jugador de la partida*/
  Command *last_cmd[MAX_PLAYERS];         /*!< Almacena ultimo comando propio al jugador*/
  int n_players;                          /*!< Almacena el numero de jugadores en la partida*/
  int turn;                               /*!< Almacena el turno del jugador*/
  Object *objects[MAX_OBJECTS];           /*!< Puntero a array de objetos de la partida*/
  int n_objects;                          /*!< Almacena el numero de objetos en la partida*/
  Character *characters[MAX_CHARACTERS];  /*!< Puntero a array de personajes en la partida*/
  int n_characters;                       /*!< Almacena el numero de personajes*/
  Space *spaces[MAX_SPACES];              /*!< Array estático de un número limitado de espacios*/
  int n_spaces;                           /*!< Número de espacios*/
  Link *links[MAX_LINKS];                 /*!< Puntero a array de enlaces entre espacios*/
  int n_links;                            /*!< Almacena el numero de enlaces en la partida*/
  Bool finished;                          /*!< Determina si la partida esta terminada*/
  char message[WORD_SIZE];                /*!< Almacena el ultimo mensaje de personaje*/
  Id prev_player_location;                /*!< La ubicacion del anterior jugador en el array*/
};

/**
   Game interface implementation
*/

Game* game_create() { 
  int i;
  Game* game = NULL;

  if( !(game = (Game*)calloc(1, sizeof(Game))) ) return NULL;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    game->players[i] = NULL;
    game->last_cmd[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    game->characters[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++) {
    game->links[i] = NULL;
  }

  game->n_players = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->n_spaces = 0;

  return game;
}

Status game_destroy(Game *game) {
  int i;

  for (i=0; i<game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  for(i=0; i<game->n_objects; i++)
    object_destroy(game->objects[i]);

  for(i=0; i<game->n_characters; i++){
    character_destroy(game->characters[i]);
  }

  for(i=0; i<game->n_players; i++){
    command_destroy(game->last_cmd[i]);
    player_destroy(game->players[i]);
  }


  for(i=0; i<game->n_links; i++)
    link_destroy(game->links[i]);

  free(game);
  game = NULL;

  return OK;
}

Command* game_get_last_command(Game *game) {
  if(game && game->last_cmd[ game->turn ])
    return game->last_cmd[game->turn]; 

  return NULL;
}

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd[game->turn] = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

Player** game_players(Game *game){
  return game == NULL ? NULL : game->players;
}

Player* game_get_player(Game *game){  
  if(!game )
    return NULL;

  return game->players[ game->turn ];
} 

Status game_set_turn(Game *game, int turn) {
  if(!game )
    return ERROR;

  game->turn=turn;

  return OK;
}

int game_get_n_players(Game *game){
  return game == NULL ? -1 : game->n_players;
}

int game_get_n_spaces(Game *game){
  return game == NULL ? -1 : game->n_spaces;
}

Status game_add_player(Game *game, Player* player){
  if( !game || !player ) return ERROR; 

  game->players[ game->n_players ] = player;
  game->last_cmd[ game->n_players ] = command_create();
  game->n_players++;
  return OK;
}

int game_get_turn(Game* game){
  return game == NULL ? -1 : game->turn;
}

Status game_next_turn(Game* game, int turn){
  if(!game) return ERROR;

  game->turn = turn;
  return OK;
}

Status game_add_object(Game *game, Object* object){
  if( !game || !object) return ERROR;

  game->objects[ game->n_objects ] = object;
  game->n_objects++;
  return OK;
}

Status game_remove_object(Game *game, Id object_id){  
  int j = object_id - 1;
  
  if( !game )
    return ERROR;

  /*TO DO esta linea sobra?*/
  space_del_object( game_get_space(game, player_get_location(game_get_player(game))), object_id );
  object_set_id( game_get_object(game, object_id), NO_ID );
  object_destroy(game->objects[ j ]);

  /*Desplaza todos los elementos a la izq, de esta manera, no quedan huecos libres*/
  for(; j<game->n_objects; j++){
    game->objects[j] = game->objects[j+1];
  }

  game->objects[ game->n_objects ] = NULL;

  game->n_objects--;
  
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

Object **game_get_objects(Game *game) {
  if(!game)
  return NULL;

  return game->objects;
}

Character **game_get_characters(Game *game) {
  if(!game)
  return NULL;

  return game->characters;
}

Space **game_get_spaces(Game *game) {
  if(!game)
  return NULL;

  return game->spaces;
}

Link **game_get_links(Game *game) {
  if(!game)
  return NULL;

  return game->links;
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

Status game_set_n_spaces(Game* game, int n_spaces){
  if(!game)
    return ERROR;

  game->n_spaces = n_spaces;

  return OK;
}

Status game_set_n_players(Game* game, int n_players){
  if(!game)
    return ERROR;

  game->n_players = n_players;

  return OK;
}

Status game_set_n_characters(Game* game, int n_characters){
  if(!game)
    return ERROR;

  game->n_characters = n_characters;

  return OK;
}

Status game_set_n_links(Game* game, int n_links){
  if(!game)
    return ERROR;

  game->n_links = n_links;

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
  int j = character_id - 1;
  
  if( !game )
    return ERROR;

  space_del_character( game_get_space(game, player_get_location(game_get_player(game))), character_id );
  character_set_id( game_get_character(game, character_id), NO_ID );
  character_destroy(game->characters[ j ]);

  /*Desplaza todos los elementos a la izq, de esta manera, no quedan huecos libres*/
  for(; j<game->n_characters; j++){
    game->characters[j] = game->characters[j+1];
  }

  game->characters[ game->n_characters ] = NULL;

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

Character* game_get_character_at(Game* game, int i) {
  if (!game || i < 0 || i >= game->n_characters) {
    return NULL;
  }

  return game->characters[i];
}

int game_get_n_characters(Game* game){
  if( !game )
    return -1;

  return game->n_characters;
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

Link* game_get_link(Game* game, Id origin, Id destination){
  int i;
  if (!game|| origin == NO_ID || destination == NO_ID){
    return NULL;
  }
  for (i=0;i<game->n_links;i++){
    if( origin == link_get_origin(game->links[i]) && destination == link_get_destination(game->links[i])){
      return game->links[i];
    }
  }
  return NULL;
}

Status game_add_link(Game* game, Link* link){
  if( !game || !link || game->n_links >= MAX_LINKS) return ERROR;

  game->links[game->n_links] = link;
  game->n_links++;

  return OK;
}

int game_get_n_links(Game* game){
  if (!game){
    return -1;
  }

  return game->n_links;
}

Id game_get_connection(Game *game, Id id, Direction direction){
  int i;
  if (!game){
    return NO_ID;
  }
  for(i=0;i<game->n_links;i++){
    if(id == link_get_origin(game->links[i]) && link_get_direction(game->links[i]) == direction)
      return link_get_destination(game->links[i]);
  }

  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id id, Direction direction){
  int i;
  if (!game){
    return FALSE;
  }

  for(i=0;i<game->n_links;i++){
    if(id == link_get_origin(game->links[i]) && link_get_direction(game->links[i])==direction){
      if(link_get_open(game->links[i])==TRUE){
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
  }

  return FALSE;
}

Status game_set_message(Game* game, char* str){
  if( !game || !str ) return ERROR;

  strcpy(game->message, str);

  return OK;
}

char* game_get_message(Game* game){
  return game == NULL ? NULL : game->message;
}

Link* game_get_link_by_name(Game *game, char* name) {
  int i;
  if( !game )
    return NULL;

  for(i=0; i<game->n_links; i++){
    if( !strcasecmp(link_get_name(game->links[i]), name) )
    return game->links[i];
  }

  return NULL;
}

Id game_get_prev_player_location(Game* game){
  return game == NULL ? NO_ID : game->prev_player_location;
}

Status game_set_prev_player_location(Game* game, Id location){
  if( !game || location == NO_ID) return ERROR;

  game->prev_player_location = location;
  return OK;
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
  player_print(game->players[0]);
}
