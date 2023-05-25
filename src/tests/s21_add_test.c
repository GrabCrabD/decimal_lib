#include "s21_decimal_tests.h"

START_TEST(s21_add_1) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  // s21_decimal value_2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {0};
  s21_decimal res;
  int src = -2;
  s21_from_int_to_decimal(src, &value_2);
  ck_assert_int_eq(2, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = {{123, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {{12, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = {{4, 0, 0, 0}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(&value_1, 5);
  s21_set_scale(&value_2, 3);
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(&value_1, 5);
  s21_set_scale(&value_2, 8);
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = 100;
  int value2 = 10000;
  int result = value1 + value2;
  int sum = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_add(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sum);
  ck_assert_int_eq(result, sum);
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = -100;
  int value2 = 10000;
  int result = value1 + value2;
  int sum = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_add(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sum);
  ck_assert_int_eq(result, sum);
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = 100;
  int value2 = -10000;
  int result = value1 + value2;
  int sum = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_add(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sum);
  ck_assert_int_eq(result, sum);
}
END_TEST

START_TEST(s21_add_13) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = -100;
  int value2 = -10000;
  int result = value1 + value2;
  int sum = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_add(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sum);
  ck_assert_int_eq(result, sum);
}
END_TEST

START_TEST(s21_add_14) {
  s21_decimal dec1 = {{666, 0, 0, 0}};
  s21_decimal dec2 = {{9723, 0, 0, 0}};
  s21_decimal true_ans = {{10389, 0, 0, 0}};
  s21_decimal ans;
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(66, 66, 66, 0);
  true_ans = create_decimal(100, 100, 100, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(34, 34, 34, MINUS_SIGN);
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(0, 0, 0, 0);
  dec2 = create_decimal(0, 0, 0, MINUS_SIGN);
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(34, 34, 34, MINUS_SIGN);
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(0, s21_add(dec2, dec1, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(0, 0, 0, 0);
  true_ans = create_decimal(34, 34, 34, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, MINUS_SIGN);
  dec2 = create_decimal(66, 66, 66, MINUS_SIGN);
  true_ans = create_decimal(100, 100, 100, MINUS_SIGN);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, MINUS_SIGN);
  dec2 = create_decimal(66, 66, 66, 0);
  true_ans = create_decimal(32, 32, 32, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(66, 66, 66, MINUS_SIGN);
  true_ans = create_decimal(32, 32, 32, MINUS_SIGN);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(66, 66, 66, MINUS_SIGN);
  true_ans = create_decimal(32, 32, 32, MINUS_SIGN);
  ck_assert_int_eq(0, s21_add(dec2, dec1, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  // НЕ целые числа

  dec1 = create_decimal(1, 0, 0, 0);
  dec2 = create_decimal(1002, 0, 0, DEFAULT_BASE * 3);
  true_ans = create_decimal(2002, 0, 0, DEFAULT_BASE * 3);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(613478421, 0, 0, DEFAULT_BASE * 3);
  dec2 = create_decimal(2056771366, 613, 0, DEFAULT_BASE * 6);
  true_ans = create_decimal(1354869038, 756, 0, DEFAULT_BASE * 6);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(5450, 0, 0, MINUS_SIGN);
  dec2 = create_decimal(550000, 0, 0, MINUS_SIGN + DEFAULT_BASE * 3);
  true_ans = create_decimal(6000000, 0, 0, MINUS_SIGN + DEFAULT_BASE * 3);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  // Большие значения

  dec1 = create_decimal(4238529012, 4294967295, 0, 0);
  dec2 = create_decimal(56438283, 4294967295, 4294967294, 0);
  true_ans = create_decimal(4294967295, 4294967294, 4294967295, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(4567567, 0, 0, DEFAULT_BASE * 3);
  dec2 = create_decimal(433, 0, 0, DEFAULT_BASE * 3);
  true_ans = create_decimal(4568, 0, 0, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(4294967294, 4294967295, 4294967295, 0);
  dec2 = create_decimal(1, 0, 0, DEFAULT_BASE * 28);
  true_ans = create_decimal(4294967294, 4294967295, 4294967295, 0);
  ck_assert_int_eq(0, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  // Ошибки

  dec1 = create_decimal(4238529012, 4294967295, 4294967295, 0);
  dec2 = create_decimal(56438283, 4294967295, 4294967294, 0);
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(1, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(4238529012, 4294967295, 4294967295, MINUS_SIGN);
  dec2 = create_decimal(56438283, 4294967295, 4294967294, MINUS_SIGN);
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(2, s21_add(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));
}
END_TEST

// Функция создания набора тестов.
Suite *s21_add_suite_create(void) {
  Suite *suite = suite_create("s21_add");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_add");
  suite_add_tcase(suite, tcase_core);
  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_add_1);
  tcase_add_test(tcase_core, s21_add_2);
  tcase_add_test(tcase_core, s21_add_3);
  tcase_add_test(tcase_core, s21_add_4);
  tcase_add_test(tcase_core, s21_add_5);
  tcase_add_test(tcase_core, s21_add_6);
  tcase_add_test(tcase_core, s21_add_7);
  tcase_add_test(tcase_core, s21_add_8);
  tcase_add_test(tcase_core, s21_add_9);
  tcase_add_test(tcase_core, s21_add_10);
  tcase_add_test(tcase_core, s21_add_11);
  tcase_add_test(tcase_core, s21_add_12);
  tcase_add_test(tcase_core, s21_add_13);
  tcase_add_test(tcase_core, s21_add_14);

  // Добавление теста в тестовый набор.

  return suite;
}

// int test_add(void) {
//   // Создаем структуру и заполняем ее тест кейсами
//   Suite *suite = s21_add_suite_create();
//   /*Создаем ранер тестов*/
//   SRunner *suite_runner = srunner_create(suite);
//   srunner_run_all(suite_runner, CK_NORMAL);
//   // Получаем количество проваленных тестов.
//   int failed_count = srunner_ntests_failed(suite_runner);
//   /*Освобождаем память*/
//   srunner_free(suite_runner);
//   if (failed_count != 0) {
//     // Сигнализируем о том, что тестирование прошло неудачно.
//     return EXIT_FAILURE;
//   }
//   return EXIT_SUCCESS;
// }