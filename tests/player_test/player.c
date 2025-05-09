/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Danyyil Shykerynets
 * @version 22
 * @date 24-04-2025
 * @copyright GNU Public License
 */  
 
 #include "player.h"
 #include "object.h"
  
 #include <stdio.h> 
 #include <stdlib.h>
 #include <string.h>  
 
 /**
  * @brief Jugadores (usuarios)
  */
 struct _Player {
   Id id;                      /*!<-ID del jugador*/
   Id location;                /*!<-ID del espacio en el que se ubica el jugador*/
   char name[WORD_SIZE + 1];   /*!<-Nombre del jugador*/
   char gdesc[PLY_GDESC + 1];  /*!<-Descripcion grafica del jugador*/
   Inventory* backpack;        /*!<-Inventario del jugador*/
   int health;                 /*!<-Vida del jugador*/
   int strength;               /*!<-Fuerza del jugador*/
   Set* followers;             /*!<-Seguidores del jugador*/
 };
 
 Player *player_create(){
   Player *output = NULL;
 
   if( !(output = (Player*)calloc(1, sizeof(Player))) )
     return NULL;
 
   output->id = NO_ID;
   output->location = NO_ID;
   output->name[0] = '\0';
   output->gdesc[0] = '\0';
   output->backpack = inventory_create();
   output->health = 0;
   output->strength = 1;
   output->followers = set_create();
 
   return output;
 }
 
 Status player_destroy(Player *player){
   if( player ){
     inventory_destroy(player->backpack);
     set_destroy(player->followers);
     free(player);
     player = NULL;
   }
   return OK;
 }
 
 Id player_get_id(Player* player){
   return player == NULL ? NO_ID : player->id;
 }
 
 Status player_set_id(Player *player, Id id){
   if( !player || id == NO_ID ) { return ERROR; }
 
   player->id = id;
 
   return OK;
 }
 
 const char* player_get_name(Player* player){
   return player == NULL ? NULL : player->name;
 }
 
 Status player_set_name(Player* player, const char* name){
   if( !player || !name ) return ERROR;
 
   strcpy(player->name, name);
   return OK;
 }
 
 Id player_get_location(Player *player) { 
   if( !player ) { return NO_ID; }
   
   return player->location; 
 }
 
 Status player_set_location(Player *player, Id id) {
   if (id == NO_ID || !player) {
     return ERROR;
   }
 
   player->location = id;
 
   return OK;
 }
 
 Status player_add_object(Player *player, Object* object){
   if( !player || !object ){ return ERROR; }
 
   if (inventory_is_full(player->backpack)==TRUE) {
     return ERROR;
   } 
 
   inventory_add_object(player->backpack, object_get_id(object));
 
   return OK;
 }
 
 Status player_del_object(Player *player, Object *object) {
   if( !player || !object ){ return ERROR; }
 
   if (inventory_is_empty(player->backpack)==TRUE) {
     return ERROR; 
   }
 
   inventory_del_object(player->backpack, object_get_id(object));
 
   return OK;
 }
 
 Inventory* player_get_objects(Player *player){
   if( !player ) { return NULL; }
   
   return player->backpack;
 }
 
 Bool player_find_object(Player *player, Object *object) {
   if (!player || !object) {
     return FALSE;
   }
 
   return inventory_find_object(player->backpack, object_get_id(object));  
 }
 
 Status player_set_health(Player *player, int health){
   if(!player) { return ERROR; }
 
   player->health = health;
 
   return OK;
 }
 
 int player_get_health(Player* player){
   if( !player ) { return -1; }
 
   return player->health;
 }
 
 Status player_set_gdesc(Player* player, const char* gdesc){
   if( !player || !gdesc ) return ERROR;
 
   strcpy(player->gdesc, gdesc);
 
   return OK;
 }
 
 Status player_set_strength(Player *player, int strength){
   if(!player) { return ERROR; }
 
   player->strength = strength;
 
   return OK;
 }
 
 int player_get_strength(Player* player){
   if( !player ) { return -1; }
 
   return player->strength;
 }
 
 char* player_get_gdesc(Player* player){
   return player == NULL ? NULL : player->gdesc;
 }
 
 Set* player_get_followers(Player* player){
   return player == NULL ? NULL : player->followers;
 }
 
 Status player_print(Player *player){
   Set *set=inventory_get_objects(player->backpack);
   if( player ){
     printf("Player ID: %ld\nPlayer location: %ld\nPlayer name: %s\nPlayer health: %dPlayer strength: %d", player->id, player->location, player->name, player->health, player->strength);
     printf("Player objects: \n");
     set_print(set);
     return OK;
   }else
     return ERROR;
 } 
