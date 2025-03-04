/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Danyyil Shykerynets
 * @version 7
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "player.h"
#include "object.h"
#include "space.h"
#include "types.h"
#include "command.h"

#define MAX_SPACES 100

typedef struct _Game Game;

/**
 * @brief Crea el juego reservando la memoria 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Game* game_create();

/**
 * @brief Destruye el juego liberando la memoria reservada
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_destroy(Game *game);

/**
 * @brief El juego obtiene el último comando utilizado
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return Un puntero a Command
 */
Command* game_get_last_command(Game *game);

/**
 * @brief El juego define el último comando utilizado
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief El juego define el último comando utilizado
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Bool game_get_finished(Game *game);

/**
 * @brief Se define el fin del juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @param finished EL valor TRUE o FALSE
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Imprime el juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 */
void game_print(Game *game);

/**
 * @brief Obtiene el puntero del jugador de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @return Puntero a la estructura player de la partida "game" 
 */
Player *game_get_player(Game* game);

/**
 * @brief Establece un nuevo objeto en el array de objetos de la partida
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param object Objeto a establecer en la partida
 * @return OK en caso de exito, ERROR en caso contrario 
 */
Status game_add_object(Game* game, Object* object);

/**
 * @brief Obtiene el puntero de un objeto con cierto id de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param id Id del objeto que se quiere obtener
 * @return Puntero a la estructura objeto de la partida "game" 
 */
Object* game_get_object(Game *game, Id id);

/**
 * @brief Obtiene el puntero de un objeto con cierto nombre de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param name Nombre del objeto que se quiere obtener
 * @return Puntero a la estructura objeto de la partida "game" 
 */
Object* game_get_object_by_name(Game *game, char* name);

/**
 * @brief Establece un nuevo personaje en el array de personajes de la partida
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param character Personaje a establecer en la partida
 * @return OK en caso de exito, ERROR en caso contrario 
 */
Status game_add_character(Game* game, Character* character);

/**
 * @brief Reduce el numero de personajes en 1 de la partida
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param character_id ID del personaje a destruir
 * @return OK en caso de exito, ERROR en caso contrario 
 */
Status game_remove_character(Game *game, Id character_id);

/**
 * @brief Devuelve el numero de personajes en la partida
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @return INT con numero de personajes vivos en la partida
 */
int game_get_n_characters(Game* game);

/**
 * @brief Obtiene el puntero de un personaje con cierto id de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param id Id del personaje que se quiere obtener
 * @return Puntero a la estructura objeto de la partida "game" 
 */
Character* game_get_character(Game* game, Id id);

/**
 * @brief Crea un espacio nuevo en el array de espacios
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param space Estructura del espacio a agregar en el array
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief EL juego obtiene el espacio definido
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param Id el número id del espacio
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Obtiene del espacio en cierta posicion del array de espacios de la partida
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param position Coordenada del array a la que acceder en el array de espacios
 * @return Id del espacio que buscabamos
 */
Id game_get_space_id_at(Game *game, int position);

#endif