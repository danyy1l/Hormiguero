/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Danyyil Shykerynets
 * @version 7
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#include "../include/player.h"
#include "../include/object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Player {
  Id id;                      /*!<-ID del jugador*/
  Id location;                /*!<-ID del espacio en el que se ubica el jugador*/
  char name[WORD_SIZE + 1];   /*!<-Nombre del jugador*/
  Object* object;                  /*!<-ID del objeto que porta el jugador*/
  int health;                 /*!<-Vida del jugador*/
};

Player *player_create(){
  Player *output = NULL;

  if( !(output = (Player*)calloc(1, sizeof(Player))) )
    return NULL;

  if( !(output->object = object_create(NO_ID)) )
    return NULL;

  output->id = NO_ID;
  output->location = NO_ID;
  output->name[0] = '\0';

  return output;
}

Status player_destroy(Player *player){
  if( player ){
    free(player);
    player = NULL;
    return OK;

  }else
    return ERROR;
}

Status player_set_id(Player *player, Id id){
  if( !player || id == NO_ID ) { return ERROR; }

  player->id = id;

  return OK;
}

Id player_get_location(Player *player) { 
  if( !player ) { return NO_ID; }
  
  return player->location; 
}

Status player_set_location(Player *player, Id id) {
  if (id == NO_ID || !player) {
    return ERROR;
  }

  player->location = id;

  return OK;
}

Status player_set_object(Player *player, Id id){
  if( !player ){ return ERROR; }

  object_set_id(player->object, id);

  return OK;
}

Object* player_get_object(Player *player){
  if( !player ) { return NULL; }
  
  return player->object;
}

Status player_set_health(Player *player, int health){
  if(!player) { return ERROR; }

  player->health = health;

  return OK;
}

int player_get_health(Player* player){
  if( !player ) { return -1; }

  return player->health;
}

Status player_print(Player *player){
  if( player ){
    printf("Player ID: %ld\nPlayer location: %ld\nPlayer name: %s\nPlayer object: %ld\nPlayer health: %d", player->id, player->location, player->name, object_get_id(player_get_object(player)), player->health);
    return OK;
  }else
    return ERROR;
}