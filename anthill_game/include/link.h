/**
 * @brief It defines the link module interface
 *
 * @file link.h
 * @author Danyyil Shykerynets
 * @version 1
 * @date 21-03-2025
 * @copyright GNU Public License
*/

#include "types.h"

/**
 * @brief Link
 * Esta estructura almacena toda la información del enlace
 */
typedef struct _Link Link;

/**
 * @brief Crea un enlace
 * @author Danyyil Shykerynets
 * 
 * @return Enlace inicializado
 */
Link* link_create();

/**
 * @brief Destruye un enlace
 * @author Danyyil Shykerynets
 * @param link Un puntero a Link
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status link_destroy(Link* link);

/**
 * @brief Obtiene el id del enlace
 * @author Danyyil Shykerynets
 * @param link Un puntero a enlace 
 * @return ID del enlace
 */
Id link_get_id(Link* link);

/**
 * @brief Establece un id para el enlace
 * @author Danyyil Shykerynets
 * @param link Un puntero a link
 * @param id el identificador del enlace
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status link_set_id(Link* link, Id id);

/**
 * @brief Obtiene el nombre del enlace
 * @author Danyyil Shykerynets
 * @param link Un puntero a Link
 * 
 * @return Una cadena que es el nombre del enlace
 */
const char* link_get_name(Link* link);

/**
 * @brief Establece un nuevo nombre para el enlace
 * @author Danyyil Shykerynets
 * @param link Un puntero a Link
 * @param name Una cadena con el nombre del enlace
 * 
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status link_set_name(Link* link, char* name);

/**
 * @brief Obtiene el origen del enlace
 * @author Danyyil Shykerynets
 * @param link Puntero al enlace
 * @return Devuelve el id del espacio del que surge el enlace
 */
Id link_get_origin(Link *link);

/**
 * @brief Establece el origen del enlace
 * @author Danyyil Shykerynets
 * @param origin Id del espacio origen del enlace
 * @param link Puntero al enlace
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status link_set_origin(Link *link, Id origin);

/**
 * @brief Obtiene el destino del enlace
 * @author Danyyil Shykerynets
 * @param link Puntero al enlace
 * @return Devuelve el id del espacio del que surge el enlace
 */
Id link_get_destination(Link *link);

/**
 * @brief Establece el destino del enlace
 * @author Danyyil Shykerynets
 * @param destination Id del espacio destino del enlace
 * @param link Puntero al enlace
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status link_set_destination(Link *link, Id destination);

/**
 * @brief Obtiene la direccion del enlace
 * @author Danyyil Shykerynets
 * @param link Puntero al enlace
 * @return Devuelve un entero (Direction) que indica la direccion del enlace
 */
Direction link_get_direction(Link *link);

/**
 * @brief Establece la direccion del enlace
 * @author Danyyil Shykerynets
 * @param dir Entero que indica la direccion (Direction)
 * @param link Puntero al enlace
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status link_set_direction(Link *link, Direction dir);

/**
 * @brief Obtiene la apertura del enlace
 * @author Danyyil Shykerynets
 * @param link Puntero al enlace
 * @return Booleano que indica si esta abierto el enlace o no
 */
Bool link_get_open(Link *link);

/**
 * @brief Establece la apertura del enlace
 * @author Danyyil Shykerynets
 * @param open Booleano que indica si esta abierto el enlace o no
 * @param in Puntero al enlace
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status link_set_open(Link *link, Bool open);

/**
 * @brief Imprime el enlace
 * @author Danyyil Shykerynets
 * @param link Un puntero a Link
 */
void link_print(Link* link);