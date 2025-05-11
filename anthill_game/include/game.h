/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Danyyil Shykerynets
 * @version 22
 * @date 24-04-2025
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

/**
 * @brief Declaracion de la estructura que contiene todos los datos de la partida
 */
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
 * @brief Devuelve el array de jugadores de la partida
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @return Puntero a los jugadores
 */
Player** game_players(Game *game);

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

/**
 * @brief Obtiene turno de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @return Entero con el turno
 */
int game_get_turn(Game* game);

/**
 * @brief Establece el turno de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param turn Nuevo turno a establecer
 * @return OK en caso de exito, ERROR en caso contrario
 */
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
 * @brief Reduce el numero de objetos en 1 de la partida
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param object_id ID del objeto a destruir
 * @return OK en caso de exito, ERROR en caso contrario 
 */
Status game_remove_object(Game *game, Id object_id);

/**
 * @brief Obtiene el puntero de un objeto con cierto id de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param id Id del objeto que se quiere obtener
 * @return Puntero a la estructura objeto de la partida "game" 
 */
Object* game_get_object(Game *game, Id id);

/**
 * @brief Obtiene los objetos del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @return Puntero al array de objetos del juego
 */
Object **game_get_objects(Game *game);

/**
 * @brief Obtiene los characters del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @return Puntero al array de characters del juego
 */
Character **game_get_characters(Game *game);

/**
 * @brief Obtiene los espacios del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @return Puntero al array de espacios del juego
 */
Space **game_get_spaces(Game *game);

/**
 * @brief Obtiene los links del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @return Puntero al array de links del juego
 */
Link **game_get_links(Game *game);

/**
 * @brief Obtiene los players del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @return Puntero al array de players del juego
 */
Player **game_get_players(Game *game);

/**
 * @brief Devuelve el numero de espacios del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @return Numero de espacios del juego
 */
int game_get_n_spaces(Game *game);

/**
 * @brief Establece el número de jugadores del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param n_players Número de jugadores a establecer
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
Status game_set_n_players(Game *game, int n_players);

/**
 * @brief Establece el número de personajes del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param n_characters Número de personajes a establecer
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
Status game_set_n_characters(Game *game, int n_characters);

/**
 * @brief Establece el número de enlaces del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param n_links Número de enlaces a establecer
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
Status game_set_n_links(Game *game, int n_links);

/**
 * @brief Establece el número de espacios del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param n_spaces Número de espacios a establecer
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
Status game_set_n_spaces(Game *game, int n_spaces);

/**
 * @brief Establece el número de objetos del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param n_objects Número de objetos a establecer
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
Status game_set_n_objects(Game *game, int n_objects);

/**
 * @brief Establece el turno del juego
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param turn Turno del juego
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
Status game_set_turn(Game *game, int turn);

/**
 * @brief Obtiene un link por su id
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param id Un id de un link
 * @return NULL o el puntero al link
 */
Link *game_get_link_by_id(Game *game, Id id);

/**
 * @brief Obtiene un player por su id
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param id Un id de un player
 * @return NULL o el puntero al player
 */
Player *game_get_player_by_id(Game *game, Id id);

/**
 * @brief Obtiene el puntero de un objeto con cierto nombre de la estructura game
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param name Nombre del objeto que se quiere obtener
 * @return Puntero a la estructura objeto de la partida "game" 
 */
Object* game_get_object_by_name(Game *game, char* name);

/**
 * @brief Obtiene el puntero de un link con cierto nombre de la estructura game
 * @author Hugo Martín
 * @param game Un puntero a Game
 * @param name Nombre del link que se quiere obtener
 * @return Puntero a la estructura objeto de la partida "game" 
 */
Link* game_get_link_by_name(Game *game, char* name);

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
 * @brief Reduce el numero de objetos en 1 de la partida
 * @author Danyyil Shykerynets
 * @param game Un puntero a Game
 * @param object_id ID del objeto a destruir
 * @return OK en caso de exito, ERROR en caso contrario 
 */
Status game_remove_object(Game *game, Id object_id);

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
 * @brief Devuelve el personaje en la posición i del array de personajes del juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game puntero a la estructura Game
 * @param i índice del personaje (0 <= i < n_characters)
 * @return puntero al personaje o NULL si hay error
 */
Character* game_get_character_at(Game* game, int i);

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
 * @brief Establece el ultimo mensaje de la partida
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @param str Mensaje a establecer
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_set_message(Game* game, char* str);

/**
 * @brief Obtiene el ultimo mensaje guardado en la partida
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @return String con el mensaje
 */
char* game_get_message(Game* game);

/**
 * @brief Establece la ubicacion del anterior jugadro de la partida
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @param Id ubicacion a establecer
 * @return OK en caso de exito, ERROR en caso contrario
 */
Status game_set_prev_player_location(Game* game, Id location);

/**
 * @brief Obtiene la ubicacion del anterior jugador
 * @author Danyyil Shykerynets
 * @param game Puntero a la partida
 * @return Id con la ubicacion del anterior jugador
 */
Id game_get_prev_player_location(Game* game);

/**
 * @brief Imprime el juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 */
void game_print(Game *game);

#endif
