/**
 * @brief Funcionalidad relacionada al jugador
 *
 * @file player.h
 * @author Danyyil Shykerynets
 * @version 7
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "object.h"

/**
 * @brief Estructura de datos del jugador, id, nombre, location y objeto portado
 * @author Danyyil Shykerynets
 */
typedef struct _Player Player;

/**
 * @brief Crea un jugador nuevo
 * @author Danyyil Shykerynets
 * 
 * @return Devuelve un puntero a una estructura jugador
 */
Player *player_create();

/**
 * @brief Destruye un jugador
 * @author Danyyil Shykerynets
 * 
 * @param player
 * Una estructura jugador
 */
Status player_destroy(Player *player);

/**
 * @brief Obtiene el id del objeto
 * @author Danyyil Shykerynets
 * 
 * @param object Un puntero a objeto 
 * @return el id del objeto
 */
Id player_get_id(Player* player);

/**
 * @brief Establece un id para el objeto
 * @author Danyyil Shykerynets
 * 
 * @param player Un puntero a player
 * @param id el identificador del objeto
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status player_set_id(Player* player, Id id);

/**
 * @brief Obtiene el nombre del playero
 * @author Danyyil Shykerynets
 * 
 * @param player Un puntero a player
 * @return Una cadena que es el nombre del objeto
 */
const char* player_get_name(Player* player);

/**
 * @brief Establece un nuevo nombre para el objeto
 * @author Danyyil Shykerynets
 * 
 * @param player Un puntero a player
 * @param name Una cadena con el nombre del objeto
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief Obtiene la ubicacion del jugador
 * @author Danyyil Shykerynets
 * 
 * @param player puntero a la estructura player
 * @return Devuelve el id del espacio en el que se ubica el jugador
 */
Id player_get_location(Player *player);

/**
 * @brief Establece la ubicacion del jugador
 * @author Danyyil Shykerynets
 * 
 * @param id
 * Id del espacio inicial del jugador
 * @param player puntero a la estructura player
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status player_set_location(Player *player, Id id);

/**
 * @brief Recibe el id del objeto que lleva el jugador (NO_ID en caso de no llevar)
 * @author Danyyil Shykerynets
 * 
 * @param player Puntero a la estructura del jugador
 * @return Devuelve el objeto que lleva el jugador
 */
Object* player_get_object(Player *player);

/**
 * @brief Establece el id del objeto en la estructura jugador
 * Analogamente es "agregar" un objeto con cierto id al inventario del jugador
 * @author Danyyil Shykerynets
 * 
 * @param player Jugador al que darle el objeto
 * @param id id del objeto que anadir al inventario
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status player_set_object(Player *player, Id id);

/**
 * @brief Recibe la vida del jugador
 * @author Danyyil Shykerynets
 * 
 * @param player Puntero a la estructura del jugador
 * @return Devuelve un int con la vida del jugador, -1 en caso de error
 */
int player_get_health(Player* player);

/**
 * @brief Establece la vida en la estructura jugador
 * @author Danyyil Shykerynets
 * 
 * @param player Jugador al que apunta player
 * @param health Nueva vida del jugador
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status player_set_health(Player *player, int health);

/**
 * @brief Imprime los datos del jugador
 * @author Danyyil Shykerynets
 * 
 * @param player
 * Estructura que contiene los datos del jugador a imprimir
 */
Status player_print(Player *player);

#endif