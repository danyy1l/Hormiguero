/**
 * @brief It implements the inventory module
 * @file inventory.c
 * @author Álvaro Rodríguez
 * @version 0
 * @date 20-03-2025
 * @copyright GNU Public License
*/

#include "../include/inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Inventory{
  Set *objects;
  int max_objects;
};

Inventory *inventory_create(){
  Inventory *newInventory=NULL;

  newInventory=(Inventory*)malloc(sizeof(Inventory));
  if (!newInventory) return NULL;

  newInventory->max_objects=MAX_INVENTORY_OBJS;
  newInventory->objects=set_create();
  if (newInventory->objects==NULL){
    free(newInventory);
    return NULL;
  }

  return newInventory;
}

Status inventory_destroy(Inventory * inventory){
  if (inventory){
    set_destroy(inventory->objects);
    free(inventory);
    inventory=NULL;
  }
  return OK;
}

Bool inventory_is_empty(Inventory * inventory){
  if (!inventory){
    return TRUE;
  }

  if (set_get_nids(inventory->objects)==0){
    return TRUE;
  }else{
    return FALSE;
  }
}

Bool inventory_is_full(Inventory * inventory){
  if (!inventory){
    return FALSE;
  }

  if (set_get_nids(inventory->objects)==inventory->max_objects){
    return TRUE;
  }else{
    return FALSE;
  }
}

Status inventory_add_object(Inventory* inventory, Id id){
  if (!inventory || id==NO_ID){
    return ERROR;
  }
  
  set_add_value(inventory->objects,id);
  return OK;
}
  
Status inventory_del_object(Inventory* inventory, Id id){
  if (!inventory|| id== NO_ID){
    return ERROR;
  }
  
  set_del_value(inventory->objects,id);
  return OK;
}

Bool inventory_find_object(Inventory* inventory,Id id){
  if (!inventory || id==NO_ID){
    return FALSE;
  }

  return set_find_object(inventory->objects,id);
}

Status inventory_set_max_objects(Inventory *inventory, int n){
  if (!inventory || n<=0){
    return ERROR;
  }

  inventory->max_objects=n;
  return OK;
}

int inventory_get_max_objects(Inventory *inventory){
  if (!inventory){
    return -1;
  }

  return inventory->max_objects;
}
 
Set *inventory_get_objects(Inventory *inventory) {
  if (!inventory) {
    return NULL;
  } 

  return inventory->objects;
}

Status inventory_print(Inventory* inventory){
  if (!inventory){
    return ERROR;
  }

  fprintf(stdout,"Capacity:%d\n",inventory->max_objects);
  set_print(inventory->objects);
  return OK;
}