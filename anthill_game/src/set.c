/**
* @brief Implementa las interfaces del set.h
* @file set.c
* @author Anthony Eduardo Alvarado Carbajal
* @version 1
* @date 24-04-2025
* @copyright GNU Public License
*/ 


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "../include/set.h"

/**
 * @brief Conjuntos
 */
struct _Set{
  Id ids[MAX_IDS];    /*!< Array de ids de los objetos del conjunto */
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
  if (set){
    free(set);
    set=NULL;
  }

  return OK;
}

int set_get_nids(Set* set){
  if (!set){
    return -1;
  } 

  return set->n_ids;
}

Status set_set_nids(Set* set, int n){
  if (!set){
    return ERROR;
  }

  set->n_ids=n; 
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
  int i, j;

  if (!set|| id==NO_ID){
    return ERROR;
  }

  for(i=0;i<set->n_ids;i++){
    if(set->ids[i]==id){
      set->ids[i]=NO_ID;

      /*Desplaza todos los elementos a la izq, de esta manera, no quedan huecos libres*/
      for(j=i; j<MAX_IDS-1; j++){
        set->ids[j] = set->ids[j+1];
      }

      set->ids[MAX_IDS-1] = NO_ID;
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

  for (i=0;i<set->n_ids;i++){
    if(set->ids[i]==id){
      return TRUE;
    }
  }
  return FALSE;
}

Id *set_id_object(Set *set){
  if (!set){
    return NULL;
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

