#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

//#include <assert.h>
#include <stdlib.h>
#include <limits.h>
//#include <math.h>

#define DECIMAL_SIZE 4
#define MAX_BITS 128
#define MAX_BITS_INT 32
#define MAX_BITS_INTEGRAL 96

#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

/*
bits[0], bits[1], bits[2] contain the low, middle and high 32 bits 
of the 96-bit integer number accordingly

bits[3] contains the scale factor and sign, using layout as follows:
- 0-15 unused and must be zero (low bits)
- 16-23 contain an exponent between 0 and 28 (indicates the power of 10 to divide the integer number)
- 24-30 unused and must be zero
- 31 sign (0 is positive and 1 is negative)
*/

// main struct of the s21_decimal type
typedef struct {
  unsigned int bits[DECIMAL_SIZE];
} s21_decimal;

// 256 bits struct
typedef struct {
  s21_decimal decimals[2];
} s21_big_decimal;

// union for making it easier to access bits[3]
typedef union {
  int i;
  struct {  /* ':' is bit layout */
    uint32_t low_empty : 16;
    uint32_t exponent : 8;
    uint32_t high_empty : 7;
    uint32_t sign : 1;
  } layout;
} s21_decimal_bit3;

// enum for making it easier to work with signs
typedef enum {
  S21_POSITIVE = 0,
  S21_NEGATIVE = 1
} s21_decimal_sign;

// enum that eliminates the need to use <stdbool.h>
typedef enum {
  S21_TRUE = 1,
  S21_FALSE = 0
} s21_bool;

/*
  ERROR AND RESULT ENUMS
*/
typedef enum {
  S21_ARITHMETIC_OK = 0,
  S21_ARITHMETIC_BIG = 1,
  S21_ARITHMETIC_SMALL = 2,
  S21_ARITHMETIC_ZERO_DIV = 3,
  S21_ARITHMETIC_INCORRECT_DATA = 4
} s21_arithmetic_errors;

typedef enum {
  S21_FALSE = 0,
  S21_TRUE = 1
} s21_comparison_res;

typedef enum {
  S21_CONVERSION_OK = 0,
  S21_CONVERSION_ERROR = 1
} s21_conversion_errors;

typedef enum {
  S21_OTHER_OK = 0,
  S21_OTHER_ERROR = 1
} s21_other_errors;


// binary operations
int s21_test_bit(unsigned int value, int index);
int s21_decimal_test_bit(s21_decimal decimal, int index);
int s21_set_bit(unsigned int value, int index);
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index);
int s21_unset_bit(unsigned int value, int index);
int s21_invert_bit(unsigned int value, int index);
int s21_decimal_get_non_zero_bit(s21_decimal decimal);
/* BINARY SHIFTS */
s21_decimal s21_decimal_binary_shift_left_one(s21_decimal decimal);
s21_decimal s21_decimal_binary_shift_left(s21_decimal decimal, int shift);
s21_decimal s21_decimal_binary_shift_right_one(s21_decimal decimal);
s21_decimal s21_decimal_binary_shift_right(s21_decimal decimal, int shift);
s21_big_decimal s21_big_decimal_binary_shift_left(s21_big_decimal decimal, int shift);
s21_big_decimal s21_big_decimal_binary_shift_right(s21_big_decimal decimal, int shift);
/* BINARY LOGIC */
s21_decimal s21_decimal_binary_and(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_decimal_binary_not(s21_decimal value_1);
s21_decimal s21_decimal_binary_xor(s21_decimal value_1, s21_decimal value_2);
/* BINARY COMPARISON */
int s21_decimal_binary_is_zero(s21_decimal decimal);
int s21_decimal_binary_compare(s21_decimal value_1, s21_decimal value_2);
/* BINARY ADDITION */
s21_decimal s21_decimal_binary_addition(s21_decimal value_1, s21_decimal value_2);
s21_big_decimal s21_big_decimal_binary_addition(s21_big_decimal value_1, s21_big_decimal value_2);
/* BINARY MULTIPLICATION */
s21_big_decimal s21_decimal_binary_multiplication(s21_decimal value_1, s21_decimal value_2);
s21_big_decimal s21_big_decimal_binary_multiplication(s21_big_decimal big_value_1, s21_decimal value_2);
/* BINARY SUBTRACTION */
s21_decimal s21_decimal_binary_subtraction(s21_decimal value_1, s21_decimal value_2);
s21_big_decimal s21_big_decimal_binary_subtraction(s21_big_decimal value_1, s21_big_decimal value_2);
/* BINARY DIVISION */
s21_decimal s21_decimal_binary_division(s21_decimal dividend, s21_decimal divisor, s21_decimal *remainder);


// utility functions operating on bits[3]
int s21_decimal_correctness(s21_decimal decimal);
int s21_decimal_low_empty_check(s21_decimal decimal);
int s21_decimal_high_empty_check(s21_decimal decimal);
int s21_decimal_get_exponent(s21_decimal decimal);
void s21_decimal_set_exponent(s21_decimal *decimal, int exponent);
int s21_decimal_get_sign(s21_decimal decimal);
void s21_decimal_set_sign(s21_decimal *decimal, int sign);


// arithmetic
s21_decimal s21_abs(s21_decimal value);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/* helpers */
int s21_max(int a, int b);
void s21_decimal_levelling(s21_decimal value_1, s21_decimal value_2, s21_big_decimal *value_1_l, s21_big_decimal *value_2_l);


// compare
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);


// converters
int s21_from_int_to_decimal(int src, s21_decimal *dst); // NEEDED FOR ARITHMETIC ADDITION (and levelling)
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);


// constructors
s21_decimal s21_decimal_get_inf(void);
void s21_clear_decimal(s21_decimal *decimal);
s21_decimal s21_decimal_get_zero(void);
void s21_decimal_clear_bit3(s21_decimal *decimal);
s21_big_decimal s21_decimal_to_big_decimal(s21_decimal decimal);


// other (rounding, negate etc.)
int s21_round(s21_decimal value, s21_decimal *result);
int s21_bamk_round(s21_decimal value, s21_decimal *result);

#endif  // SRC_S21_DECIMAL_H_
