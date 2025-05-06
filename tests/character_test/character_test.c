/** 
 * @brief It tests character module
 * 
 * @file character_test.c
 * @author Álvaro Rodríguez
 * @version 2.0 
 * @date 21-04-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include "character.h"
 #include "character_test.h"
 #include "test.h"
 
 #define MAX_TESTS 42
 
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
 
 
   if (all || test == 1) test1_character_create();
   if (all || test == 2) test2_character_create();
   if (all || test == 3) test1_character_get_id();
   if (all || test == 4) test2_character_get_id();
   if (all || test == 5) test1_character_set_id();
   if (all || test == 6) test2_character_set_id();
   if (all || test == 7) test3_character_set_id();
   if (all || test == 8) test1_character_get_name();
   if (all || test == 9) test2_character_get_name();
   if (all || test == 10) test1_character_set_name();
   if (all || test == 11) test2_character_set_name();
   if (all || test == 12) test3_character_set_name();
   if (all || test == 13) test1_character_get_gdesc();
   if (all || test == 14) test2_character_get_gdesc();
   if (all || test == 15) test1_character_set_gdesc();
   if (all || test == 16) test2_character_set_gdesc();
   if (all || test == 17) test3_character_set_gdesc();
   if (all || test == 18) test1_character_get_health();
   if (all || test == 19) test2_character_get_health();
   if (all || test == 20) test1_character_set_health();
   if (all || test == 21) test2_character_set_health();
   if (all || test == 22) test1_character_get_friendly();
   if (all || test == 23) test2_character_get_friendly();
   if (all || test == 24) test1_character_set_friendly();
   if (all || test == 25) test2_character_set_friendly();
   if (all || test == 26) test1_character_get_message();
   if (all || test == 27) test2_character_get_message();
   if (all || test == 28) test1_character_set_message();
   if (all || test == 29) test2_character_set_message();
   if (all || test == 30) test3_character_set_message();
   if (all || test == 31) test1_character_get_location();
   if (all || test == 32) test2_character_get_location();
   if (all || test == 33) test1_character_set_location();
   if (all || test == 34) test2_character_set_location();
   if (all || test == 35) test1_character_get_strength();
   if (all || test == 36) test2_character_get_strength();
   if (all || test == 37) test1_character_set_strength();
   if (all || test == 38) test2_character_set_strength();
   if (all || test == 39) test1_character_get_following();
   if (all || test == 40) test2_character_get_following();
   if (all || test == 41) test1_character_set_following();
   if (all || test == 42) test2_character_set_following();
   PRINT_PASSED_PERCENTAGE;
 
   return 1;
 }
 
 void test1_character_create() {
   int result;
   Character *s;
   s = character_create();
   result=s!=NULL ;
   PRINT_TEST_RESULT(result);
   character_destroy(s);
 }
 
 void test2_character_create() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_get_id(s));
   character_destroy(s);
 }
 
 void test1_character_get_id() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_get_id(s) == NO_ID);
   character_destroy(s);
 }
 
 void test2_character_get_id() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_get_id(s) == NO_ID);
 }
 
 void test1_character_set_id() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_set_id(s, NO_ID) == ERROR);
   character_destroy(s);
 }
 
 void test2_character_set_id(){
  Character *s;
  s= character_create();
  PRINT_TEST_RESULT(character_set_id(s, 30) == OK);
  character_destroy(s);
 }

 void test3_character_set_id() {
  Character *s = NULL;
  PRINT_TEST_RESULT(character_set_id(s, 30) == ERROR);
}

 void test1_character_get_name() {
   Character *s;
   s = character_create();
   character_set_name(s, "Dani");
   PRINT_TEST_RESULT(character_get_name(s) != NULL);
   character_destroy(s);
 }
 
 void test2_character_get_name() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_get_name(s) == ERROR);
 }
 
 void test1_character_set_name() {
   Character *s;
   s = character_create();
   character_set_name(s, "Daniel");
   PRINT_TEST_RESULT(strcmp(character_get_name(s), "Daniel") == 0);
   character_destroy(s);
 }
 
 void test2_character_set_name() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_set_name(s, "Adios") == ERROR);
 }
 
 void test3_character_set_name(){
  Character* s;
  s = character_create();
  PRINT_TEST_RESULT(character_set_name(s, NULL) == ERROR);
  character_destroy(s);
 }

 void test1_character_get_gdesc() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_get_gdesc(s) != NULL);
   character_destroy(s);
 }
 
 void test2_character_get_gdesc() {
   Character *s = NULL;
   PRINT_TEST_RESULT(strcmp(character_get_gdesc(s),"      ")==0);
 }
 
 void test1_character_set_gdesc() {
   Character *s;
   s = character_create();
   character_set_gdesc(s, "_/-.-\\_");
   PRINT_TEST_RESULT(strcmp(character_get_gdesc(s), "_/-.-\\_") == 0);
   character_destroy(s);
 }
 
 void test2_character_set_gdesc() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_set_gdesc(s, "...") == ERROR);
  }
  
  void test3_character_set_gdesc(){
    Character *s;
    s = character_create();
    PRINT_TEST_RESULT(character_set_gdesc(s, NULL) == ERROR);
    character_destroy(s);
  }
 
  void test1_character_get_health() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_get_health(s) == 1);
   character_destroy(s);
 }
 
 void test2_character_get_health() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_get_health(s) == -1);
 }
 
 void test1_character_set_health() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_set_health(s, 10) == OK);
   character_destroy(s);
 }
 
 void test2_character_set_health() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_set_health(s, 10) == ERROR);
 }
 
 void test1_character_get_friendly() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_get_friendly(s) == TRUE);
   character_destroy(s);
 }

 void test2_character_get_friendly() {
   Character *s;
   s = character_create();
   character_set_friendly(s,FALSE);
   PRINT_TEST_RESULT(character_get_friendly(s) == FALSE);
   character_destroy(s);  
 }
 
 void test1_character_set_friendly() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_set_friendly(s, TRUE) == ERROR);
 }
 
 void test2_character_set_friendly() {
   Character *s;
   s = character_create();
   character_set_friendly(s, FALSE);
   PRINT_TEST_RESULT(character_get_friendly(s) == FALSE);
   character_destroy(s);
 }
 
 void test1_character_get_message() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_get_message(s) == NULL);
 }
 
 void test2_character_get_message() {
   Character *s;
   s = character_create();
   character_set_message(s, "Hello!");
   PRINT_TEST_RESULT(character_get_message(s) != NULL);
   character_destroy(s);
 }
 
 void test1_character_set_message() {
   Character *s = NULL;
   PRINT_TEST_RESULT(character_set_message(s, "Hello!") == ERROR);
 }
 
 void test2_character_set_message() {
   Character *s;
   s = character_create();
   character_set_message(s, "Hi!");
   PRINT_TEST_RESULT(strcmp(character_get_message(s), "Hi!") == 0);
   character_destroy(s);
 }
 
 void test3_character_set_message() {
   Character *s;
   s = character_create();
   PRINT_TEST_RESULT(character_set_message(s, NULL) == ERROR);
   character_destroy(s);
 }

 void test1_character_get_location(){
  Character *s;
  s = character_create();
  character_set_location(s, 10);
  PRINT_TEST_RESULT(character_get_location(s) == 10 );
  character_destroy(s);
 }

 void test2_character_get_location(){
  Character *s = NULL;
  PRINT_TEST_RESULT(character_get_location(s) == NO_ID);
 }

 void test1_character_set_location(){
  Character *s;
  s = character_create();
  PRINT_TEST_RESULT(character_set_location(s, 11) == OK);
  character_destroy(s);
 }

 void test2_character_set_location(){
  Character *s = NULL;
  PRINT_TEST_RESULT(character_set_location(s, 10) == ERROR);
 }

void test1_character_get_strength() {
  Character *s = NULL;
  s = character_create();
  PRINT_TEST_RESULT(character_get_strength(s) == 1);
  character_destroy(s);
}
void test2_character_get_strength(){
  Character *s = NULL;
  PRINT_TEST_RESULT(character_get_strength(s) == -1);
}
void test1_character_set_strength(){
  Character *s = NULL;
  s =character_create();
  PRINT_TEST_RESULT(character_set_strength(s,2) == OK);
  character_destroy(s);
}
void test2_character_set_strength(){
  Character *s = NULL;
  PRINT_TEST_RESULT(character_set_strength(s,2) == ERROR);
}
void test1_character_get_following(){
  Character *s = NULL;
  s =character_create();
  character_set_following(s, 10);
  PRINT_TEST_RESULT(character_get_following(s) == 10);
  character_destroy(s);
}
void test2_character_get_following(){
  Character *s = NULL;
  character_set_following(s, 10);
  PRINT_TEST_RESULT(character_get_following(s) == NO_ID);
}
void test1_character_set_following(){
  Character *s = NULL;
  s = character_create();
  PRINT_TEST_RESULT(character_set_following(s, 10) == OK);
  character_destroy(s);

}
void test2_character_set_following(){
  Character *s = NULL;
  PRINT_TEST_RESULT(character_set_following(s, 10) == ERROR);
}