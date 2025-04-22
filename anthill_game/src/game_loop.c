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

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file);

void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *file_name);

int main(int argc, char *argv[])
{
  FILE *log_file = NULL;
  Game *game = NULL;
  Graphic_engine *gengine;
  int i, seed=INIT, log=INIT;


  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  for( i=0; i<argc; i++ ){
    if( strcmp(argv[i], "-l") == 0 ) log=i;
    if( strcmp(argv[i], "-d") == 0 ) seed = NUM_SEED;
  }

  if (log != INIT){
    log_file = fopen(argv[log+1], "w");
    if (log_file == NULL){
      fprintf(stderr, "Error al abrir el archivo de LOG: %s\n", argv[log+1]);
      return EXIT_FAILURE;
    }
  }

  if (seed == INIT) seed = time(NULL);
  srand(seed);
  
  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine, log_file);
    game_loop_cleanup(game, gengine, log_file);
  }

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
  if (!(*game = game_create_from_file(file_name)))
  {
    fprintf(stderr, "Error while initializing game.\n");
    return EXIT_FAILURE;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(*game);
    return EXIT_FAILURE;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file)
{
  Command *last_cmd;
  int turn = -1;
  Status cmd_output;
  char *result;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  if (!gengine || !game)
  {
    return;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != QUIT) && (game_get_finished(game) == FALSE))
  {
    turn = (turn + 1) % game_get_n_players(game);
    game_next_turn(game, turn);

    graphic_engine_paint_game(gengine, game, last_cmd);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);
    space_player_arrive(game_get_space(game, player_get_location(game_get_player(game))));

    if (log_file)
    {
      cmd_output = command_get_output(last_cmd);
      if (cmd_output == OK) result = "OK";
      else result = "ERROR";
      fprintf(log_file, "%s(%s) %s %s %s: %s (P%ld)\n", cmd_to_str[command_get_code(last_cmd) - NO_CMD][CMDL], cmd_to_str[command_get_code(last_cmd) - NO_CMD][CMDS], command_get_arguments(last_cmd), command_get_arguments1(last_cmd), command_get_arguments2(last_cmd), result,player_get_id(game_get_player(game)));
    }
  }

  if (game_get_finished(game) == TRUE)
    graphic_engine_paint_game_over(gengine, game);
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *log_file)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
  if (log_file)
  {
    fclose(log_file);
  }
}
