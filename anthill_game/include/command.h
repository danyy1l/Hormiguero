/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 7
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 8


typedef enum { CMDS, CMDL } CommandType;

typedef enum { 
  NO_CMD = -1,
  UNKNOWN,
  QUIT,
  MOVE,
  TAKE,
  DROP,
  ATTACK,
  CHAT
}CommandCode;

typedef struct _Command Command;

/**
 * @brief Crea un nuevo comando reservando su espacio
 * @author Anthony Eduardo Alvarado Carbajal
 * @return Un nuevo comando inicializado
 */
Command* command_create();

/**
 * @brief Destruye el comando liberando su memoria
 * @author Anthony Eduardo Alvarado Carbajal
 * @param command un puntero a Command
 * @return Ok si todo va bien o ERROR si hay un fallo
 */
Status command_destroy(Command* command);

/**
 * @brief Define el código para el comando
 * @author Anthony Eduardo Alvarado Carbajal
 * @param command un puntero a Command 
 *
 * @param code un valor de Commandcode, ya sea NO_CMD,UNKNOWN,EXIT,NORTH,EAST,SOUTH,WEST
 * @return Ok si todo va bien o ERROR si hay un fallo
*/
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Obtiene un codigo a través del comando
 * @author Anthony Eduardo Alvarado Carbajal
 * @param command un puntero a Command
 * @return NO_CMD,UNKNOWN,EXIT,NORTH,EAST,SOUTH,WEST
 */
CommandCode command_get_code(Command* command);

/**
 * @brief La función define un usuario
 * @author Anthony Alvarado Carbajal
 * @param command un puntero a Command
 * @return OK si todo va bien o ERROR si hay algun fallo
 */
Status command_get_user_input(Command* command);

/**
 * @brief Obtiene el output del ultimo comando
 * @author Danyyil Shykerynets
 * @param command un puntero a Command
 * @return OK si el comando se ejecuto o ERROR si no
 */
Status command_get_output(Command *command);

/**
 * @brief Cambia el output del ultimo comando
 * @author Danyyil Shykerynets
 * @param command un puntero a Command
 * @return OK si se ha cambiado con exito o ERROR si no
 */
Status command_set_output(Command *command, Status new_output);

/**
 * @brief Obtiene el el argumento adicional del ultimo comando
 * @author Danyyil Shykerynets
 * @param command un puntero a Command
 * @return un string con los argumentos que se hayan añadido al comando
 * Ejemplo: si el comando es take grain, devuelve grain
 */
char* command_get_arguments(Command *command);

/**
 * @brief Obtiene la dirección del argumento en caso de que command sea MOVE
 * @author Danyyil Shykerynets
 * @param command comando recibido
 * @return Una direccion (enumeracion) que representa la dirección a la que moverse
 */
Direction command_move_get_direction(Command *command);

#endif
