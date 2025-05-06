/**
 * @brief It declares the tests for the character module
 * 
 * @file character_test.h
 * @author Álvaro Rodríguez
 * @version 2.0
 * @date 21-04-2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

/**
 * @test Test character creation
 * @post Non NULL pointer to character 
 */
void test1_character_create();
void test2_character_create();

/**
 * @test Test id obtaining
 * @pre Pointer to character
 * @post Non negative ID of character 
 */
void test1_character_get_id();
void test2_character_get_id();

/**
 * @test Test id setting
 * @pre Pointer to character
 * @pre New ID to set 
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_id();
void test2_character_set_id();
void test3_character_set_id();

/**
 * @test Test name obtaining
 * @pre Pointer to character
 * @post Non NULL string
 */
void test1_character_get_name();
void test2_character_get_name();

/**
 * @test Test name setting
 * @pre Pointer to character
 * @pre New name to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_name();
void test2_character_set_name();
void test3_character_set_name();

/**
 * @test Test gdesc obtaining
 * @pre Pointer to character
 * @post Non NULL string
 */
void test1_character_get_gdesc();
void test2_character_get_gdesc();

/**
 * @test Test gdesc setting
 * @pre Pointer to character
 * @pre New gdesc to set 
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_gdesc();
void test2_character_set_gdesc();
void test3_character_set_gdesc();

/**
 * @test Test health obtaining
 * @pre Pointer to character
 * @post Non negative int
 */
void test1_character_get_health();
void test2_character_get_health();

/**
 * @test Test health setting
 * @pre Pointer to character
 * @pre New health to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_health();
void test2_character_set_health();

/**
 * @test Test friendliness obtaining
 * @pre Pointer to character
 * @post Boolean
 */
void test1_character_get_friendly();
void test2_character_get_friendly();

/**
 * @test Test friendliness setting
 * @pre Pointer to character
 * @pre New boolean to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_friendly();
void test2_character_set_friendly();

/**
 * @test Test message obtaining
 * @pre Pointer to character
 * @post Non NULL string 
 */
void test1_character_get_message();
void test2_character_get_message();

/**
 * @test Test message setting
 * @pre Pointer to character
 * @pre New message to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_message();
void test2_character_set_message();
void test3_character_set_message();

/**
 * @test Test location obtaining
 * @pre Pointer to character
 * @post Non negative ID 
 */
void test1_character_get_location();
void test2_character_get_location();

/**
 * @test Test location setting
 * @pre Pointer to character
 * @pre New location to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_location();
void test2_character_set_location();
/**
 * @test Test strength get
 * @pre Pointer to character
 * @post int whit the strength or -1 in case of error 
 */
void test1_character_get_strength();
void test2_character_get_strength();
/**
 * @test Test strength setting
 * @pre Pointer to character
 * @pre New strength to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_strength();
void test2_character_set_strength();
/**
 * @test Test following get
 * @pre Pointer to character
 * @post id whit the following or no in case of error 
 */
void test1_character_get_following();
void test2_character_get_following();
/**
 * @test Test following setting
 * @pre Pointer to character
 * @pre New following to set
 * @post Status command, OK if triumph, ERROR otherwise 
 */
void test1_character_set_following();
void test2_character_set_following();

#endif