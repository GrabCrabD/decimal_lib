#include "../s21_decimal.h"

/*
 * #17
 * Округляет Decimal до ближайшего целого числа.
 * */

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = ERR_COMPUTING;
  if (result) {
    for (int i = s21_get_scale(value) - 1; i > 0; i--) div_ten(value, &value);
    if (0 < s21_get_scale(value)) {
      int remain = div_ten(value, &value);
      if (remain > 5 &&
          s21_get_bit(value,
                      0)) {  //  банковское округление => проверяем чётность
        s21_decimal ad = {0};
        s21_from_int_to_decimal(1, &ad);
        add_bit(value, ad, &value);
      }
      s21_set_scale(&value, 0);
      s21_copy(result, value);
    }
    status = OK;
  }
  return status;
}
