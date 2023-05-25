#include "s21_decimal_tests.h"

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123;
  value_2.bits[0] = 123;
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123;
  value_2.bits[0] = 12;
  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123;
  value_2.bits[0] = 124;
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {  // +0 -0
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {{0, 0, 0, 2147483648}};
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[1] = 12;
  value_2.bits[0] = 22;
  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal value_1 = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {{0, 0, 0, ~(UINT_MAX / 2)}};
  value_1.bits[0] = 123;
  value_2.bits[0] = 123;
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  value_1.bits[0] = 123;
  value_2.bits[0] = 123;
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_or_equal_9) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  value_1.bits[0] = 123;
  value_2.bits[0] = 123;
  s21_set_scale(&value_1, 5);
  s21_set_scale(&value_2, 3);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// Функция создания набора тестов.
Suite *s21_is_less_or_equal_suite_create(void) {
  Suite *suite = suite_create("s21_is_less_or_equal");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_is_less_or_equal");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_is_less_or_equal_1);
  tcase_add_test(tcase_core, s21_is_less_or_equal_2);
  tcase_add_test(tcase_core, s21_is_less_or_equal_3);
  tcase_add_test(tcase_core, s21_is_less_or_equal_4);
  tcase_add_test(tcase_core, s21_is_less_or_equal_5);
  tcase_add_test(tcase_core, s21_is_less_or_equal_6);
  tcase_add_test(tcase_core, s21_is_less_or_equal_7);
  tcase_add_test(tcase_core, s21_is_less_or_equal_8);
  tcase_add_test(tcase_core, s21_is_less_or_equal_9);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_is_less_or_equal(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_is_less_or_equal_suite_create();
  /*Создаем ранер тестов*/
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  // Получаем количество проваленных тестов.
  int failed_count = srunner_ntests_failed(suite_runner);
  /*Освобождаем память*/
  srunner_free(suite_runner);
  if (failed_count != 0) {
    // Сигнализируем о том, что тестирование прошло неудачно.
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}