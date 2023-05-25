#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef _S21_DECIMAL_H_
#define _S21_DECIMAL_H_
//  Функции возвращают код ошибки:
#define OK 0
#define VARY_BIG_OR_INFINITY 1
#define VARY_LIT_OR_NEG_INFI 2
#define ZERO_DIVISION 3
#define EXTRA_CODE 4
//  Возвращаемое значение: (Операторы сравнение)
#define FALSE 0
#define TRUE 1
//  Возвращаемое значение - код ошибки: (Преобразователи и Другие функции)
#define ERR_CONVERT 1
#define ERR_COMPUTING 1
//  для s21_shift()
#define RIGHT 8907
#define LEFT 1234

// из ветки Oakensh =======
#define MAX_DECIMAL \
  79228162514264337593543950335.  //  79,228,162,514,264,337,593,543,950,335
#define MIN_DECIMAL -79228162514264337593543950335.
#define MAX_POW 28
#define EPS 1e-6
#define TOO_BIG_OR_INF 1
#define TOO_SMALL_OR_NEG_INF 2
#define MAX_UINT 4294967295
#define MINUS_SIGN 2147483648
#define DEFAULT_BASE 65536
// ========================

enum { LOW, MID, HIGH, SCALE };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
  int sign;
  int scale;
} overflow_decimal;

//
// Arithmetic Operators
//

/**
 * @brief Сложение двух чисел децимал
 * @param value_1 число децимал
 * @param value_2 число децимал
 * @param result указатель на результат вычитания в децимал
 * @return код ошибки
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/**
 * @brief Вычитание двух чисел децимал
 * @param value_1 число децимал
 * @param value_2 число децимал
 * @param result указатель на результат вычитания в децимал
 * @return код ошибки
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/**
 * @brief Умножение двух чисел децимал
 * @param value_1 число децимал
 * @param value_2 число децимал
 * @param result указатель на результат умножения в децимал
 * @return код ошибки
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/**
 * @brief Деление двух чисел децимал
 * @param value_1 делимое децимал
 * @param value_2 делитель децимал
 * @param result указатель на результат деления в децимал
 * @return код ошибки
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//
//  Comparison Operators
//

/**
 * @brief Первое число меньше ли второго
 * @param first Первое число децимал
 * @param second Второе число децимал
 * @return 0 - first >= second , 1 - first < second
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
/**
 * @brief Первое число меньше ли второго
 * @param first Первое число децимал
 * @param second Второе число децимал
 * @return 0 - first >= second , 1 - first < second
 */
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
/**
 * @brief Первое число больше ли второго
 * @param first Первое число децимал
 * @param second Второе число децимал
 * @return 0 - second >= first, 1 - first > second
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
/**
 * @brief Первое число больше или равно ли второго
 * @param first Первое число децимал
 * @param second Второе число децимал
 * @return 0 - second > first, 1 - first >= second
 */
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
/**
 * @brief Равны ли два числа децимал
 * @param first Первое число децимал
 * @param second Второе число децимал
 * @return 0 - first != second, 1 - first == second
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
/**
 * @brief Не равны ли два числа децимал
 * @param first Первое число децимал
 * @param second Второе число децимал
 * @return 0 - first == second, 1 - first != second
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

//
//  Convertors and parsers
//

/**
 * @brief Перевод из int в децимал
 * @param src число int
 * @param dst указатель на число децимал
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst);
/**
 * @brief Перевод из float в децимал
 * @param src число float
 * @param dst указатель на число децимал
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst);
/**
 * @brief Перевод из децимал в int
 * @param src число децимал
 * @param dst указатель на число int
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst);
/**
 * @brief Перевод из децимал в float
 * @param src число децимал
 * @param dst указатель на число float
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst);

//
//  Another functions
//

/**
 * @brief Округляет число decimal до ближайшего целого числа в сторону
 * отрицательной бесконечности
 * @param value число децимал
 * @param result указатель на округленный decimal
 * @return 0 - ОК, 1 - ошибка вычисления
 */
int s21_floor(s21_decimal value, s21_decimal *result);
/**
 * @brief Округляет число decimal до ближайшего целого
 * (банковское округление!)
 * @param value число децимал
 * @param result указатель на округленный decimal
 * @return 0 - ОК, 1 - ошибка вычисления
 */
int s21_round(s21_decimal value, s21_decimal *result);
/**
 * @brief Отбрасывает дробные цифры указанного Decimal, включая конечные нули
 * @param value число децимал
 * @param result указатель на decimal несущий только целые цифры
 * @return 0 - ОК, 1 - ошибка вычисления
 */
int s21_truncate(s21_decimal value, s21_decimal *result);
/**
 * @brief Умножает указанный Decimal на -1.
 * @param value число децимал
 * @param result указатель на decimal * (-1)
 * @return 0 - ОК, 1 - ошибка вычисления
 */
int s21_negate(s21_decimal value, s21_decimal *result);

//
//  extra_func.c
//

//  catch one bit
int is_bit(const unsigned value, const int index);
int s21_last_bit(const s21_decimal value);
int s21_get_scale(const s21_decimal src);
int get_scale(const s21_decimal src);
void s21_set_scale(s21_decimal *src, int scale);
int s21_get_bit(const s21_decimal src, int index);
void s21_set_bit(s21_decimal *src, int index, int bit);

void s21_shift(s21_decimal *src, int step, const int direct);
void s21_shift_left(s21_decimal *src);
void s21_shift_right(s21_decimal *src);
int is_empty(const s21_decimal value);

int s21_get_sign(s21_decimal src);
void s21_set_sign(s21_decimal *src, int sign);
void s21_clean(s21_decimal *src);
void s21_copy(s21_decimal *dst, s21_decimal src);
void s21_swap(s21_decimal *value_1, s21_decimal *value_2);
int add_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_less_or_equal_abs(s21_decimal value_1, s21_decimal value_2);

int div_ten(s21_decimal value, s21_decimal *result);
void scale_increase(s21_decimal *value);
void scale_decrease(s21_decimal *value, int shift);
void s21_alligment_scale(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal create_decimal(unsigned int low_num, unsigned int mid_num,
                           unsigned int high_num, unsigned int scale_info);
float get_full_bits(s21_decimal val);
void float_to_bin(float num, s21_decimal *result);
int is_too_small(float val);
int is_too_big(float val);

//
//  overflow_decimal
//

void show(const overflow_decimal value);
int last_bit(const overflow_decimal value);
int get_bit(const overflow_decimal src, int index);
void set_bit(overflow_decimal *value, int index, int bit);
void clean(overflow_decimal *value);

void to_overflow(s21_decimal src, overflow_decimal *dst);
void to_decimal(s21_decimal *dst, overflow_decimal src);
void shift(overflow_decimal *src, int step, const int direct);
void shift_l(overflow_decimal *src);
void shift_r(overflow_decimal *src);

int big_bit_addition(overflow_decimal *val_1, overflow_decimal *val_2,
                     overflow_decimal *result, int code);
int big_scale_eq(overflow_decimal *val_1, overflow_decimal *val_2);
int big_zero_check(overflow_decimal val_1, overflow_decimal val_2);
int big_s21_is_equal(overflow_decimal first, overflow_decimal second);
void big_convert_to_addcode(overflow_decimal *val_1);
int big_s21_is_greater(overflow_decimal first, overflow_decimal second);
void big_div_only_bits(overflow_decimal value_1, overflow_decimal value_2,
                       overflow_decimal *div_remainder,
                       overflow_decimal *result);
int big_s21_is_greater_or_equal(overflow_decimal first,
                                overflow_decimal second);
// void to_overflow_bets(s21_decimal src, overflow_decimal *dst);

#endif  // _S21_DECIMAL_H_
