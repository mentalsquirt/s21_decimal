#include "s21_decimal.h"

/*
operating on bits[3]
*/
// checks if the decimal layout is set correctly (returns 0 if ok, 1 upon error)
int s21_decimal_correctness(s21_decimal decimal) {
  int res = 0;

  if ((s21_decimal_low_empty_check(decimal) != 0) || (s21_decimal_high_empty_check(decimal) != 0)) {
    res = 1;
  } else {
    int exponent = s21_decimal_get_exponent(decimal);
    if(exponent < 0 || exponent > 28) {
      res = 1;
    }
  }

  return res;
}

// checks if the 0-15 bits are set to 0 (returns the int value of the bits)
int s21_decimal_low_empty_check(s21_decimal decimal) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal.bits[3];
  return bit3.layout.low_empty;
}

// checks if the 24-30 bits are set to 0 (returns the int value of the bits)
int s21_decimal_high_empty_check(s21_decimal decimal) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal.bits[3];
  return bit3.layout.high_empty;
}

// returns the exponent
int s21_decimal_get_exponent(s21_decimal decimal) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal.bits[3];
  return bit3.layout.exponent;
}

void s21_decimal_set_exponent(s21_decimal *decimal, int exponent) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal->bits[3];
  bit3.layout.exponent = exponent;

  decimal->bits[3] = bit3.i;
}

// sets a desired sign to the s21_decimal number provided
void s21_decimal_set_sign(s21_decimal *decimal, int sign) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal->bits[3];
  if (sign == S21_POSITIVE) {
    bit3.layout.sign = S21_POSITIVE;
  } else {
    bit3.layout.sign = S21_NEGATIVE;
  }

  decimal->bits[3] = bit3.i;
}
