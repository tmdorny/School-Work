#include <stdio.h>
#include <string.h>
#include "minunit.h"

/*  Unit testing added by Tim Dorny
    In-Class Example Aug 24 2016*/

int is_negative(double d)
{
  unsigned long p;
  memcpy(&p, &d, sizeof(d)); 
  return p >> 63;
}

int tests_run = 0;

static char * test_is_not_neg_1() {
    mu_assert("Error: expected 0 but got 1.", is_negative(5) == 0);
    return 0;
}
static char * test_is_not_neg_2() {
    mu_assert("Error: expected 0 but got 1.", is_negative(0) == 0);
    return 0;
}
static char * test_is_not_neg_3() {
    mu_assert("Error: expected 0 but got 1.", is_negative(99) == 0);
    return 0;
}
static char * test_is_not_neg_4() {
    mu_assert("Error: expected 0 but got 1.", is_negative(3527245) == 0);
    return 0;
}
static char * test_is_not_neg_5() {
    mu_assert("Error: expected 0 but got 1.", is_negative(11111) == 0);
    return 0;
}
static char * test_is_neg_1() {
    mu_assert("Error: expected 1 but got 0.", is_negative(-5) == 1);
    return 0;
}
static char * test_is_neg_2() {
    mu_assert("Error: expected 1 but got 0.", is_negative(-668) == 1);
    return 0;
}
static char * test_is_neg_3() {
    mu_assert("Error: expected 1 but got 0.", is_negative(-12020304) == 1);
    return 0;
}
static char * test_is_neg_4() {
    mu_assert("Error: expected 1 but got 0.", is_negative(-1) == 1);
    return 0;
}
static char * test_is_neg_5() {
    mu_assert("Error: expected 1 but got 0.", is_negative(-1111111) == 1);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_is_not_neg_1);
    mu_run_test(test_is_not_neg_2);
    mu_run_test(test_is_not_neg_3);
    mu_run_test(test_is_not_neg_4);
    mu_run_test(test_is_not_neg_5);
    mu_run_test(test_is_neg_1);
    mu_run_test(test_is_neg_2);
    mu_run_test(test_is_neg_3);
    mu_run_test(test_is_neg_4);
    mu_run_test(test_is_neg_5);
    return 0;
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
    //printf("%d\n", is_negative(10));
    //printf("%d\n", is_negative(-10));
    return 0;
}
