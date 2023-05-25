#include "s21_decimal_tests.h"

START_TEST(s21_div_1) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_decimal res;
  int rez_int = 0;
  s21_div(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &rez_int);
  ck_assert_int_eq(1, rez_int);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(ZERO_DIVISION, s21_div(value_1, value_2, &res));
}
END_TEST

// Функция создания набора тестов.
Suite *s21_div_suite_create(void) {
  Suite *suite = suite_create("s21_div");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_div");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_div_1);
  tcase_add_test(tcase_core, s21_div_2);
  tcase_add_test(tcase_core, s21_div_4);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_div(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_div_suite_create();
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