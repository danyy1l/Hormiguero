/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Danyyil Shykerynets
 * @version 0
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Player {

  Id id;
  Id location;
  char name[WORD_SIZE + 1];
  Id object;

};

Player *player_create(Id id, Id location, char *name, Id object){
  
  Player *output = NULL;
  
  if(!name || id == NO_ID || location == NO_ID){ return NULL; }

  if( !(output = (Player*)calloc(1, sizeof(Player))) )
    return NULL;

  output->id = id;
  output->location = location;
  strcpy(output->name, name);
  output->object = object;

  return output;
}

void player_destroy(Player *player){

  if( player ){
    free(player);
    player = NULL;
  }

}

Id player_get_location(Game *game) { return game->player_location; }

Status player_set_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }

  game->player_location = id;

  return OK;
}

void player_print(Player *player){
  printf("Player ID: %ld\nPlayer location: %ld\nPlayer name: %s\nPlayer object: %ld", player->id, player->location, player->name, player->object);
}