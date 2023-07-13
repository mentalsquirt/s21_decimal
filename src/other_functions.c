#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  return 0;  // TODO!!!!!!
}

int s21_bank_round(s21_decimal value, s21_decimal *result) {
  return 0;  // TODO!!!!!!!!
}

s21_decimal s21_decimal_remove_trailing_zeros(s21_decimal value) {
  s21_decimal res = value;
  int sign = s21_decimal_get_sign(value);
  int exponent = s21_decimal_get_exponent(value);
  if (exponent > 0 && s21_decimal_correctness(value)) {
    s21_decimal remainder = s21_decimal_get_zero();
    s21_decimal tmp = value;
    s21_decimal_clear_bit3(&tmp);
    while (exponent > 0) {
      tmp = s21_decimal_binary_di
    }
  }
}
