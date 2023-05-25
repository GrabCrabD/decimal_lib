#include "../s21_decimal.h"

/*
 * #16
 * Округляет указанное Decimal число до ближайшего целого числа в сторону
 * отрицательной бесконечности.
 * */

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = ERR_COMPUTING;
  if (result) {
    for (int i = s21_get_scale(value) - 1; i > 0; i--) div_ten(value, &value);
    if (0 < s21_get_scale(value)) {
      int remain = div_ten(value, &value);
      if (remain && s21_get_sign(value)) {
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
