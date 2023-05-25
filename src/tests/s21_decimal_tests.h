#ifndef _S21_DECIMAL_TESTS_H_
#define _S21_DECIMAL_TESTS_H_
#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

/* создание тестов */
Suite* s21_add_suite_create(void);
Suite* s21_div_suite_create(void);
Suite* s21_floor_suite_create(void);
Suite* s21_from_decimal_to_float_suite_create(void);
Suite* s21_from_decimal_to_int_suite_create(void);
Suite* s21_from_float_to_decimal_suite_create(void);
Suite* s21_from_int_to_decimal_suite_create(void);
Suite* s21_is_equal_suite_create(void);
Suite* s21_floor_suite_create(void);
Suite* s21_is_greater_or_equal_suite_create(void);
Suite* s21_is_greater_suite_create(void);
Suite* s21_is_less_or_equal_suite_create(void);
Suite* s21_is_less_suite_create(void);
Suite* s21_is_not_equal_suite_create(void);
// Suite* s21_mod_suite_create(void);
Suite* s21_mul_suite_create(void);
Suite* s21_negate_suite_create(void);
Suite* s21_round_suite_create(void);
Suite* s21_sub_suite_create(void);
Suite* s21_truncate_suite_create(void);
/* Запуск тестов */
int test_add(void);
int test_div(void);
int test_floor(void);
int test_from_decimal_to_float(void);
int test_from_decimal_to_int(void);
int test_from_float_to_decimal(void);
int test_from_int_to_decimal(void);
int test_is_equal(void);
int test_is_greater_or_equal(void);
int test_is_greater(void);
int test_is_less_or_equal(void);
int test_is_less(void);
int test_is_not_equal(void);
// int test_mod(void);
int test_mul(void);
int test_negate(void);
int test_round(void);
int test_sub(void);
int test_truncate(void);

#endif  // _S21_DECIMAL_TESTS_H_