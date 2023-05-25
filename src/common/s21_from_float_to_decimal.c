#include "../s21_decimal.h"

/*
 * #13
 * Из float в decimal
 * */

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_clean(dst);
  if (src == 0) {
    return OK;
  }
  char str_decimal[100] = {'\0'};
  int status = OK;
  int exp = 0;
  float float_no_exp = 0;
  if (is_too_big(fabs(src)) || is_too_small(fabs(src))) {
    return ERR_CONVERT;
  }
  if (src < 0) {
    dst->bits[3] = MINUS_SIGN;
    src *= -1;
  }
  sprintf(str_decimal, "%.6e", src);
  int exp_flag = 1, sign;
  int exp_pow = 0, float_pow = 0;
  for (int i = strlen(str_decimal) - 1; i >= 0; i--) {
    if (str_decimal[i] == '.') {
      continue;
    } else if (str_decimal[i] == '+' || str_decimal[i] == '-') {
      sign = (str_decimal[i] - 44) * -1;
    } else if (str_decimal[i] == 'e') {
      exp_flag = 0;
    } else {
      if (exp_flag) {
        exp += (str_decimal[i] - 48) * pow(10, exp_pow);
        exp_pow++;
      } else {
        float_no_exp += (str_decimal[i] - 48) * pow(10, float_pow);
        float_pow++;
      }
    }
  }
  if (exp == 0) {
    while ((int)float_no_exp % 10 == 0) {
      float_no_exp /= 10;
      exp++;
    }
    dst->bits[LOW] = (int)float_no_exp;
    s21_set_scale(dst, 6 - exp);
  } else {
    if (sign < 0) {
      while ((int)float_no_exp % 10 == 0) {
        float_no_exp /= 10;
        exp--;
      }
      dst->bits[LOW] = (int)float_no_exp;
      s21_set_scale(dst, exp + 6);
    } else {
      if (exp >= 6) {
        while (exp - 6 > 0) {
          float_no_exp *= 10;
          exp--;
        }
        if (is_too_big(fabs(float_no_exp))) {
          status = ERR_CONVERT;
        } else {
          float_to_bin(float_no_exp, dst);
        }
      } else {
        while ((int)float_no_exp % 10 == 0) {
          float_no_exp /= 10;
        }
        dst->bits[LOW] = (int)float_no_exp;
        int float_len = sprintf(str_decimal, "%d", (int)float_no_exp);
        s21_set_scale(dst, float_len - (exp + 1));
      }
    }
  }

  if (s21_get_scale(*dst) > 28) {
    status = ERR_CONVERT;
  }
  // либо конвериторовать 7 цифр децимала и умножать децималы на 10^нужное
  // кол-во нулей
  return status;
}

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//   int status = ERR_CONVERT, scale = 0;
//   double tmp = (double)src;

//   if (dst && src <= MAX_DECIMAL && src >= MIN_DECIMAL) {
//     s21_clean(dst);
//     s21_set_sign(dst, (src < 0.));
//     if (tmp < 0.) tmp *= -1;

//     while (scale < 7 && fabs(tmp - (int)tmp) > EPS) {
//       tmp *= 10.;
//       ++scale;
//     }
//     dst->bits[0] = (int)tmp;
//     s21_s21_set_scale(dst, scale);
//     status = OK;
//   }
//   return status;
// }
