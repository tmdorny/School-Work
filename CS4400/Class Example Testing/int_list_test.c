#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

/*  Unit testing added by Tim Dorny
 In-Class Example Sept 14 2016*/

typedef struct int_list {
  int val;
  struct int_list *next;
} int_list;

int tests_run = 0;
int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};



int sum_list(int_list *lst) {
  int sum = 0;
  while (lst != NULL) {
    sum += lst->val;
    lst = lst->next;
  }
  return sum;
}

int_list *array_to_list(int *a, int len) {
  int_list *nota = NULL;
  int_list *add = NULL;
  int i = len - 1;
  for (; i >= 0; i--){
    add = nota;
    nota = malloc(sizeof(int_list));
    nota->val = a[i];
    nota->next = add;
  }
  return nota;
}

static char * test_sumlist_len1(){
  mu_assert("Error: sum_list != 1", sum_list(array_to_list(a, 1)) == 1);
  return 0;
}
static char * test_sumlist_len2(){
  mu_assert("Error: sum_list != 3", sum_list(array_to_list(a, 2)) == 3);
  return 0;
}
static char * test_sumlist_len3(){
  mu_assert("Error: sum_list != 6", sum_list(array_to_list(a, 3)) == 6);
  return 0;
}
static char * test_sumlist_len4(){
  mu_assert("Error: sum_list != 10", sum_list(array_to_list(a, 4)) == 10);
  return 0;
}
static char * test_sumlist_len5(){
  mu_assert("Error: sum_list != 15", sum_list(array_to_list(a, 5)) == 15);
  return 0;
}
static char * test_sumlist_len6(){
  mu_assert("Error: sum_list != 21", sum_list(array_to_list(a, 6)) == 21);
  return 0;
}
static char * test_sumlist_len7(){
  mu_assert("Error: sum_list != 28", sum_list(array_to_list(a, 7)) == 28);
  return 0;
}
static char * test_sumlist_len8(){
  mu_assert("Error: sum_list != 36", sum_list(array_to_list(a, 8)) == 36);
  return 0;
}
static char * test_sumlist_len9(){
  mu_assert("Error: sum_list != 45", sum_list(array_to_list(a, 9)) == 45);
  return 0;
}
static char * test_sumlist_len10(){
  mu_assert("Error: sum_list != 55", sum_list(array_to_list(a, 10)) == 55);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_sumlist_len1);
  mu_run_test(test_sumlist_len2);
  mu_run_test(test_sumlist_len3);
  mu_run_test(test_sumlist_len4);
  mu_run_test(test_sumlist_len5);
  mu_run_test(test_sumlist_len6);
  mu_run_test(test_sumlist_len7);
  mu_run_test(test_sumlist_len8);
  mu_run_test(test_sumlist_len9);
  mu_run_test(test_sumlist_len10);
  return 0;
}

int main() {
  // begin tests
  char * result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  }
  else {
    printf("All Tests Passed!\n");
  }
  printf("Tests Run: %d\n", tests_run);

// end tests
  //printf("%d\n", sum_list(array_to_list(a, 10)));
  return 0;
}
