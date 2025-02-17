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
 * @brief EL juego obtiene el espacio definido
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param Id el número id del espacio
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Space *game_get_space(Game *game, Id id);

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
 * @brief Crea un espacio nuevo en el array de espacios
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param space Estructura del espacio a agregar en el array
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Obtiene del espacio en cierta posicion del array de espacios de la partida
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param position Coordenada del array a la que acceder en el array de espacios
 * @return Id del espacio que buscabamos
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief Crea el juego partiendo de un fichero
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game 
 * @param filename una cadena con el nombre del fichero
 * @return OK, si todo va bien o ERROR si hay algun fallo
 */
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
char *game_object_check(char *objs, Game *game);

#endif