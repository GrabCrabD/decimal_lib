#include "s21_decimal.h"

int s21_get_sign(s21_decimal src) { return s21_get_bit(src, 127); }
int s21_get_scale(const s21_decimal src) { return (char)(src.bits[3] >> 16); }
int s21_get_bit(const s21_decimal src, int index) {
  return !!(src.bits[index / 32] & (1u << (index % 32)));
}
// int is_bit(const unsigned value, const int index) {
//   return (value >> index) & 1;
// }

void s21_set_sign(s21_decimal *src, int sign) { s21_set_bit(src, 127, sign); }
void s21_clean(s21_decimal *src) {
  src->bits[0] = src->bits[1] = src->bits[2] = src->bits[3] = 0;
}

int s21_last_bit(const s21_decimal value) {
  int last_bit = 95;
  for (; last_bit >= 0 && !s21_get_bit(value, last_bit); last_bit--)
    ;
  return last_bit;
}

void s21_set_bit(s21_decimal *src, int index, int bit) {
  if (index / 32 < 4 && bit)
    src->bits[index / 32] |= (1u << (index % 32));
  else if (index / 32 < 4 && !bit)
    src->bits[index / 32] &= (~((1u) << (index % 32)));
}

int add_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = OK;
  s21_decimal extent;
  s21_clean(&extent);

  while (value_2.bits[0] || value_2.bits[1] || value_2.bits[2]) {
    for (int i = 0; i < 3; i++) {
      extent.bits[i] = value_1.bits[i] & value_2.bits[i];
      value_1.bits[i] = value_1.bits[i] ^ value_2.bits[i];
    }

    if (95 == s21_last_bit(extent)) {
      status = s21_get_sign(value_1) ? TOO_SMALL_OR_NEG_INF : TOO_BIG_OR_INF;
      break;
    } else {
      s21_shift_left(&extent);
      s21_copy(&value_2, extent);
    }
  }
  s21_copy(result, value_1);
  return status;
}

void scale_decrease(s21_decimal *value, int shift) {
  for (int y = 0; y < shift; y += 1) {
    unsigned long long overflow = value->bits[2];
    for (int x = 2; x >= 0; x -= 1) {
      value->bits[x] = overflow / 10;
      overflow = (overflow % 10) * (MAX_UINT + 1) + value->bits[x ? x - 1 : x];
    }
  }
  s21_set_scale(value, (s21_get_scale(*value) - shift));
}

void scale_increase(s21_decimal *value) {  // в тупую умножаем на 10
  if ((s21_get_scale(*value) + 1) < 29) {
    s21_set_scale(value, (s21_get_scale(*value) + 1));
    s21_decimal d1 = *value;
    s21_decimal d2 = *value;
    s21_shift_left(&d1);           // *2^1
    s21_shift(&d2, 3, LEFT);       // *2^3
    if (add_bit(d1, d2, value)) {  //  10*x = (2+8)*x = 2x + 8x
      s21_set_bit(value, 96, 1);
    }
  }
}

float get_full_bits(s21_decimal val) {
  int bin_num[96] = {0};
  int k = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      if (val.bits[i] & (1 << j)) {
        bin_num[k] = 1;
      }
      k++;
    }
  }

  float num = 0;
  for (k = 0; k < 96; k++) {
    if (bin_num[k] == 1) {
      num += bin_num[k] * pow(2, k);
    }
  }

  return num;
}

void float_to_bin(float num, s21_decimal *result) {
  int i = 0;
  while (num > 0) {
    s21_set_bit(result, i, (long long int)num % 2);
    i++;
    num /= 2;
  }
}

int is_too_small(float val) {
  int result = 0;
  int scale = 0;
  while ((int)val == 0) {
    scale++;
    val *= 10;
  }
  if (scale > 28) result = 1;
  return result;
}

int is_too_big(float val) {
  int result = 0;
  if (val - 79228162514264337593543950335.0 > 0) {
    result = 1;
  }
  return result;
}

//==========функции=отладки===========================
// void show_int(const unsigned value) {
//   // printf("\n");
//   // printf("%3d = ", value);
//   for (int i = 32; i > 0; i--) {
//     if (i % 4 == 0 && i != 0) printf(" ");
//     printf("%i", is_bit(value, i - 1));
//   }
//   // printf("\n");
// }

// void show_decimal(const s21_decimal *src) {
//   printf("\n");
//   for (int i = 0; i < 3; i++) {
//     printf(" [");
//     show_int(src->bits[i]);
//     printf("] ");
//   }
//   printf(" [");
//   for (int i = 1; i <= 32; i++) {
//     // if (i-1 % 4 == 0 && i != 0) {printf(" ");}

//     if ((i > 0 && i <= 16) || (i > 24 && i <= 31)) {
//       printf("_");
//     } else {
//       printf("%i", is_bit(src->bits[3], i - 1));
//     }
//   }
//   // show_int(src->bits[3]);
//   printf("] ");
// }
//======================================================

int div_ten(s21_decimal value, s21_decimal *result) {
  long long int tmp = 0, remains = 0, Umax = UINT_MAX;
  Umax += 1;

  remains = value.bits[2] % 10;
  value.bits[2] /= 10;

  tmp = value.bits[1];
  tmp += remains * Umax;
  remains = tmp % 10;
  value.bits[1] = tmp / 10;

  tmp = value.bits[0];
  tmp += remains * Umax;
  value.bits[0] = tmp / 10;

  s21_copy(result, value);
  return tmp % 10;
}

void s21_set_scale(s21_decimal *src, int scale) {
  int sign = s21_get_sign(*src);
  src->bits[3] = 0;
  src->bits[3] = src->bits[3] | (scale << 16);
  s21_set_sign(src, sign);
}

void s21_shift_left(s21_decimal *src) {
  int a = s21_get_bit(*src, 31), b = s21_get_bit(*src, 63);
  for (int i = 0; i < 3; i++) src->bits[i] <<= 1;
  s21_set_bit(src, 32, a);
  s21_set_bit(src, 64, b);
}

void s21_shift_right(s21_decimal *src) {
  int a = s21_get_bit(*src, 32), b = s21_get_bit(*src, 64);
  for (int i = 0; i < 3; i++) src->bits[i] >>= 1;
  s21_set_bit(src, 31, a);
  s21_set_bit(src, 63, b);
}

void s21_shift(s21_decimal *src, int step, const int direct) {
  step %= 96;
  if (direct == RIGHT) {
    for (int i = 0; i + step < 96; i++)
      s21_set_bit(src, i, s21_get_bit(*src, i + step));
    for (int i = 96 - step; i < 96; i++) s21_set_bit(src, i, 0);
  } else if (direct == LEFT) {
    for (int i = 95; i - step >= 0; i--)
      s21_set_bit(src, i, s21_get_bit(*src, i - step));
    for (int i = 0; i < step; i++) s21_set_bit(src, i, 0);
    // for (int i = 0; i < step; i++) s21_shift_left(src);
  }
}

void s21_alligment_scale(s21_decimal *value_1, s21_decimal *value_2) {
  if (s21_get_scale(*value_1) != s21_get_scale(*value_2)) {
    if (s21_get_scale(*value_1) < s21_get_scale(*value_2)) {
      s21_alligment_scale(value_2, value_1);
    } else {
      int scaleLow = s21_get_scale(*value_2);
      int scaleHigh = s21_get_scale(*value_1);
      for (; (scaleHigh - scaleLow) && !s21_get_bit(*value_2, 96); ++scaleLow)
        scale_increase(value_2);
      for (; scaleHigh - scaleLow; --scaleHigh) {
        scale_decrease(value_1, scaleHigh - scaleLow);
        s21_set_scale(value_1, scaleLow);
      }
    }
  }
}

void s21_copy(s21_decimal *dst, s21_decimal src) {
  for (int i = 0; i < 4; i++) dst->bits[i] = src.bits[i];
}

void s21_swap(s21_decimal *value_1, s21_decimal *value_2) {
  int tmp, i = 0;
  for (; i < 4; i++) {
    tmp = value_1->bits[i];
    value_1->bits[i] = value_2->bits[i];
    value_2->bits[i] = tmp;
  }
}

int s21_is_less_or_equal_abs(s21_decimal value_1, s21_decimal value_2) {
  int less_or_equal = TRUE;

  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(value_1, i) > s21_get_bit(value_2, i)) {
      less_or_equal = FALSE;
      break;
    } else if (s21_get_bit(value_2, i) && !s21_get_bit(value_1, i)) {
      break;
    }
  }
  return less_or_equal;
}

int is_empty(const s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

//
//  overflow
//

int get_bit(const overflow_decimal value, int index) {
  return !!(value.bits[index / 32] & (1u << (index % 32)));
}

void set_bit(overflow_decimal *value, int index, int bit) {
  if (index / 32 < 6 && bit)
    value->bits[index / 32] |= (1u << (index % 32));
  else if (index / 32 < 6 && !bit)
    value->bits[index / 32] &= (~((1u) << (index % 32)));
}

void clean(overflow_decimal *value) {
  memset(&(value->bits), 0, sizeof(value->bits));
  value->sign = 0;
  value->scale = 0;
}

int last_bit(const overflow_decimal value) {
  int last_bit = 191;
  for (; last_bit >= 0 && !get_bit(value, last_bit); last_bit--)
    ;
  return last_bit;
}

// void show(const overflow_decimal value) {
//   printf("\n");
//   for (int i = 0; i < 6; i++) {
//     printf("[");
//     show_int(value.bits[i]);
//     printf("] ");
//   }
// }

void shift(overflow_decimal *value, int step, const int direct) {
  step %= 192;
  if (direct == RIGHT) {
    for (int i = 0; i + step < 192; i++)
      set_bit(value, i, get_bit(*value, i + step));
    for (int i = 192 - step; i < 192; i++) set_bit(value, i, 0);
  } else if (direct == LEFT) {
    for (int i = 192; i - step >= 0; i--)
      set_bit(value, i, get_bit(*value, i - step));
    for (int i = 0; i < step; i++) set_bit(value, i, 0);
  }
}

void shift_l(overflow_decimal *value) {
  int a = get_bit(*value, 31);
  int b = get_bit(*value, 63);
  int c = get_bit(*value, 95);
  int d = get_bit(*value, 127);
  int e = get_bit(*value, 159);
  for (int i = 0; i < 6; i++) value->bits[i] <<= 1;
  set_bit(value, 32, a);
  set_bit(value, 64, b);
  set_bit(value, 96, c);
  set_bit(value, 128, d);
  set_bit(value, 160, e);
}

void shift_r(overflow_decimal *value) {
  int a = get_bit(*value, 32);
  int b = get_bit(*value, 64);
  int c = get_bit(*value, 96);
  int d = get_bit(*value, 128);
  int e = get_bit(*value, 160);
  for (int i = 0; i < 6; i++) value->bits[i] >>= 1;
  set_bit(value, 31, a);
  set_bit(value, 63, b);
  set_bit(value, 95, c);
  set_bit(value, 127, d);
  set_bit(value, 159, e);
}

void to_overflow(s21_decimal src, overflow_decimal *dst) {
  dst->bits[LOW] = src.bits[LOW];
  dst->bits[MID] = src.bits[MID];
  dst->bits[HIGH] = src.bits[HIGH];
  dst->scale = s21_get_scale(src);
  dst->sign = s21_get_sign(src);
}

void to_decimal(s21_decimal *dst, overflow_decimal src) {
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  s21_set_scale(dst, src.scale);
  s21_set_sign(dst, src.sign);
}

int big_scale_eq(overflow_decimal *val_1, overflow_decimal *val_2) {
  int check = OK;
  overflow_decimal *small = NULL;
  if (val_1->scale > val_2->scale) {
    small = val_2;
  } else {
    small = val_1;
  }
  int scaleSmall = 0;
  overflow_decimal tmp1 = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  while (val_1->scale != val_2->scale) {
    // повышение скейла
    scaleSmall = small->scale;
    tmp1 = *small;
    // умножение на 10
    for (int i = 0; i < 9; i++) {
      check = big_bit_addition(small, &tmp1, small, OK);
      if (check == TOO_BIG_OR_INF) {
        break;
      }
    }
    small->scale = scaleSmall + 1;
  }
  return check;
}

int big_s21_is_equal(overflow_decimal first, overflow_decimal second) {
  int result = 1;
  if ((first.sign == second.sign) || !big_zero_check(first, second)) {
    if (first.scale != second.scale) {
      big_scale_eq(&first, &second);
    }
    for (int i = 0; i < 6; i++) {
      if (first.bits[i] != second.bits[i]) {
        result = 0;
        break;
      }
    }
  } else {
    result = 0;
  }
  return result;
}

int big_zero_check(overflow_decimal val_1, overflow_decimal val_2) {
  int is_zero = 1;
  if (!val_1.bits[0] && !val_2.bits[0] && !val_1.bits[1] && !val_2.bits[1] &&
      !val_1.bits[2] && !val_2.bits[2] && !val_1.bits[3] && !val_2.bits[3] &&
      !val_1.bits[4] && !val_2.bits[4] && !val_1.bits[5] && !val_2.bits[5]) {
    is_zero = 0;
  }
  return is_zero;
}

int big_s21_is_greater(overflow_decimal first, overflow_decimal second) {
  int result = -1;
  if (first.sign == 0 && second.sign == 1) {
    result = 1;
  } else if (first.sign == 1 && second.sign == 0) {
    result = 0;
  } else {
    if (first.scale != second.scale) {
      big_scale_eq(&first, &second);
    }
    for (int i = 191; i >= 0 && result == -1; i--) {
      int bit_val_1 = get_bit(first, i);
      int bit_val_2 = get_bit(second, i);
      if (bit_val_1 && !bit_val_2) {
        result = 1;
      } else if (!bit_val_1 && bit_val_2) {
        result = 0;
      }
      if (result != -1) {
        if (first.sign && second.sign) {
          result = !result;
        }
      }
    }
  }

  if (big_s21_is_equal(first, second)) {
    result = 0;
  }
  return result;
}

void big_convert_to_addcode(overflow_decimal *val_1) {
  overflow_decimal result = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
  overflow_decimal one = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
  // инвертируем мантиссу
  val_1->bits[LOW] = ~val_1->bits[LOW];
  val_1->bits[MID] = ~val_1->bits[MID];
  val_1->bits[HIGH] = ~val_1->bits[HIGH];
  val_1->bits[3] = ~val_1->bits[3];
  val_1->bits[4] = ~val_1->bits[4];
  val_1->bits[5] = ~val_1->bits[5];
  // прибавляем 1
  big_bit_addition(val_1, &one, &result, OK);
  val_1->bits[LOW] = result.bits[LOW];
  val_1->bits[MID] = result.bits[MID];
  val_1->bits[HIGH] = result.bits[HIGH];
  val_1->bits[3] = result.bits[3];
  val_1->bits[4] = result.bits[4];
  val_1->bits[5] = result.bits[5];
}

int big_bit_addition(overflow_decimal *val_1, overflow_decimal *val_2,
                     overflow_decimal *result, int code) {
  int status = OK;
  int one_in_head = 0;
  for (int i = 0; i < 192; i++) {
    int bit_val_1 = get_bit(*val_1, i);
    int bit_val_2 = get_bit(*val_2, i);
    if (bit_val_1 == 0 && bit_val_2 == 0) {
      if (one_in_head) {
        set_bit(result, i, 1);
        one_in_head = 0;
      } else {
        set_bit(result, i, 0);
      }
    } else if (bit_val_1 != bit_val_2) {
      if (one_in_head) {
        set_bit(result, i, 0);
        one_in_head = 1;
      } else {
        set_bit(result, i, 1);
      }
    } else if (bit_val_1 && bit_val_2) {
      if (one_in_head) {
        set_bit(result, i, 1);
        one_in_head = 1;
      } else {
        set_bit(result, i, 0);
        one_in_head = 1;
      }
    }
    if (i == 191 && one_in_head == 1 && code != EXTRA_CODE) {
      status = TOO_BIG_OR_INF;
    }
  }
  return status;
}

int big_s21_is_greater_or_equal(overflow_decimal first,
                                overflow_decimal second) {
  int res = 0;
  if (big_s21_is_greater(first, second) || big_s21_is_equal(first, second)) {
    res = 1;
  }
  return res;
}

void big_div_only_bits(overflow_decimal value_1, overflow_decimal value_2,
                       overflow_decimal *div_remainder,
                       overflow_decimal *result) {
  int tmp = 1;
  int check = 1;
  int scale_val_1 = value_1.scale;
  value_1.scale = 0;
  value_2.scale = 0;
  int sign_val_1 = value_1.sign;
  value_1.sign = 0;
  value_2.sign = 0;
  if (big_s21_is_greater_or_equal(value_1, value_2)) {
    overflow_decimal sum = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    overflow_decimal t_val = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    overflow_decimal t_val_sup = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    overflow_decimal dif = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    while (check) {
      t_val_sup = value_2;
      int i = 0;
      while (tmp) {
        t_val = value_2;
        shift(&t_val, i, LEFT);
        if (big_s21_is_greater(t_val, value_1)) {
          tmp = 0;
          shift(&t_val_sup, i - 1, LEFT);
          t_val = t_val_sup;
          overflow_decimal one = {{1, 0, 0, 0, 0, 0, 0}, 0, 0};
          shift(&one, i - 1, LEFT);
          overflow_decimal sum_sup = one;
          big_bit_addition(&sum, &sum_sup, &sum, OK);
        }
        i++;
      }
      tmp = 1;
      big_convert_to_addcode(&t_val);
      big_bit_addition(&value_1, &t_val, &dif, EXTRA_CODE);
      if (big_s21_is_greater_or_equal(dif, value_2)) {
        value_1 = dif;
      } else {
        check = 0;
        *div_remainder = dif;
        *result = sum;
      }
    }
    result->scale = scale_val_1;
    result->sign = sign_val_1;
  } else {
    clean(result);
    *div_remainder = value_1;
  }
}

s21_decimal create_decimal(unsigned int low_num, unsigned int mid_num,
                           unsigned int high_num, unsigned int scale_info) {
  s21_decimal d;
  s21_clean(&d);
  d.bits[LOW] = low_num;
  d.bits[MID] = mid_num;
  d.bits[HIGH] = high_num;
  d.bits[3] = scale_info;
  return d;
}