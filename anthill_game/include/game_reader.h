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

/**
 * @brief Crea el array de espacios del mapa, tomando el archivo proporcionado
 * El nombre del archivo se especifica en makefile EXE
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param filename Nombre del archivo del que extraer el mapa
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_load_spaces(Game *game, char *filename);

/**
 * @brief Crea el array de objetos del mapa, tomando el archivo proporcionado
 * anthill.dat esta como predeterminado
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param filename Nombre del archivo del que extraer el mapa
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_load_objects(Game *game, char *filename);

/**
 * @brief Crea el array de personajes del mapa, tomando el archivo proporcionado
 * anthill.dat esta como predeterminado
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param filename Nombre del archivo del que extraer el mapa
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_load_characters(Game *game, char *filename);

/**
 * @brief Crea el juego partiendo de un fichero
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game 
 * @param filename una cadena con el nombre del fichero
 * @return OK, si todo va bien o ERROR si hay algun fallo
 */
Game* game_create_from_file(char *filename);

#endif