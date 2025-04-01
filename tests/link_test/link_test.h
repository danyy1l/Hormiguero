/**
 * @brief It declares the tests for th link module
 * @file link_test.h
 * @author Danyyil Shykerynets
 * @version 1
 * @date 01-04-2024
 * @copyright GNU Public License
 */

#ifndef link_TEST_H
#define link_TEST_H

/*TO DO: REVISAR DOCUMENTACION*/

/**
 * @test Creates an link
 * @pre a number id for the new link
 * @post NULL pointer to set
 */
void test1_link_create();

/**
 * @test Crea un objeto
 * @pre a number id = NO_ID
 * @post NULL pointer to set                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
 */
void test2_link_create();

/**
 * @test Sets an link id
 * @pre a pointer to link
 * @pre a number id
 * @post Output==OK
 */
void test1_link_set_id();

/**
 * @test Sets an link id
 * @pre a pointer to link=NULL
 * @pre a number id
 * @post Output==ERROR
 */
void test2_link_set_id();

/**
 * @test Sets an link id
 * @pre a pointer to link
 * @pre a number id=NO_ID
 * @post Output==ERROR
 */
void test3_link_set_id();


/**
 * @test Obtains an id link
 * @pre a pointer to link
 * @post a non NULL id link
 */
void test1_link_get_id();

/**
 * @test Obtains an id link
 * @pre a pointer to link=NULL
 * @post a NULL id link
 */
void test2_link_get_id();

/**
 * @test Set a name for an link
 * @pre a pointer link
 * @pre char name
 * @post Output==OK
 */
void test1_link_set_name();

/**
 * @test Set a name for an link
 * @pre a pointer link=NULL
 * @pre char name
 * @post Output==ERROR
 */
void test2_link_set_name();

/**
 * @test Set a name for an link
 * @pre a pointer link
 * @pre char name=NULL
 * @post Output==ERROR
 */
void test3_link_set_name();

/**
 * @test Obtains a name for an link
 * @pre a pointer to objrct
 * @post a non NULL char name
 */
void test1_link_get_name();

/**
 * @test Obtains a name for an link
 * @pre a pointer to link=NULL
 * @post NULL char name
 */
void test2_link_get_name();

/**
 * @test Set a origin for the link
 * @pre a pointer to link
 * @pre an link id
 * @post Output==OK
 */
void test1_link_set_origin();

/**
 * @test Set a origin for the link
 * @pre a pointer to link=NULL
 * @pre an link id
 * @post Output==ERROR
 */
void test2_link_set_origin();

/**
 * @test Set a origin for the link
 * @pre a pointer to link
 * @pre an link id=NO_ID
 * @post Output==ERROR
 */
void test3_link_set_origin();

/**
 * @test Obtains the origin for an link
 * @pre a pointer to link
 * @post a non negative id
 */
void test1_link_get_origin();

/**
 * @test Obtains the origin for an link
 * @pre a pointer to link
 * @post a negative id
 */
void test2_link_get_origin();

/**
 * @test Set a destination for the link
 * @pre a pointer to link
 * @pre an ID destination
 * @post Output==OK
 */
void test1_link_set_destination();

/**
 * @test Set a destination for the link
 * @pre a pointer to link=NULL
 * @pre an ID destination
 * @post Output==ERROR
 */
void test2_link_set_destination();

/**
 * @test Set a destination for the link
 * @pre a pointer to link
 * @pre a NO_ID destination
 * @post Output==ERROR
 */
void test3_link_set_destination();

/**
 * @test Obtain the destination for the link
 * @pre a pointer to link
 * @post a non NULL char destination
 */
void test1_link_get_destination();

/**
 * @test Obtain the destination for the link
 * @pre a pointer to link=NULL
 * @pre a char destination
 * @post a NULL char destination
 */
void test2_link_get_destination();

/**
 * @test Set a direction for the link
 * @pre a pointer to link
 * @pre a char direction
 * @post Output==OK
 */
void test1_link_set_direction();

/**
 * @test Set a direction for the link
 * @pre a pointer to link=NULL
 * @pre a char direction
 * @post Output==ERROR
 */
void test2_link_set_direction();

/**
 * @test Set a direction for the link
 * @pre a pointer to link
 * @pre a char direction=NULL
 * @post Output==ERROR
 */
void test3_link_set_direction();

/**
 * @test Obtain the direction for the link
 * @pre a pointer to link
 * @pre a char direction
 * @post a non NULL char direction
 */
void test1_link_get_direction();

/**
 * @test Obtain the direction for the link
 * @pre a pointer to link=NULL
 * @pre a char direction
 * @post a NULL char direction
 */
void test2_link_get_direction();

/**
 * @test Set a direction for the link
 * @pre a pointer to link
 * @pre a char direction
 * @post Output==OK
 */
void test1_link_set_open();

/**
 * @test Set a open for the link
 * @pre a pointer to link=NULL
 * @pre a char open
 * @post Output==ERROR
 */
void test2_link_set_open();

/**
 * @test Obtain the open for the link
 * @pre a pointer to link
 * @pre a char open
 * @post a non NULL char open
 */
void test1_link_get_open();

/**
 * @test Obtain the open for the link
 * @pre a pointer to link=NULL
 * @pre a char open
 * @post a NULL char open
 */
void test2_link_get_open();

#endif
