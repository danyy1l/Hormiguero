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

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

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
  Object* object;
  Character* character;
  CommandCode last_cmd = UNKNOWN;
  char action_return[STATUS_SIZE], character_gdesc[GDESC_SIZE];
  char str[WORD_SIZE], foo, foo1;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, id_count, dir_check = 0;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = player_get_location(game_get_player(game))) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_north = space_get_north(space_act);
    space_north = game_get_space(game, id_north);
    id_south = space_get_south(space_act);
    space_south = game_get_space(game, id_south);
    id_east = space_get_east(space_act);
    space_east = game_get_space(game, id_east);
    id_west = space_get_west(space_act);
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

    /*foo represents the object close to the player indicating that it is in their inventory*/
    if( object_get_id(player_get_object(game_get_player(game))) != NO_ID )
      foo = '*';
    else
      foo = ' ';

    strcpy(character_gdesc, "\0");
    if( space_get_character_id(space_act) == NO_ID )
      strcpy(character_gdesc, "      ");
    else
      strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_get_character_id(space_act))) );

    for(i=0; i<GDESC_MAX;i++)
      if( strlen(space_get_gdesc(space_act, i)) < 9 ){
        space_set_gdesc(space_act, "         ", i);
      if( strlen(space_get_gdesc(space_north, i)) < 9 )
        space_set_gdesc(space_north, "         ", i);
      if( strlen(space_get_gdesc(space_south, i)) < 9 )
        space_set_gdesc(space_south, "         ", i);
      if( strlen(space_get_gdesc(space_east, i)) < 9 )
        space_set_gdesc(space_east, "         ", i);
      if( strlen(space_get_gdesc(space_west, i)) < 9 )
        space_set_gdesc(space_west, "         ", i);
    }

    switch(dir_check){
    case 1:
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc,(int)id_act);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '<';
          else
            foo= ' ';
          sprintf(str, "|%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      break;
    case 2:
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    | m0^%c %s %2d|", foo, character_gdesc,(int)id_act);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        strcpy(str, "                    |");
        strcat(str, space_get_gdesc(space_act, i));
        strcat(str, "      |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      }

      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      break;
    case 3:
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc,(int)id_act);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '<';
          else
            foo= ' ';
          sprintf(str, "|%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }

      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      break;
    case 4:
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      
      if (id_act != NO_ID) {
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    | m0^%c %s %2d|   |      %s %2d|", foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '>';
          else
            foo= ' ';
          sprintf(str, "                    |%s      | %c |%s      |", space_get_gdesc(space_act, i), foo, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                    |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      break;
    case 5:
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|   |      %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = '<';
            foo1 = '>';
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|%s      | %c |%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      break;
    case 6:
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    | m0^%c %s %2d|   |      %s %2d|", foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '>';
          else
            foo= ' ';
          sprintf(str, "                    |%s      | %c |%s      |", space_get_gdesc(space_act, i), foo, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                    |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      break;
    case 7:
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                               ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|   |      %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = '<';
            foo1 = '>';
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|%s      | %c |%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      break;
    case 8:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "                    +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    | m0^%c %s %2d|", foo, character_gdesc,(int)id_act);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          strcpy(str, "                    |");
          strcat(str, space_get_gdesc(space_act, i));
          strcat(str, "      |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                    |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    +---------------+");
        screen_area_puts(ge->map, str);
      }
      break;
    case 9:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc,(int)id_act);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '<';
          else
            foo= ' ';
          sprintf(str, "|%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      break;
    case 10:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "                    +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    | m0^%c %s %2d|", foo, character_gdesc,(int)id_act);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          strcpy(str, "                    |");
          strcat(str, space_get_gdesc(space_act, i));
          strcat(str, "      |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                    |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    +---------------+");
        screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      break;
    case 11:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc,(int)id_act);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '<';
          else
            foo= ' ';
          sprintf(str, "|%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }

      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      screen_area_puts(ge->map, str);
      break;
    case 12:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    | m0^%c %s %2d|   |      %s %2d|", foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '>';
          else
            foo= ' ';
          sprintf(str, "                    |%s      | %c |%s      |", space_get_gdesc(space_act, i), foo, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                    |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      break;
    case 13:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|   |      %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = '<';
            foo1 = '>';
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|%s      | %c |%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      break;
    case 14:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    | m0^%c %s %2d|   |      %s %2d|", foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2)
            foo = '>';
          else
            foo= ' ';
          sprintf(str, "                    |%s      | %c |%s      |", space_get_gdesc(space_act, i), foo, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                    |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                    +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      break;
    case 15:
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|      %s %2d|   | m0^%c %s %2d|   |      %s %2d|", character_get_gdesc( game_get_character(game, space_get_character_id(space_west))), (int)id_west, foo, character_gdesc, (int)id_act, character_get_gdesc( game_get_character(game, space_get_character_id(space_east))), (int)id_east);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2){
            foo = '<';
            foo1 = '>';
          }
          else{
            foo = ' ';
            foo1= ' ';
          }
          sprintf(str, "|%s      | %c |%s      | %c |%s      |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|               |   |               |   |               |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+---------------+   +---------------+   +---------------+");
        screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                    |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    +---------------+");
      screen_area_puts(ge->map, str);
      break;
    default:
      break; 
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  if( (player_location = player_get_location(game_get_player(game))) != NO_ID) {
    sprintf(str, "  Player: ");
    screen_area_puts(ge->descript, str);
    sprintf(str, "    Location: %d", (int)player_location);
    screen_area_puts(ge->descript, str);
    sprintf(str, "    Health: %d", player_get_health(game_get_player(game)));
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
      sprintf(str, "    %s: %d", object_get_name(object), (int)object_get_location(object));
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
      sprintf(str, "    %s: %d  (%d HP)", character_get_gdesc(character), (int)character_get_location(character), character_get_health(character));
      screen_area_puts(ge->descript, str);
    }else
      i--;
  }

  screen_area_puts(ge->descript, " ");

  if( !player_get_object(game_get_player(game) ))
    sprintf(str, "  Player has no object");
  else
    sprintf(str, "  Player has %s (%ld)", object_get_name(player_get_object(game_get_player(game))), object_get_id(player_get_object(game_get_player(game))) );
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, " ");

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " North(n), South(s), East(e), West(w), Take(t), Drop(d), Attack(a), Chat(c), Quit(q)");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  if( command_get_output(game_get_last_command(game)) == OK )
    strcpy(action_return,"Ok");
  else
    strcpy(action_return,"Error");
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], action_return);
  screen_area_puts(ge->feedback, str);
  
  if( last_cmd == CHAT && character_get_friendly(game_get_character(game, space_get_character_id(space_act))) ){
    sprintf(str, "  %s: %s",character_get_name(game_get_character(game, space_get_character_id(space_act))), character_get_message( game_get_character(game, space_get_character_id(space_act)) ));
    screen_area_puts(ge->descript, str);
  }

  /* Dump to the terminal */
  screen_paint();
  printf("Prompt => ");
}
