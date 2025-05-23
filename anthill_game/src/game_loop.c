/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Alvaro Rodriguez
 * @version 22
 * @date 22-04-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/player.h"
#include "../include/command.h"
#include "../include/game_rules.h"
#include "../include/game_actions.h"
#include "../include/game_management.h"
#include "../include/game.h"
#include "../include/graphic_engine.h"

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name, int seed);

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

  if (!game_loop_init(&game, &gengine, argv[1], seed))
  {
    game_loop_run(game, gengine, log_file);
    game_loop_cleanup(game, gengine, log_file);
  }

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name, int seed)
{
  Graphic_engine *g = NULL;
  char p1[PLY_NAME], p2[PLY_NAME], enter[PLY_NAME];

  if (!(*game = game_create_from_file(file_name)))
  {
    fprintf(stderr, "Error while initializing game.\n");
    return EXIT_FAILURE;
  }

  /*Game start screen */
  g = graphic_engine_start();
  graphic_engine_paint_start(g, *game);
  fprintf(stdout, "Prompt => ");
  fscanf(stdin, "%s", p1);
  player_set_name(game_get_players(*game)[0], p1);
  graphic_engine_paint_start(g, *game);
  fprintf(stdout, "Prompt => ");
  fscanf(stdin, "%s", p2);
  player_set_name(game_get_players(*game)[1], p2);
  graphic_engine_paint_start(g, *game);
  fprintf(stdout, "Prompt => ");
  fscanf(stdin, "%s", enter);
  graphic_engine_destroy_start(g);

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(*game);
    return EXIT_FAILURE;
  }

  game_set_seed(*game, seed);
  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file)
{
  Command *last_cmd;
  int turn = 0;
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
    if( !set_find_object(player_get_teammates(game_get_player(game)), player_get_id(game_players(game)[turn])) ) game_next_turn(game, turn);
    game_rules_update(game, last_cmd);
    graphic_engine_paint_game(gengine, game, last_cmd);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);
    if( command_get_output(last_cmd) == OK && (command_get_code(last_cmd) != ATTACK) ){
      turn = (turn + 1) % game_get_n_players(game);
    }
    
    if (log_file)
    {
      cmd_output = command_get_output(last_cmd);
      if (cmd_output == OK) result = "OK";
      else result = "ERROR";
      fprintf(log_file, "%s(%s) %s %s %s: %s (P%ld)\n", cmd_to_str[command_get_code(last_cmd) - NO_CMD][CMDL], cmd_to_str[command_get_code(last_cmd) - NO_CMD][CMDS], command_get_arguments(last_cmd), command_get_arguments1(last_cmd), command_get_arguments2(last_cmd), result,player_get_id(game_get_player(game)));
    }
  }

  if (game_get_finished(game) == TRUE  )
    graphic_engine_paint_game_over(gengine, game);
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *log_file)
{
  if( game_get_n_players(game) < 2 ) game_set_n_players(game, 2);
  game_destroy(game);
  graphic_engine_destroy(gengine);
  if (log_file)
  {
    fclose(log_file);
  }
}
