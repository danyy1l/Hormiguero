/**
 * @brief It declares the tests for th object module
 * @file object_test.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 1
 * @date 25-03-2024
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H



/**
 * @test Creates an object
 * @pre a number id for the new object
 * @post NULL pointer to set
 */
void test1_object_create();

/**
 * @test Crea un objeto
 * @pre a number id = NO_ID
 * @post NULL pointer to set                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
 */
void test2_object_create();

/**
 * @test Destroys an obejct
 * @pre a pointer to object
 * @post Output==OK
 */
void test1_object_destroy();

/**
 * @test Destroys an obejct
 * @pre a pointer to object=NULL
 * @post Output==ERROR
 */
void test2_object_destroy();


/**
 * @test Sets an object id
 * @pre a pointer to object
 * @pre a number id
 * @post Output==OK
 */
void test1_object_set_id();

/**
 * @test Sets an object id
 * @pre a pointer to object=NULL
 * @pre a number id
 * @post Output==ERROR
 */
void test2_object_set_id();

/**
 * @test Sets an object id
 * @pre a pointer to object
 * @pre a number id=NO_ID
 * @post Output==ERROR
 */
void test3_object_set_id();


/**
 * @test Obtains an id object
 * @pre a pointer to object
 * @post a non NULL id object
 */
void test1_object_get_id();

/**
 * @test Obtains an id object
 * @pre a pointer to object=NULL
 * @post a NULL id object
 */
void test2_object_get_id();

/**
 * @test Set a name for an object
 * @pre a pointer object
 * @pre char name
 * @post Output==OK
 */
void test1_object_set_name();

/**
 * @test Set a name for an object
 * @pre a pointer object=NULL
 * @pre char name
 * @post Output==ERROR
 */
void test2_object_set_name();

/**
 * @test Set a name for an object
 * @pre a pointer object
 * @pre char name=NULL
 * @post Output==ERROR
 */
void test3_object_set_name();

/**
 * @test Obtains a name for an object
 * @pre a pointer to objrct
 * @post a non NULL char name
 */
void test1_object_get_name();

/**
 * @test Obtains a name for an object
 * @pre a pointer to object=NULL
 * @post NULL char name
 */
void test2_object_get_name();

/**
 * @test Set a location for the obejct
 * @pre a pointer to object
 * @pre an object id
 * @post Output==OK
 */
void test1_object_set_location();

/**
 * @test Set a location for the obejct
 * @pre a pointer to object=NULL
 * @pre an object id
 * @post Output==ERROR
 */
void test2_object_set_location();

/**
 * @test Set a location for the obejct
 * @pre a pointer to object
 * @pre an object id=NO_ID
 * @post Output==ERROR
 */
void test3_object_set_location();

/**
 * @test Obtains the location for an object
 * @pre a pointer to object
 * @post a non negative id
 */
void test1_object_get_location();

/**
 * @test Obtains the location for an object
 * @pre a pointer to object
 * @post a negative id
 */
void test2_object_get_location();

/**
 * @test Set a description for the object
 * @pre a pointer to object
 * @pre a char description
 * @post Output==OK
 */
void test1_object_set_description();

/**
 * @test Set a description for the object
 * @pre a pointer to object=NULL
 * @pre a char description
 * @post Output==ERROR
 */
void test2_object_set_description();

/**
 * @test Set a description for the object
 * @pre a pointer to object
 * @pre a char description=NULL
 * @post Output==ERROR
 */
void test3_object_set_description();

/**
 * @test Obtain the description for the object
 * @pre a pointer to object
 * @pre a char decription
 * @post a non NULL char description
 */
void test1_object_get_description();

/**
 * @test Obtain the description for the object
 * @pre a pointer to object=NULL
 * @pre a char description
 * @post a NULL char description
 */
void test2_object_get_description();

/**
 * @test Set a description for the object
 * @pre a pointer to object
 * @post Output==OK
 */
void test1_object_set_taken();

/**
 * @test Set a description for the object
 * @pre a pointer to object = NULL
 * @post Output==ERROR
 */
void test2_object_set_taken();

/**
 * @test Obtain whether is taken the object
 * @pre a pointer to non NULL object
 * @pre Sets true to object->taken
 * @post a TRUE Bool
 */
void test1_object_get_taken();

/**
 * @test Obtain whether is taken the object
 * @pre a pointer to object=NULL
 * @post a FALSE booleean
 */
void test2_object_get_taken();

#endif
