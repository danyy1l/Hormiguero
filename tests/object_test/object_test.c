/** 
 * @brief It tests character module
 * 
 * @file character_test.c
 * @author Danyyil Shykerynets
 * @version 0.0 
 * @date 24-02-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 
 #include "test.h"
 #include "object.h"
 #include "object_test.h"
 
 #define MAX_TESTS 26
 
 /** 
  * @brief Main function for CHARACTER unit tests. 
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

   if (all || test == 1) test1_object_create();
   if (all || test == 2) test2_object_create();
   if (all || test == 3) test1_object_set_id();
   if (all || test == 4) test2_object_set_id();
   if (all || test == 5) test3_object_set_id();
   if (all || test == 6) test1_object_get_id();
   if (all || test == 7) test2_object_get_id();
   if (all || test == 8) test1_object_set_name();
   if (all || test == 9) test2_object_set_name();
   if (all || test == 10) test3_object_set_name();
   if (all || test == 11) test1_object_get_name();
   if (all || test == 12) test2_object_get_name();
   if (all || test == 13) test1_object_set_location();
   if (all || test == 14) test2_object_set_location();
   if (all || test == 15) test3_object_set_location();
   if (all || test == 16) test1_object_get_location();
   if (all || test == 17) test2_object_get_location();
   if (all || test == 18) test1_object_set_description();
   if (all || test == 19) test2_object_set_description();
   if (all || test == 20) test3_object_set_description();
   if (all || test == 21) test1_object_get_description();
   if (all || test == 22) test2_object_get_description();
   if (all || test == 23) test1_object_set_taken();
   if (all || test == 24) test2_object_set_taken();
   if (all || test == 25) test1_object_get_taken();
   if (all || test == 26) test2_object_get_taken();

   PRINT_PASSED_PERCENTAGE;
 
   return 1;
   
 }

void test1_object_create(){
    Object *s;
    s=object_create(10);
    PRINT_TEST_RESULT(object_get_id(s)==10);
    object_destroy(s);
}

void test2_object_create(){
    int result;
    Object *s;
    s=object_create(10);
    result=s!=NULL;
    PRINT_TEST_RESULT(result);
    object_destroy(s);
}

void test1_object_set_id(){
    Object *s;
    s=object_create(20);
    PRINT_TEST_RESULT(object_set_id(s,20)==OK);
    object_destroy(s);
}

void test2_object_set_id(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_set_id(s,20)==ERROR);
}

void test3_object_set_id(){
    Object *s;
    s=object_create(20);
    PRINT_TEST_RESULT(object_set_id(s,NO_ID)==ERROR);
    object_destroy(s);
}
void test1_object_get_id(){
    Object *s;
    s=object_create(30);
    PRINT_TEST_RESULT(object_get_id(s)==30);
    object_destroy(s);
}

void test2_object_get_id(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_get_id(s)==NO_ID);
}
void test1_object_set_name(){
    Object *s;
    s=object_create(40);
    PRINT_TEST_RESULT(object_set_name(s,"objeto")==OK);
    object_destroy(s);
}

void test2_object_set_name(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_set_name(s,"objeto")==ERROR);
}

void test3_object_set_name(){
    Object *s;
    s=object_create(40);
    PRINT_TEST_RESULT(object_set_name(s,NULL)==ERROR);
    object_destroy(s);
}

void test1_object_get_name(){
    Object *s;
    s=object_create(50);
    object_set_name(s,"objeto");
    PRINT_TEST_RESULT(strcmp(object_get_name(s),"objeto")==0);
    object_destroy(s);
}

void test2_object_get_name(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_get_name(s)==NULL);
}

void test1_object_set_location(){
    Object *s;
    s=object_create(60);
    PRINT_TEST_RESULT(object_set_location(s,60)==OK);
    object_destroy(s);
}

void test2_object_set_location(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_set_location(s,60)==ERROR);
}

void test3_object_set_location(){
    Object *s;
    s=object_create(60);
    PRINT_TEST_RESULT(object_set_location(s,NO_ID)==ERROR);
    object_destroy(s);
}

void test1_object_get_location(){
    Object *s;
    s=object_create(70);
    object_set_location(s,70);
    PRINT_TEST_RESULT(object_get_location(s)==70);
    object_destroy(s);
}
void test2_object_get_location(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_get_location(s)==-1);
}

void test1_object_set_description(){
    Object *s;
    s=object_create(80);
    PRINT_TEST_RESULT(object_set_description(s,"hola")==OK);
    object_destroy(s);
}

void test2_object_set_description(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_set_description(s,"hola")==ERROR);
}

void test3_object_set_description(){
    Object *s;
    s=object_create(80);
    PRINT_TEST_RESULT(object_set_description(s,NULL)==ERROR);
    object_destroy(s);
}

void test1_object_get_description(){
    Object *s;
    s=object_create(90);
    object_set_description(s,"objeto");
    PRINT_TEST_RESULT(strcmp(object_get_description(s),"objeto")==0);
    object_destroy(s);
}

void test2_object_get_description(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_get_description(s)==NULL);
}

void test1_object_set_taken(){
    Object *s;
    s=object_create(80);
    PRINT_TEST_RESULT(object_set_taken(s,TRUE)==OK);
    object_destroy(s);
}

void test2_object_set_taken(){
    Object *s=NULL;
    PRINT_TEST_RESULT(object_set_taken(s,TRUE)==ERROR);
}

void test1_object_get_taken(){
    Object *s;
    s=object_create(100);
    object_set_taken(s, TRUE);
    PRINT_TEST_RESULT(object_get_taken(s) == TRUE);
    object_destroy(s);
}

void test2_object_get_taken(){
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_taken(s) == FALSE);
}