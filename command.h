/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Danyyil Shykerynets
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 7


typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NORTH, SOUTH, EAST, WEST} CommandCode;

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
  * @param code un valor de Commandcode, ya sea NO_CMD,UNKNOWN,EXIT,NEXT o BACK
  * @return Ok si todo va bien o ERROR si hay un fallo
*/
Status command_set_code(Command* command, CommandCode code);

 /**
  * @brief Obtiene un codigo a través del comando
  * @author Anthony Eduardo Alvarado Carbajal
  * @param command un puntero a Command
  * @return NO_CMD,UNKNOWN,EXIT,NEXT o BACK
*/
CommandCode command_get_code(Command* command);

 /**
  * @brief La función define un usuario
  * @author Anthony Alvarado Carbajal
  * @param command un puntero a Command
  * @return OK si todo va bien o ERROR si hay algun fallo
*/
Status command_get_user_input(Command* command);

#endif

