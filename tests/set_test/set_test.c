/**
 * @brief It tests the set module
 * @file set_test.c
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 1
 * @date 28-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "set.h"
#include "set_test.h"

#define MAX_TESTS 17

 /** 
  * @brief Main function for SET unit tests. 
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


  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test1_set_get_nids();
  if (all || test == 4) test2_set_get_nids();
  if (all || test == 5) test1_set_set_nids();
  if (all || test == 6) test2_set_set_nids();
  if (all || test == 7) test1_set_add_value();
  if (all || test == 8) test2_set_add_value();
  if (all || test == 9) test3_set_add_value();
  if (all || test == 10) test1_set_del_value();
  if (all || test == 11) test2_set_del_value();
  if (all || test == 12) test3_set_del_value();
  if (all || test == 13) test1_set_find_object();
  if (all || test == 14) test2_set_find_object();
  if (all || test == 15) test3_set_find_object();
  if (all || test == 16) test1_set_id_object();
  if (all || test == 17) test2_set_id_object();

  PRINT_PASSED_PERCENTAGE;

  return 1;
  }
  void test1_set_create(){
    int result;
    Set *s;
    s=set_create();
    result=s!=NULL ;
    PRINT_TEST_RESULT(result);
    set_destroy(s);
  }

  void test2_set_create(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(s != NULL);
    set_destroy(s);
  }

  void test1_set_get_nids(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(set_get_nids(s)==0);
    set_destroy(s);
  }

  void test2_set_get_nids(){
    Set *s=NULL;
    PRINT_TEST_RESULT(set_get_nids(s)==-1);
  }

  void test1_set_set_nids(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(set_set_nids(s,10)==OK);
    set_destroy(s);
  }

  void test2_set_set_nids(){
    Set *s=NULL;
    PRINT_TEST_RESULT(set_set_nids(s,10)==ERROR);
  }
  
  void test1_set_add_value(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(set_add_value(s,20)==OK);
    set_destroy(s);
  }
  void test2_set_add_value(){
    Set *s=NULL;
    PRINT_TEST_RESULT(set_add_value(s,20)==ERROR);
  }

  void test3_set_add_value(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(set_add_value(s,NO_ID)==ERROR);
    set_destroy(s);
  }

  void test1_set_del_value(){
    Set *s;
    s=set_create();
    set_add_value(s,20);
    PRINT_TEST_RESULT(set_del_value(s,20)==OK);
    set_destroy(s);
  }

  void test2_set_del_value(){
    Set *s=NULL; 
    PRINT_TEST_RESULT(set_del_value(s,20)==ERROR);
  }

  void test3_set_del_value(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(set_del_value(s,NO_ID)==ERROR);
    set_destroy(s);
  }
  void test1_set_find_object(){
    Set *s;
    s=set_create();
    set_add_value(s, 10);
    PRINT_TEST_RESULT(set_find_object(s,10)==TRUE);
    set_destroy(s);
  }
  
  void test2_set_find_object(){
    Set *s=NULL;
    PRINT_TEST_RESULT(set_find_object(s,10)==FALSE);
  }

  void test3_set_find_object(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(set_find_object(s,NO_ID)==FALSE);
    set_destroy(s);
  }

  void test1_set_id_object(){
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(set_id_object(s)!=NULL);
    set_destroy(s);
  }

  void test2_set_id_object(){
    Set *s=NULL;
    PRINT_TEST_RESULT(set_id_object(s)==NULL);
  }
 
