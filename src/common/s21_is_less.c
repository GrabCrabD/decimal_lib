#include "../s21_decimal.h"

/*
 * #6
 * Меньше
 * */
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int less = TRUE;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  if (!sign_1 && !sign_2) {
    if (s21_get_scale(value_1) != s21_get_scale(value_2)) {
      s21_alligment_scale(&value_1, &value_2);
    }
    for (int i = 95; i >= 0; i--) {
      if (s21_get_bit(value_1, i) && !s21_get_bit(value_2, i)) {
        less = FALSE;
        break;
      } else if (!s21_get_bit(value_1, i) && s21_get_bit(value_2, i)) {
        less = TRUE;
        break;
      }
    }
  } else if (sign_1 && sign_2) {
    s21_negate(value_1, &value_1);
    s21_negate(value_2, &value_2);
    less = s21_is_less(value_2, value_1);
  } else {
    if (sign_1 < sign_2) {
      less = FALSE;
    } else {
      less = TRUE;
    }
  }
  return less && !s21_is_equal(value_1, value_2);
}
