/**
 * @brief Definiciones de la funcionalidad relacionada a los objetos
 *
 * @file object.h
 * @author Danyyil Shykerynets
 * @version 0
 * @date 06-02-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"

/**
 * @brief Estructura objeto que contendra el ID y nombre del objeto
 */
typedef struct _Object Object;

/**
 * @brief Crea un objeto nuevo
 * 
 * @param 
 *  Los parametros son los datos a introducir en el objeto a crear
 * @return Devuelve un puntero a una estructura objeto
 */
Object *object_create(Id id, char icon, char* name);

/**
 * @brief Crea un objeto nuevo
 * 
 * @param object
 * Puntero al objeto a liberar
 */
void object_destroy(Object *object);

/**
 * @brief Establece la ubicacion del objeto en el id de entrada
 * 
 * @param id
 *  ID del espacio en el que colocar el objeto
 * @param game
 *  Estructura de la partida actual
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status object_set_location(Game *game, Id id);

/**
 * @brief Crea un jugador nuevo
 * 
 * @param id
 * Id del objeto a localizar
 * @param game
 * Estructura de la partida actual 
 * @return Devuelve el ID de la ubicacion del objeto
 */
Id object_get_location(Game *game);

/**
 * @brief Imprime los datos del objeto 
 * @param object
 * Puntero a la estructura del objeto cuyos datos quiero imprimir
 */
void object_print(Object *object);

/**
 * @brief Funcion que revisa si hay objetos en los alrededores del jugador
 * 
 * @param objs
 * Array con chars de los objetos en los alrededores en el orden: [PlayerLocation, N, E, S, W]
 * @param game
 * Estructura juego con las posiciones necesarias para el desarrollo
 * @return Array de chars de los objetos, ' ' si no hay, '*' si hay
 */
char *game_object_check(char *objs, Game *game);

#endif