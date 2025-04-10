/**
 * @brief Implementa la funcionalidad de los objetos
 *
 * @file object.c
 * @author Hugo Martín
 * @version 7
 * @date 06-02-2025
 * @copyright GNU Public License
 */

#include "../include/object.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/**
 * @brief Object 
 * Esta estructura define los elementos del objeto 
 */
struct _Object{
  Id id;                            /*!< Número de id del objeto*/
  char name[WORD_SIZE + 1];         /*!< Nombre del objeto*/
  Id location;                      /*!< Id del espacio donde esta el objeto*/ 
  char description[WORD_SIZE];      /*!< Descripción del objeto*/
  Bool taken;                       /*!< Determina si el objeto ha sido tomado por alguien*/
  int health;                       /*!< Puntos de vida que añade o quita al jugador*/
  Bool movable;                     /*!< Indica si el objeto se puede mover o no (Coger o no)*/
  Id dependency;                    /*!< Indica si el objeto depende de otro o no*/
  Id open;                          /*!< Indica si el objeto puede abrir un enlace o no*/
};

Object* object_create(Id id){
  Object *newObject = NULL;

  newObject = (Object *) malloc(sizeof (Object));
  if (newObject == NULL)
    return NULL;

  newObject->id = id;
  newObject->name[0] = '\0';
  newObject->location = NO_ID;

  newObject->health=0;
  newObject->movable=FALSE;
  newObject->dependency=NO_ID;
  newObject->open=NO_ID;

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

int object_get_health(Object *object) {
  if (!object) {
    return 0;
  }
  return object->health; 
}

Status object_set_health(Object *object, int health) {
  if (!object) {
    return ERROR;
  }
  object->health=health;
  return OK;
}

Bool object_get_movable(Object *object) {
  if (!object) {
    return FALSE;
  }
  return object->movable;
}

Status object_set_movable(Object *object, Bool movable) {
  if (!object) {
    return ERROR;
  }
  object->movable=movable;
  return OK;
}

Id object_get_dependency(Object *object) {
  if (!object) {
    return NO_ID;
  }
  return object->dependency;
}

Status object_set_dependency(Object *object, Id dependency) {
   if (!object) {
    return ERROR;
  }
  object->dependency=dependency;
  return OK;
}

Id object_get_open(Object *object) {
  if (!object) {
    return NO_ID;
  }
  return object->open;
}

Status object_set_open(Object *object, Id open) {
   if (!object) {
    return ERROR;
  }
  object->open=open;
  return OK;
}

Status object_print(Object* object){
  if (!object)
    return ERROR;

  fprintf(stdout, "-->object (id: %ld; name: %s; location id: %ld)", object->id, object->name, object->location);
  return OK;
}