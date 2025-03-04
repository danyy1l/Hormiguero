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
#define GDESC_SIZE 6
#define STATUS_SIZE 6
#define NO_ID -1

#define CHARACTERS_NUM 2
#define OBJECTS_NUM 4

typedef long Id;

typedef enum { FALSE, TRUE } Bool;

typedef enum { ERROR, OK } Status;

typedef enum { N, S, E, W } Direction;

#endif
