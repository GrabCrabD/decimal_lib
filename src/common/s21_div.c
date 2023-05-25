#include "../s21_decimal.h"

/*
 * #4
 * Деление
 * */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;  // sign = (s21_get_sign(value_1)) ^ (s21_get_sign(value_2));
  s21_decimal tmp = {{0, 0, 0, 0}};
  s21_clean(result);

  if (is_empty(value_2)) {
    status = ZERO_DIVISION;
  } else {
    // s21_alligment_scale(&value_1, &value_2);
    // while (is_chet(value_1) && is_chet(value_2))  //
    // {
    //   s21_shift_right(&value_1);
    //   s21_shift_right(&value_2);
    // }
    s21_from_int_to_decimal(1000, &tmp);
    s21_mul(value_1, tmp, &value_1);

    for (int i = 95; i >= 0; i--) {
      s21_clean(&tmp);
      s21_copy(&tmp, value_2);
      s21_shift(&tmp, i, LEFT);
      if (s21_is_less_or_equal_abs(tmp, value_1)) {
        s21_sub(value_1, tmp, &value_1);

        s21_clean(&tmp);
        s21_from_int_to_decimal(1, &tmp);
        s21_shift(&tmp, i, LEFT);
        s21_add(*result, tmp, result);
      }
    }

    s21_set_scale(result, 3 + s21_get_scale(*result));
  }
  return status;
}
