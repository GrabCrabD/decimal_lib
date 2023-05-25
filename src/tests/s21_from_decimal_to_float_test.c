#include "s21_decimal_tests.h"

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal dec = {{0, 0, 0, 0}};
  float ans;
  float true_ans = 0;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq(ans, true_ans);

  dec = create_decimal(9384, 0, 0, MINUS_SIGN);
  true_ans = -9384;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq(ans, true_ans);

  dec = create_decimal(9384, 5643, 39846, 0);
  true_ans = 735028964385267294151848.0f;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq(ans, true_ans);

  dec = create_decimal(0, 453, 0, MINUS_SIGN);
  true_ans = -1945620185088.0f;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq(ans, true_ans);

  dec = create_decimal(4, 0, 0, DEFAULT_BASE * 7);
  true_ans = 0.0000004f;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq_tol(ans, true_ans, 1e-7);

  dec = create_decimal(347684574, 347684574, 32988346, DEFAULT_BASE * 27);
  true_ans = 0.608527577570274067214843614f;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq_tol(ans, true_ans, 1e-7);

  dec = create_decimal(347684574, 347684574, 32988346, DEFAULT_BASE * 22);
  true_ans = 60852.7577570274067214843614f;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq_tol(ans, true_ans, 1e-7);

  dec = create_decimal(UINT32_MAX, UINT32_MAX, UINT32_MAX, 0);
  true_ans = 79228162514264337593543950335.0f;
  ck_assert_int_eq(0, s21_from_decimal_to_float(dec, &ans));
  ck_assert_float_eq(ans, true_ans);
}
END_TEST

// Функция создания набора тестов.
Suite *s21_from_decimal_to_float_suite_create(void) {
  Suite *suite = suite_create("s21_from_decimal_to_float");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_from_decimal_to_float");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_from_decimal_to_float_1);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_from_decimal_to_float(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_from_decimal_to_float_suite_create();
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