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

#include "types.h"

/**
 * @brief Estructura de datos del jugador, id, nombre, location y objeto portado
*/
typedef struct _Player Player;

/**
 * @brief Crea un jugador nuevo
 * 
 * 
 * @return Devuelve un puntero a una estructura jugador
 */
Player *player_create();

/**
 * @brief Destruye un jugador
 * 
 * @param player
 * Una estructura jugador
 */
void player_destroy(Player *player);

/**
 * @brief Obtiene el id del objeto
 * 
 * @param object Un puntero a objeto 
 * @return el id del objeto
 */
Id player_get_id(Player* player);

/**
 * @brief Establece un id para el objeto
 * 
 * @param player Un puntero a player
 * @param id el identificador del objeto
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status player_set_id(Player* player, Id id);

/**
 * @brief Establece un nuevo nombre para el objeto
 * 
 * @param player Un puntero a player
 * @param name Una cadena con el nombre del objeto
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief Obtiene el nombre del playero
 * 
 * @param player Un puntero a player
 * @return Una cadena que es el nombre del objeto
 */
const char* player_get_name(Player* player);

/**
 * @brief Obtiene la ubicacion del jugador
 * 
 * @param player puntero a la estructura player
 * @return Devuelve el id del espacio en el que se ubica el jugador
 */
Id player_get_location(Player *player);

/**
 * @brief Establece la ubicacion del jugador
 * 
 * @param id
 * Id del espacio inicial del jugador
 * @param player puntero a la estructura player
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status player_set_location(Player *player, Id id);

/**
 * @brief Imprime los datos del jugador
 * 
 * @param player
 * Estructura que contiene los datos del jugador a imprimir
 */
void player_print(Player *player);

#endif