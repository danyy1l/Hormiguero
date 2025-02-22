/**
* @brief Implementa las interfaces del set.h
* @file set.c
* @author Anthony Eduardo Alvarado Carbajal
* @version 1
* @date 18-02-2025
* @copyright GNU Public License
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".../include/set.h"

struct _Set{
    Id ids[MAX_IDS];     /*!< Array de ids de los objetos del conjunto */
    int n_ids;          /*!< El número de objetos del conjunto */
};

Set *set_create(){
  
  int i;
  Set *newSet=NULL;

  newSet=(Set*)malloc(1*sizeof(Set));

  if (newSet==NULL){
    return NULL;
  }

  for (i=0;i<MAX_IDS;i++){
    newSet->ids[i]=NO_ID;
  }

  newSet->n_ids=0;

  return newSet;
}

Status set_destroy(Set* set){

  if (!set){
    return ERROR;
  }
  free(set);

  set=NULL;

  return OK;
}

Status set_add_value(Set *set, Id id){

  int i;
  if (!set||id==NO_ID){
    return ERROR;
  }

  for(i=0;i<MAX_IDS;i++){
    if(set->ids[i]==NO_ID){
      set->ids[i]=id;
      set->n_ids++;
      return OK;
    }
  } 
  return ERROR;
}

Status set_del_value(Set *set,Id id){
  int i;

  if (!set|| id==NO_ID){
    return NULL;
  }

  for(i=0;i<MAX_IDS;i++){
    if(set->ids[i]==id){
      set->ids[i]=NO_ID;
      set->n_ids--;
      return OK;
    }
  }

  return ERROR;
}


Bool set_find_object(Set *set, Id id){
  int i;
  if (!set||id==NO_ID){
    return FALSE;
  }

  for (i=0;i<MAX_IDS;i++){
    if(set->ids[i]=id){
      return TRUE;
    }
  }
  return FALSE;
}

Id *set_id_object(Set *set){
  if (!set){
    return NO_ID;
  }

  return set->ids;
}

Status set_print(Set *set){
  int i;
  if (!set){
    return ERROR;
  }
  fprintf(stdout,"Número de objetos: %d\n",set->n_ids);

  for(i=0;i<MAX_IDS;i++){
    if(set->ids[i]!=NO_ID){
        fprintf(stdout, "Id: %ld\n",set->ids[i]);
    }
  }
  return OK;
}

