#include "s21_decimal.h"

/*
BINARY OPERATIONS
*/
// looks up if a bit is set (returns 1 if set, 0 if not set)
int s21_test_bit(unsigned int value, int index) {
  return value & (1U << index);
}

// s21_decimal type version (returns 1 if set, 0 if not set)
int s21_decimal_test_bit(s21_decimal decimal, int index) {
  return s21_test_bit(decimal.bits[index / MAX_BITS_INT], index % MAX_BITS_INT);
}

// sets the bit at *index* to be 1 (returns new int with the requested bit set)
int s21_set_bit(unsigned int value, int index) {
  return (value | (1U << index));
}

// s21_decimal type version (returns new modified s21_decimal)
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index) {
  decimal.bits[index / MAX_BITS_INT] = s21_set_bit(decimal.bits[index / MAX_BITS_INT],
                                                                index % MAX_BITS_INT);
  return decimal;
}

// sets the bit at *index* to be 0 (returns new int with the requested bit unset)
int s21_unset_bit(unsigned int value, int index) {
  return value & ~(1U << index);
}

// inverts whatever the value the bit already has to be the opposite (returns new int with the requested bit inverted)
int s21_invert_bit(unsigned int value, int index) {
  return value ^ (1U << index);
}

// returns an index of the first occurance of a non-zero bit starting from the highest
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
// shifts the s21_decimal by one bit to the left (s21_decimal << 1)
s21_decimal s21_decimal_binary_shift_left_one(s21_decimal decimal) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = decimal.bits[i] << 1;
  }
  for (size_t i = 0; i < DECIMAL_SIZE - 1; ++i) {
    int highest = s21_test_bit(decimal.bits[i], MAX_BITS_INT - 1);
    if (highest) res.bits[i + 1] = s21_set_bit(res.bits[i + 1], 0);
  }
  return res;
}

// shifts the s21_decimal by *shift* bits to the left (s21_decimal << shift)
s21_decimal s21_decimal_binary_shift_left(s21_decimal decimal, int shift) {
  s21_decimal res = decimal;
  while (shift > 0) {
    res = s21_decimal_binary_shift_left_one(res);
    --shift;
  }
  return res;
}

// shifts the s21_decimal by one bit to the right (s21_decimal >> 1)
s21_decimal s21_decimal_binary_shift_right_one(s21_decimal decimal) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = decimal.bits[i] >> 1;
  }
  for (size_t i = 3; i > 0; --i) {
    int lowest = s21_test_bit(decimal.bits[i], 0);
    if (lowest) res.bits[i - 1] = s21_set_bit(res.bits[i - 1], MAX_BITS_INT - 1);
  }
}

// shifts the s21_decimal by *shift* bits to the right (s21_decimal >> shift)
s21_decimal s21_decimal_binary_shift_right(s21_decimal decimal, int shift) {
  s21_decimal res = decimal;
  while (shift > 0) {
    res = s21_decimal_binary_shift_right_one(res);
    --shift;
  }
  return res;
}

// shifts the s21_big_decimal by *shift* bits to the left (s21_big_decimal << shift)
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

//shifts the s21_big_decimal by *shift* bits to the right (s21_big_decimal >> shift)
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
// returns the bitwise AND of two s21_decimal values interpreted as uint128s
s21_decimal s21_decimal_binary_and(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = value_1.bits[i] & value_2.bits[i];
  }
  return res;
}

// returns the bitwise NOT of a s21_decimal value interpreted as uint128
s21_decimal s21_decimal_binary_not(s21_decimal value_1) {
  s21_decimal res = s21_decimal_get_zero();
  for (size_t i = 0; i < DECIMAL_SIZE; ++i) {
    res.bits[i] = ~value_1.bits[i];
  }
  return res;
}

// returns the bitwise XOR of two s21_decimal values interpreted as uint128s
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
// returns 1 if all bits are unset(zeros), returns 0 otherwise
int s21_decimal_binary_is_zero(s21_decimal decimal) {
  return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 && decimal.bits[3] == 0;
}

// compares two s21_decimal values as uint128s, returns -1 if value_1 < value_2, 0 if value_1 == value_2, 1 if value_1 > value_2
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
ADDITION
*/
// binary addition using bitwise operations, returns s21_decimal - sum of the two parameters
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

// binary addition using bitwise operations, returns s21_big_decimal - sum of the two parameters
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
// binary multiplication using bitwise operations, returns s21_big_decimal - product of the two s21_decimal parameters
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

// binary multiplication using bitwise operations, returns s21_big_decimal - product of s21_big_decimal parameter and s21_decimal parameter
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
