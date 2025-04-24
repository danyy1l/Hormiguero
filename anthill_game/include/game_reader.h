/**
 * @brief Contiene la funcionalidad necesaria para la carga de los espacios
 * 
 * @file game_reader.h
 * @author Hugo Martín
 * @version 7
 * @date 05-02-2025
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

/**
 * @brief Guarda la partida
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * @param filename Nombre del archivo donde se guardará la partida
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_management_save(Game *game, char *filename);

/**
 * @brief Carga la partida
 * @author Hugo Martín
 * @param game Estructura de la partida actual
 * @param filename Nombre del archivo donde se cargará la partida
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_management_load(Game *game, char *filename);

#endif