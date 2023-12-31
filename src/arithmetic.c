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


/*
  returns the absolute value of a s21_decimal number
*/
s21_decimal s21_abs(s21_decimal value) {
  s21_decimal res = value;
  s21_decimal_set_sign(&res, S21_POSITIVE);
  return res;
}


/*
  performs an addition of value_1 and value_2 and saves into result
  returns s21_arithmetic_errors code
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  if (!result) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
  } else if (!s21_decimal_correctness(value_1) || !s21_decimal_correctness(value_2)) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
    *result = s21_decimal_get_inf();
  } else {
    // all of the tests are passed
    *result = s21_decimal_get_zero();
    s21_decimal res = s21_decimal_get_zero();
    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);
    if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      error = s21_add_helper(value_1, value_2, &res);
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
      // TODO: s21_sub required for s21_add to work properly
      error = s21_sub(value_1, s21_abs(value_2), &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
      // TODO: s21_sub required for s21_add to work properly
      error = s21_sub(s21_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      error = s21_add_helper(s21_abs(value_1), s21_abs(value_2), &res);
      s21_negate(res, &res);
    }
    if (s21_decimal_get_sign(res) == S21_NEGATIVE && error == S21_ARITHMETIC_BIG) {
      error = S21_ARITHMETIC_SMALL;
    }
    *result = res;
  }
  return error;
}

//TODO
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return 0;
}

/*
  performs multiplication of value_1 and value_2 and saves into result
  returns s21_arithmetic_errors code
*/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  if (!result) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
  } else if (!s21_decimal_correctness(value_1) || !s21_decimal_correctness(value_2)) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
    *result = s21_decimal_get_inf();
  } else {
    // all of the tests are passed
    *result = s21_decimal_get_zero();
    s21_decimal res = s21_decimal_get_zero();
    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);
    if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      error = s21_mul_helper(value_1, value_2, &res);
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
      error = s21_mul_helper(value_1, s21_abs(value_2), &res);
      s21_negate(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
      error = s21_mul_helper(s21_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      error = s21_mul_helper(s21_abs(value_1), s21_abs(value_2), &res);
    }
    if (error == S21_ARITHMETIC_BIG) {
      if (s21_decimal_get_sign(res) == S21_NEGATIVE) {
        error = S21_ARITHMETIC_SMALL;
      }
    }
    if (error == S21_ARITHMETIC_OK && s21_is_not_equal(value_1, s21_decimal_get_zero()) &&
        s21_is_not_equal(value_2, s21_decimal_get_zero()) && s21_is_equal(res, s21_decimal_get_zero())) {
      error = S21_ARITHMETIC_SMALL;
    }
    *result = res;
  }
  return error;
}

//TODO
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return 0;
}

/*
HELPERS
*/

/*
  function performs addition on two positive s21_decimal numbers
  writes into *result
  returns s21_arithmetic_errors code
*/
int s21_add_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  int exponent_max = s21_max(exponent_1, exponent_2);
  // level the values (both the exponent and sign will be nullified)
  s21_decimal_levelling(value_1, value_2, &big_value_1, &big_value_2);
  // add the values as two humongous integral numbers
  s21_big_decimal big_res = s21_big_decimal_binary_addition(big_value_1, big_value_2);
  // figure out how to shift the decimal point to fit the result into 96 bits of mantissa
  int shift = s21_big_decimal_shift_to_decimal(big_res);
  int res_exponent = exponent_max - shift;
  if (res_exponent < 0) {
    error = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    s21_decimal ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(10, &ten);
    while (shift > 28) {
      big_res = s21_big_decimal_binary_division(big_res, s21_decimal_to_big_decimal(ten), NULL);
      --shift;
    }
    s21_big_decimal remainder = s21_decimal_to_big_decimal(s21_decimal_get_zero());
    s21_decimal power_of_ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(pow(10., shift), &power_of_ten);
    s21_big_decimal big_power_of_ten = s21_decimal_to_big_decimal(power_of_ten);
    // make the result fit into 96 bits of mantissa
    big_res = s21_big_decimal_binary_division(big_res, big_power_of_ten, &remainder);
    s21_decimal_set_exponent(&remainder.decimals[0], shift);
    big_res.decimals[0] = s21_bank_round(big_res.decimals[0], remainder.decimals[0]);
    s21_decimal_set_exponent(&big_res.decimals[0], res_exponent);
    if (!s21_decimal_binary_is_zero(big_res.decimals[1]) || !s21_decimal_correctness(big_res.decimals[0])) {
      error = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    } else {
      *result = big_res.decimals[0];
    }
  }
  return error;
}

/*
  function performs multiplication on two positive s21_decimal numbers
  writes into *result
  returns s21_arithmetic_errors code
*/
int s21_mul_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  s21_decimal_clear_bit3(&value_1);
  s21_decimal_clear_bit3(&value_2);
  s21_big_decimal res = s21_decimal_binary_multiplication(value_1, value_2);
  int shift = s21_big_decimal_shift_to_decimal(res);
  int exponent_res = exponent_1 + exponent_2 - shift;
  if (exponent_res < 0) {
    error = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    s21_decimal ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(10, &ten);
    while (shift > 28) {
      res = s21_big_decimal_binary_division(res, s21_decimal_to_big_decimal(ten), NULL);
      --shift;
    }
    if (exponent_res > 28) {
      s21_big_decimal tmp = res;
      int exponent_tmp = exponent_res;
      while (exponent_tmp > 28) {
        tmp = s21_big_decimal_binary_division(tmp, s21_decimal_to_big_decimal(ten), NULL);
        --exponent_tmp;
      }
      shift = exponent_res - exponent_tmp + shift;
      exponent_res = exponent_tmp;
    }
    s21_big_decimal remainder = s21_decimal_to_big_decimal(s21_decimal_get_zero());
    s21_decimal power_of_ten_tmp = s21_decimal_get_zero();
    s21_from_int_to_decimal(pow(10., (double)shift), &power_of_ten_tmp);
    s21_big_decimal power_of_ten = s21_decimal_to_big_decimal(power_of_ten_tmp);
    res = s21_big_decimal_binary_division(res, power_of_ten, &remainder);
    s21_decimal_set_exponent(&remainder.decimals[0], shift);
    res.decimals[0] = s21_bank_round(res.decimals[0], remainder.decimals[0]);
    s21_decimal_set_exponent(&res.decimals[0], exponent_res);
    if (!s21_decimal_binary_is_zero(res.decimals[1]) || !s21_decimal_correctness(res.decimals[0])) {
      error = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    } else {
      *result = res.decimals[0];
    }
  }
  return error;
}

/*
  returns max of two integers
*/
int s21_max(int value_1, int value_2) {
  return value_1 > value_2 ? value_1 : value_2;
}

/*
  calculates the amount of divisions by 10 for the value 
  to fit into 96bits of mantissa in s21_decimal
  returns an int exponent of 10
*/
int s21_big_decimal_shift_to_decimal(s21_big_decimal value) {
  int res = 0;
  if (!(s21_decimal_binary_is_zero(value.decimals[0]) &&
        s21_decimal_binary_is_zero(value.decimals[1]))) {
    s21_big_decimal max = s21_decimal_to_big_decimal(s21_decimal_get_max());
    s21_big_decimal quotient = s21_big_decimal_binary_division(value, max, NULL);
    while (S21_TRUE) {
      s21_decimal power_of_ten = s21_decimal_get_zero();
      s21_from_int_to_decimal(pow(10., res), &power_of_ten);
      int compare_res = s21_decimal_binary_compare(quotient.decimals[0], power_of_ten);
      if (compare_res == 0 || compare_res == -1) {
        break;
      }
      ++res;
    }
    s21_decimal power_of_ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(pow(10., res), &power_of_ten);
    s21_big_decimal tmp = s21_big_decimal_binary_division(value, s21_decimal_to_big_decimal(power_of_ten), NULL);
    if (!s21_decimal_binary_is_zero(tmp.decimals[1]) || tmp.decimals[0].bits[3] != 0) {
      ++res;
    }
  }
  return res;
}

/*
  levelled values are only the integral part of the decimal, hence if exponents
  differ significantly — we may get a lot of trailing zeros

  we store the levelled values in a uint256 in case of overflow
*/
void s21_decimal_levelling(s21_decimal value_1, s21_decimal value_2, s21_big_decimal *big_value_1, s21_big_decimal *big_value_2) {
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  s21_decimal tmp1 = value_1;
  s21_decimal tmp2 = value_2;
  s21_decimal power_of_ten = s21_decimal_get_zero();
  s21_decimal_clear_bit3(&tmp1);
  s21_decimal_clear_bit3(&tmp2);
  if (exponent_1 > exponent_2) {
    s21_from_int_to_decimal(pow(10., exponent_1 - exponent_2), &power_of_ten);
    *big_value_1 = s21_decimal_to_big_decimal(tmp1);
    *big_value_2 = s21_decimal_binary_multiplication(tmp2, power_of_ten);
  } else if (exponent_1 < exponent_2) {
    s21_from_int_to_decimal(pow(10., exponent_2 - exponent_1), &power_of_ten);
    *big_value_1 = s21_decimal_binary_multiplication(tmp1, power_of_ten);
    *big_value_2 = s21_decimal_to_big_decimal(tmp2);
  } else {
    *big_value_1 = s21_decimal_to_big_decimal(tmp1);
    *big_value_2 = s21_decimal_to_big_decimal(tmp2);
  }
}
