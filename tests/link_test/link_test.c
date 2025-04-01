/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Danyyil Shykerynets
 * @version 0.0 
 * @date 24-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#include "test.h"
#include "link.h"
#include "link_test.h"
 
#define MAX_TESTS 31
 
/** 
 * @brief Main function for LINK unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Character:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }
  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test1_link_set_id();
  if (all || test == 4) test2_link_set_id();
  if (all || test == 5) test3_link_set_id();
  if (all || test == 6) test1_link_get_id();
  if (all || test == 7) test2_link_get_id();
  if (all || test == 8) test1_link_set_name();
  if (all || test == 9) test2_link_set_name();
  if (all || test == 10) test3_link_set_name();
  if (all || test == 11) test1_link_get_name();
  if (all || test == 12) test2_link_get_name();
  if (all || test == 13) test1_link_set_origin();
  if (all || test == 14) test2_link_set_origin();
  if (all || test == 15) test3_link_set_origin();
  if (all || test == 16) test1_link_get_origin();
  if (all || test == 17) test2_link_get_origin();
  if (all || test == 18) test1_link_set_destination();
  if (all || test == 19) test2_link_set_destination();
  if (all || test == 20) test3_link_set_destination();
  if (all || test == 21) test1_link_get_destination();
  if (all || test == 22) test2_link_get_destination();
  if (all || test == 23) test1_link_set_direction();
  if (all || test == 24) test2_link_set_direction();
  if (all || test == 25) test3_link_set_direction();
  if (all || test == 26) test1_link_get_direction();
  if (all || test == 27) test2_link_get_direction();
  if (all || test == 28) test1_link_set_open();
  if (all || test == 29) test2_link_set_open();
  if (all || test == 30) test1_link_get_open();
  if (all || test == 31) test2_link_get_open();
  PRINT_PASSED_PERCENTAGE;

  return 1;
  
}

void test1_link_create(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_get_id(s)==NO_ID);
    link_destroy(s);
}

void test2_link_create(){
    int result;
    Link *s;
    s=link_create();
    result=s!=NULL;
    PRINT_TEST_RESULT(result);
    link_destroy(s);
}

void test1_link_set_id(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_id(s,1)==OK);
    link_destroy(s);
}

void test2_link_set_id(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_set_id(s,1)==ERROR);
}

void test3_link_set_id(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_id(s,NO_ID)==ERROR);
    link_destroy(s);
}
void test1_link_get_id(){
    Link *s;
    s=link_create();
    link_set_id(s, 2);
    PRINT_TEST_RESULT(link_get_id(s)==2);
    link_destroy(s);
}

void test2_link_get_id(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_get_id(s)==NO_ID);
}
void test1_link_set_name(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_name(s,"enlace")==OK);
    link_destroy(s);
}

void test2_link_set_name(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_set_name(s,"enlace")==ERROR);
}

void test3_link_set_name(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_name(s,NULL)==ERROR);
    link_destroy(s);
}

void test1_link_get_name(){
    Link *s;
    s=link_create();
    link_set_name(s,"objeto");
    PRINT_TEST_RESULT(strcmp(link_get_name(s),"objeto")==0);
    link_destroy(s);
}

void test2_link_get_name(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_get_name(s)==NULL);
}

void test1_link_set_origin(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_origin(s,1)==OK);
    link_destroy(s);
}

void test2_link_set_origin(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_set_origin(s,1)==ERROR);
}

void test3_link_set_origin(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_origin(s,NO_ID)==ERROR);
    link_destroy(s);
}

void test1_link_get_origin(){
    Link *s;
    s=link_create();
    link_set_origin(s,1);
    PRINT_TEST_RESULT(link_get_origin(s)==1);
    link_destroy(s);
}
void test2_link_get_origin(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_get_origin(s)==NO_ID);
}

void test1_link_set_destination(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_destination(s,2)==OK);
    link_destroy(s);
}

void test2_link_set_destination(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_set_destination(s,2)==ERROR);
}

void test3_link_set_destination(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_destination(s,NO_ID)==ERROR);
    link_destroy(s);
}

void test1_link_get_destination(){
    Link *s;
    s=link_create();
    link_set_destination(s,2);
    PRINT_TEST_RESULT(link_get_destination(s)==2);
    link_destroy(s);
}

void test2_link_get_destination(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_get_destination(s)==NO_ID);
}

void test1_link_set_direction(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_direction(s,N)==OK);
    link_destroy(s);
}

void test2_link_set_direction(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_set_direction(s,S)==ERROR);
}

void test3_link_set_direction(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_direction(s, -1 )==ERROR);
    link_destroy(s);
}

void test1_link_get_direction(){
    Link *s;
    s=link_create();
    link_set_direction(s,N);
    PRINT_TEST_RESULT(link_get_direction(s)==N);
    link_destroy(s);
}

void test2_link_get_direction(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_get_direction(s)==U);
}

void test1_link_set_open(){
    Link *s;
    s=link_create();
    PRINT_TEST_RESULT(link_set_open(s,TRUE)==OK);
    link_destroy(s);
}

void test2_link_set_open(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_set_open(s,TRUE)==ERROR);
}

void test1_link_get_open(){
    Link *s;
    s=link_create();
    link_set_open(s,TRUE);
    PRINT_TEST_RESULT(link_get_open(s)==TRUE);
    link_destroy(s);
}

void test2_link_get_open(){
    Link *s=NULL;
    PRINT_TEST_RESULT(link_get_open(s)==FALSE);
}
