/**
 * @brief It implements the space module
 * @file space.c
 * @author Danyyil Shykerynets 
 * @author Anthony Eduardo Alvarado
 * @version 8
 * @date 24-02-2025
 * @copyright GNU Public License
 */

#include "../include/space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Eliminar funciones object y susituir por otras funciones set ya que el campo tipo object ya no existe  */

/**
* @brief Space
*
* This struct stores all the information of a space.
*/
struct _Space { 
  Id id;                              /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];           /*!< Name of the space */
  Id north;                           /*!< Id of the space at the north */
  Id south;                           /*!< Id of the space at the south */
  Id east;                            /*!< Id of the space at the east */
  Id west;                            /*!< Id of the space at the west */
  Id character_id;                    /*!< Id of the character in the space, NO_ID if no characters*/
  Set *objects;                       /*!< Array of objects*/
  char gdesc[GDESC_MAX][GDESC_SIZE];  /*!< 5x9 Array containing space's graphic desc*/
};

/** space_create allocates memory for a new space
*  and initializes its members
*/
Space* space_create(Id id) {
  int i;
  Space* newSpace = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newSpace = (Space*)malloc(sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->character_id=NO_ID;
  newSpace->objects = set_create();
  if(newSpace->objects==NULL){
    free(newSpace);
    return NULL;
  }

  /*Si en el .dat el espacio no tiene gdesc definido, al pintar la partida, aparecerán estos espacios*/
  for(i=0;i<GDESC_MAX;i++){
  strcpy(newSpace->gdesc[i],"");
}

  return newSpace;
}

Status space_destroy(Space* space) {
  if(space){
  set_destroy(space->objects);
    free(space);
    space = NULL;
    return OK;
  }else
    return ERROR;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Status space_add_object(Space* space, Id id){
  if (!space|| id==NO_ID){
    return ERROR;
  }
  
  set_add_value(space->objects,id);
  return OK;
}

Status space_del_object(Space* space, Id id){
  if (!space|| id== NO_ID){
    return ERROR;
  }
  
  set_del_value(space->objects,id);
  return OK;
}

Bool space_find_object(Space* space,Id id){
  if (!space){
    return FALSE;
  }
  if (set_find_object(space->objects,id)==TRUE){
    return TRUE;
  }
  return FALSE;
}

Id* space_id_object(Space *space){
  if (!space){
    return NULL;
  }
  
  return (set_id_object(space->objects));
}

Status space_set_character(Space *space, Id character_id){
  if( !space ){
    return ERROR;
  }
  space->character_id = character_id;
  return OK;
}

Id space_get_character_id(Space *space){
  if( !space ){
    return NO_ID;
  }
  return space->character_id;
}

char* space_get_gdesc(Space *space, int pos){
  if (!space){
    return NULL;
  }
  return space->gdesc[pos];
}

Status space_set_gdesc(Space *space, char* name, int pos){
  if (!space||!name){
    return ERROR;
  }

  strcpy(space->gdesc[pos], name);
  return OK;
}

Status space_print(Space* space) {
  Id idaux = NO_ID;

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  if (space_find_object(space,idaux)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  /* 4. Print if there is a character in the space or not*/
  if (space_get_character_id(space) != NO_ID){
    fprintf(stdout, "---> Character in the space with ID: %ld.\n", space_get_character_id(space));
  } else {
    fprintf(stdout, "---> No character in the space.\n");
  }
  
  return OK;
}
