/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Danyyil Shykerynets
 * @version 7
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "../include/graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/command.h"
#include "../include/game_reader.h"
#include "../include/libscreen.h"
#include "../include/object.h"
#include "../include/player.h"
#include "../include/space.h"
#include "../include/types.h"

#define WIDTH_MAP 57
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 29
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3

#define LINE_SPACE 13

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

void print_blank(char* str, Graphic_engine* ge){
  int i;
  for(i=0; i<10; i++){
    sprintf(str, "                               ");
    screen_area_puts(ge->map, str);
  }
}

void print_objects(Game* game, Id id, char* str){
  int i, id_count;
  char foo[WORD_SIZE] = "";
  Object* object;
  Space* space;
  Id* ids;

  space = game_get_space(game, id);
  ids = space_id_object(space);
  id_count = set_get_nids(space_get_set_objects(space));

  for(i=0; i<id_count; i++){
    
    object = game_get_object(game, ids[i]);
    
    if( player_find_object(game_get_player(game), object)==TRUE )
      continue;
    
    if( strlen(foo) + strlen(object_get_name(object)) > LINE_SPACE ){
      foo[strlen(foo)-2] = '\0';
      break;
    }
    strcat(foo, object_get_name(object));
    if( i!=id_count-1 ){
      strcat(foo, ", ");
    }
    
  }
  
  if(i!=id_count && strlen(foo) < LINE_SPACE)
    strcat(foo, ",");

  /*LINE_SPACE es el numero de espacios que tiene de ancho las casillas, que son 15 menos 2 de los laterales que ya los imprime otra funcion*/
  while(strlen(foo) < LINE_SPACE){
    strcat(foo, " ");
  }

  strcat(str, foo);
  
}

void print_act(Graphic_engine* ge, Game* game, char* str, Id id_act, Space* space_act){
  Player* player = game_get_player(game);
  char character_gdesc[GDESC_SIZE];
  int i;

  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( space_get_character_id(space_act) == NO_ID )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_get_character_id(space_act))) );  

  if (id_act != NO_ID) {
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    | %s %s %2d|", player_get_gdesc(player), character_gdesc,(int)id_act);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      strcpy(str, "                    |");
      strcat(str, space_get_gdesc(space_act, i));
      strcat(str, "      |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                    | ");
    print_objects(game, id_act, str);
    strcat(str, " |");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
  }
}

void print_north(Graphic_engine* ge, Game* game, char* str, Id id_north, Space* space_north){
  int i;
  if( space_get_discovered(space_north) ){
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    |      %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_north))),(int)id_north);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      strcpy(str, "                    |");
      strcat(str, space_get_gdesc(space_north, i));
      strcat(str, "      |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                    | ");
    print_objects(game, id_north, str);
    strcat(str, " |");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
  }else{
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    |             %2d|", (int)id_north);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX + 1; i++){
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
  }

  if(game_connection_is_open(game, game_get_connection(game, id_north, S), N))
      sprintf(str, "                            ^");
    else
      sprintf(str, "                            X");
  screen_area_puts(ge->map, str);
}

void print_south(Graphic_engine* ge, Game *game, char* str, Id id_south, Space* space_south){
  int i;
  if(game_connection_is_open(game, game_get_connection(game, id_south, N), S))
    sprintf(str, "                            v");
  else
    sprintf(str, "                            X");
  screen_area_puts(ge->map, str);
  if(space_get_discovered(space_south)){
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    |      %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_south))),(int)id_south);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      strcpy(str, "                    |");
      strcat(str, space_get_gdesc(space_south, i));
      strcat(str, "      |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                    | ");
    print_objects(game, id_south, str);
    strcat(str, " |");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
  }else{
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                    |             %2d|", (int)id_south);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX + 1; i++){
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                    +---------------+");
    screen_area_puts(ge->map, str);
  }
}

void print_west(Graphic_engine* ge, Game *game, char* str, Id id_west, Id id_act, Space* space_west, Space* space_act){
  int open_west, i;
  Player* player = game_get_player(game);
  char character_gdesc[GDESC_SIZE], foo;

  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( space_get_character_id(space_act) == NO_ID )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_get_character_id(space_act))) );
  
  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, W) )
    open_west = '<';
  else
    open_west = 'X';

  if(space_get_discovered(space_west)){
    if (id_act != NO_ID) {
      sprintf(str, "+---------------+   +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "|      %s %2d|   | %s %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, player_get_gdesc(player), character_gdesc,(int)id_act);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        if(i==2)
          foo = open_west;
        else
          foo= ' ';
        sprintf(str, "|%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "| ");
      print_objects(game, id_west, str);
      strcat(str, " |   | ");
      print_objects(game, id_act, str);
      strcat(str, " |");
      screen_area_puts(ge->map, str);

      sprintf(str, "+---------------+   +---------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    sprintf(str, "+---------------+   +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "|             %2d|   | %s %s %2d|", (int)id_west, player_get_gdesc(player), character_gdesc,(int)id_act);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      if(i==2)
        foo = open_west;
      else
        foo= ' ';
      sprintf(str, "|               | %c |%s      |", foo, space_get_gdesc(space_act, i));
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "|               |   |               |");
    screen_area_puts(ge->map, str);
    sprintf(str, "+---------------+   +---------------+");
    screen_area_puts(ge->map, str);
  }
}

void print_east(Graphic_engine* ge, Game *game, char* str, Id id_east, Id id_act, Space* space_east, Space* space_act){
  int open_east, i;
  Player* player = game_get_player(game);
  char character_gdesc[GDESC_SIZE], foo;
  
  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( space_get_character_id(space_act) == NO_ID )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_get_character_id(space_act))) );  

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, E) )
    open_east = '>';
  else
    open_east = 'X';

  if( space_get_discovered(space_east) ){
    if (id_act != NO_ID) {
      sprintf(str, "                    +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    | %s %s %2d|   |      %s %2d|", player_get_gdesc(player), character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        if(i==2)
          foo = open_east;
        else
          foo= ' ';
        sprintf(str, "                    |%s      | %c |%s      |", space_get_gdesc(space_act, i), foo, space_get_gdesc(space_east, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                    | ");
      print_objects(game, id_act, str);
      strcat(str, " |   | ");
      print_objects(game, id_east, str);
      strcat(str, " |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    if (id_act != NO_ID) {
      sprintf(str, "                    +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    | %s %s %2d|   |             %2d|", player_get_gdesc(player), character_gdesc, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        if(i==2)
          foo = open_east;
        else
          foo= ' ';
        sprintf(str, "                    |%s      | %c |               |", space_get_gdesc(space_act, i), foo);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                    |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
    }
  }
}

void print_east_and_west(Graphic_engine* ge, Game *game, char* str, Id id_west, Id id_east, Id id_act, Space* space_west, Space* space_east, Space* space_act){
  int open_east, open_west, i;
  Player* player = game_get_player(game);
  char character_gdesc[GDESC_SIZE], foo, foo1;

  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( space_get_character_id(space_act) == NO_ID )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_get_character_id(space_act))) );  

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, W) )
    open_west = '<';
  else
    open_west = 'X';
  if( game_connection_is_open(game, id_act, E) )
    open_east = '>';
  else
    open_east = 'X';

  if( space_get_discovered(space_east) ){
    if(space_get_discovered(space_west)){
      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | %s %s %2d|   |      %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, player_get_gdesc(player), character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = open_west;
            foo1 = open_east;
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|%s      | %c |%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_west, str);
        strcat(str, " |   | ");
        print_objects(game, id_act, str);
        strcat(str, " |   | ");
        print_objects(game, id_east, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|             %2d|   | %s %s %2d|   |      %s %2d|", (int)id_west, player_get_gdesc(player), character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = open_west;
            foo1 = open_east;
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|               | %c |%s      | %c |%s      |", foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   | ");
        print_objects(game, id_act, str);
        strcat(str, " |   | ");
        print_objects(game, id_east, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_west)){
      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | %s %s %2d|   |             %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, player_get_gdesc(player), character_gdesc, (int)id_act, (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = open_west;
            foo1 = open_east;
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|%s      | %c |%s      | %c |               |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_west, str);
        strcat(str, " |   | ");
        print_objects(game, id_act, str);
        strcat(str, " |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|             %2d|   | %s %s %2d|   |             %2d|", (int)id_west, player_get_gdesc(player), character_gdesc, (int)id_act, (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = open_west;
            foo1 = open_east;
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|               | %c |%s      | %c |               |", foo, space_get_gdesc(space_act, i), foo1);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   | ");
        print_objects(game, id_act, str);
        strcat(str, " |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }
}

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID, player_location = NO_ID;
  Space *space_act = NULL, *space_north = NULL, *space_south = NULL, *space_east = NULL, *space_west = NULL;
  Object* object=NULL;
  Character* character;
  CommandCode last_cmd = UNKNOWN;
  Status last_cmd_status;
  char action_return[STATUS_SIZE];
  char str[WORD_SIZE], friendly[WORD_SIZE/2];
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, id_count, dir_check = 0;

  Player *player=game_get_player(game);                               /*Jugador del game*/
  Inventory *inventory=player_get_objects(player);                    /*Inventario del jugador del game*/
  int n_ids=set_get_nids(inventory_get_objects(inventory)); 
  Id *set_ids=set_id_object(inventory_get_objects(inventory));        /*Array de Ids, con los ids de los objetos de la mochila del jugador*/     

  /* Paint the in the map area */
  screen_area_clear(ge->map);
    if( (id_act = player_get_location(player)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_north = game_get_connection(game, id_act, N);
    space_north = game_get_space(game, id_north);
    id_south = game_get_connection(game, id_act, S);
    space_south = game_get_space(game, id_south);
    id_east = game_get_connection(game, id_act, E);
    space_east = game_get_space(game, id_east);
    id_west = game_get_connection(game, id_act, W);
    space_west = game_get_space(game, id_west);

    /*Each direction sums a binary value so that if theres a space north and west
    it'd be equivalent to 1010 (NESW) = 10 in decimal*/
    
    if (id_north != NO_ID) {
      dir_check += 8;
    }

    if (id_east != NO_ID) {
      dir_check += 4;
    }

    if (id_south != NO_ID) {
      dir_check += 2;
    }

    if (id_west != NO_ID) {
      dir_check += 1;
    }

    /*Caso especial: Si el espacio no tiene gdesc, relleno los 5 campos con 9 espacios*/
    for(i=0; i<GDESC_MAX;i++){
      if( space_act && strlen(space_get_gdesc(space_act, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_act, "         ", i);
      if( space_north && strlen(space_get_gdesc(space_north, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_north, "         ", i);
      if( space_south && strlen(space_get_gdesc(space_south, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_south, "         ", i);
      if( space_east && strlen(space_get_gdesc(space_east, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_east, "         ", i);
      if( space_west && strlen(space_get_gdesc(space_west, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_west, "         ", i);
    }

    /*IMPRESIÓN DE CASILLAS, Para mejor view, cerrar*/
    switch(dir_check){
    case 1:
      print_blank(str, ge);
      print_west(ge, game, str, id_west, id_act, space_west, space_act);
      break;
    case 2:
      print_blank(str, ge);
      print_act(ge, game, str, id_act, space_act);
      print_south(ge, game, str, id_south, space_south);
      break;
    case 3:
      print_blank(str, ge);
      print_west(ge, game, str, id_west, id_act, space_west, space_act);
      print_south(ge, game, str, id_south, space_south);
      break;
    case 4:
      print_blank(str, ge);
      print_east(ge, game, str, id_east, id_act, space_east, space_act);
      break;
    case 5:
      print_blank(str, ge);
      print_east_and_west(ge, game, str, id_west, id_east, id_act, space_west, space_east, space_act);
      break;
    case 6:
      print_blank(str, ge);
      print_east(ge, game, str, id_east, id_act, space_east, space_act);     
      print_south(ge, game, str, id_south, space_south);
      break;
    case 7:
      print_blank(str, ge);
      print_east_and_west(ge, game, str, id_west, id_east, id_act, space_west, space_east, space_act);
      print_south(ge, game, str, id_south, space_south);
      break;
    case 8:
      print_north(ge, game, str, id_north, space_north);
      print_act(ge, game, str, id_act, space_act);
      break;
    case 9:
      print_north(ge, game, str, id_north, space_north);
      print_west(ge, game, str, id_west, id_act, space_west, space_act);
      break;
    case 10:
      print_north(ge, game, str, id_north, space_north);
      print_act(ge, game, str, id_act, space_act);
      print_south(ge, game, str, id_south, space_south);
      break;
    case 11:
      print_north(ge, game, str, id_north, space_north);
      print_west(ge, game, str, id_west, id_act, space_west, space_act);
      print_south(ge, game, str, id_south, space_south);
      break;
    case 12:
      print_north(ge, game, str, id_north, space_north);
      print_east(ge, game, str, id_east, id_act, space_east, space_act);
      break;
    case 13:
      print_north(ge, game, str, id_north, space_north);
      print_east_and_west(ge, game, str, id_west, id_east, id_act, space_west, space_east, space_act);
      break;
    case 14:
      print_north(ge, game, str, id_north, space_north);
      print_east(ge, game, str, id_east, id_act, space_east, space_act);
      print_south(ge, game, str, id_south, space_south);
      break;
    case 15:
      print_north(ge, game, str, id_north, space_north);
      print_east_and_west(ge, game, str, id_west, id_east, id_act, space_west, space_east, space_act);
      print_south(ge, game, str, id_south, space_south);
      break;
    default:
      break; 
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  if( (player_location = player_get_location(player)) != NO_ID) {
    sprintf(str, "  Turn: %d", game_get_turn(game) + 1);
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Player %s: ", player_get_name(game_get_player(game)));
    screen_area_puts(ge->descript, str);
    sprintf(str, "   Location: %d", (int)player_location);
    screen_area_puts(ge->descript, str);
    sprintf(str, "   Health: %d", player_get_health(player));
    screen_area_puts(ge->descript, str);
    screen_area_puts(ge->descript, " ");
  }

  sprintf(str, "  Objects: ");
  screen_area_puts(ge->descript, str);
  i=0;
  id_count = 0;
  while(i < game_get_n_objects(game)){
    object = game_get_object(game, id_count);
    if( object ){
      sprintf(str, "   %s: %d", object_get_name(object), (int)object_get_location(object));
      screen_area_puts(ge->descript, str);
      i++;
      id_count++;
    }else
      id_count++;

  }
  screen_area_puts(ge->descript, " "); 

  sprintf(str, "  Characters: ");
  screen_area_puts(ge->descript, str);
  id_count = 100;
  for(i=0; i<game_get_n_characters(game); i++, id_count+=100){
    if( (character = game_get_character(game, id_count)) ){
      if( character_get_friendly(character) ){ strcpy(friendly, "Friend"); }
      else{ strcpy(friendly, "Enemy"); }
      sprintf(str, "   %s: %d  (%d HP) %s", character_get_gdesc(character), (int)character_get_location(character), character_get_health(character), friendly);
      screen_area_puts(ge->descript, str);
    }else
      i--;
  }

  screen_area_puts(ge->descript, " ");

  if(inventory_is_empty(player_get_objects(player))==TRUE) {
    sprintf(str, "  Player has no object");
    screen_area_puts(ge->descript, str);
  } else {
    sprintf(str, "  Player has these objects: %d", set_get_nids(inventory_get_objects(player_get_objects(player))));
    screen_area_puts(ge->descript, str);
    for (i=0;i<n_ids;i++) {
      object=game_get_object(game, set_ids[i]);       /*Cada uno de los objetos de la mochila del jugador*/
      sprintf(str, "  %s (Id: %ld)", object_get_name(object), object_get_id(object));
      screen_area_puts(ge->descript, str);
    }
  }
  screen_area_puts(ge->descript, " ");

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " Move(m), Take(t), Drop(d), Attack(a), Chat(c), Inspect(i), Quit(q)");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  if(last_cmd >= NO_CMD && last_cmd <= INSPECT ){
    last_cmd_status = command_get_output(game_get_last_command(game));
    if( last_cmd_status )
      strcpy(action_return,"Ok");
    else
      strcpy(action_return,"Error");

    sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], action_return);
    screen_area_puts(ge->feedback, str);
  }

  if( last_cmd == CHAT && last_cmd_status ){
    sprintf(str, "  %s: %s",character_get_name(game_get_character(game, space_get_character_id(space_act))), character_get_message( game_get_character(game, space_get_character_id(space_act)) ));
    screen_area_puts(ge->descript, str);
  }

  if( last_cmd == INSPECT && last_cmd_status ){
    sprintf(str, "  %s: %s", object_get_name(game_get_object_by_name(game, command_get_arguments(game_get_last_command(game)))), object_get_description(game_get_object_by_name(game, command_get_arguments(game_get_last_command(game)))));
    screen_area_puts(ge->descript, str);
  }

  /* Dump to the terminal */
  screen_paint(game_get_turn(game));
  printf("Prompt => ");
}

void graphic_engine_paint_game_over(Graphic_engine* ge, Game *game){
  int i;
  char str[WORD_SIZE];

  /* Paint the in the map area */
  screen_area_clear(ge->map);

  for(i=0; i<HEIGHT_MAP; i++){
    if( i == HEIGHT_MAP/2 ){
      sprintf(str, "                     GAME OVER!                ");
      screen_area_puts(ge->map, str);
      sprintf(str, "            Player \"%s\" has died :(        ", player_get_name(game_get_player(game)));
      screen_area_puts(ge->map, str);
    }else{
      sprintf(str, "                                           ");
      screen_area_puts(ge->map, str);
    }
  }
  
  screen_paint(game_get_turn(game));
}