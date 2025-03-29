/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Danyyil Shykerynets
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 15
 * @date 19-03-2025
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
#include "link.h"

#define MAX_SPACES 100
#define MAX_LINKS 400

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
 * @brief El juego obtiene el último comando utilizado para cierto jugador
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return Un puntero a Command
 */
Command* game_get_last_command(Game *game);

/**
 * @brief El juego define el último comando utilizado para cierto jugador
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @param command comando a establecer
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief El juego define el último comando utilizado para cierto jugador
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Bool game_get_finished(Game *game);

/**
 * @brief Se define el fin del juego para cierto jugador
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @param finished EL valor TRUE o FALSE
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Obtiene el puntero del jugador de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game a obtener
 * @return Puntero a la estructura player de la partida "game" 
 */
Player *game_get_player(Game* game);

/**
 * @brief Obtiene el numero de jugadores de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @return Entero con numero de jugadores
 */
int game_get_n_players(Game *game);

/**
 * @brief Establece un nuevo jugador en el array de objetos de la partida
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param player jugador a establecer en la partida
 * @return OK en caso de exito, ERROR en caso contrario 
 */
Status game_add_player(Game *game, Player* player);

/*TO DO: Documentar*/

int game_get_turn(Game* game);

Status game_next_turn(Game* game, int turn);

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
 * @brief Obtiene el numero de objetos de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @return INT con numero de objetos de la partida "game" 
 */
int game_get_n_objects(Game* game);

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
 * @brief El juego obtiene el puntero de un link con un id determinado en la estructura game 
 * @author Anthony Eduardo Alvarado Carbajal 
 * @param game Un puntero a game
 * @param origin ID del origen
 * @param destination ID del espacio destino
 * @return Un puntero a link en la partida game
 */
Link* game_get_link(Game* game, Id origin, Id destination);

/**
 * @brief Adicion de un nuevo enlace a la partida 
 * @author Danyyil Shykerynets
 * @param game Un puntero a game
 * @param link estructura del enlace creado (game_reader)
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_add_link(Game* game, Link* link);

/**
 * @brief El juego obtiene el numero de links
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a game
 * @return El numero de links
 */
int game_get_n_links(Game* game);

/**
 * @brief Obtiene del espacio en cierta posicion del array de espacios de la partida
 * @author Danyyil Shykerynets
 * @param game Estructura de la partida actual
 * @param position Coordenada del array a la que acceder en el array de espacios
 * @return Id del espacio que buscabamos
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief Obtiene una conexion id del destino si existe un enlace valido
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a game
 * @param id ID del espacio actual
 * @param direction una direccion
 * @return el id destinatario
 */
Id game_get_connection(Game *game, Id id, Direction direction);

/**
 * @brief Verifica si la conexion está abierta o cerrada
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a juego
 * @param id ID del espacio actual
 * @param direction una direccion
 * @return TRUE, si la conexion esta abierta o FALSE en caso contrario
 */
Bool game_connection_is_open(Game *game, Id id, Direction direction);

/**
 * @brief Imprime el juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 */
void game_print(Game *game);

#endif