/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Danyyil Shykerynets
 * @version 0
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "game_reader.h"

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
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID, obj_loc = NO_ID, ply_loc = NO_ID;
  Space *space_act = NULL;
  char objs[OBJ_NUM];
  char str[WORD_SIZE];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int dir_check = 0;
  //Each direction sums a binary value so that if theres a space north and west
  //it'd be equivalent to 1010 (NESW) = 10 in decimal

  /*Objects array => [ Ply Pos, N, E, S, W ]  */
  for(int i=0; i<OBJ_NUM; i++){
    objs[i] = '*';
  }

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_north = space_get_north(space_act);
    id_south = space_get_south(space_act);
    id_east = space_get_east(space_act);
    id_west = space_get_west(space_act);

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

    obj_check(objs, game);

    /*TODO: Mejorar esto*/
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
      sprintf(str, "     %2d|   <    | m0^      %2d|",(int)id_west, (int)id_act);
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
      sprintf(str, "                | m0^      %2d|", (int)id_act);
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
      sprintf(str, "       %2d  |   <   | m0^      %2d|",(int)id_west, (int)id_act);
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
      sprintf(str, "               | m0^      %2d|   >    |        %2d",(int)id_act, (int)id_east);
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
      sprintf(str, "     %2d|   <    | m0^      %2d|    >   |      %2d ",(int)id_west, (int)id_act, (int)id_east);
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
      sprintf(str, "                | m0^      %2d|   >   |        %2d",(int)id_act, (int)id_east);
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
      sprintf(str, "      %2d|   <    | m0^      %2d|    >   |      %2d",(int)id_west, (int)id_act, (int)id_east);
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
      sprintf(str, "                | m0^      %2d|", (int)id_act);
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
      sprintf(str, "        %2d|   <   | m0^      %2d|",(int)id_west, (int)id_act);
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
      sprintf(str, "                | m0^      %2d|", (int)id_act);
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
      sprintf(str, "        %2d|   <   | m0^      %2d|",(int)id_west, (int)id_act);
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
      sprintf(str, "                | m0^      %2d|   >    |        %2d",(int)id_act, (int)id_east);
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
      sprintf(str, "        %2d|   <   | m0^      %2d|   >    |        %2d",(int)id_west, (int)id_act, (int)id_east);
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
      sprintf(str, "                | m0^      %2d|   >    |      %2d", (int)id_act, (int)id_east);
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
      sprintf(str, "     %2d|   <    | m0^      %2d|    >   |      %2d",(int)id_west, (int)id_act, (int)id_east);
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
  if( (obj_loc = game_get_object_location(game)) != NO_ID) {
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }
  if( (ply_loc = game_get_player_location(game)) != NO_ID) {
    sprintf(str, "  Player location:%d", (int)ply_loc);
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " North(n), South(s), East(e), West(w), Quit(q)");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt => ");
}