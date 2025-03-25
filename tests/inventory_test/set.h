/**
 * @brief Define las interfaces de Set
 * @file set.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 1
 * @date 18-02-2025
 * @copyright GNU Public License
*/

#ifndef SET_H
#define SET_H
#define MAX_IDS 100
#include "types.h"
 
/**
 * @brief Define la estrcura Set
 * @author Anthony Eduardo Alvarado Carbajal
 */
typedef struct _Set Set;

/**
* @brief Crea un Set
* @author Anthony Eduardo Alvarado Carbajal
 * @return Un puntero a Set
 */
Set *set_create();

/**
 * @brief Destruye un Set
 * @author Anthony Eduardo Alvarado Carbajal
 * @param set un puntero a Set
 * @return OK, si todo va bien , o ERROR si existe algún fallo
 */
Status set_destroy(Set *set);

/**
 * @brief Obtiene el numero de ids del set
 * @author Anthony Eduardo Alvarado Carbajal
 * @param set Un puntero a Set
 * @return el número de ids
 */
int set_get_nids(Set* set);

/**
 * @brief Establece el numero de ids del set
 * @author Anthony Eduardo Alvarado Carbajal
 * @param set Un puntero a Set
 * @return OK, si todo va bien, o ERROR si existe algún fallo
 */
Status set_set_nids(Set* set, int n);

/**
 * @brief Añade el valor del un Set
 * @author Anthony Eduardo Alvarado Carbajal
 * @param set un puntero a Set
 * @param id el numero id del objeto
 * @return OK, si todo va bien , o ERROR si existe algún fallo
 */
Status set_add_value(Set *set, Id id);

/**
 * @brief Elimina el valor de un Set
 * @author Anthony Eduardo Alvarado Carbajal
 * @param set un puntero a Set
 * @param id el numero id del objeto
 * @return OK, si todo va bien , o ERROR si existe algún fallo
 */
Status set_del_value(Set *set, Id id);

/**
 * @brief Verifica si se encuentra el objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param set Un puntero a Set
 * @param id un número id
 * @return TRUE si el objeto es encontrado ,FALSE en caso contrario 
 */
Bool set_find_object(Set *set, Id id);

/**
 * @brief establece el id del objeto
 * @author Anthony Eduardo Alvarado Carbajal 
 * @param set Un puntero a Set
 * @return El número id del objeto 
 */
Id* set_id_object(Set* set);

/**
 * @brief Imprime el Set
 * @author Anthony Eduardo Alvarado Carbajal
 * @param set un puntero a Set
 * @return OK, si todo va bien, o ERROR, si hay un fallo
 */
Status set_print(Set *set);


#endif
