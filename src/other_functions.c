#include "s21_decimal.h"

/*
  **ERROR CODES FOR OTHER FUNCTIONS MODULE**

  s21_other_errors enum:
    S21_OTHER_OK = 0,
    S21_OTHER_ERROR = 1
*/


/*
  rounds value to the closest integer number and stores in *result
  if the value is equidistant from two integers — rounds to the closest even number
  returns an error code
*/
int s21_round(s21_decimal value, s21_decimal *result) {
  s21_other_errors error = S21_OTHER_OK;
  if (!result) {
    error = S21_OTHER_ERROR;
  } else if (!s21_decimal_correctness(value)) {
    error = S21_OTHER_ERROR;
    *result = s21_decimal_get_inf();
  } else {
    *result = s21_decimal_get_zero();
    int sign = s21_decimal_get_sign(value);
    s21_decimal fraction;
    s21_decimal value_cleaned;
    s21_decimal value_unsigned = s21_abs(value);
    s21_truncate(value_unsigned, &value_cleaned);
    // s21_sub(value_unsigned, value_cleaned, &fraction);
  }
}

// {{0x5, 0x0, 0x0, 0x10000}} is 0.5 in decimal
int s21_bank_round(s21_decimal value, s21_decimal *result) {
  return 0;  // TODO!!!!!!!!
}

/*
  removes trailing zeros from an s21_decimal
  returns new s21_decimal without the trailing zeros
*/
s21_decimal s21_decimal_remove_trailing_zeros(s21_decimal value) {
  s21_decimal res = value;
  int sign = s21_decimal_get_sign(value);
  int exponent = s21_decimal_get_exponent(value);
  if (s21_decimal_correctness(value) && exponent > 0) {
    s21_decimal remainder = s21_decimal_get_zero();
    s21_decimal tmp = value;
    s21_decimal_clear_bit3(&tmp);
    s21_decimal ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(10, &ten);
    while (exponent > 0) {
      tmp = s21_decimal_binary_division(tmp, ten, &remainder);
      if (s21_decimal_binary_is_zero(remainder)) {
        --exponent;
        res = tmp;
      } else {
        break;
      }
    }
    s21_decimal_set_exponent(&res, exponent);
    s21_decimal_set_sign(&res, sign);
  }
  return res;
}

/*
  truncates all of the fractional digits of a s21_decimal, including trailing zeros
  writes into *result
  returns an error code
*/
int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_other_errors error = S21_OTHER_OK;
  if (!result) {
    error = S21_OTHER_ERROR;
  } else if (!s21_decimal_correctness(value)) {
    error = S21_OTHER_ERROR;
    *result = s21_decimal_get_inf();
  } else {
    int exponent = s21_decimal_get_exponent(value);
    s21_decimal tmp = value;
    s21_decimal_clear_bit3(&tmp);
    *result = s21_decimal_get_zero();
    s21_decimal power_of_ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(pow(10., exponent), &power_of_ten);
    tmp = s21_decimal_binary_division(tmp, power_of_ten, NULL);
    *result = tmp;
    if (s21_decimal_get_sign(value) == S21_NEGATIVE) {
      s21_decimal_set_sign(result, S21_NEGATIVE);
    }
  }
  return error;
}
