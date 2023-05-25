#include "s21_decimal_tests.h"

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal value = {{0}};
  int res = 123;
  int tmp = -111;
  s21_from_int_to_decimal(res, &value);
  s21_from_decimal_to_int(value, &tmp);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal value = {{1, 2, 0, 0}};
  int res = 0;
  ck_assert_int_eq(1, s21_from_decimal_to_int(value, &res));
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int ans;
  int true_ans = 0;
  ck_assert_int_eq(0, s21_from_decimal_to_int(dec, &ans));
  ck_assert_int_eq(ans, true_ans);

  dec = create_decimal(9384, 0, 0, MINUS_SIGN);
  true_ans = -9384;
  ck_assert_int_eq(0, s21_from_decimal_to_int(dec, &ans));
  ck_assert_int_eq(ans, true_ans);

  dec = create_decimal(INT32_MAX, 0, 0, 0);
  true_ans = INT32_MAX;
  ck_assert_int_eq(0, s21_from_decimal_to_int(dec, &ans));
  ck_assert_int_eq(ans, true_ans);

  // С ДРОБНОЙ ЧАСТЬЮ
  dec = create_decimal(903, 0, 0, DEFAULT_BASE * 2);
  true_ans = 9;
  ck_assert_int_eq(0, s21_from_decimal_to_int(dec, &ans));
  ck_assert_int_eq(ans, true_ans);

  dec = create_decimal(567349, 4787346, 34345, DEFAULT_BASE * 21);
  true_ans = 633;
  ck_assert_int_eq(0, s21_from_decimal_to_int(dec, &ans));
  ck_assert_int_eq(ans, true_ans);

  dec = create_decimal(9, 0, 0, DEFAULT_BASE);
  true_ans = 0;
  ck_assert_int_eq(0, s21_from_decimal_to_int(dec, &ans));
  ck_assert_int_eq(ans, true_ans);

  // ОШИБКИ КОНВЕРТАЦИИ
  dec = create_decimal(UINT32_MAX, 0, 0, 0);
  ck_assert_int_eq(1, s21_from_decimal_to_int(dec, &ans));

  dec = create_decimal(45, 565675, 345, 0);
  ck_assert_int_eq(1, s21_from_decimal_to_int(dec, &ans));
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal value = {{0, 0, 0, ~(UINT_MAX / 2)}};
  int res = 10;
  ck_assert_int_eq(0, s21_from_decimal_to_int(value, &res));
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal value = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 11111;
  s21_from_decimal_to_int(value, &tmp);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_decimal_to_int_6) {
  s21_decimal value = {{0, 429, 429, 0}};
  int res = 1;
  int tmp = 0;
  ck_assert_int_eq(res, s21_from_decimal_to_int(value, &tmp));
}
END_TEST

// Функция создания набора тестов.
Suite *s21_from_decimal_to_int_suite_create(void) {
  Suite *suite = suite_create("s21_from_decimal_to_int");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_from_decimal_to_int");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_from_decimal_to_int_1);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_2);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_3);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_4);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_5);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_6);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_from_decimal_to_int(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_from_decimal_to_int_suite_create();
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