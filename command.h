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

Command* command_create();
Status command_destroy(Command* command);
Status command_set_code(Command* command, CommandCode code);
CommandCode command_get_code(Command* command);
Status command_get_user_input(Command* command);

#endif

