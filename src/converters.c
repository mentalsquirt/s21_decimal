#include "s21_decimal.h"


/*
  **ERROR CODES FOR CONVERSION MODULE**

  s21_conversion_errors enum:
    S21_CONVERSION_OK = 0,
    S21_CONVERSION_ERROR = 1
*/


/*
  converts an integer number into s21_decimal
  returns s21_conversion_errors int code
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_conversion_errors error = S21_CONVERSION_OK;
  if (!dst) error = S21_CONVERSION_ERROR;
  if (error == S21_CONVERSION_OK) {
    *dst = s21_decimal_get_zero();
    int sign;
    if (src < 0) {
      sign = S21_NEGATIVE;
      // -INT_MIN cannot be represented as an int
      if (src != INT_MIN) {
        src = -src;
      }
    } else {
      sign = S21_POSITIVE;
    }
    dst->bits[0] = src;
    s21_decimal_set_sign(dst, sign);
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  return 0;  // TODO
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  return 0;  // TODO
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  return 0;  // TODO
}
