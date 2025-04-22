/**
 * @brief Define los interfaces del objeto
 * @file object.h
 * @author Hugo Martín
 * @version 7
 * @date 05-02-2024
 * @copyright GNU Public License
 */ 
#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>  
#include "types.h"

/**
 * @brief Object
 * Esta estructura almacena toda la información del objeto
 */
typedef struct _Object Object;

/**
 * @brief Crea un objeto
 * @author Hugo Martín
 * @param id el número id para el nuevo objeto
 * @return un nuevo objeto,inicializado
 */
Object* object_create(Id id);

/**
 * @brief Destruye un objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param object Un puntero a Object
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status object_destroy(Object* object);

/**
 * @brief Establece un id para el objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param object Un puntero a object
 * @param id el identificador del objeto
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status object_set_id(Object* object, Id id);

/**
 * @brief Obtiene el id del objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param object Un puntero a objeto 
 * @return el id del objeto
 */
Id object_get_id(Object* object);

/**
 * @brief Establece un nuevo nombre para el objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param object Un puntero a Object
 * @param name Una cadena con el nombre del objeto
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief Obtiene el nombre del objecto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param object Un puntero a Object
 * @return Una cadena que es el nombre del objeto
 */
const char* object_get_name(Object* object);

/**
 * @brief Establece la ubicacion del objeto
 * 
 * @param id Id del espacio inicial del objeto
 * @param object Puntero al objecto
 * @return OK en caso de que no haya errores, ERROR en caso contrario
 */
Status object_set_location(Object *object, Id id);

/**
 * @brief Obtiene la ubicacion del objeto
 * 
 * @param object Puntero al objeto a localizar
 *  Estructura juego con los datos de espacios, objetoes y objetos
 * @return Devuelve el id del espacio en el que se ubica el objeto
 */
Id object_get_location(Object *object);

/**
 * @brief Establece la descripción del objecto
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @param description Un puntero a una cadena con la descripción
 * @return OK si todo va bien y ERROR si va mal
 */
Status object_set_description(Object *object, char *description);

/**
 * @brief Obtiene la descripción del objecto
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @param description Un puntero a una cadena con la descripción
 * @return Una cadena que es la descripción del objeto
 */
char *object_get_description(Object *object);

/**
 * @brief Obtiene la informacion sobre si el objeto ha sido tomado por algun jugador
 * @author Danyyil Shykerynets
 * @param object puntero al objeto
 * @return Booleano TRUE si esta tomado, FALSE en caso contrario
 */
Bool object_get_taken(Object* object);

/**
 * @brief Establece la informacion sobre si el objeto ha sido tomado por algun jugador
 * @author Danyyil Shykerynets
 * @param object puntero al objeto
 * @param taken Booleano a establecer
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status object_set_taken(Object* object, Bool taken);

/**
 * @brief Obtiene la vida del objeto
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @return Una entero con la vida del objeto
 */
int object_get_health(Object *object);

/**
 * @brief Establece la vida del objeto
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @param health La vida del objeto
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status object_set_health(Object *object, int health);

/**
 * @brief Devuelve si el objeto se puede coger o no
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @return TRUE en caso de que se pueda, FALSE en caso contrario
 */
Bool object_get_movable(Object *object);

/**
 * @brief Establece la movilidad del objeto
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @param movable Si se puede mover o no
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status object_set_movable(Object *object, Bool movable);

/**
 * @brief Devuelve si el objeto depende de otro o no
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @return Id del objeto si tiene dependencias o NO_ID en caso contrario
 */
Id object_get_dependency(Object *object);

/**
 * @brief Establece la dependencia del objeto
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @param dependency Si depende o no
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status object_set_dependency(Object *object, Id dependency);

/**
 * @brief Devuelve si el objeto puede abrir enlaces o no
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @return Id del enlace si puede abrir alguno o NO_ID en caso contrario
 */
Id object_get_open(Object *object);

/**
 * @brief Establece en enlace que puede abrir
 * @author Hugo Martín
 * @param object Un puntero a Object
 * @param open Id del enlace
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status object_set_open(Object *object, Id open);

/**
 * @brief Imprime el objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param object Un puntero a Object
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status object_print(Object* object);

#endif
