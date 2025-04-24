/**
 * @brief Funcionalidad relacionada al jugador
 *
 * @file player.h
 * @author Danyyil Shykerynets
 * @version 22
 * @date 24-04-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "object.h"
#include "inventory.h"

/**
 * @brief Estructura de datos del jugador, id, nombre, location, inventario, vida, seguidores y fuerza
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
Status player_set_name(Player* player, const char* name);

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
 * @param id Id del espacio inicial del jugador
 * @param player puntero a la estructura player
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status player_set_location(Player *player, Id id);

/**
 * @brief Devuelve el inventario del jugador (mochila)
 * @author Hugo Martín
 * 
 * @param player Puntero a la estructura del jugador
 * @return Devuelve un puntero de tipo Inventory con la mochila
 */
Inventory* player_get_objects(Player *player);

/**
 * @brief Añade un objeto a la mochila del jugador
 * @author Hugo Martín
 * 
 * @param player Jugador al que añadir el objeto
 * @param object Objeto que anadir al inventario
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status player_add_object(Player *player, Object* object);

/**
 * @brief Elimina un objeto a la mochila del jugador
 * @author Hugo Martín
 * 
 * @param player Jugador al que eliminar el objeto
 * @param object Objeto que eliminar del inventario
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status player_del_object(Player *player, Object *object);

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
 * @brief Recibe la fuerza del jugador
 * @author Danyyil Shykerynets
 * 
 * @param player Puntero a la estructura del jugador
 * @return Devuelve un int con la fuerza del jugador, -1 en caso de error
 */
int player_get_strength(Player* player);

/**
 * @brief Establece la fuerza en la estructura jugador
 * @author Danyyil Shykerynets
 * 
 * @param player Jugador al que apunta player
 * @param strength Nueva fuerza del jugador
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status player_set_strength(Player *player, int strength);

/**
 * @brief Busca si el objeto que recibe se encuentra en el inventario del jugador
 * @author Hugo Martín
 * 
 * @param player Jugador al que apunta player
 * @param object Objeto que queremos encontrar
 * @return OK en caso de exito, ERROR en caso contrario
 */
Bool player_find_object(Player *player, Object *object);

/**
 * @brief Establece la descripcion grafica de un jugador
 * @author Danyyil Shykerynets
 * 
 * @param player Puntero al jugador a modifcar
 * @param gdesc Desc Grafica a establecer en player
 * @return OK o ERROR
 */
Status player_set_gdesc(Player* player, const char* gdesc);

/**
 * @brief Obtiene la descripcion grafica de un jugador
 * @author Danyyil Shykerynets
 * 
 * @param player Puntero al jugador del que obtener la descripcion
 * @return string con la desc grafica del player
 */
char* player_get_gdesc(Player* player);

/**
 * @brief Obtiene los seguidores de un jugador
 * @author Danyyil Shykerynets
 * 
 * @param player
 * @return Set de seguidores del player
 */
Set* player_get_followers(Player* player);

/**
 * @brief Imprime los datos del jugador
 * @author Hugo Martín
 * 
 * @param player
 * Estructura que contiene los datos del jugador a imprimir
 */
Status player_print(Player *player);

#endif