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

Space *game_get_space(Game *game, Id id);

Status game_create_from_file(Game *game, char *filename);

#endif