#include "s21_decimal_tests.h"

START_TEST(s21_floor_1) {
  s21_decimal dec = {{9, 0, 0, 0}};
  s21_decimal fl_res;
  s21_set_scale(&dec, 1);
  int dec_res = 0;
  int res = 0;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal dec = {{19, 0, 0, 0}};
  s21_decimal fl_res;
  s21_set_scale(&dec, 1);
  int dec_res = 0;
  int res = 1;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal dec = {{119, 0, 0, 0}};
  s21_decimal fl_res;
  s21_set_scale(&dec, 1);
  int dec_res = 0;
  int res = 11;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal dec = {{119, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal fl_res;
  s21_set_scale(&dec, 1);
  int dec_res = 0;
  int res = -12;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal dec = {{111, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal fl_res;
  s21_set_scale(&dec, 1);
  int dec_res = 0;
  int res = -12;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_decimal fl_res;
  // s21_set_scale(&dec, 1);
  int dec_res = 0;
  int res = 0;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_decimal fl_res;
  // s21_set_scale(&dec, 1);
  int dec_res = 0;
  int res = 0;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal dec = {{123, 500, 0, 0}};
  s21_decimal dec_2 = {{123, 500, 0, 0}};
  s21_decimal fl_res;
  s21_set_scale(&dec, 2);
  s21_set_scale(&dec_2, 2);
  int dec_res = 0;
  int res = 0;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  s21_from_decimal_to_int(dec_2, &res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_9) {
  s21_decimal dec = {{193, 500, 0, 0}};
  s21_decimal dec_2 = {{193, 500, 0, 0}};
  s21_decimal fl_res;
  s21_set_scale(&dec, 2);
  s21_set_scale(&dec_2, 2);
  int dec_res = 0;
  int res = 0;
  s21_floor(dec, &fl_res);
  s21_from_decimal_to_int(fl_res, &dec_res);
  s21_from_decimal_to_int(dec_2, &res);
  ck_assert_int_eq(dec_res, res);
}
END_TEST

START_TEST(s21_floor_10) {
  s21_decimal dec = {{9, 0, 0, 0}};
  s21_decimal *fl_res = NULL;
  int res = 0;
  res = s21_floor(dec, fl_res);
  ck_assert_int_eq(ERR_COMPUTING, res);
}
END_TEST

// Функция создания набора тестов.
Suite *s21_floor_suite_create(void) {
  Suite *suite = suite_create("s21_floor");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of s21_floor");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_floor_1);
  tcase_add_test(tcase_core, s21_floor_2);
  tcase_add_test(tcase_core, s21_floor_3);
  tcase_add_test(tcase_core, s21_floor_4);
  tcase_add_test(tcase_core, s21_floor_5);
  tcase_add_test(tcase_core, s21_floor_6);
  tcase_add_test(tcase_core, s21_floor_7);
  tcase_add_test(tcase_core, s21_floor_8);
  tcase_add_test(tcase_core, s21_floor_9);
  tcase_add_test(tcase_core, s21_floor_10);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int test_floor(void) {
  // Создаем структуру и заполняем ее тест кейсами
  Suite *suite = s21_floor_suite_create();
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