/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Álvaro Rodríguez Hernández
 * @version 3
 * @date 1-04-2025
 * @copyright GNU Public License
 */

 #ifndef SPACE_TEST_H
 #define SPACE_TEST_H
 
 /**
  * @test Test space creation
  * @pre Space ID 
  * @post Non NULL pointer to space 
  */
 void test1_space_create();
 
 /**
  * @test Test space creation
  * @pre Space ID 
  * @post Space_ID == Supplied Space Id
  */
 void test2_space_create();
 
 /**
  * @test Test function for space_name setting
  * @pre String with space name
  * @post Ouput==OK 
  */
 void test1_space_set_name();
 
 /**
  * @test Test function for space_name setting
  * @pre pointer to space = NULL 
  * @post Output==ERROR
  */
 void test2_space_set_name();
 
 /**
  * @test Test function for space_name setting
  * @pre pointer to space_name = NULL (point to space = NON NULL) 
  * @post Output==ERROR
  */
 void test3_space_set_name();

 /**
  * @test Test function for space id setting located at the north
  * @pre A pointer to space
  * @pre A number id 
  * @post Output==OK
  */
 void test1_space_set_north();

 /**
  * @test Test function for space id setting located at the north
  * @pre pointer to space=NULL
  * @pre number id
  * @post Output==ERROR
  */
 void test2_space_set_north();

 /**
  * @test Test function for space id setting located at the north
  * @pre pointer to space
  * @pre number id =NO_ID 
  * @post Output==ERROR
  */
 void test3_space_set_north();

  /**
  * @test Test function for space id setting located at the south
  * @pre A pointer to space
  * @pre A number id 
  * @post Output==OK
  */
 void test1_space_set_south();

  /**
  * @test Test function for space id setting located at the south
  * @pre pointer to space=NULL
  * @pre number id
  * @post Output==ERROR
  */
 void test2_space_set_south();

  /**
  * @test Test function for space id setting located at the south
  * @pre pointer to space
  * @pre number id =NO_ID 
  * @post Output==ERROR
  */
 void test3_space_set_south();

   /**
  * @test Test function for space id setting located at the east
  * @pre A pointer to space
  * @pre A number id 
  * @post Output==OK
  */
 void test1_space_set_east();

   /**
  * @test Test function for space id setting located at the east
  * @pre pointer to space=NULL
  * @pre number id
  * @post Output==ERROR
  */
 void test2_space_set_east();

   /**
  * @test Test function for space id setting located at the east
  * @pre pointer to space
  * @pre number id =NO_ID 
  * @post Output==ERROR
  */
 void test3_space_set_east();

  /**
  * @test Test function for space id setting located at the west
  * @pre A pointer to space
  * @pre A number id 
  * @post Output==OK
  */
 void test1_space_set_west();

  /**
  * @test Test function for space id setting located at the west
  * @pre pointer to space=NULL
  * @pre number id
  * @post Output==ERROR
  */
 void test2_space_set_west();

  /**
  * @test Test function for space id setting located at the west
  * @pre pointer to space=NULL
  * @pre number id
  * @post Output==ERROR
  */
 void test3_space_set_west();

  /**
  * @test Test the gdesc string setting
  * @pre a string name(pointer to space=non NULL)
  * @pre position
  * @post Output==OK
  */
 void test1_space_set_gdesc();

  /**
  * @test Test the gdesc string setting
  * @pre pointer to space=NULL
  * @post Output==ERROR
  */
 void test2_space_set_gdesc();

   /**
  * @test Test the gdesc string setting
  * @pre NULL string
  * @post Output==ERROR
  */
 void test3_space_set_gdesc();

 /**
  * @test Test the object addition
  * @pre pointer to space
  * @pre number id
  * @post Output==OK
  */
 void test1_space_add_object();

 /**
  * @test Test the object addition
  * @pre pointer to space=NULL
  * @pre number id
  * @post Output==ERROR
  */
 void test2_space_add_object();

  /**
  * @test Test the object addition
  * @pre pointer to space
  * @pre number id=NO_ID
  * @post Output==ERROR
  */
 void test3_space_add_object();

  /**
  * @test Test the object removal
  * @pre pointer to space
  * @pre id number
  * @post Output==OK
  */
 void test1_space_del_object();

  /**
  * @test Test the object removal
  * @pre pointer to space=NULL
  * @pre id number
  * @post Output==ERROR
  */
 void test2_space_del_object();

  /**
  * @test Test the object removal
  * @pre pointer to space
  * @pre id number = NO_ID
  * @post Output==ERROR
  */
 void test3_space_del_object();

   /**
  * @test Test the object removal
  * @pre pointer to space = NULL
  * @pre id number = NO_ID
  * @post Output==ERROR
  */
 void test4_space_del_object();

 /**
  * @test Test the id obtaining
  * @pre pointer to space
  * @post non negative ID
  */
 void test1_space_get_id();

 /**
  * @test Test the id obtaining
  * @pre pointer to space=NULL
  * @post a negative ID
  */
 void test2_space_get_id();

 /**
  * @test Test the name obtaining
  * @pre pointer to space
  * @post a string
  */
 void test1_space_get_name();

  /**
  * @test Test the name obtaining
  * @pre pointer to space=NULL
  * @post a string=NULL
  */
 void test2_space_get_name();

  /**
  * @test Test the string obtaining
  * @pre pointer to space
  * @post non NULL string 
  */
 void test1_space_get_gdesc();
 
 /**
  * @test Test the string obtaining
  * @pre pointer to space=NULL
  * @post NULL string
  */
 void test2_space_get_gdesc();

  /**
  * @test Test function for space id obtaining located at the north
  * @pre pointer to space
  * @post non negative id
  */
 void test1_space_get_north();

  /**
  * @test Test function for space id obtaining located at the north
  * @pre pointer to space=NULL
  * @post a negative id 
  */
 void test2_space_get_north();

  /**
  * @test Test function for space id obtaining located at the south
  * @pre pointer to space
  * @post non negative id 
  */
 void test1_space_get_south();

  /**
  * @test Test function for space id obtaining located at the south
  * @pre pointer to space=NULL
  * @post a negative id 
  */
 void test2_space_get_south();

  /**
  * @test Test function for space id obtaining located at the east
  * @pre pointer to space
  * @post non negative id 
  */
 void test1_space_get_east();

  /**
  * @test Test function for space id obtaining located at the east
  * @pre pointer to space=NULL
  * @post a negative id 
  */
 void test2_space_get_east();

  /**
  * @test Test function for space id obtaining located at the west
  * @pre pointer to space
  * @post non negative id 
  */
 void test1_space_get_west();

  /**
  * @test Test function for space id obtaining located at the west
  * @pre pointer to space=NULL
  * @post a negative id 
  */
 void test2_space_get_west();

  /**
  * @test Test function for space get set objects
  * @pre pointer to space
  * @post a set != NULL
  */
 void test1_space_get_set_objects();
  /**
  * @test Test function for space get set objects
  * @pre pointer to space=NULL
  * @post a set == NULL
  */
 void test2_space_get_set_objects();
  /**
  * @test Test function for space get discovered
  * @pre pointer to space
  * @post a bool=TRUE
  */
 void test1_space_get_discovered();
  /**
  * @test Test function for space get discovered
  * @pre pointer to space=NULL
  * @post a bool=FALSE
  */
 void test2_space_get_discovered();
  /**
  * @test Test function for space set discovered
  * @pre pointer to space
  * @post a status=OK
  */
 void test1_space_set_discovered();
  /**
  * @test Test function for space set discovered
  * @pre pointer to space=NULL
  * @post a status=ERROR
  */
 void test2_space_set_discovered();

 #endif
