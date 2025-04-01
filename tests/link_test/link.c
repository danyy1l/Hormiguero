/**
 * @brief It implements the link module
 * @file link.c
 * @author Danyyil Shykerynets
 * @version 0
 * @date 21-03-2025
 * @copyright GNU Public License
*/

#include "types.h"
#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Link{
  Id id;                  /*!<-ID del enlace*/
  char name[WORD_SIZE];   /*!<-Nombre del enlace*/
  Id origin, destination; /*!<-IDs de origen y destino del enlace*/
  Direction dir;          /*!<-Direccion en la que se orienta el enlace*/
  Bool open;              /*!<-Booleano que representa la apertura del enlace*/
};

Link* link_create(){
  Link* output = NULL;
  
  if( !(output = (Link*)calloc(1, sizeof(Link))) ) return NULL;

  output->id = NO_ID;
  output->origin = NO_ID;
  output->destination = NO_ID;
  output->dir = U;
  output->open = FALSE;

  return output;
}

Status link_destroy(Link* link){
  if(link) free(link);
  
  return OK;
}

Id link_get_id(Link* link){
  if( !link ) return NO_ID;

  return link->id;
}

Status link_set_id(Link* link, Id id){
  if( !link  || id == NO_ID) return ERROR;

  link->id = id;

  return OK;
}

const char* link_get_name(Link* link){
  if( !link ) return NULL;

  return link->name; 
}

Status link_set_name(Link* link, char* name){
  if( !link || !name ) return ERROR;

  strcpy(link->name, name);

  return OK; 
}

Id link_get_origin(Link* link){
  if( !link ) return NO_ID;

  return link->origin; 
}

Status link_set_origin(Link* link, Id origin){
  if( !link || origin == NO_ID) return ERROR;

  link->origin = origin;

  return OK; 
}

Id link_get_destination(Link* link){
  if( !link ) return NO_ID;

  return link->destination; 
}

Status link_set_destination(Link* link, Id destination){
  if( !link || destination == NO_ID) return ERROR;

  link->destination = destination;

  return OK; 
}

Direction link_get_direction(Link* link){
  if( !link ) return U;

  return link->dir;
}

Status link_set_direction(Link* link, Direction dir){
  if( !link || dir < U || dir > W) return ERROR;

  link->dir = dir;

  return OK; 
}

Bool link_get_open(Link* link) { 
  if( !link ) return FALSE;
  
  return link->open; 
}

Status link_set_open(Link* link, Bool open){
  if( !link ) return ERROR;

  link->open = open;

  return OK; 
}

void link_print(Link* link){
  if( !link ) return;

  fprintf(stdout, "Link ID: %ld\nLink name: %s\nConnection: %ld - %ld\n", link->id, link->name, link->origin, link->destination);
  fprintf(stdout, "Link direction: %d\nLink is open: %d\n", link->dir, link->open);
}