/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Danyyil Shykerynets 
 * @version 7
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "../include/command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 100

char *cmd_to_str[N_CMD][N_CMDT] = {
  {"", "No command"},
  {"", "Unknown"},
  {"q", "Quit"},
  {"m", "Move"},
  {"t", "Take"},
  {"d", "Drop"},
  {"a", "Attack"},
  {"c", "Chat"},
  {"i", "Inspect"},
  {"u", "Use"},
  {"o", "Open"},
  {"r", "Recruit"},
  {"ab", "Abandon"}
};

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command {
  CommandCode code;               /*!< Name of the command */
  Status output;                  /*!< Return of executed command, either OK or ERROR*/
  char arguments[WORD_SIZE];      /*!< Name of the object desired to take*/
  char arguments1[WORD_SIZE];     /*!< "over" for USE and "with" for OPEN*/
  char arguments2[WORD_SIZE];     /*!< Name of the character or the object*/
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Command* command_create() {
  Command* newCommand = NULL; 

  newCommand = (Command*)malloc(sizeof(Command));
  if (newCommand == NULL) {
    return NULL;
  }

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;
  newCommand->arguments[0] = '\0';
  newCommand->arguments1[0] = '\0';
  newCommand->arguments2[0] = '\0';
  newCommand->output = ERROR;

  return newCommand;
}

Status command_destroy(Command* command) {
  if(command){
    free(command);
    command = NULL;
    return OK;
  }else
    return ERROR;
}

Status command_set_code(Command* command, CommandCode code) {
  if (!command) {
    return ERROR;
  }

  command->code=code;

  return OK;
}

CommandCode command_get_code(Command* command) {
  if (!command) {
    return NO_CMD;
  }
  return command->code;
}

Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "", *token = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  if (!command) { 
    return ERROR;
  }

  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \n");
    if (!token) {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
      } else {
        i++;
      }
    }
    
    if( (token = strtok(NULL, " \n")) ){ 
      strcpy(command->arguments, token);
    }else
      strcpy(command->arguments, "\0");

    if( (token = strtok(NULL, " \n")) ){ 
      strcpy(command->arguments1, token);
    }else
      strcpy(command->arguments1, "\0");

    if( (token = strtok(NULL, " \n")) ){ 
      strcpy(command->arguments2, token);
    }else
      strcpy(command->arguments2, "\0");
    
    return command_set_code(command, cmd);
  }
  else
    return command_set_code(command, QUIT);
}

Status command_get_output(Command *command){
  if(!command)
    return ERROR;

  return command->output;
}

Status command_set_output(Command *command, Status new_output){
  if(!command)
    return ERROR;

  command->output = new_output;
 
  return OK;
}

char* command_get_arguments(Command *command){
  if( !command )
    return NULL;

  return command->arguments;
}

char* command_get_arguments1(Command *command){
  if( !command )
    return NULL;

  return command->arguments1;
}

char* command_get_arguments2(Command *command){
  if( !command )
    return NULL;

  return command->arguments2;
}
