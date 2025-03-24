/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 7
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define GDESC_SIZE 10
#define GDESC_MAX 5
#define STATUS_SIZE 6
#define NO_ID -1

#define PLY_GDESC 4
#define CHAR_GDESC 6

#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100
#define MAX_PLAYERS 4

typedef long Id;

typedef enum { FALSE, TRUE } Bool;

typedef enum { ERROR, OK } Status;

typedef enum { U, N, E, S, W } Direction;

#endif
