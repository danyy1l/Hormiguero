/**
 * @brief It declares the tests for the player module
 * 
 * @file player_test.h
 * @author Hugo Martín
 * @version 1.0 
 * @date 25-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test player creation
 * @post Non NULL pointer to player 
 */
void test1_player_create();
void test2_player_create();

/**
 * @test Test id obtaining
 * @pre Pointer to player
 * @post Non negative ID of player 
 */
void test1_player_get_id();
void test2_player_get_id();

/**
 * @test Test id setting
 * @pre Pointer to player
 * @pre New ID to set 
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_player_set_id();
void test2_player_set_id();
void test3_player_set_id();

/**
 * @test Test name obtaining
 * @pre Pointer to player
 * @post Non NULL string
 */
void test1_player_get_name();
void test2_player_get_name();

/**
 * @test Test name setting
 * @pre Pointer to player
 * @pre New name to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_player_set_name();
void test2_player_set_name();
void test3_player_set_name();

/**
 * @test Test gdesc obtaining
 * @pre Pointer to player
 * @post Non NULL string
 */
void test1_player_get_gdesc();
void test2_player_get_gdesc();

/**
 * @test Test gdesc setting
 * @pre Pointer to player
 * @pre New gdesc to set 
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_player_set_gdesc();
void test2_player_set_gdesc();
void test3_player_set_gdesc();

/**
 * @test Test health obtaining
 * @pre Pointer to player
 * @post Non negative int
 */
void test1_player_get_health();
void test2_player_get_health();

/**
 * @test Test health setting
 * @pre Pointer to player
 * @pre New health to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_player_set_health();
void test2_player_set_health();

/**
 * @test Test location obtaining
 * @pre Pointer to player
 * @post Non negative ID 
 */
void test1_player_get_location();
void test2_player_get_location();

/**
 * @test Test location setting
 * @pre Pointer to player
 * @pre New location to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_player_set_location();
void test2_player_set_location();

/**
 * @test Test objects obtaining
 * @pre Pointer to player
 * @post Non negative int
 */
void test1_player_get_objects();
void test2_player_get_objects();

/**
 * @test Test objects obtaining
 * @pre Pointer to player
 * @post Non negative int
 */
void test1_player_add_object();
void test2_player_add_object();

/**
 * @test Test objects obtaining
 * @pre Pointer to player
 * @post Non negative int
 */
void test1_player_del_object();
void test2_player_del_object();

/**
 * @test Test objects obtaining
 * @pre Pointer to player
 * @post Non negative int
 */
void test1_player_find_object();
void test2_player_find_object();

/**
 * @test Test health getting
 * @pre Pointer to player
 * @post Non negative int
 */
void test1_player_get_strength();
void test2_player_get_strength();

/**
 * @test Test health setting
 * @pre Pointer to player
 * @pre new strength to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_player_set_strength();
void test2_player_set_strength();


/**
 * @test Test followers obtaining
 * @pre Pointer to player
 * @post a set of followers
 */
void test1_player_get_followers();
void test2_player_get_followers();
#endif
