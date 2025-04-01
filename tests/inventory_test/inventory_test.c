/**
 * @brief It tests the inventory module
 * @file inventory_tets.c
 * @author Álvaro Rodríguez 
 * @version 1
 * @date 24-03-2025
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "test.h"
 #include "inventory.h"
 #include "inventory_test.h"
 
 #define MAX_TESTS 20
 
  /** 
   * @brief Main function for Inventory unit tests. 
   * 
   * You may execute ALL or a SINGLE test
   *   1.- No parameter -> ALL test are executed 
   *   2.- A number means a particular test (the one identified by that number) 
   *       is executed
   *  
   */
 int main(int argc, char** argv){
   int test = 0;
   int all = 1;
 
   if (argc < 2) {
     printf("Running all test for module Set:\n");
   } else {
     test = atoi(argv[1]);
     all = 0;
     printf("Running test %d:\t", test);
     if (test < 1 && test > MAX_TESTS) {
       printf("Error: unknown test %d\t", test);
       exit(EXIT_SUCCESS);
     }
   }
 
 
   if (all || test == 1) test1_inventory_create();
   if (all || test == 2) test2_inventory_create();
   if (all || test == 3) test1_inventory_destroy();
   if (all || test == 4) test2_inventory_destroy();
   if (all || test == 5) test1_inventory_is_empty();
   if (all || test == 6) test2_inventory_is_empty();
   if (all || test == 7) test1_inventory_is_full();
   if (all || test == 8) test2_inventory_is_full();
   if (all || test == 9) test1_inventory_add_object();
   if (all || test == 10) test2_inventory_add_object();
   if (all || test == 11) test1_inventory_del_object();
   if (all || test == 12) test2_inventory_del_object();
   if (all || test == 13) test1_inventory_find_object();
   if (all || test == 14) test2_inventory_find_object();
   if (all || test == 15) test1_inventory_set_max_objects();
   if (all || test == 16) test2_inventory_set_max_objects();
   if (all || test == 17) test1_inventory_get_max_objects();
   if (all || test == 18) test2_inventory_get_max_objects();
   if (all || test == 19) test1_inventory_get_objects();
   if (all || test == 20) test2_inventory_get_objects();
 
   PRINT_PASSED_PERCENTAGE;
 
   return 1;
   }

void test1_inventory_create(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(i != NULL);
    inventory_destroy(i);
}
void test2_inventory_create(){
    Inventory *i=NULL;
    PRINT_TEST_RESULT(i == NULL);
}
void test1_inventory_destroy(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_destroy(i)==OK);
}
void test2_inventory_destroy(){
    Inventory *i=NULL;
    i=inventory_create();
    inventory_destroy(i);
    PRINT_TEST_RESULT(i!=NULL);
}
void test1_inventory_is_empty(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_is_empty(i)==TRUE);
    inventory_destroy(i);
}
void test2_inventory_is_empty(){
    Inventory *i=NULL;
    i=inventory_create();
    inventory_add_object(i,10);
    PRINT_TEST_RESULT(inventory_is_empty(i)==FALSE);
    inventory_destroy(i);
}
void test1_inventory_is_full(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_is_full(i)==FALSE);
    inventory_destroy(i);
}
void test2_inventory_is_full(){
    Inventory *i=NULL;
    int j=0;
    i=inventory_create();
    for ( j = 0; j < MAX_INVENTORY_OBJS; j++)
    {
        inventory_add_object(i,j);
    }
    PRINT_TEST_RESULT(inventory_is_full(i)==TRUE);
    inventory_destroy(i);
}
void test1_inventory_add_object(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_add_object(i,10)==OK);
    inventory_destroy(i);
}
void test2_inventory_add_object(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_add_object(i,NO_ID)==ERROR);
    inventory_destroy(i);
}
void test1_inventory_del_object(){
    Inventory *i=NULL;
    i=inventory_create();
    inventory_add_object(i,10);
    PRINT_TEST_RESULT(inventory_del_object(i,10)==OK);
    inventory_destroy(i);
}
void test2_inventory_del_object(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_del_object(i,NO_ID)==ERROR);
    inventory_destroy(i);
}
void test1_inventory_find_object(){
    Inventory *i=NULL;
    i=inventory_create();
    inventory_add_object(i,10);
    PRINT_TEST_RESULT(inventory_find_object(i,10)==TRUE);
    inventory_destroy(i);
}
void test2_inventory_find_object(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_find_object(i,10)==FALSE);
    inventory_destroy(i);
}
void test1_inventory_set_max_objects(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_set_max_objects(i,10)==OK);
    inventory_destroy(i);
}
void test2_inventory_set_max_objects(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_set_max_objects(i,-1)==ERROR);
    inventory_destroy(i);
}
void test1_inventory_get_max_objects(){
    Inventory *i=NULL;
    i=inventory_create();
    PRINT_TEST_RESULT(inventory_get_max_objects(i)==MAX_INVENTORY_OBJS);
    inventory_destroy(i);
}
void test2_inventory_get_max_objects(){
    Inventory *i=NULL;
    PRINT_TEST_RESULT(inventory_get_max_objects(i)==-1);
}
void test1_inventory_get_objects(){
    Inventory *i=NULL;
    i=inventory_create();
    inventory_add_object(i,10);
    PRINT_TEST_RESULT(inventory_get_objects(i)!=NULL);
    inventory_destroy(i);
}
void test2_inventory_get_objects(){
    Inventory *i=NULL;
    PRINT_TEST_RESULT(inventory_get_objects(i)==NULL);

}