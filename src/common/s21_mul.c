#include "../s21_decimal.h"

/*
 * #3
 * Умножение
 * */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;
  int sign = (s21_get_sign(value_1)) ^ (s21_get_sign(value_2));
  s21_clean(result);
  // s21_alligment_scale(&value_1, &value_2);

  int scale = s21_get_scale(value_1) + s21_get_scale(value_1);

  while (value_1.bits[0] != 0 || value_1.bits[1] != 0 || value_1.bits[2] != 0) {
    if ((value_1.bits[0] & 1)) {
      status = s21_add(*result, value_2, result);
    }
    s21_shift_right(&value_1);
    if (95 == s21_last_bit(value_2)) {
      status = sign ? TOO_SMALL_OR_NEG_INF : TOO_BIG_OR_INF;
      break;
    }
    s21_shift_left(&value_2);
  }
  s21_set_sign(result, sign);
  s21_set_scale(result, scale);
  return status;
}