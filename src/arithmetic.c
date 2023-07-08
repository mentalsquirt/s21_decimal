#include "s21_decimal.h"

/*
  **ERROR CODES FOR ARITHMETIC MODULE**

  s21_arithmetic_errors enum:
    S21_ARITHMETIC_OK = 0,
    S21_ARITHMETIC_BIG = 1,
    S21_ARITHMETIC_SMALL = 2,
    S21_ARITHMETIC_ZERO_DIV = 3,
    S21_ARITHMETIC_INCORRECT_DATA = 4
*/

// returns the absolute value of a s21_decimal number
s21_decimal s21_abs(s21_decimal value) {
  s21_decimal res = value;
  s21_decimal_set_sign(&res, S21_POSITIVE);
  return res;
}

// performs an addition of value_1 and value_2 and saves into result (returns s21_arithmetic_errors code)
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  if (!result) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
  } else if (s21_decimal_correctness(value_1) || s21_decimal_correctness(value_2)) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
    *result = s21_decimal_get_inf();
  } else {
    // all of the tests are passed
    *result = s21_decimal_get_zero();
    s21_decimal res = s21_decimal_get_zero();

    int sign1 = s21_decimal_get_sign(value_1);
    int sign2 = s21_decimal_get_sign(value_2);

    if(sign1 == S21_POSITIVE && sign2 == S21_POSITIVE) {
      // handle addition
    }
  }
}

// function performs addition on two positive s21_decimal numbers (returns s21_arithmetic_errors code)
int s21_add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  int exponent_max = s21_max(exponent_1, exponent_2);
  // level the values (both the exponent and sign will be nullified)
  s21_decimal_levelling(value_1, value_2, &big_value_1, &big_value_2);
  // ...TODO
}

//TODO
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return 0;
}

//TODO
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return 0;
}

//TODO
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return 0;
}

/* HELPERS */
// returns max of two integers
int s21_max(int a, int b) {
  return a > b ? a : b;
}

/*
levelled values are only the integral part of the decimal, hence if exponents
differ a lot — we may get a lot of trailing zeros

we store the levelled values in the s21_big_decimal in case of overflow

...todo
*/
void s21_decimal_levelling(s21_decimal value_1, s21_decimal value_2, s21_big_decimal *big_value_1, s21_big_decimal *big_value_2) {
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  s21_decimal tmp1 = value_1;
  s21_decimal tmp2 = value_2;
  s21_decimal_clear_bit3(&tmp1);
  s21_decimal_clear_bit3(&tmp2);
  if (exponent_1 > exponent_2) {
    // TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  } else if (exponent_1 < exponent_2) {

  } else {

  }
}
