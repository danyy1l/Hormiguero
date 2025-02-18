/**
 * @brief Contiene la funcionalidad necesaria para la carga de los espacios
 * 
 * @file game_reader.h
 * @author Danyyil Shykerynets
 * @version 7
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

#define OBJ_NUM 5

/**
 * @brief Crea el array de espacios del mapa, tomando el archivo proporcionado
 * anthill.dat esta como predeterminado
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param filename Nombre del archivo del que extraer el mapa
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_load_spaces(Game *game, char *filename);

/**
 * @brief Crea el juego partiendo de un fichero
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game 
 * @param filename una cadena con el nombre del fichero
 * @return OK, si todo va bien o ERROR si hay algun fallo
 */
Game* game_create_from_file(char *filename);

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
char *game_object_check(char *objs, Game *game);

#endif