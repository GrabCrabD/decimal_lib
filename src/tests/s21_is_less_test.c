#include "s21_decimal_tests.h"

START_TEST(s21_is_less_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123;
  value_2.bits[0] = 12;
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123;
  value_2.bits[0] = 124;
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123;
  value_2.bits[0] = 123;
  value_1.bits[2] = 122;
  value_2.bits[2] = 123;
  s21_set_scale(&value_1, 5);
  s21_set_scale(&value_2, 10);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123;
  value_2.bits[0] = 123;
  value_1.bits[2] = 122;
  value_2.bits[2] = 123;
  s21_set_scale(&value_1, 10);
  s21_set_scale(&value_2, 5);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_6) {  // +0 -0
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {{0, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_7) {  // +0 -0
  s21_decimal value_1 = {{0, 0, 0, 2147483648}};
  s21_decimal value_2 = {0};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_8) {  // +0 -0
  s21_decimal value_1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {0};
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_9) {  // - -
  s21_decimal value_1 = {{UINT_MAX, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {{UINT_MAX, 0, 0, ~(UINT_MAX / 2)}};
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

START_TEST(s21_is_less_10) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_set_scale(&value_2, 7);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
}
END_TEST

// Функция создания набора тестов.
Suite *s21_is_less_suite_create(void) {
  Suite *suite = suite_create("s21_is_less");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_is_less");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_is_less_1);
  tcase_add_test(tcase_core, s21_is_less_2);
  tcase_add_test(tcase_core, s21_is_less_3);
  tcase_add_test(tcase_core, s21_is_less_4);
  tcase_add_test(tcase_core, s21_is_less_5);
  tcase_add_test(tcase_core, s21_is_less_6);
  tcase_add_test(tcase_core, s21_is_less_7);
  tcase_add_test(tcase_core, s21_is_less_8);
  tcase_add_test(tcase_core, s21_is_less_9);
  tcase_add_test(tcase_core, s21_is_less_10);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_is_less(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_is_less_suite_create();
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