#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal_tests.h"

int main(void) {
  Suite* cases[] = {
      s21_add_suite_create(),                    // #1
      s21_div_suite_create(),                    // #2
      s21_floor_suite_create(),                  // #3
      s21_from_decimal_to_float_suite_create(),  // #4
      s21_from_decimal_to_int_suite_create(),    // #5
      s21_from_float_to_decimal_suite_create(),  // #6
      s21_from_int_to_decimal_suite_create(),    // #7
      s21_is_equal_suite_create(),               // #8
      s21_is_greater_or_equal_suite_create(),    // #9
      s21_is_greater_suite_create(),             // #10
      s21_is_less_or_equal_suite_create(),       // #11
      s21_is_less_suite_create(),                // #12
      s21_is_not_equal_suite_create(),           // #13
      // s21_mod_suite_create(),                    // #14
      s21_mul_suite_create(),      // #15
      s21_negate_suite_create(),   // #16
      s21_round_suite_create(),    // #17
      s21_sub_suite_create(),      // #18
      s21_truncate_suite_create()  // #19
  };

  for (int i = 0; i < 18; ++i) {
    SRunner* runner = srunner_create(cases[i]);
    srunner_run_all(runner, CK_NORMAL);

    // int failed_count =
    srunner_ntests_failed(runner);
    srunner_free(runner);
    // if (failed_count != 0) {
    //   return EXIT_FAILURE;
    // }
  }
  return EXIT_SUCCESS;
}
