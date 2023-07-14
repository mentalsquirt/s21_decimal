#include "s21_decimal.h"

/*
  returns an infinity as a s21_decimal number
*/
s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  return result;
}

/*
  returns 0 as a s21_decimal number
*/
s21_decimal s21_decimal_get_zero(void) {
  s21_decimal result;
  s21_clear_decimal(&result);
  return result;
}

/*
  returns 79228162514264337593543950335 (decimal max value) as an s21_decimal
*/
s21_decimal s21_decimal_get_max(void) {
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  return res;
}

/*
  0s at all bits of a s21_decimal
*/
void s21_clear_decimal(s21_decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

/*
  clears everything except for mantissa
*/
void s21_decimal_clear_bit3(s21_decimal *decimal) {
  decimal->bits[3] = 0;
}

/*
  returns new uint256 made from s21_decimal
*/
s21_big_decimal s21_decimal_to_big_decimal(s21_decimal decimal) {
  s21_big_decimal result;
  result.decimals[0] = decimal;
  result.decimals[1] = s21_decimal_get_zero();
  return result;
}
