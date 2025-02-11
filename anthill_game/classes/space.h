/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Danyyil Shykerynets
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "object.h"
#include "types.h"

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Danyyil Shykerynets
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief It sets whether the space has an object or not
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @param object A pointer to the object to add to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_object(Space* space, Object *object);

/**
 * @brief It gets whether the space has an object or not
 * @author Danyyil Shykerynets
 *
 * @param space a pointer to the space
 * @return A pointer to the object in the space
 */
Object *space_get_object(Space* space);

/**
 * @brief It prints the space information
 * @author Danyyil Shykerynets
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

#endif
