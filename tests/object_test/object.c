/**
 * @brief Implementa la funcionalidad de los objetos
 *
 * @file object.c
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 7
 * @date 06-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "object.h"

/**
 * @brief Object
 * Esta estructura define los elementos del objeto 
 */

 struct _Object{
  Id id;                            /*!< Número de id del objeto*/
  char name[WORD_SIZE + 1];         /*!< Nombre del objeto*/
  Id location;                      /*!< Id del espacio donde esta el objeto*/ 
  char description[WORD_SIZE];      /*!< Descripción del objeto*/
  Bool taken;                       /*!< Determina si el objeto ha sido tomado por algun jugador*/
};

Object* object_create(Id id){
  Object *newObject = NULL;

  newObject = (Object *) malloc(sizeof (Object));
  if (newObject == NULL)
    return NULL;

  newObject->id = id;
  newObject->name[0] = '\0';
  newObject->location = NO_ID;
  newObject->taken = FALSE;
  return newObject;
}

Status object_destroy(Object* object){
  if(object){  
    free(object);
    object = NULL;
  }
  return OK;
}

Status object_set_id(Object* object, Id id){
  if(!object||id==NO_ID)
    return ERROR;

  object->id=id;
  return OK;
} 

Id object_get_id(Object* object){
  if (!object)
    return NO_ID;

  return object->id;
}

Status object_set_location(Object *object, Id id){
  if( id == NO_ID || !object )  {return ERROR;}

  object->location = id;

  return OK;
}

Id object_get_location(Object *object){
  if( !object ) { return NO_ID; }

  return object->location;
}

Status object_set_name(Object* object, char* name) {
  if (!object || !name)
    return ERROR;

  if (!strcpy(object->name, name))
    return ERROR;

  return OK;
}


const char *object_get_name(Object* object) {
  if (!object)
    return NULL;

  return object->name;
}

Status object_set_description(Object *object, char *description) {
  if (!object || !description) {
    return ERROR;
  }
  strcpy(object->description, description);
  return OK;
}

char *object_get_description(Object *object) {
  if (!object) {
    return NULL;
  }

  return object->description;
}
 
Bool object_get_taken(Object* object){
  return object == NULL ? FALSE : object->taken;
}

Status object_set_taken(Object* object, Bool taken){
  if(!object) return ERROR;

  object->taken = taken;

  return OK;
}

Status object_print(Object* object){
  if (!object)
    return ERROR;

  fprintf(stdout, "-->object (id: %ld; name: %s; location id: %ld)", object->id, object->name, object->location);
  return OK;
}