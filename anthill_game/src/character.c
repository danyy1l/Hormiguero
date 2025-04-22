/**
 * @brief Implementacion del TAD Character
 *
 * @file character.c
 * @author Danyyil Shykerynets
 * @version 2
 * @date 27-02-2025
 * @copyright GNU Public License
 */

#include "../include/character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Character
 *
 * This struct stores all the information related to a character.
 */
struct _Character{
  Id id;                    /*!< ID of the character*/
  Id location;              /*!< ID of the locations of this character*/
  char name[WORD_SIZE];     /*!< String containing name of the character*/
  char gdesc[CHAR_GDESC];   /*!< String containing gdesc of the character*/
  int health;               /*!< Int containing health of character*/
  Bool friendly;            /*!< Sympathy of the character*/
  char message[WORD_SIZE];  /*!< String containing message of the character*/
  Id following;             /*!< Id of the player he follow or NO_ID if he do not follow anyone*/
};

Character* character_create(){
  Character* character = NULL;

  if( !(character = (Character*)calloc(1,sizeof(Character))) )
    return NULL;

  character->id = NO_ID;
  character->health = 1;
  character->friendly = TRUE;
  character->following = NO_ID;
  /* Calloc inicializa gdesc a \0 */
  return character;
}

Status character_destroy(Character* character){
  if( character ){
    free(character);
    character = NULL;
  }
  return OK;
}

Id character_get_id(Character* character){ 
  if( !character ){ return NO_ID; }
  return character->id; 
}

Status character_set_id(Character* character, Id id){
  if(!character || id == NO_ID)
    return ERROR;

  character->id = id;

  return OK;
}

Id character_get_location(Character* character){ 
  if( !character ){ return NO_ID; }
  return character->location; 
}

Status character_set_location(Character* character, Id location){
  if(!character || location == NO_ID)
    return ERROR;

  character->location = location;

  return OK;
}

char* character_get_name(Character* character){ 
  if( !character ){ return NULL; }
  return character->name; 
}

Status character_set_name(Character* character, char* name){
  if(!character || !name)
    return ERROR;

  strcpy(character->name, name);
  
  return OK;
}

char* character_get_gdesc(Character* character){ 
  if( !character ){ return "      "; }
  return character->gdesc; 
}

Status character_set_gdesc(Character* character, char* gdesc){
  if(!character || !gdesc)
    return ERROR;

  strcpy(character->gdesc, gdesc);
  
  return OK;
}

int character_get_health(Character* character){ 
  if( !character ){ return -1; }
  return character->health; 
}

Status character_set_health(Character* character, int health){
  if(!character)
    return ERROR;
    
  character->health = health;

  return OK;
}

Bool character_get_friendly(Character* character){ 
  if( !character ){ return FALSE; }
  return character->friendly; 
}

Status character_set_friendly(Character* character, Bool friendly){
  if( !character )
    return ERROR;

  character->friendly = friendly;

  return OK;
}

char* character_get_message(Character* character){ 
  if( !character ){ return NULL; }
  return character->message; 
}

Status character_set_message(Character* character, char* message){
  if(!character || !message)
    return ERROR;

  strcpy(character->message, message);
  
  return OK;  
}

Id character_get_following(Character *character){
  if (!character)
  {
    return NO_ID;
  }
  return character->following;
}

Status character_set_following(Character *character, Id id){
  if (!character || id == NO_ID)
  {
    return ERROR;
  }
  character->following = id;
  return OK;
}

void character_print(Character* c){
  if( !c )
    return;

  fprintf(stdout,"Character with ID: %ld\nName: %s\nGraphic Desc: %s\nHealth: %d\nFriendliness: %d\nMessage: %s\n", c->id, c->name, c->gdesc, c->health, c->friendly, c->message);
}
