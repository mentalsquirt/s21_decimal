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
  decimal.bits[index / MAX_BITS_INT] = s21_set_bit(decimal.bits[index / MAX_BITS_INT], index % MAX_BITS_INT);
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
// returns 1 if all bits are 0, 0 otherwise
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
  }
}
