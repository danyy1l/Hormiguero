/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 7
 * @date 24-04-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H
 
#include "types.h"

#define N_CMDT 2
#define N_CMD 17

/**
 * Enumeracion que representa la palabra de llamada al comando, CMDS es para la corta y CMDL para la palabra completa
 */
typedef enum { CMDS, CMDL } CommandType;

/**
 * Enumeracion de posibles comandos
 */
typedef enum { 
  NO_CMD = -1,  /*!<-Representa ningun comando recibido*/
  UNKNOWN,      /*!<-Comando desconocido*/
  QUIT,         /*!<-Este comando termina la partida*/
  MOVE,         /*!<-Movimiento, hay que añadir la direccion en el argumento*/
  TAKE,         /*!<-Tomar un objeto, se debe añadir el nombre del objeto*/
  DROP,         /*!<-Soltar un objeto, se debe añadir el nombre */
  ATTACK,       /*!<-Ataca a un personaje enemigo*/
  CHAT,         /*!<-Conversa con un personaje amigo*/
  LOOK,         /*!<-Mira la informacion sobre un espacio*/
  INSPECT,      /*!<-Inspecciona un objeto*/
  USE,          /*!<-Usa un objeto*/
  OPEN,         /*!<-Abre un enlace con un objeto*/
  SAVE,         /*!<-Guarda la partida*/
  LOAD,         /*!<-Carga una partida guardada*/
  RECRUIT,      /*!<Recruits a friendly character>*/
  ABANDON,      /*!<Abandons a friendly character>*/
  TEAM          /*!<Teams with another player>*/
}CommandCode;

typedef struct _Command Command;

/**
 * @brief Crea un nuevo comando reservando su espacio
 * @author Hugo Martín
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
 * @param code un valor de Commandcode, ya sea NO_CMD,UNKNOWN,EXIT,MOVE,TAKE,DROP,ATTACK,CHAT,INSPECT
 * @return Ok si todo va bien o ERROR si hay un fallo
*/
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Obtiene un codigo a través del comando
 * @author Anthony Eduardo Alvarado Carbajal
 * @param command un puntero a Command
 * @return NO_CMD,UNKNOWN,EXIT,MOVE,TAKE,DROP,ATTACK,CHAT,INSPECT
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
 * @brief Obtiene el el argumento adicional del tercer comando
 * @author Hugo Martín
 * @param command un puntero a Command
 * @return un string con los argumentos que se hayan añadido al comando
 * Ejemplo: si el comando es take grain, devuelve grain
 */
char* command_get_arguments1(Command *command);

/**
 * @brief Obtiene el el argumento adicional del ultimo comando
 * @author Hugo Martín
 * @param command un puntero a Command
 * @return un string con los argumentos que se hayan añadido al comando
 * Ejemplo: si el comando es take grain, devuelve grain
 */
char* command_get_arguments2(Command *command);

/**
 * @brief Establece el argumento adicional del último comando
 * @author Hugo Martín
 * @param command Un puntero a Command
 * @param arguments Un string con los argumentos que se quieran añadir al comando
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 * Ejemplo: si el comando es take grain, arguments sería "grain" 
 */
Status command_set_arguments(Command *command, const char *arguments);

/**
 * @brief Establece el argumento adicional del segundo campo del comando
 * @author Hugo Martín
 * @param command Un puntero a Command
 * @param arguments1 Un string con los argumentos que se quieran añadir al comando
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 * Ejemplo: si el comando es use key over door, arguments1 sería "over"
 */
Status command_set_arguments1(Command *command, const char *arguments1);

/**
 * @brief Establece el argumento adicional del tercer campo del comando
 * @author Hugo Martín
 * @param command Un puntero a Command
 * @param arguments2 Un string con los argumentos que se quieran añadir al comando
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 * Ejemplo: si el comando es use key over door, arguments2 sería "door"
 */
Status command_set_arguments2(Command *command, const char *arguments2);

#endif
