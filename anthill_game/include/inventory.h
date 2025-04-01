/**
 * @brief It defines the inventory module interface
 *
 * @file inventory.h
 * @author Álvaro Rodríguez
 * @version 0
 * @date 20-03-2025
 * @copyright GNU Public License
*/

#ifndef INVENTORY_H
#define INVENTORY_H
 
#define MAX_INVENTORY_OBJS 5

#include "object.h"
#include "types.h"
#include "set.h"
 
/**
 * @brief Estructura Inventory con campos:
 * array de objects, int maximo de objetos 
 * @author Álvaro Rodríguez
*/
typedef struct _Inventory Inventory;

/**
 * @brief Crea un inventario nuevo
 * @author Álvaro Rodríguez
 * @param 
 * @return Devuelve puntero a la nueva estrucura invebtory en caso de exito y NULL en caso contrario
*/
Inventory *inventory_create();

/**
 * @brief destruye un inventario 
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
*/
Status inventory_destroy(Inventory * inventory);

/**
 * @brief comprueva si el inventario esta vacio
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @return Devuelve TRUE en caso de que este vacio y FALSE en caso contrario
*/
Bool inventory_is_empty(Inventory * inventory);

/**
 * @brief comprueva si el inventario esta lleno
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @return Devuelve TRUE en caso de que este lleno y FALSE en caso contrario
*/
Bool inventory_is_full(Inventory * inventory);

/**
 * @brief añade un objeto al inventario
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @param Id id del objeto
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
*/
Status inventory_add_object(Inventory* inventory, Id id);

/**
 * @brief borra un objeto del inventario
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @param Id id del objeto
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
*/
Status inventory_del_object(Inventory* inventory, Id id);

/**
 * @brief verifica que un objeto este en el inventario 
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @param Id id del objeto
 * @return Devuelve TRUE en caso de que este en el inventario y FALSE en caso contrario
*/
Bool inventory_find_object(Inventory* inventory,Id id);

/**
 * @brief modifica el maximo de objetos del inventario
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @param int nuevo maximo
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
*/
Status inventory_set_max_objects(Inventory *inventory,int n);

/**
 * @brief recoje el maximo de objetos del inventario
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @return Devuelve el maximo de objetos del inventario en caso de exito y -1 en caso contrario
*/
int inventory_get_max_objects(Inventory *inventory);

/**
 * @brief recoje el set de objetos del inventario
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @return Devuelve el conjunto de objetos del inventario en caso de exito y NULL en caso contrario
*/
Set *inventory_get_objects(Inventory *inventory);

/**
 * @brief imprime las caracteristicas del inventario
 * @author Álvaro Rodríguez
 * @param Inventory puntero al inventario
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
*/
Status inventory_print(Inventory* inventory);

#endif