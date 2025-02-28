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

#include "../include/command.h"
#include "../include/game_reader.h"
#include "../include/libscreen.h"
#include "../include/object.h"
#include "../include/player.h"
#include "../include/space.h"
#include "../include/types.h"

#define WIDTH_MAP 48
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 13
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
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
  Space *space_act = NULL;
  Object* object;
  Character* character;
  char objs[OBJ_NUM], str[WORD_SIZE], object_taken = ' ';
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, id_count, dir_check = 0;

  int object_take;

  /*Objects array => [ Ply Pos, N, E, S, W ]  */
  for(i=0; i<OBJ_NUM; i++){
    objs[i] = ' ';
  }

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = player_get_location(game_get_player(game))) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_north = space_get_north(space_act);
    id_south = space_get_south(space_act);
    id_east = space_get_east(space_act);
    id_west = space_get_west(space_act);

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

    /*object_taken represents the object close to the player indicating that it is in their inventory*/
    game_object_check(objs, game);
    if( object_get_id(player_get_object(game_get_player(game))) != NO_ID )
      object_taken = '*';
    else
      object_taken = ' ';

    switch(dir_check){
    case 1:
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "-------+        +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "     %2d|   <    | m0^%c     %2d|",(int)id_west, object_taken, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "%c      |        |     %c      |", objs[4], objs[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "-------+        +------------+");
      screen_area_puts(ge->map, str);
      }
      break;
    case 2:
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                | m0^%c     %2d|", object_taken, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |", objs[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      }

      sprintf(str, "                       v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                |          %2d|", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |      %c     |", objs[3]);
      screen_area_puts(ge->map, str);
      break;
    case 3:
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ");
      screen_area_puts(ge->map, str);


      if (id_act != NO_ID) {
      sprintf(str, "----------+        +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "       %2d  |   <   | m0^%c     %2d|",(int)id_west, object_taken, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "   %c       |       |     %c      |", objs[4], objs[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "----------+        +------------+");
      screen_area_puts(ge->map, str);
      }

      sprintf(str, "                        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                 +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                 |         %2d|", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                 |     %c     |", objs[3]);
      screen_area_puts(ge->map, str);
      break;
    case 4:
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                +------------+        +----------");
      screen_area_puts(ge->map, str);
      sprintf(str, "               | m0^%c     %2d|   >    |        %2d",object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, "               |     %c      |        |     %c    ", objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+        +----------");
      screen_area_puts(ge->map, str);
      }
      break;
    case 5:
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                      ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "-------+        +------------+        +--------");
      screen_area_puts(ge->map, str);
      sprintf(str, "     %2d|   <    | m0^%c     %2d|    >   |      %2d ",(int)id_west, object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, " %c     |        |     %c      |        |     %c   ", objs[4], objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "-------+        +------------+        +--------");
      screen_area_puts(ge->map, str);
      }
      break;
    case 6:
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                +------------+        +----------");
      screen_area_puts(ge->map, str);
      sprintf(str, "                | m0^%c     %2d|   >   |        %2d",object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |       |     %c    ", objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+        +----------");
      screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                       v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                |        %2d |", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c     |", objs[3]);
      break;
    case 7:
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                              ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "--------+        +------------+        +--------");
      screen_area_puts(ge->map, str);
      sprintf(str, "      %2d|   <    | m0^%c     %2d|    >   |      %2d",(int)id_west, object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, "  %c     |        |     %c      |        |     %c  ", objs[4], objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "--------+        +------------+        +--------");
      screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                       v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                |         %2d|", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c     |", objs[3]);
      break;
    case 8:
      sprintf(str, "                |          %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |      %c     |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                | m0^%c     %2d|", object_taken, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |", objs[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      }
      break;
    case 9:
      sprintf(str, "                |         %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c     |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "----------+        +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        %2d|   <   | m0^%c     %2d|",(int)id_west, object_taken, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "   %c      |       |     %c      |", objs[4], objs[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "----------+        +------------+");
      screen_area_puts(ge->map, str);
      }
      break;
    case 10:
      sprintf(str, "                |          %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |      %c     |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                | m0^%c     %2d|", object_taken, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |", objs[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                       v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                |          %2d|", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |", objs[3]);
      screen_area_puts(ge->map, str);
      break;
    case 11:
      sprintf(str, "                |         %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c     |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "----------+        +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        %2d|   <   | m0^%c     %2d|",(int)id_west, object_taken, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "   %c      |       |     %c      |", objs[4], objs[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "----------+        +------------+");
      screen_area_puts(ge->map, str);
      }

      sprintf(str, "                        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                 +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                 |          %2d|", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                 |      %c     |", objs[3]);
      screen_area_puts(ge->map, str);
      break;
    case 12:
      
      sprintf(str, "                |          %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |      %c     |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                +------------+        +----------");
      screen_area_puts(ge->map, str);
      sprintf(str, "                | m0^%c     %2d|   >    |        %2d",object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |        |     %c    ", objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+        +----------");
      screen_area_puts(ge->map, str);
      }
      break;
    case 13:
      sprintf(str, "                |          %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "----------+         +------------+        +----------");
      screen_area_puts(ge->map, str);
      sprintf(str, "        %2d|   <   | m0^%c     %2d|   >    |        %2d",(int)id_west, object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, "   %c      |       |     %c      |        |     %c    ", objs[4], objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "----------+         +------------+        +----------");
      screen_area_puts(ge->map, str);
      }
      break;
    case 14:
      sprintf(str, "                |          %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |      %c     |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "                +------------+        +---------");
      screen_area_puts(ge->map, str);
      sprintf(str, "                | m0^%c     %2d|   >    |      %2d", object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |        |     %c  ", objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+        +---------");
      screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                       v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                |          %2d|", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |", objs[3]);
      screen_area_puts(ge->map, str);
      break;
    case 15:
      sprintf(str, "                |          %2d|", (int)id_north);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |      %c     |", objs[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       ^");
      screen_area_puts(ge->map, str);

      if (id_act != NO_ID) {
      sprintf(str, "-------+        +------------+        +--------");
      screen_area_puts(ge->map, str);
      sprintf(str, "     %2d|   <    | m0^%c     %2d|    >   |      %2d",(int)id_west, object_taken, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      sprintf(str, " %c     |        |     %c      |        |     %c  ", objs[4], objs[0], objs[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "-------+        +------------+        +--------");
      screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "                       v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                +------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                |          %2d|", (int)id_south);
      screen_area_puts(ge->map, str);
      sprintf(str, "                |     %c      |", objs[3]);
      screen_area_puts(ge->map, str);
      break;
    default:
      break; 
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  if( (player_location = player_get_location(game_get_player(game))) != NO_ID) {
    sprintf(str, "  Player location: %d", (int)player_location);
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Player health: %d", player_get_health(game_get_player(game)));
    screen_area_puts(ge->descript, str);
    screen_area_puts(ge->descript, " ");
  }

  id_count = 0;
  for(i=0; i<OBJECTS_NUM; i++){
    id_count += 10;
    object = game_get_object(game, id_count);
    if( object ){
      sprintf(str, "  %s location: %d", object_get_name(object), (int)object_get_location(object));
      screen_area_puts(ge->descript, str);
    }
  }
  screen_area_puts(ge->descript, " ");

  id_count = 0;
  for(i=0; i<game_get_n_characters(game); i++){
    id_count += 100;
    character = game_get_character(game, id_count);
    if( character ){
      sprintf(str, "  %s: %d | %d", character_get_gdesc(character), (int)character_get_location(character), character_get_health(character));
      screen_area_puts(ge->descript, str);
    }
  }

  if( player_get_object(game_get_player(game) ))
    object_take = 1;
  else
    object_take = 0;

  sprintf(str, "  Have object: %d", object_take);
  screen_area_puts(ge->descript, str);

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " North(n), South(s), East(e), West(w), Take(t), Drop(d), Quit(q)");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);
  if( last_cmd == CHAT && character_get_location(game_get_character(game, space_get_character_id(space_act))) == player_get_location(game_get_player(game))){
    sprintf(str, " %s: %s",character_get_name(game_get_character(game, space_get_character_id(space_act))), character_get_message( game_get_character(game, space_get_character_id(space_act)) ));
    screen_area_puts(ge->feedback, str);
  }

  /* Dump to the terminal */
  screen_paint();
  printf("Prompt => ");
}
