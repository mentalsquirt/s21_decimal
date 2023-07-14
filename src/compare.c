#include "s21_decimal.h"


/*
  **RESULT CODES FOR COMPARISON MODULE**

  s21_comparison_res enum:
    S21_FALSE = 0,
    S21_TRUE = 1
*/


/*
  checks if value_1 is less than value_2
  returns an s21_comparison_res code:
    S21_FALSE(0) -- value_1 is NOT less than value_2
    S21_TRUE(1) -- value_1 is less than value_2
*/
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_res res = S21_FALSE;
  int sign_1 = s21_decimal_get_sign(value_1);
  int sign_2 = s21_decimal_get_sign(value_2);
// one zero cannot be less than another
  if (s21_is_equal(value_1, s21_decimal_get_zero()) && s21_is_equal(value_2, s21_decimal_get_zero())) {
    res = S21_FALSE;
// negative number is always less than positive
  } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
    res = S21_TRUE;
// positive number cannot be less than negative
  } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
    res = S21_FALSE;
// two negative numbers — make them positive and switch their places
  } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
    res = s21_is_less_helper(s21_abs(value_2), s21_abs(value_1));
  } else {
    res = s21_is_less_helper(value_1, value_2);
  }
  return res;
}

/*
  checks if value_1 is less than OR equal to value_2
  returns an s21_comparison_res code:
    S21_FALSE(0) -- value_1 is NOT less than nor equal to value_2
    S21_TRUE(1) -- value_1 is either less than or equal to value_2
*/
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

/*
  checks if value_1 is greater than value_2
  returns an s21_comparison_res code:
    S21_FALSE(0) -- value_1 is NOT greater than value_2
    S21_TRUE(1) -- value_1 is greater than value_2
*/
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_2, value_1);
}

/*
  checks if value_1 is greater than OR equal to value_2
  returns an s21_comparison_res code:
    S21_FALSE(0) -- value_1 is NOT greater than nor equal to value_2
    S21_TRUE(1) -- value_1 is either greater than or equal to value_2
*/
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

/*
  checks if value_1 is equal to value_2
  returns an s21_comparison_res code:
    S21_FALSE(0) -- value_1 is NOT equal to value_2
    S21_TRUE(1) -- value_1 is equal to value_2
*/
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_res res = S21_TRUE;
  s21_decimal tmp_1 = s21_decimal_remove_trailing_zeros(value_1);
  s21_decimal tmp_2 = s21_decimal_remove_trailing_zeros(value_2);
  // -0 == 0
  if (tmp_1.bits[0] == 0 && tmp_2.bits[0] == 0
      && tmp_1.bits[1] == 0 && tmp_2.bits[1] == 0
      && tmp_1.bits[2] == 0 && tmp_2.bits[2] == 0) {
    res = S21_TRUE;
  } else {
    res = tmp_1.bits[0] == tmp_2.bits[0]
        && tmp_1.bits[1] == tmp_2.bits[1]
        && tmp_1.bits[2] == tmp_2.bits[2]
        && tmp_1.bits[3] == tmp_2.bits[3];
  }
  return res;
}

/*
  checks if value_1 is not equal to value_2
  returns an s21_comparison_res code:
    S21_FALSE(0) -- value_1 is equal to value_2
    S21_TRUE(1) -- value_1 is NOT equal to value_2
*/
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}


/*
  **HELPERS**
*/

/*
  s21_is_less helper which compares two positive numbers
  returns an s21_comparison_res code:
    1 -- value_1 < value_2
    0 -- !(value_1 < value_2)
*/
int s21_is_less_helper(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_res res = S21_FALSE;
  s21_decimal tmp_1 = value_1;
  s21_decimal tmp_2 = value_2;
  s21_big_decimal big_tmp_1;
  s21_big_decimal big_tmp_2;
  s21_decimal_levelling(tmp_1, tmp_2, &big_tmp_1, &big_tmp_2);
  int compare = s21_big_decimal_binary_compare(big_tmp_1, big_tmp_2);
  if (compare == -1) {
    res = S21_TRUE;
  } else {
    res = S21_FALSE;
  }
  return res;
}
