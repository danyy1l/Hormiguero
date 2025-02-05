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

Status game_set_object_location(Game *game, Id id);

Id game_get_object_location(Game *game);

Status game_create_from_file(Game *game, char *filename);

/**
 * @brief Funcion que revisa si hay objetos en los alrededores del jugador
 * @author Danyyil Shykerynets
 * 
 * @param objs
 * Array con chars de los objetos en los alrededores en el orden: [PlayerLocation, N, E, S, W]
 * @param game
 * Estructura juego con las posiciones necesarias para el desarrollo
 * @return Array de chars de los objetos, ' ' si no hay, '*' si hay
 */
char *obj_check(char *objs, Game *game);

#endif