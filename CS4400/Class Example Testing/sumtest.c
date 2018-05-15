#include <stdio.h>
#include "minunit.h"

/*  Unit testing added by Tim Dorny
  In-Class Example Aug 31 2016*/

/*
  Implement sum() to summary an array of integers
    - using `goto` and labels
    - without using `for`, `while`, or `do`
    - with only one-armed `if`s
    - with only `goto` in the "then" part of `if`
*/

int tests_run = 0;

int a[] = {1, 2, 5, 7, 4, 6, 8, 0, 11};

static char * test_sum_len1() {
  mu_assert("error: sum != 1", sum(a, 1) == 1);
  return 0;
}
static char * test_sum_len2() {
  mu_assert("error: sum != 3", sum(a, 2) == 3);
  return 0;
}
static char * test_sum_len3() {
  mu_assert("error: sum != 8", sum(a, 3) == 8);
  return 0;
}
static char * test_sum_len4() {
  mu_assert("error: sum != 15", sum(a, 4) == 15);
  return 0;
}
static char * test_sum_len5() {
  mu_assert("error: sum != 19", sum(a, 5) == 19);
  return 0;
}
static char * test_sum_len6() {
  mu_assert("error: sum != 25", sum(a, 6) == 25);
  return 0;
}
static char * test_sum_len7() {
  mu_assert("error: sum != 33", sum(a, 7) == 33);
  return 0;
}
static char * test_sum_len8() {
  mu_assert("error: sum != 33", sum(a, 8) == 33);
  return 0;
}
static char * test_sum_len9() {
  mu_assert("error: sum != 44", sum(a, 9) == 44);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_sum_len1);
  mu_run_test(test_sum_len2);
  mu_run_test(test_sum_len3);
  mu_run_test(test_sum_len4);
  mu_run_test(test_sum_len5);
  mu_run_test(test_sum_len6);
  mu_run_test(test_sum_len7);
  mu_run_test(test_sum_len8);
  mu_run_test(test_sum_len9);
  return 0;
}

int sum(int *a, int len)
{
  int sum_so_far = 0;
  int index = 0;

 fakewhile:
  if(index < len) goto doit;
  return sum_so_far;

 doit:
  sum_so_far = sum_so_far + a[index];
  index++;
  goto fakewhile;
}


int main()
{
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
  //int v = sum(a, sizeof(a) / sizeof(int));

  printf("%d\n", v);

  return 0;
}
