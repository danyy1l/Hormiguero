/**
 * @brief Definicion del modulo character 
 *
 * @file character.h
 * @author Danyyil Shykerynets
 * @version 1
 * @date 18-02-2025
 * @copyright GNU Public License
 */

#include "types.h"

 /**
 * @brief Estructura character con campos:
 * ID, name, descripcion grafica, vida, friendly y un mensaje
 * @author Danyyil Shykerynets
 */
typedef struct _Character Character;

/**
 * @brief Crea un NPC nuevo
 * @author Danyyil Shykerynets
 * @return Devuelve a una estructura character inicializada
 */
Character* character_create();

/**
 * @brief Destruye una estructura character
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_destroy(Character* character);

/**
 * @brief Obtiene el ID de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve el ID del personaje objetivo
 */
Id character_get_id(Character* character);

/**
 * @brief Establece el id de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @param id ID a establecer en el personaje
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_set_id(Character* character, Id id);

/**
 * @brief Obtiene la ubicacion de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve el location del personaje objetivo
 */
Id character_get_location(Character* character);

/**
 * @brief Establece la ubicacion de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @param location Ubicacion a establecer en el personaje
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_set_location(Character* character, Id location);

/**
 * @brief Obtiene el nombre de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve el nombre del personaje objetivo
 */
char* character_get_name(Character* character);

/**
 * @brief Establece el nombre de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @param name Nombre a establecer en el personaje
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_set_name(Character* character, char* name);

/**
 * @brief Obtiene la descripcion grafica de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve la descripcion grafica del personaje objetivo
 */
char* character_get_gdesc(Character* character);

/**
 * @brief Establece la descripcion grafica de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @param gdesc Descripcion grafica a establecer en el personaje
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_set_gdesc(Character* character, char* gdesc);

/**
 * @brief Obtiene la descripcion grafica de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve la descripcion grafica del personaje objetivo
 */
int character_get_health(Character* character);

/**
 * @brief Establece la vida de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @param health Vida a establecer en el personaje
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_set_health(Character* character, int health);

/**
 * @brief Obtiene si el personaje es amistoso
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve 1 si es amistoso y 0 si no
 */
Bool character_get_friendly(Character* character);

/**
 * @brief Establece si un personaje es amistoso o no
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @param friendly Simpatia a establecer en el personaje
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_set_friendly(Character* character, Bool friendly);

/**
 * @brief Obtiene el mensaje de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @return Devuelve el mensaje del personaje objetivo
 */
char* character_get_message(Character* character);

/**
 * @brief Establece el mensaje de un personaje
 * @author Danyyil Shykerynets
 * @param character Puntero al personaje objetivo
 * @param message Mensaje a establecer en el personaje
 * @return Devuelve OK en caso de exito y ERROR en caso contrario
 */
Status character_set_message(Character* character, char* message);

/**
 * @brief Imprime los atributos de un personaje
 * @author Danyyil Shykerynets
 * @param c Puntero al personaje objetivo
 */
void character_print(Character* c);