/**
 * @brief Contiene la funcionalidad necesaria para la carga de los espacios
 * TODO: Añadir objetos y jugadores
 * 
 * @file game_reader.h
 * @author Danyyil Shykerynets
 * @version 0
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"


Status game_create_from_file(Game *game, char *filename);

Space *game_get_space(Game *game, Id id);

Id game_get_player_location(Game *game);

Status game_set_player_location(Game *game, Id id);

Id game_get_object_location(Game *game);

Status game_set_object_location(Game *game, Id id);

char *obj_check(char *objs, Game *game);

#endif