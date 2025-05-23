/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Danyyil Shykerynets
 * @version 22
 * @date 22-04-2025
 * @copyright GNU Public License
 */

#include "../include/graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "../include/command.h"
#include "../include/game_management.h"
#include "../include/libscreen.h"
#include "../include/object.h"
#include "../include/player.h"
#include "../include/space.h"
#include "../include/types.h"

#define WIDTH_MAP 66
#define WIDTH_DES 33
#define WIDTH_BAN 27
#define HEIGHT_MAP 29
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3

#define LINE_SPACE 16

/**
 * @brief Interfaz grafica
 */
struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

/*Declaracion de funciones privadas */
const char* get_dir_by_enum(int i);

void print_blank(char* str, Graphic_engine* ge);
void print_objects(Game* game, Id id, char* str);
void print_act(Graphic_engine* ge, Game* game, char* str, Id id_act, Space* space_act);

void print_south(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Space* space_south);
void print_sw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_sw, Space* space_sw);
void print_se(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_se, Space* space_se);
void print_south_and_sw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Id id_sw, Space* space_south, Space* space_sw);
void print_south_and_se(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Id id_se, Space* space_south, Space* space_se);
void print_sw_and_se(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_se, Id id_sw, Space* space_se, Space* space_sw);
void print_bot(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Id id_se, Id id_sw, Space* space_south, Space* space_se, Space* space_sw);

void print_north(Graphic_engine* ge, Game* game, char* str, Id id_act, Id id_north, Space* space_north);
void print_nw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_nw, Space* space_nw);
void print_ne(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_ne, Space* space_ne);
void print_north_and_nw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_north, Id id_nw, Space* space_north, Space* space_nw);
void print_north_and_ne(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_north, Id id_ne, Space* space_north, Space* space_ne);
void print_nw_and_ne(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_ne, Id id_nw, Space* space_ne, Space* space_nw);
void print_top(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_north, Id id_ne, Id id_nw, Space* space_north, Space* space_ne, Space* space_nw);

void print_west(Graphic_engine* ge, Game *game, char* str, Id id_west, Id id_act, Space* space_west, Space* space_act);
void print_east(Graphic_engine* ge, Game *game, char* str, Id id_east, Id id_act, Space* space_east, Space* space_act);
void print_mid(Graphic_engine* ge, Game *game, char* str, Id id_west, Id id_east, Id id_act, Space* space_west, Space* space_east, Space* space_act);

/*GE*/
Graphic_engine *graphic_engine_start(){
  Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 2);
  return ge;
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

  if(ge->map)       screen_area_destroy(ge->map);
  if(ge->descript)  screen_area_destroy(ge->descript);
  if(ge->banner)    screen_area_destroy(ge->banner);
  if(ge->help)      screen_area_destroy(ge->help);
  if(ge->feedback)  screen_area_destroy(ge->feedback);
  

  screen_destroy();
  free(ge);
}

void graphic_engine_destroy_start(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);

  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Command *command) {
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID, player_location = NO_ID;
  Id id_ne = NO_ID, id_se = NO_ID, id_sw = NO_ID, id_nw = NO_ID; 

  Space *space_act = NULL, *space_north = NULL, *space_south = NULL, *space_east = NULL, *space_west = NULL, *prev_space = NULL;
  Space *space_ne = NULL, *space_se = NULL, *space_sw = NULL, *space_nw = NULL;
  
  Player* dummy = NULL;
  Object* object=NULL, *lantern = game_get_object_by_name(game, "Linterna");
  Character* character = NULL;
  CommandCode last_cmd = UNKNOWN;
  Status last_cmd_status;

  char action_return[STATUS_SIZE];
  char str[WORD_SIZE], str1[WORD_SIZE/2];
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, n_objs, n_chars, strength = 0;

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
    id_ne = game_get_connection(game, id_act, NE);
    space_ne = game_get_space(game, id_ne);
    id_east = game_get_connection(game, id_act, E);
    space_east = game_get_space(game, id_east);
    id_se = game_get_connection(game, id_act, SE);
    space_se = game_get_space(game, id_se);
    id_south = game_get_connection(game, id_act, S);
    space_south = game_get_space(game, id_south);
    id_sw = game_get_connection(game, id_act, SW);
    space_sw = game_get_space(game, id_sw);
    id_west = game_get_connection(game, id_act, W);
    space_west = game_get_space(game, id_west);
    id_nw = game_get_connection(game, id_act, NW);
    space_nw = game_get_space(game, id_nw);

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
      if( space_ne && strlen(space_get_gdesc(space_ne, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_ne, "         ", i);
      if( space_nw && strlen(space_get_gdesc(space_nw, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_nw, "         ", i);
      if( space_se && strlen(space_get_gdesc(space_se, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_se, "         ", i);
      if( space_sw && strlen(space_get_gdesc(space_sw, i)) < (GDESC_SIZE - 1) )
        space_set_gdesc(space_sw, "         ", i);
    }

    if( inventory_find_object(player_get_objects(player), object_get_id(lantern)) ){ 
      print_top(ge, game, str, id_act, id_north, id_ne, id_nw, space_north, space_ne, space_nw);
      print_mid(ge, game, str, id_west, id_east, id_act, space_west, space_east, space_act);
      print_bot(ge, game, str, id_act, id_south, id_se, id_sw, space_south, space_se, space_sw);
    }else{
      print_north(ge, game, str, id_act, id_north, space_north);
      print_mid(ge, game, str, id_west, id_east, id_act, space_west, space_east, space_act);
      print_south(ge, game, str, id_act, id_south, space_south);
    }

  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);

  screen_area_puts(ge->descript, " ");
  sprintf(str, "            NW  N  NE");
  screen_area_puts(ge->descript, str);
  sprintf(str, "              \\ ^ /");
  screen_area_puts(ge->descript, str);
  sprintf(str, "            W < O > E");
  screen_area_puts(ge->descript, str);
  sprintf(str, "              / v \\");
  screen_area_puts(ge->descript, str);
  sprintf(str, "            SW  S  SE");
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, " ");

  if( (player_location = player_get_location(player)) != NO_ID) {
    if( game_get_n_players(game) > 1 ){  
      sprintf(str, "  Turn: %d", game_get_turn(game) + 1);
      screen_area_puts(ge->descript, str);
    }
    sprintf(str, "  Player %s: ", player_get_name(game_get_player(game)));
    screen_area_puts(ge->descript, str);
    sprintf(str, "   Location: %d", (int)player_location);
    screen_area_puts(ge->descript, str);
    sprintf(str, "   Health: %d", player_get_health(player));
    screen_area_puts(ge->descript, str);
    
    if( set_get_nids(player_get_teammates(player)) > 0 ){
      sprintf(str, "   Teammates: ");
      screen_area_puts(ge->descript, str);
      for( i=0; i<game_get_n_players(game)+1; i++){
        dummy = game_players(game)[i];
        if( player_get_id(dummy) == player_get_id(player) || !set_find_object(player_get_teammates(player), player_get_id(dummy)) ) continue;
        sprintf(str, "    ");
        strcat(str, player_get_name(dummy));
        strcat(str, ": ");
        sprintf(str1, "%d HP",player_get_health(dummy));
        strcat(str, str1);
        screen_area_puts(ge->descript, str);
      }
    }

    n_chars = set_get_nids(player_get_followers(player));
    
    if( n_chars > 0 ){
      sprintf(str, "   Followers: ");
      screen_area_puts(ge->descript, str);
      for( i=0; i<n_chars; i++){
        if( !(character = game_get_character(game, set_id_object(player_get_followers(player))[i])) ) continue;
        sprintf(str, "    ");
        strcat(str, character_get_name(character));
        strcat(str, ": ");
        sprintf(str1, "%d HP",character_get_health(character));
        strcat(str, str1);
        strength += character_get_strength(character);
        screen_area_puts(ge->descript, str);
      }
    }

    strength += player_get_strength(player);
    sprintf(str, "   St: %d", strength);
    screen_area_puts(ge->descript, str);
    screen_area_puts(ge->descript, " ");

  }

  if(inventory_is_empty(player_get_objects(player))==TRUE) {
    sprintf(str, "  Player has no object");
    screen_area_puts(ge->descript, str);
  } else {
    sprintf(str, "  Player has %d objects:", set_get_nids(inventory_get_objects(player_get_objects(player))));
    screen_area_puts(ge->descript, str);
    for (i=0;i<n_ids;i++) {
      object=game_get_object(game, set_ids[i]);       /*Cada uno de los objetos de la mochila del jugador*/
      sprintf(str, "  %s (Id: %ld)", object_get_name(object), object_get_id(object));
      screen_area_puts(ge->descript, str);
    }
  }
  screen_area_puts(ge->descript, " ");

  n_chars = set_get_nids(space_get_set_characters(space_act));
  for(i=0; i<n_chars; i++){
    character = game_get_character(game, set_id_object(space_get_set_characters(space_act))[i]);
    sprintf(str, "  %s: %d HP, St: %d", character_get_gdesc(character), character_get_health(character), character_get_strength(character));
    screen_area_puts(ge->descript, str);
    if( character_get_friendly(character) ) strcpy(str1, "Friendly");
    else strcpy(str1, "Enemy");
    sprintf(str, "  %s: %s", character_get_name(character), str1);
    screen_area_puts(ge->descript, str);
  }

  screen_area_puts(ge->descript, " ");

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "   The Blackout game  ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " Move(m), Take(t), Drop(d), Attack(a), Chat(c), Look (l), Inspect(i), Use(u), Open(o), Save(sg)");
  screen_area_puts(ge->help, str);
  sprintf(str, " Load(lg), Recruit(r), Abandon(ab), Team(te), Quit(q)");
  screen_area_puts(ge->help, str);

  /*Impresion del ultimo comando*/
  screen_area_clear(ge->feedback);
  last_cmd = command_get_code(command); 
  if(last_cmd >= NO_CMD && last_cmd <= TEAM ){
    last_cmd_status = command_get_output(command);
    if( last_cmd_status )
    strcpy(action_return,"Ok");
    else
    strcpy(action_return,"Error");
    
    sprintf(str, " P%d - %s (%s): %s", ((game_get_turn(game)+1)%game_get_n_players(game))+1, cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], action_return);
    screen_area_puts(ge->feedback, str);
  }
  
  if( (last_cmd == OPEN || last_cmd == USE) && last_cmd_status ) space_set_message1( game_get_space(game, game_get_prev_player_location(game)) , space_get_message2(game_get_space(game, game_get_prev_player_location(game))));

  /*Impresion del mensaje del espacio*/
  if( strlen(space_get_message1(space_act)) > 2 ){
    sprintf(str, " %s", space_get_message1(space_act));
    screen_area_puts(ge->feedback, str);
  }

  /*Caso: Comando LOOK, imprime datos de objetos, personajes y enlaces*/
  if( last_cmd == LOOK && last_cmd_status ){
    prev_space = game_get_space(game, game_get_prev_player_location(game));
    n_objs = set_get_nids(space_get_set_objects(prev_space));
    for(i=0; i<n_objs; i++){
      if( !(object = game_get_object(game, set_id_object(space_get_set_objects(prev_space))[i])) ) break;
      sprintf(str, "  ");
      strcat(str, object_get_name(object));
      strcat(str, ": ");
      strcat(str, object_get_description(object));
      screen_area_puts(ge->descript, str);
    }

    for(i=0; i<game_get_n_players(game)+1; i++){
      dummy = game_players(game)[i];
      if( player_get_location(dummy) != player_get_location(player) || player_get_id(dummy) == player_get_id(player) ) continue;
      sprintf(str, "  ");
      strcat(str, player_get_name(player));
      strcat(str, ": ");
      sprintf(str1, "%d HP, St: %d ",player_get_health(player), player_get_strength(player));
      strcat(str, str1);
      screen_area_puts(ge->descript, str);
    }

    n_chars = set_get_nids(space_get_set_characters(prev_space));
    for(i=0; i<n_chars; i++){
      if( !(character = game_get_character(game, set_id_object(space_get_set_characters(prev_space))[i])) ) break;
      sprintf(str, "  ");
      strcat(str, character_get_name(character));
      strcat(str, ": ");
      sprintf(str1, "%d HP, St: %d ",character_get_health(character), character_get_strength(character));
      strcat(str, str1);
      screen_area_puts(ge->descript, str);
    }

    sprintf(str, "  Open links:");
    screen_area_puts(ge->descript, str);
    sprintf(str, "  ");
    for(i=NONE; i<=DOWN; i++){
      if( game_connection_is_open(game, game_get_prev_player_location(game), i)) strcat(str, get_dir_by_enum(i));
    }
    screen_area_puts(ge->descript, str);

  }

  /*Caso CHAT: Imprime el mensaje del personaje*/
  if( last_cmd == CHAT && last_cmd_status ){
    sprintf(str, "  %s",game_get_message(game));
    screen_area_puts(ge->descript, str);
  }

  /*Caso INSPECT: Imprime toda la informacion de un objeto*/
  if( last_cmd == INSPECT && last_cmd_status ){
    object = game_get_object_by_name(game, command_get_arguments(command));
    sprintf(str, "  %s: %s", object_get_name(object), object_get_description(object));
    screen_area_puts(ge->descript, str);
    if( object_get_movable(object) ) sprintf(str, "  Movable");
    else sprintf(str, "  Non movable");

    if( object_get_health(object) != 0 ){
      sprintf(str, "  HP: %d", object_get_health(object));
      screen_area_puts(ge->descript, str);
    }
    if( object_get_strength(object) > 0 ){
      sprintf(str, "  Strength: %d", object_get_strength(object));
      screen_area_puts(ge->descript, str);
    }
    if( object_get_dependency(object) != NO_ID ){
      sprintf(str, "  Needs %s", object_get_name(game_get_object(game, object_get_dependency(object))));
      screen_area_puts(ge->descript, str);
    }
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

  if( command_get_code(game_get_last_command(game)) == USE && !strcasecmp(command_get_arguments(game_get_last_command(game)), "BotonVerde") ){ 
    for(i=0; i<HEIGHT_MAP; i++){
      if( i == HEIGHT_MAP/2 ){
        sprintf(str, "                             VICTORIA!                ");
        screen_area_puts(ge->map, str);
        sprintf(str, "     Enhorabuena! Has restaurado la luz y derrotado a tu casero");
        screen_area_puts(ge->map, str);
        screen_area_puts(ge->map, " ");
        screen_area_puts(ge->map, "                        Gracias por jugar!");
      }else{
        sprintf(str, "                                           ");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    for(i=0; i<HEIGHT_MAP; i++){
      if( i == HEIGHT_MAP/2 ){
        sprintf(str, "                             GAME OVER!                ");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       Player \"%s\" has died :(        ", player_get_name(game_get_player(game)));
        screen_area_puts(ge->map, str);
        screen_area_puts(ge->map, " ");
        screen_area_puts(ge->map, "                        Gracias por jugar!");
      }else{
        sprintf(str, "                                           ");
        screen_area_puts(ge->map, str);
      }
    }
  }
  
  screen_paint(game_get_turn(game));
}

void graphic_engine_paint_start(Graphic_engine* ge, Game* game){
  char str[WORD_SIZE];

  screen_area_clear(ge->map);
  screen_area_puts(ge->map, "");

  sprintf(str, "{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}                                                                                                {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}            .o.       ooooooooo.         .o.         .oooooo.      .oooooo.   ooooo      ooo    {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}           .888.      `888   `Y88.      .888.       d8P'  `Y8b    d8P'  `Y8b  `888b.     `8'    {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}          .8\"888.      888   .d88'     .8\"888.     888           888      888  8 `88b.    8     {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}         .8' `888.     888ooo88P'     .8' `888.    888           888      888  8   `88b.  8     {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}        .88ooo8888.    888           .88ooo8888.   888     ooooo 888      888  8     `88b.8     {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}       .8'     `888.   888          .8'     `888.  `88.    .88'  `88b    d88'  8       `888     {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}      o88o     o8888o o888o        o88o     o8888o  `Y8bood8P'    `Y8bood8P'  o8o        `8     {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}                                                                                                {}");
  screen_area_puts(ge->map, str);
  sprintf(str, "{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}");
  screen_area_puts(ge->map, str);

  screen_area_puts(ge->map, " ");
  screen_area_puts(ge->map, " ");
  sprintf(str, "                              Hace 6 horas que se fue la luz en el pais.");
  screen_area_puts(ge->map, str);
  sprintf(str, "                    Vuelves del bar porque a todos les ha vuelto la electricidad,");
  screen_area_puts(ge->map, str);
  sprintf(str, "                        pero ves desde lejos que en tu bloque no hay ni una luz.");
  screen_area_puts(ge->map, str);
  sprintf(str, "                                        Tocara ver que pasa");
  screen_area_puts(ge->map, str);
  screen_area_puts(ge->map, " ");

  sprintf(str, "                                     Inserte nombre Jugador 1: ");
  screen_area_puts(ge->map, str);
  if( strcmp(player_get_name(game_get_players(game)[0]), "Player1") != 0 ){ 
    sprintf(str, "                                               %s", player_get_name(game_get_players(game)[0]));
    screen_area_puts(ge->map, str);
    sprintf(str, "                                     Inserte nombre Jugador 2: ");
    screen_area_puts(ge->map, str);
  }else{
    sprintf(str, " ");
    screen_area_puts(ge->map, str);    
  }

  if( strcmp(player_get_name(game_get_players(game)[1]), "Player2") != 0 ){
    sprintf(str, "                                               %s", player_get_name(game_get_players(game)[1]));
    screen_area_puts(ge->map, str);
    screen_area_puts(ge->map, " ");
    screen_area_puts(ge->map, " ");
    screen_area_puts(ge->map, "                                    Escriba START para comenzar");
  }

  screen_area_puts(ge->map, " ");

  screen_paint(game_get_turn(game));
}

/* ================================== IMPLEMENTACION DE FUNCIONES DE IMPRESION ============================== */

/*Conversion de enum a palabra*/
const char* get_dir_by_enum(int i){
  switch (i){
  case 1:
    return "N ";
    break;
  case 2:
    return "NE ";
    break;
  case 3:
    return "E ";
    break;
  case 4:
    return "SE ";
    break;
  case 5:
    return "S ";
    break;
  case 6:
    return "SW ";
    break;
  case 7:
    return "W ";
    break;
  case 8:
    return "NW ";
    break;
  case 9:
    return "UP ";
    break;
  case 10:
    return "DOWN ";
    break;
  default:
    break;
  }
  return NULL;
}

void print_blank(char* str, Graphic_engine* ge){
  int i;
  for(i=0; i<10; i++){
    sprintf(str, " ");
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
    
    if( !(object = game_get_object(game, ids[i]))) continue;

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
  char updown;

  if( game_connection_is_open(game, id_act, UP) ) updown = '.';
  else if( game_connection_is_open(game, id_act, DOWN) ) updown = 'x';
  else updown = ' ';

  if( game_connection_is_open(game, id_act, UP) && game_connection_is_open(game, id_act, DOWN) ) updown = '#';

  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( !space_id_character(space_act) )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_id_character(space_act)[0])) );  

  if (id_act != NO_ID) {
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       | %s %s %c %3d|", player_get_gdesc(player), character_gdesc, updown, (int)id_act);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      strcpy(str, "                       |");
      strcat(str, space_get_gdesc(space_act, i));
      strcat(str, "         |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                       | ");
    print_objects(game, id_act, str);
    strcat(str, " |");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
  }
}

/*BOTTOM PRINTING*/
void print_south(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Space* space_south){
  int i;
  Player* player;
  char gdesc[PLY_GDESC + 1] = "    ";
  
  if(id_south == NO_ID) {
    print_blank(str, ge);
    return;
  }

  for( i=0; i<game_get_n_players(game); i++){
    player = game_players(game)[i];
    if( player_get_location(player) == id_south ){
      strcpy(gdesc, player_get_gdesc(player));
      break;
    }
  }
  
  if(game_connection_is_open(game, id_act, S))
    sprintf(str, "                                 v");
  else
    sprintf(str, "                                 X");
  screen_area_puts(ge->map, str);
  if(space_get_discovered(space_south)){
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       | %s %s   %3d|", gdesc, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      strcpy(str, "                       |");
      strcat(str, space_get_gdesc(space_south, i));
      strcat(str, "         |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                       | ");
    print_objects(game, id_south, str);
    strcat(str, " |");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
  }else{
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       |               %3d|", (int)id_south);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX + 1; i++){
      sprintf(str, "                       |                  |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
  }
}

void print_sw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_sw, Space* space_sw){
  char open_asw;
  int i;
  Player* player = game_get_player(game);

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_sw ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, SW) )
    open_asw = '/';
  else
    open_asw = ' ';

  
  sprintf(str, "                     %c", open_asw);
  screen_area_puts(ge->map, str);

  if(space_get_discovered(space_sw)){
    if (id_act != NO_ID) {
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "| %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "|%s         |",space_get_gdesc(space_sw, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "| ");
      print_objects(game, id_sw, str);
      strcat(str," |");
      screen_area_puts(ge->map, str);
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    if (id_act != NO_ID) {
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "|               %3d|", (int)id_sw);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "|                  |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "|                  |");
      screen_area_puts(ge->map, str);
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
    }
  }
}

void print_se(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_se, Space* space_se){
  char open_ase;
  int i;
  Player* player = game_get_player(game);

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_se ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, SE) )
    open_ase = '\\';
  else
    open_ase = ' ';

  sprintf(str, "                                            %c", open_ase);
  screen_area_puts(ge->map, str);
    
  if( space_get_discovered(space_se) ){
    if (id_act != NO_ID) {
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "                                              |%s         |", space_get_gdesc(space_se, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                                              | ");
      print_objects(game, id_se, str);
      strcat(str," |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    if (id_act != NO_ID) {
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              |               %3d|", (int)id_se);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "                                              |                  |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                                              |                  |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
    }
  }  
}

void print_south_and_sw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Id id_sw, Space* space_south, Space* space_sw){
  char open_sw, open_asw, open_south;
  int i;
  Player* player = game_get_player(game);
  char foo;

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_south ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_sw ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_south, W) )
    open_sw = '<';
  else
    open_sw = 'X';
  if( game_connection_is_open(game, id_act, SW) )
    open_asw = '/';
  else
    open_asw = ' ';
  if( game_connection_is_open(game, id_act, S) )
    open_south = 'v';
  else
    open_south = 'X';

  sprintf(str, "                     %c           %c", open_asw, open_south);
  screen_area_puts(ge->map, str);

  if(space_get_discovered(space_sw)){
    if(space_get_discovered(space_south)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo = open_sw;
          else foo = ' ';
          sprintf(str, "|%s         | %c |%s         |",space_get_gdesc(space_sw, i), foo, space_get_gdesc(space_south, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_sw, str);
        strcat(str, " |   | ");
        print_objects(game, id_south, str);
        strcat(str, " |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, (int)id_south);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo = open_sw;
          else foo = ' ';
          sprintf(str, "|%s         | %c |                  |",space_get_gdesc(space_sw, i), foo);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_sw, str);
        strcat(str, " |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_south)){  
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|   | %s %s   %3d|", (int)id_sw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo = open_sw;
          else foo = ' ';
          sprintf(str, "|                  | %c |%s         |", foo, space_get_gdesc(space_south, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |   | ");
        print_objects(game, id_south, str);
        strcat(str, " |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|   |               %3d|", (int)id_sw, (int)id_south);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|                  |   |                  |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }
}

void print_south_and_se(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Id id_se, Space* space_south, Space* space_se){
  char open_se, open_ase, open_south;
  int i;
  Player* player = game_get_player(game);
  char foo1;

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_south ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_se ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_south, E) )
    open_se = '>';
  else
    open_se = 'X';
  if( game_connection_is_open(game, id_act, SE) )
    open_ase = '\\';
  else
    open_ase = ' ';
  if( game_connection_is_open(game, id_act, S) )
    open_south = 'v';
  else
    open_south = 'X';

  sprintf(str, "                                 %c          %c", open_south, open_ase);
  screen_area_puts(ge->map, str);

  if(space_get_discovered(space_se)){
    if(space_get_discovered(space_south)){
      if (id_act != NO_ID) {
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       | %s %s   %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_se;
          else foo1= ' ';
          sprintf(str, "                       |%s         | %c |%s         |", space_get_gdesc(space_south, i), foo1, space_get_gdesc(space_se, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       | ");
        print_objects(game, id_south, str);
        strcat(str, " |   | ");
        print_objects(game, id_se, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       |               %3d|   | %s %s   %3d|", (int)id_south, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_se;
          else foo1= ' ';
          sprintf(str, "                       |                  | %c |%s         |", foo1, space_get_gdesc(space_se, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       |                  |   | ");
        print_objects(game, id_se, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_south)){
      if( id_act != NO_ID ){
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       | %s %s   %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south, (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_se;
          else foo1= ' ';
          sprintf(str, "                       |%s         | %c |                  |", space_get_gdesc(space_south, i), foo1);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       | ");
        print_objects(game, id_south, str);
        strcat(str, " |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if( id_act != NO_ID ){
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       |               %3d|   |               %3d|", (int)id_south, (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_se;
          else foo1= ' ';
          sprintf(str, "                       |                  |   |                  |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       |                  |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }
}

void print_sw_and_se(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_se, Id id_sw, Space* space_se, Space* space_sw){
  char open_asw, open_ase;
  int i;
  Player* player = game_get_player(game);

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_sw ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_se ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, SW) )
    open_asw = '/';
  else
    open_asw = ' ';
  if( game_connection_is_open(game, id_act, SE) )
    open_ase = '\\';
  else
    open_ase = ' ';

  sprintf(str, "                     %c                      %c", open_asw, open_ase);
  screen_area_puts(ge->map, str);

  if( space_get_discovered(space_se) ){
    if(space_get_discovered(space_sw)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|                          | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|%s         |                          |%s         |",space_get_gdesc(space_sw, i), space_get_gdesc(space_se, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_sw, str);
        strcat(str, " |                          | ");
        print_objects(game, id_se, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|                          | %s %s   %3d|", (int)id_sw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|                  |                          |%s         |", space_get_gdesc(space_se, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |                          | ");
        print_objects(game, id_se, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_sw)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|                          |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|%s         |                          |                  |",space_get_gdesc(space_sw, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_sw, str);
        strcat(str, " |                          |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|                          |               %3d|", (int)id_sw, (int)id_se);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|                  |                          |                  |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |                          |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }
}

void print_bot(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_south, Id id_se, Id id_sw, Space* space_south, Space* space_se, Space* space_sw){
  char open_se, open_nw, open_asw, open_ase, open_south;
  int i, x=0;
  Player* player = game_get_player(game);
  char foo, foo1;

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";
  Player* player3;
  char gdesc3[PLY_GDESC + 1] = "    ";

  if( id_sw != NO_ID ) x += 4;
  if( id_south != NO_ID) x += 2;
  if( id_se != NO_ID) x += 1;

  switch (x){
  case 0:
    return;
  case 1:
    print_se(ge, game, str, id_act, id_se, space_se);
    return;
  case 2:
    print_south(ge, game, str, id_act, id_south, space_south);
    return;
  case 3:
    print_south_and_se(ge, game, str, id_act, id_south, id_se, space_south, space_se);
    return;
  case 4:
    print_sw(ge, game, str, id_act, id_sw, space_sw);
    return;
  case 5:
    print_sw_and_se(ge, game, str, id_act, id_se, id_sw, space_se, space_sw);
    return;
  case 6:
    print_south_and_sw(ge, game, str, id_act, id_south, id_sw, space_south, space_sw);
    return;
  default:
    break;
  }

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_se ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_sw ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player3 = game_players(game)[i];
    if( player == player3 ) continue;
    if( player_get_location(player3) == id_south ){
      strcpy(gdesc3, player_get_gdesc(player3));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_south, W) )
    open_nw = '<';
  else
    open_nw = 'X';
  if( game_connection_is_open(game, id_south, E) )
    open_se = '>';
  else
    open_se = 'X';
  if( game_connection_is_open(game, id_act, SW) )
    open_asw = '/';
  else
    open_nw = ' ';
  if( game_connection_is_open(game, id_act, SE) )
    open_ase = '\\';
  else
    open_ase = ' ';
  if( game_connection_is_open(game, id_act, S) )
    open_south = 'v';
  else
    open_south = 'X';

  sprintf(str, "                     %c           %c          %c", open_asw, open_south, open_ase);
  screen_area_puts(ge->map, str);

  if( space_get_discovered(space_se) ){
    if(space_get_discovered(space_sw)){
      if(space_get_discovered(space_south)){
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   | %s %s   %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_se;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |%s         | %c |%s         |",space_get_gdesc(space_sw, i), foo, space_get_gdesc(space_south, i), foo1, space_get_gdesc(space_se, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_sw, str);
          strcat(str, " |   | ");
          print_objects(game, id_south, str);
          strcat(str, " |   | ");
          print_objects(game, id_se, str);
          strcat(str," |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   |               %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, (int)id_south, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_se;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |                  | %c |%s         |",space_get_gdesc(space_sw, i), foo, foo1, space_get_gdesc(space_se, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_sw, str);
          strcat(str, " |   |                  |   | ");
          print_objects(game, id_se, str);
          strcat(str," |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }else{
      if(space_get_discovered(space_south)){  
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   | %s %s   %3d|   | %s %s   %3d|", (int)id_sw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_se;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|                  | %c |%s         | %c |%s         |", foo, space_get_gdesc(space_south, i), foo1, space_get_gdesc(space_se, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   | ");
          print_objects(game, id_south, str);
          strcat(str, " |   | ");
          print_objects(game, id_se, str);
          strcat(str," |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if( id_act != NO_ID ){
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   |               %3d|   | %s %s   %3d|", (int)id_sw, (int)id_south, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_se)[0])), (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_se;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|                  |   |                  | %c |%s         |", foo1, space_get_gdesc(space_se, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   |                  |   | ");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }
  }else{
    if(space_get_discovered(space_sw)){
      if(space_get_discovered(space_south)){
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   | %s %s   %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south, (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_se;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |%s         | %c |                  |",space_get_gdesc(space_sw, i), foo, space_get_gdesc(space_south, i), foo1);
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_sw, str);
          strcat(str, " |   | ");
          print_objects(game, id_south, str);
          strcat(str, " |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   |               %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_sw)[0])), (int)id_sw, (int)id_south, (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_se;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |                  |   |                  |",space_get_gdesc(space_sw, i), foo);
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_sw, str);
          strcat(str, " |   |                  |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }else{
      if(space_get_discovered(space_south)){  
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   | %s %s   %3d|   |               %3d|", (int)id_sw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_south)[0])), (int)id_south, (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_se;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|                  | %c |%s         | %c |                  |", foo, space_get_gdesc(space_south, i), foo1);
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   | ");
          print_objects(game, id_south, str);
          strcat(str, " |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   |               %3d|   |               %3d|", (int)id_sw, (int)id_south, (int)id_se);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            sprintf(str, "|                  |   |                  |   |                  |");
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   |                  |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }
  }
}

/*TOP PRINTING*/
void print_north(Graphic_engine* ge, Game* game, char* str, Id id_act, Id id_north, Space* space_north){
  int i;
  Player* player;
  char gdesc[PLY_GDESC + 1] = "    ";

  if( id_north == 999 ){
    print_blank(str, ge);
    return;
  }
  
  if(id_north == NO_ID) {
    print_blank(str, ge);
    return;
  }

  for(i=0; i<game_get_n_players(game); i++){
    player = game_players(game)[i];
    if( player_get_location(player) == id_north ){
      strcpy(gdesc, player_get_gdesc(player));
      break;
    }
  }

  if( space_get_discovered(space_north) ){
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       | %s %s   %3d|", gdesc, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      strcpy(str, "                       |");
      strcat(str, space_get_gdesc(space_north, i));
      strcat(str, "         |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                       | ");
    print_objects(game, id_north, str);
    strcat(str, " |");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
  }else{
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                       |               %3d|", (int)id_north);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX + 1; i++){
      sprintf(str, "                       |                  |");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                       +------------------+");
    screen_area_puts(ge->map, str);
  }

  if(game_connection_is_open(game, id_act, N))
      sprintf(str, "                                 ^");
    else
      sprintf(str, "                                 X");
  screen_area_puts(ge->map, str);
}

void print_nw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_nw, Space* space_nw){
  char open_anw;
  int i;
  Player* player = game_get_player(game);

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_nw ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, NW) )
    open_anw = '\\';
  else
    open_anw = ' ';

  if(space_get_discovered(space_nw)){
    if (id_act != NO_ID) {
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "| %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "|%s         |",space_get_gdesc(space_nw, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "| ");
      print_objects(game, id_nw, str);
      strcat(str," |");
      screen_area_puts(ge->map, str);
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    if (id_act != NO_ID) {
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "|               %3d|", (int)id_nw);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "|                  |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "|                  |");
      screen_area_puts(ge->map, str);
      sprintf(str, "+------------------+");
      screen_area_puts(ge->map, str);
    }
  }

  sprintf(str, "                     %c", open_anw);
  screen_area_puts(ge->map, str);
}

void print_ne(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_ne, Space* space_ne){
  char open_ane;
  int i;
  Player* player = game_get_player(game);

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_ne ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, NE) )
    open_ane = '/';
  else
    open_ane = ' ';

  if( space_get_discovered(space_ne) ){
    if (id_act != NO_ID) {
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "                                              |%s         |", space_get_gdesc(space_ne, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                                              | ");
      print_objects(game, id_ne, str);
      strcat(str," |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    if (id_act != NO_ID) {
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              |               %3d|", (int)id_ne);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        sprintf(str, "                                              |                  |");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                                              |                  |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                              +------------------+");
      screen_area_puts(ge->map, str);
    }
  }  

  sprintf(str, "                                            %c", open_ane);
  screen_area_puts(ge->map, str);
}

void print_north_and_nw(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_north, Id id_nw, Space* space_north, Space* space_nw){
  char open_nw, open_anw, open_north;
  int i;
  Player* player = game_get_player(game);
  char foo;

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_north ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_nw ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_north, W) )
    open_nw = '<';
  else
    open_nw = 'X';
  if( game_connection_is_open(game, id_act, NW) )
    open_anw = '\\';
  else
    open_anw = ' ';
  if( game_connection_is_open(game, id_act, N) )
    open_north = '^';
  else
    open_north = 'X';

  if(space_get_discovered(space_nw)){
    if(space_get_discovered(space_north)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo = open_nw;
          else foo = ' ';
          sprintf(str, "|%s         | %c |%s         |",space_get_gdesc(space_nw, i), foo, space_get_gdesc(space_north, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_nw, str);
        strcat(str, " |   | ");
        print_objects(game, id_north, str);
        strcat(str, " |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, (int)id_north);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo = open_nw;
          else foo = ' ';
          sprintf(str, "|%s         | %c |                  |",space_get_gdesc(space_nw, i), foo);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_nw, str);
        strcat(str, " |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_north)){  
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|   | %s %s   %3d|", (int)id_nw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo = open_nw;
          else foo = ' ';
          sprintf(str, "|                  | %c |%s         |", foo, space_get_gdesc(space_north, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |   | ");
        print_objects(game, id_north, str);
        strcat(str, " |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|   |               %3d|", (int)id_nw, (int)id_north);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|                  |   |                  |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }

  sprintf(str, "                     %c           %c", open_anw, open_north);
  screen_area_puts(ge->map, str);
}

void print_north_and_ne(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_north, Id id_ne, Space* space_north, Space* space_ne){
  char open_ne, open_ane, open_north;
  int i;
  Player* player = game_get_player(game);
  char foo1;

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_north ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_ne ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_north, E) )
    open_ne = '>';
  else
    open_ne = 'X';
  if( game_connection_is_open(game, id_act, NE) )
    open_ane = '/';
  else                       
    open_ane = ' ';
  if( game_connection_is_open(game, id_act, N) )
    open_north = '^';
  else
    open_north = 'X';

  if(space_get_discovered(space_ne)){
    if(space_get_discovered(space_north)){
      if (id_act != NO_ID) {
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       | %s %s   %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_ne;
          else foo1= ' ';
          sprintf(str, "                       |%s         | %c |%s         |", space_get_gdesc(space_north, i), foo1, space_get_gdesc(space_ne, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       | ");
        print_objects(game, id_north, str);
        strcat(str, " |   | ");
        print_objects(game, id_ne, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       |               %3d|   | %s %s   %3d|", (int)id_north, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_ne;
          else foo1= ' ';
          sprintf(str, "                       |                  | %c |%s         |", foo1, space_get_gdesc(space_ne, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       |                  |   | ");
        print_objects(game, id_ne, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_north)){
      if( id_act != NO_ID ){
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       | %s %s   %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north, (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_ne;
          else foo1= ' ';
          sprintf(str, "                       |%s         | %c |                  |", space_get_gdesc(space_north, i), foo1);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       | ");
        print_objects(game, id_north, str);
        strcat(str, " |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if( id_act != NO_ID ){
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       |               %3d|   |               %3d|", (int)id_north, (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          if(i==2) foo1 = open_ne;
          else foo1= ' ';
          sprintf(str, "                       |                  |   |                  |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                       |                  |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "                       +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }

  sprintf(str, "                                 %c          %c", open_north, open_ane);
  screen_area_puts(ge->map, str);
}

void print_nw_and_ne(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_ne, Id id_nw, Space* space_ne, Space* space_nw){
  char open_anw, open_ane;
  int i;
  Player* player = game_get_player(game);

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_nw ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_ne ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, NW) )
    open_anw = '\\';
  else
    open_anw = ' ';
  if( game_connection_is_open(game, id_act, NE) )
    open_ane = '/';
  else
    open_ane = ' ';

  if( space_get_discovered(space_ne) ){
    if(space_get_discovered(space_nw)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|                          | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|%s         |                          |%s         |",space_get_gdesc(space_nw, i), space_get_gdesc(space_ne, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_nw, str);
        strcat(str, " |                          | ");
        print_objects(game, id_ne, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|                          | %s %s   %3d|", (int)id_nw, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|                  |                          |%s         |", space_get_gdesc(space_ne, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |                          | ");
        print_objects(game, id_ne, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_nw)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|                          |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|%s         |                          |                  |",space_get_gdesc(space_nw, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_nw, str);
        strcat(str, " |                          |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|                          |               %3d|", (int)id_nw, (int)id_ne);
        screen_area_puts(ge->map, str);
        for(i=0; i<GDESC_MAX; i++){
          sprintf(str, "|                  |                          |                  |");
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |                          |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+                          +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }

  sprintf(str, "                     %c                      %c", open_anw, open_ane);
  screen_area_puts(ge->map, str);
}

void print_top(Graphic_engine* ge, Game *game, char* str, Id id_act, Id id_north, Id id_ne, Id id_nw, Space* space_north, Space* space_ne, Space* space_nw){
  char open_ne, open_nw, open_anw, open_ane, open_north;
  int i, x=0;
  Player* player = game_get_player(game);
  char foo, foo1;

  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";
  Player* player3;
  char gdesc3[PLY_GDESC + 1] = "    ";

  if( id_nw != NO_ID ) x += 4;
  if( id_north != NO_ID) x += 2;
  if( id_ne != NO_ID) x += 1;

  switch (x){
  case 0:
    print_blank(str, ge);
    return;
  case 1:
    print_ne(ge, game, str, id_act, id_ne, space_ne);
    return;
  case 2:
    print_north(ge, game, str, id_act, id_north, space_north);
    return;
  case 3:
    print_north_and_ne(ge, game, str, id_act, id_north, id_ne, space_north, space_ne);
    return;
  case 4:
    print_nw(ge, game, str, id_act, id_nw, space_nw);
    return;
  case 5:
    print_nw_and_ne(ge, game, str, id_act, id_ne, id_nw, space_ne, space_nw);
    return;
  case 6:
    print_north_and_nw(ge, game, str, id_act, id_north, id_nw, space_north, space_nw);
    return;
  default:
    break;
  }

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_ne ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_nw ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player3 = game_players(game)[i];
    if( player == player3 ) continue;
    if( player_get_location(player3) == id_north ){
      strcpy(gdesc3, player_get_gdesc(player3));
      break;
    }
  }

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_north, W) )
    open_nw = '<';
  else
    open_nw = 'X';
  if( game_connection_is_open(game, id_north, E) )
    open_ne = '>';
  else
    open_ne = 'X';
  if( game_connection_is_open(game, id_act, NW) )
    open_anw = '\\';
  else
    open_nw = ' ';
  if( game_connection_is_open(game, id_act, NE) )
    open_ane = '/';
  else
    open_ane = ' ';
  if( game_connection_is_open(game, id_act, N) )
    open_north = '^';
  else
    open_north = 'X';

  if( space_get_discovered(space_ne) ){
    if(space_get_discovered(space_nw)){
      if(space_get_discovered(space_north)){
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   | %s %s   %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_ne;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |%s         | %c |%s         |",space_get_gdesc(space_nw, i), foo, space_get_gdesc(space_north, i), foo1, space_get_gdesc(space_ne, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_nw, str);
          strcat(str, " |   | ");
          print_objects(game, id_north, str);
          strcat(str, " |   | ");
          print_objects(game, id_ne, str);
          strcat(str," |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   |               %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, (int)id_north, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_ne;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |                  | %c |%s         |",space_get_gdesc(space_nw, i), foo, foo1, space_get_gdesc(space_ne, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_nw, str);
          strcat(str, " |   |                  |   | ");
          print_objects(game, id_ne, str);
          strcat(str," |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }else{
      if(space_get_discovered(space_north)){  
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   | %s %s   %3d|   | %s %s   %3d|", (int)id_nw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_ne;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|                  | %c |%s         | %c |%s         |", foo, space_get_gdesc(space_north, i), foo1, space_get_gdesc(space_ne, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   | ");
          print_objects(game, id_north, str);
          strcat(str, " |   | ");
          print_objects(game, id_ne, str);
          strcat(str," |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if( id_act != NO_ID ){
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   |               %3d|   | %s %s   %3d|", (int)id_nw, (int)id_north, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_ne)[0])), (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_ne;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|                  |   |                  | %c |%s         |", foo1, space_get_gdesc(space_ne, i));
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   |                  |   | ");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }
  }else{
    if(space_get_discovered(space_nw)){
      if(space_get_discovered(space_north)){
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   | %s %s   %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north, (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_ne;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |%s         | %c |                  |",space_get_gdesc(space_nw, i), foo, space_get_gdesc(space_north, i), foo1);
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_nw, str);
          strcat(str, " |   | ");
          print_objects(game, id_north, str);
          strcat(str, " |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "| %s %s   %3d|   |               %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_nw)[0])), (int)id_nw, (int)id_north, (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_ne;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|%s         | %c |                  |   |                  |",space_get_gdesc(space_nw, i), foo);
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "| ");
          print_objects(game, id_nw, str);
          strcat(str, " |   |                  |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }else{
      if(space_get_discovered(space_north)){  
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   | %s %s   %3d|   |               %3d|", (int)id_nw, gdesc3, character_get_gdesc( game_get_character(game, space_id_character(space_north)[0])), (int)id_north, (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            if(i==2){
              foo = open_nw;
              foo1 = open_ne;
            }
            else{
              foo = ' ';
              foo1= ' ';
            }
            sprintf(str, "|                  | %c |%s         | %c |                  |", foo, space_get_gdesc(space_north, i), foo1);
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   | ");
          print_objects(game, id_north, str);
          strcat(str, " |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }else{
        if (id_act != NO_ID) {
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "|               %3d|   |               %3d|   |               %3d|", (int)id_nw, (int)id_north, (int)id_ne);
          screen_area_puts(ge->map, str);
          for(i=0; i<GDESC_MAX; i++){
            sprintf(str, "|                  |   |                  |   |                  |");
            screen_area_puts(ge->map, str);
          }
          sprintf(str, "|                  |   |                  |   |                  |");
          screen_area_puts(ge->map, str);
          sprintf(str, "+------------------+   +------------------+   +------------------+");
          screen_area_puts(ge->map, str);
        }
      }
    }
  }

  sprintf(str, "                     %c           %c          %c", open_anw, open_north, open_ane);
  screen_area_puts(ge->map, str);
}

/*MIDDLE PRINTING*/
void print_west(Graphic_engine* ge, Game *game, char* str, Id id_west, Id id_act, Space* space_west, Space* space_act){
  int open_west, i;
  Player* player = game_get_player(game);
  char character_gdesc[GDESC_SIZE], foo;
  char updown;

  Player* player1;
  char gdesc[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_west ){
      strcpy(gdesc, player_get_gdesc(player1));
      break;
    }
  }
  
  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( !space_id_character(space_act) )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_id_character(space_act)[0])) );
  
  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, W) )
    open_west = '<';
  else
    open_west = 'X';

  if( game_connection_is_open(game, id_act, UP) ) updown = '.';
  else if( game_connection_is_open(game, id_act, DOWN) ) updown = 'x';
  else updown = ' ';

  if( game_connection_is_open(game, id_act, UP) && game_connection_is_open(game, id_act, DOWN) ) updown = '#';  

  if(space_get_discovered(space_west)){
    if (id_act != NO_ID) {
      sprintf(str, "+------------------+   +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "| %s %s   %3d|   | %s %s %c %3d|", gdesc, character_get_gdesc( game_get_character(game, space_id_character(space_west)[0])), (int)id_west, player_get_gdesc(player), character_gdesc,updown, (int)id_act);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        if(i==2)
          foo = open_west;
        else
          foo= ' ';
        sprintf(str, "|%s         | %c |%s         |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "| ");
      print_objects(game, id_west, str);
      strcat(str, " |   | ");
      print_objects(game, id_act, str);
      strcat(str, " |");
      screen_area_puts(ge->map, str);

      sprintf(str, "+------------------+   +------------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    sprintf(str, "+------------------+   +------------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "|               %3d|   | %s %s %c %3d|", (int)id_west, player_get_gdesc(player), character_gdesc, updown, (int)id_act);
    screen_area_puts(ge->map, str);
    for(i=0; i<GDESC_MAX; i++){
      if(i==2)
        foo = open_west;
      else
        foo= ' ';
      sprintf(str, "|                  | %c |%s         |", foo, space_get_gdesc(space_act, i));
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "|                  |   | ");
    print_objects(game, id_act, str);
    strcat(str, " |");
    screen_area_puts(ge->map, str);
    sprintf(str, "+------------------+   +------------------+");
    screen_area_puts(ge->map, str);
  }
}

void print_east(Graphic_engine* ge, Game *game, char* str, Id id_east, Id id_act, Space* space_east, Space* space_act){
  int open_east, i;
  Player* player = game_get_player(game);
  char character_gdesc[CHAR_GDESC + 1] ,foo;
  char updown;
  
  Player* player1;
  char gdesc[PLY_GDESC + 1] = "    ";

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_east ){
      strcpy(gdesc, player_get_gdesc(player1));
      break;
    }
  }

  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( !space_id_character(space_act) )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_id_character(space_act)[0])) ); 
  

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, E) )
    open_east = '>';
  else
    open_east = 'X';

  if( game_connection_is_open(game, id_act, UP) ) 
    updown = '.';
  else if( game_connection_is_open(game, id_act, DOWN) ) 
    updown = 'x';
  else updown = ' ';

  if( game_connection_is_open(game, id_act, UP) && game_connection_is_open(game, id_act, DOWN) ) updown = '#';  

  if( space_get_discovered(space_east) ){
    if (id_act != NO_ID) {
      sprintf(str, "                       +------------------+   +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       | %s %s %c %3d|   | %s %s   %3d|", player_get_gdesc(player), character_gdesc, updown, (int)id_act, gdesc, character_get_gdesc(game_get_character(game, space_id_character(space_east)[0])), (int)id_east);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        if(i==2)
          foo = open_east;
        else
          foo= ' ';
        sprintf(str, "                       |%s         | %c |%s         |", space_get_gdesc(space_act, i), foo, space_get_gdesc(space_east, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                       | ");
      print_objects(game, id_act, str);
      strcat(str, " |   | ");
      print_objects(game, id_east, str);
      strcat(str, " |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       +------------------+   +------------------+");
      screen_area_puts(ge->map, str);
    }
  }else{
    if (id_act != NO_ID) {
      sprintf(str, "                       +------------------+   +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       | %s %s %c %3d|   |               %3d|", player_get_gdesc(player), character_gdesc, updown, (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);
      for(i=0; i<GDESC_MAX; i++){
        if(i==2)
          foo = open_east;
        else
          foo= ' ';
        sprintf(str, "                       |%s         | %c |                  |", space_get_gdesc(space_act, i), foo);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                       | ");
      print_objects(game, id_act, str);
      strcat(str," |   |                  |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                       +------------------+   +------------------+");
      screen_area_puts(ge->map, str);
    }
  }
}

void print_mid(Graphic_engine* ge, Game *game, char* str, Id id_west, Id id_east, Id id_act, Space* space_west, Space* space_east, Space* space_act){
  int open_east, open_west, i;
  Player* player = game_get_player(game);
  char character_gdesc[CHAR_GDESC + 1], foo, foo1;
  char updown;
  
  Player* player1;
  char gdesc1[PLY_GDESC + 1] = "    ";
  Player* player2;
  char gdesc2[PLY_GDESC + 1] = "    ";

  if( ( id_east == NO_ID ) && ( id_west == NO_ID ) ) {
    print_act(ge, game, str, id_act, space_act); 
    return;
  }else if( id_east == NO_ID ) {
    print_west(ge, game, str, id_west, id_act, space_west, space_act); 
    return;
  }else if( id_west == NO_ID ){
    print_east(ge, game, str, id_east, id_act, space_east, space_act); 
    return;
  }

  for(i=0; i<game_get_n_players(game); i++){
    player1 = game_players(game)[i];
    if( player == player1 ) continue;
    if( player_get_location(player1) == id_west ){
      strcpy(gdesc1, player_get_gdesc(player1));
      break;
    }
  }

  for(i=0; i<game_get_n_players(game); i++){
    player2 = game_players(game)[i];
    if( player == player2 ) continue;
    if( player_get_location(player2) == id_east ){
      strcpy(gdesc2, player_get_gdesc(player2));
      break;
    }
  }

  /*Los personajes ocupan un maximo de 6 caracteres, si no hay personaje, sustituyo la gdesc por 6 espacios*/
  if( !space_id_character(space_act) )
    strcpy(character_gdesc, "      ");
  else
    strcpy(character_gdesc, character_get_gdesc(game_get_character(game, space_id_character(space_act)[0])) );  

  /*Revision de si conexion abierta*/
  if( game_connection_is_open(game, id_act, W) )
    open_west = '<';
  else
    open_west = 'X';
  if( game_connection_is_open(game, id_act, E) )
    open_east = '>';
  else
    open_east = 'X';

  if( game_connection_is_open(game, id_act, UP) ) 
    updown = '.';
  else if( game_connection_is_open(game, id_act, DOWN) ) 
    updown = 'x';
  else updown = ' ';

  if( game_connection_is_open(game, id_act, UP) && game_connection_is_open(game, id_act, DOWN) ) 
    updown = '#';

  if( space_get_discovered(space_east) ){
    if(space_get_discovered(space_west)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|   | %s %s %c %3d|   | %s %s   %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_west)[0])), (int)id_west, player_get_gdesc(player), character_gdesc, updown, (int)id_act, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_east)[0])), (int)id_east);
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
          sprintf(str, "|%s         | %c |%s         | %c |%s         |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
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
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|   | %s %s %c %3d|   | %s %s   %3d|", (int)id_west, player_get_gdesc(player), character_gdesc, updown, (int)id_act, gdesc2, character_get_gdesc( game_get_character(game, space_id_character(space_east)[0])), (int)id_east);
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
          sprintf(str, "|                  | %c |%s         | %c |%s         |", foo, space_get_gdesc(space_act, i), foo1, space_get_gdesc(space_east, i));
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |   | ");
        print_objects(game, id_act, str);
        strcat(str, " |   | ");
        print_objects(game, id_east, str);
        strcat(str," |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }else{
    if(space_get_discovered(space_west)){
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "| %s %s   %3d|   | %s %s %c %3d|   |               %3d|", gdesc1, character_get_gdesc( game_get_character(game, space_id_character(space_west)[0])), (int)id_west, player_get_gdesc(player), character_gdesc, updown, (int)id_act, (int)id_east);
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
          sprintf(str, "|%s         | %c |%s         | %c |                  |",space_get_gdesc(space_west, i), foo, space_get_gdesc(space_act, i), foo1);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "| ");
        print_objects(game, id_west, str);
        strcat(str, " |   | ");
        print_objects(game, id_act, str);
        strcat(str, " |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }else{
      if (id_act != NO_ID) {
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "|               %3d|   | %s %s %c %3d|   |               %3d|", (int)id_west, player_get_gdesc(player), character_gdesc, updown, (int)id_act, (int)id_east);
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
          sprintf(str, "|                  | %c |%s         | %c |                  |", foo, space_get_gdesc(space_act, i), foo1);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "|                  |   | ");
        print_objects(game, id_act, str);
        strcat(str, " |   |                  |");
        screen_area_puts(ge->map, str);
        sprintf(str, "+------------------+   +------------------+   +------------------+");
        screen_area_puts(ge->map, str);
      }
    }
  }
}
