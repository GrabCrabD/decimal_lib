#include "../s21_decimal.h"

/*
 * #14
 * Из decimal в int
 * */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int negative = 1;
  int status = OK;
  int exp = s21_get_scale(src);
  if (s21_get_sign(src)) {
    negative = -1;
  }
  if (exp == 0) {  // без скейла
    unsigned long int num = 0;
    if (src.bits[MID] == 0 && src.bits[HIGH] == 0) {
      num = src.bits[LOW];
    } else {
      status = ERR_CONVERT;
    }

    if (num > INT_MAX) {
      status = ERR_CONVERT;
    } else {
      *dst = num * negative;
    }
  } else {  // со скейлом
    float tmp = 0;
    char full_num[96] = {'\0'};
    sprintf(full_num, "%.0f", get_full_bits(src));
    int k = 0;
    for (int i = strlen(full_num) - 1; i >= 0; i--) {
      if (exp == 0) {
        tmp += (full_num[i] - 48) * pow(10, k);
        k++;
      } else {
        exp--;
      }
    }

    float int_32max = 2147483647.0f;
    if (fabs(tmp) > int_32max) {
      status = ERR_CONVERT;
    } else {
      *dst = (int)tmp * negative;
    }
  }

  return status;
}

// int s21_from_decimal_to_int(s21_decimal src, int *dst) {
//   int status = ERR_CONVERT;
//   float tmp_value = 0;
//   tmp_value = src.bits[0];
//   if (tmp_value <= INT32_MAX) {  // <= поставил
//     if (src.bits[1] == 0 && src.bits[2] == 0) {
//       *dst = src.bits[0];
//       if (s21_get_sign(src)) *dst = -*dst;
//       *dst /= (int)pow(10, s21_get_scale(src));
//       status = OK;
//     }
//   } else {
//     status = ERR_CONVERT;
//   }
//   return status;
// }
