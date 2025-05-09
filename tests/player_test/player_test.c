/** 
 * @brief It tests player module
 * 
 * @file player_test.c
 * @author Hugo Martín
 * @version 0.0 
 * @date 24-02-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include "player.h"
 #include "player_test.h"
 #include "test.h"
 
 #define MAX_TESTS 40
 
 /** 
  * @brief Main function for PLAYER unit tests. 
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
     printf("Running all test for module Player:\n");
   } else {
     test = atoi(argv[1]);
     all = 0;
     printf("Running test %d:\t", test);
     if (test < 1 && test > MAX_TESTS) {
       printf("Error: unknown test %d\t", test);
       exit(EXIT_SUCCESS);
     }
   }
 
 
   if (all || test == 1) test1_player_create();
   if (all || test == 2) test2_player_create();
   if (all || test == 3) test1_player_get_id();
   if (all || test == 4) test2_player_get_id();
   if (all || test == 5) test1_player_set_id();
   if (all || test == 6) test2_player_set_id();
   if (all || test == 7) test3_player_set_id();
   if (all || test == 8) test1_player_get_name();
   if (all || test == 9) test2_player_get_name();
   if (all || test == 10) test1_player_set_name();
   if (all || test == 11) test2_player_set_name();
   if (all || test == 12) test3_player_set_name();
   if (all || test == 13) test1_player_get_gdesc();
   if (all || test == 14) test2_player_get_gdesc();
   if (all || test == 15) test1_player_set_gdesc();
   if (all || test == 16) test2_player_set_gdesc();
   if (all || test == 17) test3_player_set_gdesc();
   if (all || test == 18) test1_player_get_health();
   if (all || test == 19) test2_player_get_health();
   if (all || test == 20) test1_player_set_health();
   if (all || test == 21) test2_player_set_health();
   if (all || test == 22) test1_player_get_location();
   if (all || test == 23) test2_player_get_location();
   if (all || test == 24) test1_player_set_location();
   if (all || test == 25) test2_player_set_location();
   if (all || test == 26) test1_player_get_objects();
   if (all || test == 27) test2_player_get_objects();
   if (all || test == 28) test1_player_add_object();
   if (all || test == 29) test2_player_add_object();
   if (all || test == 30) test1_player_del_object();
   if (all || test == 31) test2_player_del_object();
   if (all || test == 32) test1_player_find_object();
   if (all || test == 33) test2_player_find_object();
   if (all || test == 34) test1_player_get_strength();
   if (all || test == 35) test2_player_get_strength();
   if (all || test == 36) test1_player_set_strength();
   if (all || test == 37) test2_player_set_strength();
   if (all || test == 38) test1_player_get_followers();
   if (all || test == 39) test2_player_get_followers();
   
 
   PRINT_PASSED_PERCENTAGE;
 
   return 1;
 }
 
 void test1_player_create() {
   int result;
   Player *s;
   s = player_create();
   result=s!=NULL;
   PRINT_TEST_RESULT(result);
   player_destroy(s);
 }
 
 void test2_player_create() {
   Player *s;
   s = player_create();
   PRINT_TEST_RESULT(player_get_id(s));
   player_destroy(s);
 }
 
 void test1_player_get_id() {
   Player *s;
   s = player_create();
   PRINT_TEST_RESULT(player_get_id(s) == NO_ID);
   player_destroy(s);
 }
 
 void test2_player_get_id() {
   Player *s = NULL;
   PRINT_TEST_RESULT(player_get_id(s) == NO_ID);
 }
 
 void test1_player_set_id() {
   Player *s;
   s = player_create();
   PRINT_TEST_RESULT(player_set_id(s, NO_ID) == ERROR);
   player_destroy(s);
 }
 
 void test2_player_set_id(){
  Player *s;
  s= player_create();
  PRINT_TEST_RESULT(player_set_id(s, 30) == OK);
  player_destroy(s);
 }

 void test3_player_set_id() {
  Player *s = NULL;
  PRINT_TEST_RESULT(player_set_id(s, 30) == ERROR);
}

 void test1_player_get_name() {
   Player *s;
   s = player_create();
   player_set_name(s, "Hugo");
   PRINT_TEST_RESULT(player_get_name(s) != NULL);
   player_destroy(s);
 }
 
 void test2_player_get_name() {
   Player *s = NULL;
   PRINT_TEST_RESULT(player_get_name(s) == ERROR);
 }
 
 void test1_player_set_name() {
   Player *s;
   s = player_create();
   player_set_name(s, "Hugo");
   PRINT_TEST_RESULT(strcmp(player_get_name(s), "Hugo") == 0);
   player_destroy(s);
 }
 
 void test2_player_set_name() {
   Player *s = NULL;
   PRINT_TEST_RESULT(player_set_name(s, "Adios") == ERROR);
 }
 
 void test3_player_set_name(){
  Player* s;
  s = player_create();
  PRINT_TEST_RESULT(player_set_name(s, NULL) == ERROR);
  player_destroy(s);
 }

 void test1_player_get_gdesc() {
   Player *s;
   s = player_create();
   PRINT_TEST_RESULT(player_get_gdesc(s) != NULL);
   player_destroy(s);
 }
 
 void test2_player_get_gdesc() {
   Player *s = NULL;
   PRINT_TEST_RESULT(player_get_gdesc(s) == NULL);
 }
 
 void test1_player_set_gdesc() {
   Player *s = NULL;
   s = player_create();
   player_set_gdesc(s, "_-.-_");
   PRINT_TEST_RESULT(strcmp(player_get_gdesc(s), "_-.-_") == 0);
   player_destroy(s);
 }
 
 void test2_player_set_gdesc() {
   Player *s = NULL;
   PRINT_TEST_RESULT(player_set_gdesc(s, "...") == ERROR);
  }
  
  void test3_player_set_gdesc(){
    Player *s;
    s = player_create();
    PRINT_TEST_RESULT(player_set_gdesc(s, NULL) == ERROR);
    player_destroy(s);
  }
 
  void test1_player_get_health() {
   Player *s; 
   s = player_create();
   PRINT_TEST_RESULT(player_get_health(s) == 0);
   player_destroy(s);
 }
 
 void test2_player_get_health() {
   Player *s = NULL;
   PRINT_TEST_RESULT(player_get_health(s) == -1);
 }
 
 void test1_player_set_health() {
   Player *s;
   s = player_create();
   PRINT_TEST_RESULT(player_set_health(s, 10) == OK);
   player_destroy(s);
 }
 
 void test2_player_set_health() {
   Player *s = NULL;
   PRINT_TEST_RESULT(player_set_health(s, 10) == ERROR);
 }
 
 void test1_player_get_location(){
  Player *s;
  s = player_create();
  player_set_location(s, 10);
  PRINT_TEST_RESULT(player_get_location(s) == 10 );
  player_destroy(s);
 }

 void test2_player_get_location(){
  Player *s = NULL;
  PRINT_TEST_RESULT(player_get_location(s) == NO_ID);
 }

 void test1_player_set_location(){
  Player *s;
  s = player_create();
  PRINT_TEST_RESULT(player_set_location(s, 11) == OK);
  player_destroy(s);
 }

 void test2_player_set_location(){
  Player *s = NULL;
  PRINT_TEST_RESULT(player_set_location(s, 10) == ERROR);
 }

 void test1_player_get_objects(){
  Player *s;
  s = player_create();
  PRINT_TEST_RESULT(player_get_objects(s) != NULL );
  player_destroy(s);
 }

 void test2_player_get_objects(){
  Player *s = NULL;
  PRINT_TEST_RESULT(player_get_objects(s) == NULL);
 }

 void test1_player_add_object(){
  Player *s;
  Object *o;
  s = player_create();
  o = object_create(3);
  PRINT_TEST_RESULT(player_add_object(s, o) == OK );
  player_destroy(s);
  object_destroy(o);
 }

 void test2_player_add_object(){
  Player *s = NULL;
  Object *o = NULL;
  PRINT_TEST_RESULT(player_add_object(s, o) == ERROR);
 }

  void test1_player_del_object(){
  Player *s;
  Object *o;
  s = player_create();
  o = object_create(3);
  player_add_object(s, o);
  PRINT_TEST_RESULT(player_del_object(s, o) == OK );
  player_destroy(s);
  object_destroy(o);
 }

 void test2_player_del_object(){
  Player *s = NULL;
  Object *o = NULL;
  PRINT_TEST_RESULT(player_del_object(s, o) == ERROR);
 }

  void test1_player_find_object(){
  Player *s;
  Object *o;
  s = player_create();
  o = object_create(3);
  player_add_object(s, o);
  PRINT_TEST_RESULT(player_find_object(s, o) != FALSE );
  player_destroy(s);
  object_destroy(o);
 }

 void test2_player_find_object(){
  Player *s = NULL;
  Object *o = NULL;
  PRINT_TEST_RESULT(player_find_object(s, o) == FALSE);
 }

 void test1_player_get_strength(){
   Player *s; 
   s = player_create();
   PRINT_TEST_RESULT(player_get_strength(s) == 1);
   player_destroy(s);
 }

 void test2_player_get_strength(){
  Player *s = NULL;
   PRINT_TEST_RESULT(player_get_strength(s) == -1);
 }

 void test1_player_set_strength(){
   Player *s;
   s = player_create();
   PRINT_TEST_RESULT(player_set_strength(s, 10) == OK);
   player_destroy(s);
 }

 void test2_player_set_strength(){
   Player *s = NULL;
   PRINT_TEST_RESULT(player_set_strength(s, 10) == ERROR);
 }

 void test1_player_get_followers(){
  Player *s;
  s=player_create();
  PRINT_TEST_RESULT(player_get_followers(s)!=NULL);
  player_destroy(s);
 }

 void test2_player_get_followers(){
  Player *s=NULL;
  PRINT_TEST_RESULT(player_get_followers(s)==NULL);
 }
