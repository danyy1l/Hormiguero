/**
 * @brief Funcionalidad relacionada al jugador
 *
 * @file player.h
 * @author Danyyil Shykerynets
 * @version 0
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

/**
 * @brief Estructura de datos del jugador, id, nombre, location y objeto portado
*/
typedef struct _Player Player;

/**
 * @brief Crea un jugador nuevo
 * 
 * @param 
 *  Los parametros son los datos a introducir en el jugador a crear
 * @return Devuelve un puntero a una estructura jugador
 */
Player *player_create(Id id, Id location, char *name, Id object);

/**
 * @brief Destruye un jugador
 * 
 * @param player
 * Una estructura jugador
 */
void player_destroy(Player *player);

/**
 * @brief Obtiene la ubicacion del jugador
 * 
 * @param game
 *  Estructura juego con los datos de espacios, jugadores y objetos
 * @return Devuelve el id del espacio en el que se ubica el jugador
 */
Id player_get_location(Game *game);

/**
 * @brief Establece la ubicacion del jugador
 * 
 * @param id
 * Id del espacio inicial del jugador
 * @param game
 * Estructura juego con los datos de espacios jugadores y objetos
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status player_set_location(Game *game, Id id);

/**
 * @brief Imprime los datos del jugador
 * 
 * @param player
 * Estructura que contiene los datos del jugador a imprimir
 */
void player_print(Player *player);

#endif