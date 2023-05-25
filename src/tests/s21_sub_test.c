#include "s21_decimal_tests.h"

START_TEST(s21_sub_1) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal value_2 = {{123, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(value_1, value_2, &res));
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = 10000;
  int value2 = 100;
  int result = value1 - value2;
  int sub = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_sub(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sub);
  ck_assert_int_eq(result, sub);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = -10000;
  int value2 = -100;
  int result = value1 - value2;
  int sub = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_sub(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sub);
  ck_assert_int_eq(result, sub);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = 10000;
  int value2 = -100;
  int result = value1 - value2;
  int sub = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_sub(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sub);
  ck_assert_int_eq(result, sub);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = -10000;
  int value2 = 100;
  int result = value1 - value2;
  int sub = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_sub(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sub);
  ck_assert_int_eq(result, sub);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal res;
  int value1 = 100;
  int value2 = 10000;
  int result = value1 - value2;
  int sub = 0;
  s21_from_int_to_decimal(value1, &value_1);
  s21_from_int_to_decimal(value2, &value_2);
  s21_sub(value_1, value_2, &res);
  s21_from_decimal_to_int(res, &sub);
  ck_assert_int_eq(result, sub);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}};
  s21_decimal value_2 = {{0, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal value_check = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  s21_sub(value_1, value_2, &res);
  ck_assert_int_eq(1, s21_is_equal(value_check, res));
}
END_TEST

START_TEST(s21_sub_11) {
  s21_decimal dec1 = {{3234, 0, 0, 0}};
  s21_decimal dec2 = {{72, 0, 0, 0}};
  s21_decimal true_ans = {{3162, 0, 0, 0}};
  s21_decimal ans;
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(13, 0, 0, 0);
  dec2 = create_decimal(23, 0, 0, 0);
  true_ans = create_decimal(10, 0, 0, MINUS_SIGN);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(532167, 0, 0, MINUS_SIGN);
  dec2 = create_decimal(123456, 0, 0, MINUS_SIGN);
  true_ans = create_decimal(408711, 0, 0, MINUS_SIGN);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(61287, 0, 0, MINUS_SIGN);
  dec2 = create_decimal(234787, 0, 0, MINUS_SIGN);
  true_ans = create_decimal(173500, 0, 0, 0);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(567, 45, 34676, 0);
  dec2 = create_decimal(23, 3, 66, 0);
  true_ans = create_decimal(544, 42, 34610, 0);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(0, 0, 0, 0);
  true_ans = create_decimal(34, 34, 34, 0);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(0, 0, 1, 0);
  dec2 = create_decimal(3467, 345346, 0, 0);
  true_ans = create_decimal(4294963829, 4294621949, 0, 0);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(34, 34, 34, 0);
  dec2 = create_decimal(66, 66, 66, 0);
  true_ans = create_decimal(32, 32, 32, MINUS_SIGN);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  // НЕ целые числа

  dec1 = create_decimal(1, 0, 0, 0);
  dec2 = create_decimal(1002, 0, 0, DEFAULT_BASE * 3);
  true_ans = create_decimal(2, 0, 0, MINUS_SIGN + DEFAULT_BASE * 3);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(532167, 0, 0, DEFAULT_BASE * 3);
  dec2 = create_decimal(1236, 0, 0, DEFAULT_BASE * 15);
  true_ans = create_decimal(607087404, 123904785, 0, DEFAULT_BASE * 15);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(100, 0, 0, 0);
  dec2 = create_decimal(1, 0, 0, DEFAULT_BASE * 28);
  true_ans = create_decimal(
      0b00001111111111111111111111111111, 0b00111110001001010000001001100001,
      0b00100000010011111100111001011110, DEFAULT_BASE * 26);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  // Большие значения

  dec1 = create_decimal(4294967295, 4294967295, 4294967295, 0);
  dec2 = create_decimal(6, 0, 0, DEFAULT_BASE);
  true_ans = create_decimal(4294967294, 4294967295, 4294967295, 0);
  ck_assert_int_eq(0, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  // Ошибки

  dec1 = create_decimal(4238529012, 4294967295, 4294967295, 0);
  dec2 = create_decimal(56438283, 4294967295, 4294967294, MINUS_SIGN);
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(1, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));

  dec1 = create_decimal(4238529012, 4294967295, 4294967295, MINUS_SIGN);
  dec2 = create_decimal(56438283, 4294967295, 4294967294, 0);
  true_ans = create_decimal(0, 0, 0, 0);
  ck_assert_int_eq(2, s21_sub(dec1, dec2, &ans));
  ck_assert_int_eq(1, s21_is_equal(true_ans, ans));
}
END_TEST

START_TEST(s21_sub_12) {
  s21_decimal a = {0};
  overflow_decimal value_1 = {0};
  if (!big_zero_check(value_1, value_1)) clean(&value_1);
  value_1.bits[0] = 1;
  shift_l(&value_1);
  shift_r(&value_1);
  shift(&value_1, 2, LEFT);
  shift(&value_1, 1, RIGHT);
  to_decimal(&a, value_1);
  ck_assert_int_eq(a.bits[0], 2);
}
END_TEST

// Функция создания набора тестов.
Suite *s21_sub_suite_create(void) {
  Suite *suite = suite_create("s21_sub");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_sub");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_sub_1);
  tcase_add_test(tcase_core, s21_sub_2);
  tcase_add_test(tcase_core, s21_sub_3);
  tcase_add_test(tcase_core, s21_sub_4);
  tcase_add_test(tcase_core, s21_sub_5);
  tcase_add_test(tcase_core, s21_sub_6);
  tcase_add_test(tcase_core, s21_sub_7);
  tcase_add_test(tcase_core, s21_sub_8);
  tcase_add_test(tcase_core, s21_sub_9);
  tcase_add_test(tcase_core, s21_sub_10);
  tcase_add_test(tcase_core, s21_sub_11);
  tcase_add_test(tcase_core, s21_sub_12);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_sub(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_sub_suite_create();
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