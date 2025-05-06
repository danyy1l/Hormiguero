/**
 * @brief It implements the space module
 * @file space.c
 * @author Anthony Eduardo Alvarado
 * @version 22
 * @date 24-04-2025
 * @copyright GNU Public License
*/

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/*TO DO: Print*/

/**
 * @brief Espacios
 *
 * This struct stores all the information of a space.
*/
struct _Space { 
  Id id;                              /*!<-Id number of the space, it must be unique */
  char name[WORD_SIZE];               /*!<-Name of the space */
  Set* characters;                    /*!<-Array of characters*/
  Set *objects;                       /*!<-Array of objects*/
  char gdesc[GDESC_MAX][GDESC_SIZE];  /*!<-5x9 Array containing space's graphic desc*/
  Bool discovered;                    /*!<-Si el espacio ha sido descubierto o no*/
  char message1[WORD_SIZE];           /*!<-Mensaje principal del espacio*/
  char message2[WORD_SIZE];           /*!<-Mensaje secundario del espacio*/
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
  newSpace->message1[0] = '\0';
  newSpace->message2[0] = '\0';
  newSpace->objects = set_create();
  if(newSpace->objects==NULL){
    free(newSpace);
    return NULL;
  }
  newSpace->characters=set_create();
  if(newSpace->characters==NULL){
    set_destroy(newSpace->objects);
    free(newSpace);
    return NULL;
  }
 
    /*Si en el .dat el espacio no tiene gdesc definido, al pintar la partida, aparecerán estos espacios*/
    for(i=0;i<GDESC_MAX;i++){
    strcpy(newSpace->gdesc[i],"");
  }

  newSpace->discovered=FALSE;
 
  return newSpace;
}
 
Status space_destroy(Space* space) {
  if(space){
    set_destroy(space->objects);
    set_destroy(space->characters);
    free(space);
    space = NULL;
  }
 
  return OK;
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

Status space_add_character(Space* space, Id id){
  if(!space||id==NO_ID){
    return ERROR;
  }
  set_add_value(space->characters,id);
  return OK;
}

Status space_del_character(Space* space, Id id){
  if(!space||id==NO_ID){
    return ERROR;
  }

  set_del_value(space->characters,id);
  return OK;
}
 
Bool space_find_character(Space* space, Id id){
  if(!space||id==NO_ID){
    return FALSE;
  }
  if(set_find_object(space->characters,id)==TRUE){
    return TRUE;
  }
  return FALSE;
}

Id* space_id_character(Space* space){
  if(!space){
    return NULL;
  }
  return set_id_object(space->characters);
}

Set* space_get_set_characters(Space* space){
  if(!space){
    return NULL;
  }
  return space->characters;
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
  if (!space||id==NO_ID){
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
   
  return set_id_object(space->objects);
}
 
Set* space_get_set_objects(Space* space){
  if( !space )
    return NULL;
 
  return space->objects;
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

Status space_set_discovered(Space *space,Bool discovered){
  if(!space){
    return FALSE;
  }

  space->discovered=discovered;
  
  return OK;
 }

Bool space_get_discovered(Space *space) {
  if (!space) {
    return FALSE;
  }

  return space->discovered;

}

void space_player_arrive(Space* space) {
  if (!space_get_discovered(space)) {
    space_set_discovered(space, TRUE);
  }
}

char* space_get_message1(Space* space){
  return space == NULL ? NULL : space->message1;
}

char* space_get_message2(Space* space){
  return space == NULL ? NULL : space->message2;
}

Status space_set_message1(Space* space, char* message1){
  if(!space|||!message1) return ERROR;

  strcpy(space->message1, message1);

  return OK;
}

Status space_set_message2(Space* space, char* message2){
  if(!space||!message2) return ERROR;

  strcpy(space->message2, message2);

  return OK;
}

Status space_print(Space* space) {
  int i;

  /* Error Control */
  if (!space) {
    return ERROR;
  }
 
  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s; Discovered: %d)\n", space->id, space->name, space->discovered);

  /*2. Print space's sets*/
  for(i=0; i<set_get_nids(space->characters); i++){
    fprintf(stdout, "--->Character %d: %ld\n", i+1, set_id_object(space->characters)[i]);
  }

  for(i=0; i<set_get_nids(space->objects); i++){
    fprintf(stdout, "--->Object %d: %ld\n", i+1, set_id_object(space->objects)[i]);
  }

  /* 3. Print space gdesc*/
  for(i=0; i<GDESC_MAX; i++){
    fprintf(stdout, "%s\n", space_get_gdesc(space, i));
  }
 
  /* 4. Print space messages*/
  if( strcmp(space->message1, "\0" ) ) fprintf(stdout, "Message 1: \"%s\"\n", space->message1);
  if( strcmp(space->message2, "\0" ) )fprintf(stdout, "Message 2: \"%s\"\n", space->message2);
  
  return OK;
}
