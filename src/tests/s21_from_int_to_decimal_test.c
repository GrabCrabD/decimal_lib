#include "s21_decimal_tests.h"

START_TEST(s21_from_int_to_decimal_1) {
  s21_decimal value = {{0}};
  int res = 0;
  int tmp = s21_from_int_to_decimal(res, &value);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  s21_decimal value = {{0}};
  int res = -123;
  int tmp = s21_from_int_to_decimal(res, &value);
  s21_from_decimal_to_int(value, &tmp);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  s21_decimal value = {{0}};
  int res = 123;
  int tmp = s21_from_int_to_decimal(res, &value);
  s21_from_decimal_to_int(value, &tmp);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimal_4) {
  s21_decimal value = {{0}};
  int res = 123;
  int tmp = -111;
  s21_from_int_to_decimal(res, &value);
  s21_from_decimal_to_int(value, &tmp);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimal_5) {
  int x = -8374;
  s21_decimal ans;
  s21_decimal true_ans = {{8374, 0, 0, MINUS_SIGN}};

  ck_assert_int_eq(0, s21_from_int_to_decimal(x, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  x = 0;
  true_ans = create_decimal(0, 0, 0, 0);

  ck_assert_int_eq(0, s21_from_int_to_decimal(x, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  x = INT32_MAX;
  true_ans = create_decimal(INT32_MAX, 0, 0, 0);

  ck_assert_int_eq(0, s21_from_int_to_decimal(x, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));

  x = -INT32_MAX;
  true_ans = create_decimal(INT32_MAX, 0, 0, MINUS_SIGN);

  ck_assert_int_eq(0, s21_from_int_to_decimal(x, &ans));
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_from_int_to_decimal_6) {
  s21_decimal *value = NULL;
  int res = 123;
  ck_assert_int_eq(1, s21_from_int_to_decimal(res, value));
}
END_TEST

// Функция создания набора тестов.
Suite *s21_from_int_to_decimal_suite_create(void) {
  Suite *suite = suite_create("s21_from_int_to_decimal");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_from_int_to_decimal");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_from_int_to_decimal_1);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_2);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_3);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_4);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_5);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_6);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_from_int_to_decimal(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_from_int_to_decimal_suite_create();
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