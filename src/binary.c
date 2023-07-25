#include "s21_decimal.h"

/*
  **BINARY OPERATIONS**

  these functions interpret s21_decimals as uint128 and
  s21_big_decimals as uint256
  hence — only positive values should be used with those
*/


/*
  looks up if a bit is set
  returns 1 if set, 0 if not set
*/
int s21_test_bit(unsigned int value, int index) {
  return value & (1U << index);
}

/*
  s21_decimal type version
  returns 1 if set, 0 if not set
*/
int s21_decimal_test_bit(s21_decimal decimal, int index) {
  return s21_test_bit(decimal.bits[index / MAX_BITS_INT], index % MAX_BITS_INT);
}

/*
  sets the bit at *index* to be 1
  returns new int with the requested bit set
*/
int s21_set_bit(unsigned int value, int index) {
  return (value | (1U << index));
}

/*
  s21_decimal type version
  returns new modified s21_decimal
*/
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index) {
  decimal.bits[index / MAX_BITS_INT] = s21_set_bit(decimal.bits[index / MAX_BITS_INT],
                                                                index % MAX_BITS_INT);
  return decimal;
}

/*
  sets the bit at *index* to be 0
  returns new int with the requested bit unset
*/
int s21_unset_bit(unsigned int value, int index) {
  return value & ~(1U << index);
}

/*
  inverts whatever the value the bit already has to be the opposite
  returns new int with the requested bit inverted
*/
int s21_invert_bit(unsigned int value, int index) {
  return value ^ (1U << index);
}

/*
  returns an index of the first occurance of a non-zero bit starting from the highest
  if there are no non-zero bits, returns -1
*/
int s21_decimal_get_non_zero_bit(s21_decimal decimal) {
  int res = -1;
  for (size_t i = MAX_BITS - 1; i >= 0; --i) {
    if (s21_decimal_test_bit(decimal, i)) {
      res = i;
      break;
    }
  }
  return res;
}


/*
SHIFTS
*/

/*
  shifts the s21_decimal by one bit to the left (s21_decimal << 1)
*/
s21_decimal s21_decimal_binary_shift_left_one(s21_decimal decimal) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = decimal.bits[i] << 1;
  }
  // check if we need to set the lowest bit in each "bits" int
  for (size_t i = 0; i < DECIMAL_SIZE - 1; ++i) {
    int highest = s21_test_bit(decimal.bits[i], MAX_BITS_INT - 1);
    if (highest) res.bits[i + 1] = s21_set_bit(res.bits[i + 1], 0);
  }
  return res;
}

/*
  shifts the s21_decimal by *shift* bits to the left (s21_decimal << shift)
*/
s21_decimal s21_decimal_binary_shift_left(s21_decimal decimal, int shift) {
  s21_decimal res = decimal;
  while (shift > 0) {
    res = s21_decimal_binary_shift_left_one(res);
    --shift;
  }
  return res;
}

/*
  shifts the s21_decimal by one bit to the right (s21_decimal >> 1)
*/
s21_decimal s21_decimal_binary_shift_right_one(s21_decimal decimal) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = decimal.bits[i] >> 1;
  }
  // check if we need to set the highest bit in each "bits" int
  for (size_t i = 3; i > 0; --i) {
    int lowest = s21_test_bit(decimal.bits[i], 0);
    if (lowest) res.bits[i - 1] = s21_set_bit(res.bits[i - 1], MAX_BITS_INT - 1);
  }
}

/*
  shifts the s21_decimal by *shift* bits to the right (s21_decimal >> shift)
*/
s21_decimal s21_decimal_binary_shift_right(s21_decimal decimal, int shift) {
  s21_decimal res = decimal;
  while (shift > 0) {
    res = s21_decimal_binary_shift_right_one(res);
    --shift;
  }
  return res;
}

/*
  shifts the s21_big_decimal by *shift* bits to the left (s21_big_decimal << shift)
*/
s21_big_decimal s21_big_decimal_binary_shift_left(s21_big_decimal decimal, int shift) {
  s21_big_decimal res = decimal;
  while (shift > 0) {
    int overflow = s21_decimal_test_bit(res.decimals[0], MAX_BITS - 1);
    for (size_t i = 0; i < 2; ++i) {
      res.decimals[i] = s21_decimal_binary_shift_left_one(res.decimals[i]);
    }
    if (overflow) res.decimals[1] = s21_decimal_set_bit(res.decimals[1], 0);
    --shift;
  }
  return res;
}

/*
  shifts the s21_big_decimal by *shift* bits to the right (s21_big_decimal >> shift)
*/
s21_big_decimal s21_big_decimal_binary_shift_right(s21_big_decimal decimal, int shift) {
  s21_big_decimal res = decimal;
  while (shift > 0) {
    int overflow = s21_decimal_test_bit(res.decimals[1], 0);
    for (size_t i = 0; i < 2; ++i) {
      res.decimals[i] = s21_decimal_binary_shift_right_one(res.decimals[i]);
    }
    if (overflow) res.decimals[0] = s21_decimal_set_bit(res.decimals[0], MAX_BITS - 1);
    --shift;
  }
  return res;
}


/*
LOGIC
*/

/*
  returns the bitwise AND of two s21_decimal values interpreted as uint128s
*/
s21_decimal s21_decimal_binary_and(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = value_1.bits[i] & value_2.bits[i];
  }
  return res;
}

/*
  returns the bitwise NOT of a s21_decimal value interpreted as uint128
*/
s21_decimal s21_decimal_binary_not(s21_decimal value_1) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = ~value_1.bits[i];
  }
  return res;
}

/*
  returns the bitwise XOR of two s21_decimal values interpreted as uint128s
*/
s21_decimal s21_decimal_binary_xor(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = value_1.bits[i] ^ value_2.bits[i];
  }
  return res;
}


/*
COMPARISON
*/

/*
  returns 1 if all bits are unset(zeros)
  returns 0 otherwise
*/
int s21_decimal_binary_is_zero(s21_decimal decimal) {
  return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 && decimal.bits[3] == 0;
}

/*
  compares two s21_decimal values as uint128s
  returns -1 if value_1 < value_2, 0 if value_1 == value_2, 1 if value_1 > value_2
*/
int s21_decimal_binary_compare(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (size_t i = MAX_BITS - 1; i >= 0; --i) {
    int bit_1 = s21_decimal_test_bit(value_1, i);
    int bit_2 = s21_decimal_test_bit(value_2, i);
    if (bit_1 > bit_2) {
      res = 1;
    } else if (bit_1 < bit_2) {
      res = -1;
    }
    if (res != 0) {
      break;
    }
  }
  return res;
}

/*
  compares two s21_big_decimal values as uint256s
  returns -1 if value_1 < value_2, 0 if value_1 == value_2, 1 if value_1 > value_2
*/
int s21_big_decimal_binary_compare(s21_big_decimal value_1, s21_big_decimal value_2) {
  int compare_res = s21_decimal_binary_compare(value_1.decimals[1], value_2.decimals[1]);
  if (!compare_res) {
    compare_res = s21_decimal_binary_compare(value_1.decimals[0], value_2.decimals[0]);
  }
  return compare_res;
}


/*
ADDITION
*/

/*
  binary addition using bitwise operations
  returns s21_decimal - sum of the two parameters
*/
s21_decimal s21_decimal_binary_addition(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = value_1;
  s21_decimal tmp = value_2;
  while(!s21_decimal_binary_is_zero(tmp)) {
    s21_decimal overflow = s21_decimal_binary_and(res, tmp);
    overflow = s21_decimal_binary_shift_left_one(overflow);
    res = s21_decimal_binary_xor(res, tmp);
    tmp = overflow;
  }
  return res;
}

/*
  binary addition using bitwise operations
  returns s21_big_decimal - sum of the two parameters
*/
s21_big_decimal s21_big_decimal_binary_addition(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal res = value_1;
  s21_big_decimal tmp = value_2;
  while (!s21_decimal_binary_is_zero(tmp.decimals[0]) || !s21_decimal_binary_is_zero(tmp.decimals[1])) {
    s21_big_decimal overflow;
    overflow.decimals[0] = s21_decimal_binary_and(res.decimals[0], tmp.decimals[0]);
    overflow.decimals[1] = s21_decimal_binary_and(res.decimals[1], tmp.decimals[1]);
    overflow = s21_big_decimal_binary_shift_left(overflow, 1);
    res.decimals[0] = s21_decimal_binary_xor(res.decimals[0], tmp.decimals[0]);
    res.decimals[1] = s21_decimal_binary_xor(res.decimals[1], tmp.decimals[1]);
    tmp = overflow;
  }
  return res;
}


/*
MULTIPLICATION
*/

/*
  binary multiplication using bitwise operations
  returns s21_big_decimal - product of the two s21_decimal parameters
*/
s21_big_decimal s21_decimal_binary_multiplication(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_res = s21_decimal_to_big_decimal(s21_decimal_get_zero());
  s21_big_decimal big_tmp = s21_decimal_to_big_decimal(value_1);
  int max_bit = s21_decimal_get_non_zero_bit(value_2);
  for (size_t i = 0; i <= max_bit; i++) {
    if (s21_decimal_test_bit(value_2, i)) {
      big_res = s21_big_decimal_binary_addition(big_res, big_tmp);
    }
    big_tmp = s21_big_decimal_binary_shift_left(big_tmp, 1);
  }
  return big_res;
}

/*
  binary multiplication using bitwise operations
  returns s21_big_decimal - product of s21_big_decimal parameter and s21_decimal parameter
*/
s21_big_decimal s21_big_decimal_binary_multiplication(s21_big_decimal big_value_1, s21_decimal value_2) {
  s21_big_decimal big_res = s21_decimal_to_big_decimal(s21_decimal_get_zero());
  s21_big_decimal big_tmp = big_value_1;
  int max_bit = s21_decimal_get_non_zero_bit(value_2);
  for (size_t i = 0; i <= max_bit; i++) {
    if (s21_decimal_test_bit(value_2, i)) {
      big_res = s21_big_decimal_binary_addition(big_res, big_tmp);
    }
    big_tmp = s21_big_decimal_binary_shift_left(big_tmp, 1);
  }
  return big_res;
}


/*
SUBTRACTION
*/

/*
  binary subtraction using bitwise operations
  returns s21_decimal - difference of the two s21_decimal parameters
*/
s21_decimal s21_decimal_binary_subtraction(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res;
  s21_decimal tmp = s21_decimal_get_zero();
  s21_from_int_to_decimal(1, &tmp);
  value_2 = s21_decimal_binary_not(value_2);
  value_2 = s21_decimal_binary_addition(value_2, tmp);
  res = s21_decimal_binary_addition(value_1, value_2);
  return res;
}

/*
  binary subtraction using bitwise operations
  returns s21_big_decimal - difference of the two s21_big_decimal parameters
*/
s21_big_decimal s21_big_decimal_binary_subtraction(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal res;
  s21_decimal tmp = s21_decimal_get_zero();
  s21_from_int_to_decimal(1, &tmp);
  value_2.decimals[0] = s21_decimal_binary_not(value_2.decimals[0]);
  value_2.decimals[1] = s21_decimal_binary_not(value_2.decimals[1]);
  s21_big_decimal one = s21_decimal_to_big_decimal(tmp);
  value_2 = s21_big_decimal_binary_addition(value_2, one);
  res = s21_big_decimal_binary_addition(value_1, value_2);
  return res;
}


/*
DIVISION
*/

/* 
  performs binary division using bitwise operations
  returns s21_decimal - quotient of the two s21_decimal parameters
  (if you don't need a remainder — pass NULL as the third arg)
*/
s21_decimal s21_decimal_binary_division(s21_decimal dividend, s21_decimal divisor, s21_decimal *remainder) {
  s21_decimal res;
  s21_decimal partial_remainder = s21_decimal_get_zero();
  s21_decimal quotient = s21_decimal_get_zero();
  if (s21_decimal_binary_is_zero(dividend)) {
    quotient = s21_decimal_get_zero();
    partial_remainder = s21_decimal_get_zero();
  } else if (s21_decimal_binary_compare(dividend, divisor) == -1) {
    quotient = s21_decimal_get_zero();
    partial_remainder = dividend;
  } else {
    int non_zero_dividend = s21_decimal_get_non_zero_bit(dividend);
    int non_zero_divisor = s21_decimal_get_non_zero_bit(divisor);
    int shift = non_zero_dividend - non_zero_divisor;
    s21_decimal shifted_divisor = s21_decimal_binary_shift_left(divisor, shift);
    s21_decimal dividend_tmp = dividend;
    s21_comparison_res subtraction = S21_TRUE;
    while (shift >= 0) {
      if (subtraction) {
        partial_remainder = s21_decimal_binary_subtraction(dividend_tmp, shifted_divisor);
      } else {
        partial_remainder = s21_decimal_binary_addition(dividend_tmp, shifted_divisor);
      }
      quotient = s21_decimal_binary_shift_left_one(quotient);
      if (!s21_decimal_test_bit(partial_remainder, MAX_BITS - 1)) {
        quotient = s21_decimal_set_bit(quotient, 0);
      }
      dividend_tmp = s21_decimal_binary_shift_left_one(partial_remainder);
      if (!s21_decimal_test_bit(partial_remainder, MAX_BITS - 1)) {
        subtraction = 1;
      } else {
        subtraction = 0;
      }
      --shift;
    }
    if (s21_decimal_test_bit(partial_remainder, MAX_BITS - 1)) {
      partial_remainder = s21_decimal_binary_addition(partial_remainder, shifted_divisor);
    }
    partial_remainder = s21_decimal_binary_shift_right(partial_remainder, non_zero_dividend - non_zero_divisor);
  }
  res = quotient;
  if (remainder != NULL) {
    *remainder = partial_remainder;
  }
  return res;
}

/* 
  performs binary division of two uint256 using bitwise operations
  returns s21_big_decimal (uint256) - quotient of the two s21_big_decimal parameters
  (if you don't need a remainder — pass NULL as the third arg)
*/
s21_big_decimal s21_big_decimal_binary_division(s21_big_decimal dividend, s21_big_decimal divisor, s21_big_decimal *remainder) {
  s21_big_decimal res;
  s21_big_decimal partial_remainder = s21_decimal_to_big_decimal(s21_decimal_get_zero());
  s21_big_decimal quotient = s21_decimal_to_big_decimal(s21_decimal_get_zero());
  if (s21_decimal_binary_is_zero(dividend.decimals[0]) &&
      s21_decimal_binary_is_zero(divisor.decimals[1])) {
    quotient = s21_decimal_to_big_decimal(s21_decimal_get_zero());
    partial_remainder = s21_decimal_to_big_decimal(s21_decimal_get_zero());
  } else if (s21_big_decimal_binary_compare(dividend, divisor) == -1) {
    quotient = s21_decimal_to_big_decimal(s21_decimal_get_zero());
    partial_remainder = dividend;
  } else {
    int non_zero_dividend = s21_decimal_get_non_zero_bit(dividend.decimals[1]);
    if (non_zero_dividend == -1) {
      non_zero_dividend = s21_decimal_get_non_zero_bit(dividend.decimals[0]);
    } else {
      non_zero_dividend = MAX_BITS + non_zero_dividend;
    }
    int non_zero_divisor = s21_decimal_get_non_zero_bit(divisor.decimals[1]);
    if (non_zero_divisor == -1) {
      non_zero_divisor = s21_decimal_get_non_zero_bit(divisor.decimals[0]);
    } else {
      non_zero_divisor = MAX_BITS + non_zero_divisor;
    }
    int shift = non_zero_dividend - non_zero_divisor;
    s21_big_decimal shifted_divisor = s21_big_decimal_binary_shift_left(divisor, shift);
    s21_big_decimal dividend_tmp = dividend;
    s21_comparison_res subtraction = S21_TRUE;
    while (shift >= 0) {
      if (subtraction) {
        partial_remainder = s21_big_decimal_binary_subtraction(dividend_tmp, shifted_divisor);
      } else {
        partial_remainder = s21_big_decimal_binary_addition(dividend_tmp, shifted_divisor);
      }
      quotient = s21_big_decimal_binary_shift_left(quotient, 1);
      if (!s21_big_decimal_test_bit(partial_remainder.decimals[1], MAX_BITS - 1)) {
        quotient.decimals[0] = s21_decimal_set_bit(quotient.decimals[0], 0);
      }
      dividend_tmp = s21_big_decimal_binary_shift_left(partial_remainder, 1);
      if (!s21_decimal_test_bit(partial_remainder.decimals[1], MAX_BITS - 1)) {
        subtraction = 1;
      } else {
        subtraction = 0;
      }
      --shift;
    }
    if (s21_decimal_test_bit(partial_remainder.decimals[1], MAX_BITS - 1)) {
      partial_remainder = s21_big_decimal_binary_addition(partial_remainder, shifted_divisor);
    }
    partial_remainder = s21_big_decimal_binary_shift_right(partial_remainder, non_zero_dividend - non_zero_divisor);
  }
  res = quotient;
  if (remainder != NULL) {
    *remainder = partial_remainder;
  }
  return res;
}
