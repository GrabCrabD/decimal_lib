#include "s21_decimal_tests.h"

// START_TEST(s21_from_float_to_decimal_1) {
//   // ck_assert_int_eq(s21_from_float_to_decimal(), from_float_to_decimal());
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal value = {{0}};
  float res = 0;
  float tmp = s21_from_float_to_decimal(res, &value);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal value = {{0}};
  float res = -123;
  float tmp = s21_from_float_to_decimal(res, &value);
  s21_from_decimal_to_float(value, &tmp);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal value = {{0}};
  float res = 123;
  float tmp = s21_from_float_to_decimal(res, &value);
  s21_from_decimal_to_float(value, &tmp);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal value = {{0}};
  float res = 123;
  float tmp = -111;
  s21_from_float_to_decimal(res, &value);
  s21_from_decimal_to_float(value, &tmp);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  float res = 0;
  ck_assert_float_eq(0, s21_from_float_to_decimal(res, &value));
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal value = {0};
  float res = 123;
  ck_assert_float_eq(0, s21_from_float_to_decimal(res, &value));
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal value = {0};
  float res = 1e-30;
  ck_assert_float_eq(1, s21_from_float_to_decimal(res, &value));
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  s21_decimal value = {{0}};
  float res = 123.456789;
  float tmp = -111;
  s21_from_float_to_decimal(res, &value);
  s21_from_decimal_to_float(value, &tmp);
  ck_assert_float_eq(res - tmp > EPS * 10, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  s21_decimal value = {{0}};
  long double tmp = MAX_DECIMAL * 100;
  ck_assert_float_eq(s21_from_float_to_decimal(tmp, &value), ERR_CONVERT);
}
END_TEST

START_TEST(s21_from_float_to_decimal_10) {
  s21_decimal ans;
  float num = 9.34f;
  s21_decimal true_ans = {{934, 0, 0, DEFAULT_BASE * 2}};
  ck_assert_int_eq(0, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = 0.0f;
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(0, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = 654.0f;
  true_ans = create_decimal(654, 0, 0, 0);
  ck_assert_int_eq(0, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = 65465523.0f;
  true_ans = create_decimal(65465520, 0, 0, 0);
  ck_assert_int_eq(0, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = -67.234f;
  true_ans = create_decimal(67234, 0, 0, MINUS_SIGN + DEFAULT_BASE * 3);
  ck_assert_int_eq(0, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = 0.233435344f;
  true_ans = create_decimal(2334353, 0, 0, DEFAULT_BASE * 7);
  ck_assert_int_eq(0, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = 0.00000000000000000000044f;
  true_ans = create_decimal(44, 0, 0, DEFAULT_BASE * 23);
  ck_assert_int_eq(0, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  // ОШИБКИ КОНВЕРТАЦИИ

  num = 0.000000000000000000000000000000000000067;
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(1, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = INFINITY;
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(1, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  num = -INFINITY;
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(1, s21_from_float_to_decimal(num, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

// Функция создания набора тестов.
Suite *s21_from_float_to_decimal_suite_create(void) {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_from_float_to_decimal");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_from_float_to_decimal_1);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_2);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_3);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_4);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_5);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_6);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_7);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_8);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_9);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_10);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_from_float_to_decimal(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_from_float_to_decimal_suite_create();
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