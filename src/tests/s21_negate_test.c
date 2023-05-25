#include "s21_decimal_tests.h"

START_TEST(s21_negate_1) {
  s21_decimal value = {{123, 0, 0, 0}};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(value);
  s21_negate(value, &res);
  int sign_after = s21_get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal value = {{123, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(value);
  s21_negate(value, &res);
  int sign_after = s21_get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal value = {0};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(value);
  s21_negate(value, &res);
  int sign_after = s21_get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(s21_negate_4) {
  s21_decimal value = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(value);
  s21_negate(value, &res);
  int sign_after = s21_get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

// Функция создания набора тестов.
Suite *s21_negate_suite_create(void) {
  Suite *suite = suite_create("s21_negate");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_negate");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_negate_1);
  tcase_add_test(tcase_core, s21_negate_2);
  tcase_add_test(tcase_core, s21_negate_3);
  tcase_add_test(tcase_core, s21_negate_4);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_negate(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_negate_suite_create();
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