/**
 * @brief It declares the tests for the inventory module
 * @file inventory_tets.c
 * @author Álvaro Rodríguez 
 * @version 1
 * @date 24-03-2025
 * @copyright GNU Public License
 */

 #ifndef INVENTORY_TEST_H
 #define INVENTORY_TEST_H

/**
 * @test Test inventory creation
 * @post Non NULL pointer to inventory 
 */
void test1_inventory_create();
void test2_inventory_create();
/**
 * @test Test character destroy
 * @post Status command, OK if triumph, ERROR otherwise
 */
void test1_inventory_destroy();
void test2_inventory_destroy();
/**
 * @test Test if an inventory is empty
 * @pre Pointer to inventory
 * @post True if inventory is empty or false in other case
 */
void test1_inventory_is_empty();
void test2_inventory_is_empty();
/**
 * @test Test if an inventory is full
 * @pre Pointer to inventory
 * @post True if inventory is full or false in other case
 */
void test1_inventory_is_full();
void test2_inventory_is_full();
/**
 * @test Test the addition of an object to an inventory
 * @pre Pointer to inventory
 * @post OK if there was not problems, or ERRER in other case
 */
void test1_inventory_add_object();
void test2_inventory_add_object();
/**
 * @test Test the remotion of an object to an inventory
 * @pre Pointer to inventory
 * @post OK if there was not problems, or ERRER in other case
 */
void test1_inventory_del_object();
void test2_inventory_del_object();
/**
 * @test Test the remotion of an object to an inventory
 * @pre Pointer to inventory
 * @pre adds an object to de inventory
 * @post return TRUE because there is the object in the inventory
 */
void test1_inventory_find_object();
/**
 * @test Test the remotion of an object to an inventory
 * @pre Pointer to inventory
 * @pre do not adds an object to de inventory
 * @post return FALSE because there no objects in the inventory
 */
void test2_inventory_find_object();
/**
 * @test Test the set of the max objects of an inventory
 * @pre Pointer to inventory
 * @post OK if there was not problems, or ERRER in other case
 */
void test1_inventory_set_max_objects();
void test2_inventory_set_max_objects();
/**
 * @test Test the get of the max objects of an inventory
 * @pre Pointer to inventory
 * @post return an int whith the max objects
 */
void test1_inventory_get_max_objects();
void test2_inventory_get_max_objects();
/**
 * @test Test the getting of the array of objects of an inventory 
 * @pre Pointer to inventory
 * @post NULL if ther are no objects or =!NULL if ther are objects in the inventory
 */
void test1_inventory_get_objects();
void test2_inventory_get_objects();



 #endif