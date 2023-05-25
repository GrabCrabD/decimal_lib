#include "../s21_decimal.h"

/*
 * #15
 * Из decimal в float
 * */

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = ERR_CONVERT;
  if (dst) {
    *dst = 0;
    double tmp = 0;
    int scale = s21_get_scale(src);

    for (int i = 0; i < 96; i++)
      if (s21_get_bit(src, i)) tmp += pow(2, i);
    if (scale > 0)
      for (int i = scale; i > 0; i--, tmp /= 10.0) {
      };
    if (s21_get_sign(src)) tmp *= -1;

    *dst = (float)tmp;
    status = OK;
  }
  return status;
}
