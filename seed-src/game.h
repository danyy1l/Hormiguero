/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"

#define MAX_SPACES 100
/**
 * @brief Game
 * Esta estructura almacena toda la información del juego
 */
typedef struct _Game {
  Id player_location;           /*!< Número id de localización del jugador*/
  Id object_location;           /*!< Número id de localización del objeto*/
  Space *spaces[MAX_SPACES];    /*!< Array estático de un número limitado de espacios*/
  int n_spaces;                 /*!< Número de espacios*/
  Command *last_cmd;            /*!< Puntero al comando*/
  Bool finished;                /*!< Valor de TRUE o FALSE*/
} Game;

/**
 * @brief Crea el juego reservando la memoria 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_create(Game *game);

/**
 * @brief Crea el juego partiendo de un fichero
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @param filename una cadena con el nombre del fichero
 * @return OK, si todo va bien o ERROR si hay algun fallo
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief Destruye el juego liberando la memoria reservada
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_destroy(Game *game);

/**
 * @brief EL juego obtiene el espacio definido
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @param Id el número id del espacio
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief El juego obtiene la locaclización del jugador 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @return El numero id del jugador 
 */
Id game_get_player_location(Game *game);

/**
 * @brief El juego define la localización del jugador 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game 
 * @param id el número del id del jugador 
 * @return OK, si todo está bien o ERROR si hay algún fallo
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief El juego obtiene la localización del objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @return el número id del obejeto
 */
Id game_get_object_location(Game *game);

/**
 * @brief El juego define la localización del objeto
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a Game
 * @param id el número id del objeto 
 * @return OK, si todo va bien o ERROR si hay algún fallo
 */
Status game_set_object_location(Game *game, Id id);

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
 * @brief Se obtiene el fin del juego
 * @author Anthony Eduardo Alvarado Carbajal
 * @param game Un puntero a game
 * @return TRUE, si el juego se temrina o FALSE si el juego continua
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

#endif
