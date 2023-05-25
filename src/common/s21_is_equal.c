#include "../s21_decimal.h"

/*
 * #10
 * Равно
 * */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int equal = TRUE;
  if (s21_get_scale(value_1) != s21_get_scale(value_2)) {
    s21_alligment_scale(&value_1, &value_2);
  }
  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    for (int i = 0; i < 3; i++) {
      if (value_1.bits[i] != value_2.bits[i]) {
        equal = FALSE;
        break;
      }
    }
  } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 &&
             value_1.bits[2] == 0 && value_2.bits[0] == 0 &&
             value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    equal = TRUE;
  } else {
    equal = FALSE;
  }

  return equal;
}
