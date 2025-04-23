/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 20
 * @date 23-04-2025
 * @copyright GNU Public License 
 */

#ifndef SPACE_H
#define SPACE_H
 
#include "object.h"
#include "types.h"
#include "set.h"
 
/**
 * @brief Space struct declaration
 */
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
 * @brief Adds a character to the space
 * @author Anthony Eduardo Alvarado Carbajal 
 * @param space A pointer to the space 
 * @param id a number id 
 * @return OK, if everything goes well, or ERROR if there is a mistake
 */
Status space_add_character(Space* space, Id id);

/**
 * @brief Deletes a character in the space
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space A pointer to the space 
 * @param id a number id 
 * @return OK, if everything goes well, or ERROR if there is a mistake
 */
Status space_del_character(Space* space, Id id);
  
/**
 * @brief Gets the characters in the space
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space A pointer to the space 
 * @return Array of object ids in the space
 */
Id* space_id_character(Space* space);

/**
 * @brief Get the set of characters of the space
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space A pointer to the space
 * @return Object set in space struct
 */
Set* space_get_set_characters(Space* space);

/**
 * @brief verifies if an character exists 
 * @author Anthony Eduardo Alvarado Carbajal 
 * @param space A pointer to the space 
 * @param id a number id of space
 * @return TRUE, if everything goes well, or FALSE if there is a mistake 
 */
Bool space_find_character(Space* space, Id id);
  
/**
 * @brief Adds an object to the space
 * @author Anthony Eduardo Alvarado Carbajal 
 * @param space A pointer to the space 
 * @param id a number id 
 * @return OK, if everything goes well, or ERROR if there is a mistake
 */
Status space_add_object(Space * space, Id id);
  
/**
 * @brief Deletes an object in the space
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space A pointer to the space 
 * @param id a number id 
 * @return OK, if everything goes well, or ERROR if there is a mistake
 */
Status space_del_object(Space *space, Id id);
  
/**
 * @brief Gets the objects in the space
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space A pointer to the space 
 * @return Array of object ids in the space
 */
Id* space_id_object(Space* space);
 
/**
 * @brief Get the set of objects of the space
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space A pointer to the space
 * @return Object set in space struct
 */
Set* space_get_set_objects(Space* space);
 
/**
 * @brief verifies if an object exists 
 * @author Anthony Eduardo Alvarado Carbajal 
 * @param space A pointer to the space 
 * @param id a number id of space
 * @return TRUE, if everything goes well, or FALSE if there is a mistake 
 */
Bool space_find_object(Space* space,Id id);

/**
 * @brief It gets the gdesc string
 * @author Anthony Eduardo Alvarado Carbajal 
 * @param space A pointer to space
 * @param pos the array's position
 * @return the gdesc string in a determined position
 */
char* space_get_gdesc(Space *space,int pos);

/**
 * @brief It sets the gdesc string 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space A pointer to space 
 * @param name the gdesc string
 * @param pos the array's position
 * @return OK, if everything goes well, or ERROR if there is a mistake 
 */
Status space_set_gdesc(Space *space, char *name,int pos);

/**
 * @brief It gets the discovered state
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space a pointer to space
 * @return the discovered state
 */
Bool space_get_discovered(Space *space);

/**
 * @brief It sets the discovered state 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space a pointer to space
 * @param discovered  the discovered state
 * @return TRUE, if evretyhting goes well o FALSE if there is a mistake
 */
Status space_set_discovered(Space *space,Bool discovered);

/**
 * @brief Set discovered value as TRUE if a player is in the space
 * @author Anthony Eduardo Alvarado Carbajal
 * @param space a pointer to space
 */
void space_player_arrive(Space *space);

/**
 * @brief It gets the spaces primary message
 * @author Danyyil Shykerynets
 * @param space pointer to space
 * @return string with spaces message
 */
char* space_get_message1(Space* space);

/**
 * @brief It gets the spaces secondary message
 * @author Danyyil Shykerynets
 * @param space pointer to space
 * @return string with spaces message
 */
char* space_get_message2(Space* space);

/**
 * @brief It sets the spaces primary message 
 * @author Danyyil Shykerynets
 * @param space a pointer to space
 * @param message1 the spaces message
 * @return OK if all right, ERROR otherwise
 */
Status space_set_message1(Space* space, char* message1);

/**
 * @brief It sets the spaces secondary message 
 * @author Danyyil Shykerynets
 * @param space a pointer to space
 * @param message2 the spaces message
 * @return OK if all right, ERROR otherwise
 */
Status space_set_message2(Space* space, char* message2);

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
