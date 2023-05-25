#include "../s21_decimal.h"

/*
 * #12
 * Из int в decimal
 * */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = ERR_CONVERT, sign = src < 0 ? 1 : 0;

  if (dst) {
    if (sign)
      src *= -1;  // максимальный инт 2 147 483 647; минимальный -2 147 483 648

    s21_clean(dst);
    s21_set_sign(dst, sign);

    dst->bits[0] = src;
    status = OK;
  }
  return status;
}
