#include "../s21_decimal.h"

/*
 * #18
 * Возвращает целые цифры указанного Decimal числа; любые дробные цифры
 * отбрасываются, включая конечные нули.
 * */

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = ERR_COMPUTING;
  if (result) {
    for (int i = s21_get_scale(value); i > 0; i--) div_ten(value, &value);
    s21_set_scale(&value, 0);
    s21_copy(result, value);
    status = OK;
  }
  return status;
}
