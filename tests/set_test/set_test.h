/**
 * @brief It declares the tests for th set module
 * @file set_test.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 1
 * @date 28-02-2024
 * @copyright GNU Public License
 */

 #ifndef SET_TEST_H
 #define SET_TEST_H
 

/**
 * @test Tests the set creation
 * @post Non NULL pointer to set
 */
void test1_set_create();
/**
 * @test Tests the set creation
 * @post A pointer to set
 */
void test2_set_create();

/**
 * @test Test the nids obtaining
 * @pre A pointer to space
 * @post The number of ids
 */
void test1_set_get_nids();

/**
 * @test Test the nids obtaining
 * @pre A pointer to space = NULL
 * @post Non negative int
 */
void test2_set_get_nids();

/**
 * @test Test the nids setting
 * @pre A pointer to space
 * @pre A number of ids
 * @post Output==OK
 */
void test1_set_set_nids();

/**
 * @test Test the nids obtaining
 * @pre A pointer to space=NULL
 * @post Output==ERROR
 */
void test2_set_set_nids();

/**
 * @test Test the value addition
 * @pre A pointer to set
 * @pre A number ID
 * @post Output==OK
 */
void test1_set_add_value();
/** 
 * @test Test the value addition
 * @pre A pointer to set = NULL
 * @post Output==ERROR
*/
void test2_set_add_value();

/** 
 * @test Test the value addition
 * @pre A number ID = NO_ID
 * @post Output==ERROR
*/
void test3_set_add_value();
/** 
 * @test Test the value removal
 * @pre A pointer to set 
 * @pre A number ID
 * @post Output==OK
*/
void test1_set_del_value();
/** 
 * @test Test the value removal
 * @pre A pointer to set = NULL 
 * @post Output==ERROR
*/
void test2_set_del_value();
/** 
 * @test Test the value removal
 * @pre A number ID = NO_ID
 * @post Output==ERROR
*/
void test3_set_del_value();

/**
 * @test It tests the search for the object
 * @pre A pointer to set
 * @pre A number ID
 * @post Output==TRUE
 */
void test1_set_find_object();

/**
 * @test It tests the search for the object
 * @pre A pointer to set = NULL
 * @post Output==FALSE
 */
void test2_set_find_object();

/**
 * @test It tests the search for the object
 * @pre A number ID = NO_ID
 * @post Output==FALSE
 */
void test3_set_find_object();

/**
 * @test Test the id setting
 * @pre A pointer to set
 * @pre A pointer to set
 * @post Output != NULL
 */
void test1_set_id_object();

/**
 * @test Test the id setting
 * @pre A pointer to set = NULL
 * @post Output==NULL
 */
void test2_set_id_object();

#endif