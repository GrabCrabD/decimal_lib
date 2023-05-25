#include "s21_decimal_tests.h"

// START_TEST(s21_mul_1) {
//   // ck_assert_int_eq(s21_mul(), mul());
// }
// END_TEST

START_TEST(s21_mul_1) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -4;
  int src2 = 2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(s21_mul_2) {
  s21_decimal dec = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int res = 0;
  s21_mul(dec, dec2, &dec3);
  s21_from_decimal_to_int(dec3, &res);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_mul_3) {
  s21_decimal dec = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal dec2;
  s21_decimal dec3;
  int src = 2;
  s21_from_int_to_decimal(src, &dec2);
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 1);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal dec = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal dec2;
  s21_decimal dec3;
  int src = -2;
  s21_from_int_to_decimal(src, &dec2);
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 2);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal dec = {{2, 0, 0, 0}};
  s21_decimal dec2 = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal dec3 = {0};
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 1);
}
END_TEST

// Функция создания набора тестов.
Suite *s21_mul_suite_create(void) {
  Suite *suite = suite_create("s21_mul");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_mul");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_mul_1);
  tcase_add_test(tcase_core, s21_mul_2);
  tcase_add_test(tcase_core, s21_mul_3);
  tcase_add_test(tcase_core, s21_mul_4);
  tcase_add_test(tcase_core, s21_mul_5);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_mul(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_mul_suite_create();
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