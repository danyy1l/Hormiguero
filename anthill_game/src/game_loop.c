/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 18
 * @date 03-03-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/player.h"
#include "../include/command.h"
#include "../include/game_actions.h"
#include "../include/game_reader.h"
#include "../include/game.h"
#include "../include/graphic_engine.h"

char *cmd_to_str[N_CMD][N_CMDT] = {
  {"", "No command"},
  {"", "Unknown"},
  {"q", "Quit"},
  {"m", "Move"},
  {"t", "Take"},
  {"d", "Drop"},
  {"a", "Attack"},
  {"c", "Chat"},
  {"i", "Inspect"}
};

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

void game_loop_run(Game *game, Graphic_engine *gengine,FILE *log_file);

void game_loop_cleanup(Game *game, Graphic_engine *gengine,FILE* file_name);

int main(int argc, char *argv[]) {
  FILE*log_file=NULL;
  Game *game = NULL;
  Graphic_engine *gengine;

  srand(time(NULL));

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if (argc == 4 && strcmp(argv[2], "-l") == 0) {
    log_file = fopen(argv[3], "w");
    if (log_file == NULL) {
        fprintf(stderr, "Error al abrir el archivo de LOG: %s\n", argv[3]);
        return 1;
    }
  }

  if (!game_loop_init(&game, &gengine, argv[1])) {
    game_loop_run(game, gengine,log_file);
    game_loop_cleanup(game, gengine,log_file);
  }

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
  if (!(*game = game_create_from_file(file_name))) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(*game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine,FILE*log_file) {
  Command *last_cmd;
  int turn = 0;
  Status cmd_output;
  char*result;
  if (!gengine) {
    return;
  }

  last_cmd=game_get_last_command(game);

  while ((command_get_code(last_cmd) != QUIT) && (game_get_n_players(game) > 0)) {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);

    if (log_file) {
      cmd_output = command_get_output(last_cmd);
      if (cmd_output == OK) {
          result = "OK";
      } else {
          result = "ERROR";
      }
      fprintf(log_file, "%s %s: %s\n", command_get_arguments(last_cmd), cmd_to_str[command_get_code(last_cmd)][CMDL], result);
    }


    if( game_get_finished(game) ){
      game_remove_player(game, game_get_player(game));
    }

    turn = (turn + 1) % game_get_n_players(game);
    game_next_turn(game, turn);
  }

}

void game_loop_cleanup(Game *game, Graphic_engine *gengine,FILE *log_file) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
  if (log_file) {
    fclose(log_file);
  }
}
void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
