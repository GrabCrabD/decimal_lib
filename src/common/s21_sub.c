#include "../s21_decimal.h"

// - - - = -
// - - + = +
// + - - = +
// + - + = -

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_clean(result);
  overflow_decimal val_1 = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  overflow_decimal val_2 = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  to_overflow(value_1, &val_1);
  to_overflow(value_2, &val_2);
  if (val_1.scale != val_2.scale) {
    big_scale_eq(&val_1, &val_2);
  }
  int check = OK;
  int res_sign = 1;
  int res_done = 0;
  overflow_decimal tmp_res = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  if (val_1.sign != val_2.sign) {
    // разные знаки, значит ++ или --
    res_sign = val_1.sign;
    val_1.sign = 0;
    val_2.sign = 0;
    big_bit_addition(&val_1, &val_2, &tmp_res, OK);
    tmp_res.sign = res_sign;
  } else {
    // знаки одинаковые, значит +- или -+
    if (big_s21_is_equal(val_1, val_2)) {
      // числа одинаковые, значит взаимоуничтожаются
      s21_clean(result);
      res_done = 1;
    } else {
      // числа разные - решаем что из чего и какой знак
      val_1.sign = 0;
      val_2.sign = 0;
      //  смотрим какое из чисел больше по модулю
      if (big_s21_is_greater(val_1, val_2)) {
        // меньшее из двух переведем в доп код и сложим
        big_convert_to_addcode(&val_2);
        big_bit_addition(&val_1, &val_2, &tmp_res, EXTRA_CODE);
        res_sign = (s21_get_sign(value_1) == 0) ? 0 : 1;
        tmp_res.sign = res_sign;
      } else {
        // меньшее из двух переведем в доп код и сложим
        big_convert_to_addcode(&val_1);
        big_bit_addition(&val_1, &val_2, &tmp_res, EXTRA_CODE);
        res_sign = (s21_get_sign(value_1) == 0) ? 1 : 0;
        tmp_res.sign = res_sign;
      }
    }
  }
  if (!res_done) {
    tmp_res.scale = val_1.scale;
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

// int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int status = OK, sign = (s21_get_sign(value_1)) ^ (s21_get_sign(value_2));
//   if (sign) {
//     s21_negate(value_2, &value_2);
//     status = s21_add(value_1, value_2, result);
//   } else {
//     int znak = s21_get_sign(value_1);
//     s21_decimal extent;
//     s21_alligment_scale(&value_1, &value_2);
//     int scale = s21_get_scale(value_1);
//     if (s21_is_less_or_equal_abs(value_1, value_2)) {
//       s21_swap(&value_1, &value_2);
//       znak = znak ? 0 : 1;
//     }

//     while (value_2.bits[0] || value_2.bits[1] || value_2.bits[2])
//     {
//       for (int i = 0; i < 3; i++) {
//         extent.bits[i] = ~value_1.bits[i] & value_2.bits[i];
//         value_1.bits[i] = value_1.bits[i] ^ value_2.bits[i];
//       }

//       if (95 == s21_last_bit(extent)) {
//         status = s21_get_sign(value_1) ? TOO_SMALL_OR_NEG_INF :
//         TOO_BIG_OR_INF; break;
//       } else {
//         s21_shift_left(&extent);
//         s21_copy(&value_2, extent);
//       }
//     }

//     s21_copy(result, value_1);
//     s21_set_sign(result, znak);
//     s21_set_scale(result, scale);
//   }
//   return status;
// }

// int sub(int minuend, int subtrahend) {
// 	int extent	= 0x00;

// 	while(subtrahend != 0x00)
// 	{
// 		extent = ((~minuend) & subtrahend);
// 		minuend = minuend ^ subtrahend;
// 		subtrahend = (extent << 1);
// 	}
// 	return minuend;
// }

// int test_sub(int value_1, int value_2) {
//   return test_add(value_1, test_add(~value_2, 1));
// }
