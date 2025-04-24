/**
 * @brief Contiene la funcionalidad necesaria para la carga de los espacios
 * 
 * @file game_reader.h
 * @author Danyyil Shykerynets
 * @version 22
 * @date 24-04-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief Crea el juego partiendo de un fichero
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game 
 * @param filename una cadena con el nombre del fichero
 * @return OK, si todo va bien o ERROR si hay algun fallo
 */
Game* game_create_from_file(char *filename);

#endif