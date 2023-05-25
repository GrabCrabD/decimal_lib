#include "../s21_decimal.h"

// - + - = +
// - + + = -
// + + - = -
// + + + = +

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int check = OK;
  s21_clean(result);
  int res_done_yet = 0;
  overflow_decimal big_val_1 = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  overflow_decimal big_val_2 = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  to_overflow(value_1, &big_val_1);
  to_overflow(value_2, &big_val_2);
  if (big_val_1.scale != big_val_2.scale) {
    check = big_scale_eq(&big_val_1, &big_val_2);
  }
  overflow_decimal tmp_res = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  if (big_val_1.sign == 0 && big_val_2.sign == 0) {
    //  если оба положительные
    big_bit_addition(&big_val_1, &big_val_2, &tmp_res, OK);
  } else if (big_val_1.sign && big_val_2.sign == 0) {
    //   val_1 - отрицательное, val_2 - положительное
    big_val_1.sign = 0;
    if (big_s21_is_equal(big_val_1, big_val_2)) {  // взаимоуничтожаются
      s21_clean(result);
      res_done_yet = 1;
    } else if (big_s21_is_greater(big_val_1, big_val_2)) {
      // если отрицательное больше
      big_convert_to_addcode(&big_val_2);
      big_bit_addition(&big_val_1, &big_val_2, &tmp_res, EXTRA_CODE);
      tmp_res.sign = 1;
    } else {
      // если положительное больше
      big_convert_to_addcode(&big_val_1);
      big_bit_addition(&big_val_1, &big_val_2, &tmp_res, EXTRA_CODE);
      tmp_res.sign = 0;
    }
    tmp_res.scale = big_val_1.scale;
  } else if (!big_val_1.sign && big_val_2.sign) {
    //   val_1 - положительное, val_2 - отрицательное
    big_val_2.sign = 0;
    if (big_s21_is_equal(big_val_1, big_val_2)) {
      s21_clean(result);
    } else if (big_s21_is_greater(big_val_2, big_val_1)) {
      // если отрицательное больше
      big_convert_to_addcode(&big_val_1);
      big_bit_addition(&big_val_1, &big_val_2, &tmp_res, EXTRA_CODE);
      tmp_res.sign = 1;
    } else {
      // если положительное больше
      big_convert_to_addcode(&big_val_2);
      big_bit_addition(&big_val_1, &big_val_2, &tmp_res, EXTRA_CODE);
      tmp_res.sign = 0;
    }
    tmp_res.scale = big_val_1.scale;
  } else {
    // оба отрицательных
    big_val_1.sign = 0;
    big_val_2.sign = 0;
    big_bit_addition(&big_val_1, &big_val_2, &tmp_res, OK);
    tmp_res.sign = 1;
  }
  if (!res_done_yet) {
    tmp_res.scale = big_val_1.scale;
    overflow_decimal ten = {{10, 0, 0, 0, 0, 0, 0}, 0, 0};
    overflow_decimal remainder = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    int bank_round = 0;
    while (tmp_res.bits[5] || tmp_res.bits[4] || tmp_res.bits[3]) {
      if (!tmp_res.bits[5] && !tmp_res.bits[4] && tmp_res.bits[3] &&
          tmp_res.scale == 1) {
        bank_round = 1;
        break;
      }
      if (tmp_res.scale) {
        big_div_only_bits(tmp_res, ten, &remainder, &tmp_res);
        tmp_res.scale = tmp_res.scale - 1;
      } else {
        check = (!tmp_res.sign) ? TOO_BIG_OR_INF : TOO_SMALL_OR_NEG_INF;
        s21_clean(result);
        break;
      }
    }
    if (bank_round) {
      big_div_only_bits(tmp_res, ten, &remainder, &tmp_res);
      tmp_res.scale = tmp_res.scale - 1;
      overflow_decimal five = {{5, 0, 0, 0, 0, 0, 0}, 0, 0};
      if (big_s21_is_greater(remainder, five)) {
        check = (!tmp_res.sign) ? TOO_BIG_OR_INF : TOO_SMALL_OR_NEG_INF;
        s21_clean(result);
      } else {
        if (big_s21_is_equal(remainder, five)) {
          if (!get_bit(tmp_res, 0)) {
            check = (!tmp_res.sign) ? TOO_BIG_OR_INF : TOO_SMALL_OR_NEG_INF;
            s21_clean(result);
          }
        }
      }
    }
    if (check == OK) {
      result->bits[0] = tmp_res.bits[0];
      result->bits[1] = tmp_res.bits[1];
      result->bits[2] = tmp_res.bits[2];
      s21_set_scale(result, tmp_res.scale);
      s21_set_sign(result, tmp_res.sign);
    }
  }
  return check;
}

// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int status = OK, sign = (s21_get_sign(value_1)) ^ (s21_get_sign(value_2));
//   if (sign) {
//     if (s21_get_sign(value_2)) {
//       s21_negate(value_2, &value_2);
//       status = s21_sub(value_1, value_2, result);
//     } else {
//       s21_negate(value_1, &value_1);
//       status = s21_sub(value_2, value_1, result);
//     }
//   } else {
//     int znak = s21_get_sign(value_1);
//     s21_alligment_scale(&value_1, &value_2);
//     int scale = s21_get_scale(value_1);
//     if ((status = add_bit(value_1, value_2, result))) {
//       printf("\nin s21_add problem whith status...\n");
// // что-то можно сделать со степенью
//     } else {
//       s21_set_sign(result, znak);
//       s21_set_scale(result, scale);
//     }
//   }
//   return status;
// }

// int add_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int status = OK;
//   s21_decimal extent;
//   s21_clean(&extent);

//   while (value_2.bits[0] || value_2.bits[1] || value_2.bits[2])
//   {
//     for (int i = 0; i < 3; i++) {
//       extent.bits[i] = value_1.bits[i] & value_2.bits[i];
//       value_1.bits[i] = value_1.bits[i] ^ value_2.bits[i];
//     }

//     if (95 == s21_last_bit(extent)) {
//       status = s21_get_sign(value_1) ? TOO_SMALL_OR_NEG_INF : TOO_BIG_OR_INF;
//       break;
//     } else {
//       s21_shift_left(&extent);
//       s21_copy(&value_2, extent);
//     }
//   }
//   s21_copy(result, value_1);
//   return status;
// }

// int test_add(int value_1, int value_2) {
//   int extent = (value_1 & value_2) << 1;
//   int overlay = value_1 ^ value_2;

//   if (extent == 0)
//     return overlay;

//   test_add(extent, overlay);
// }
