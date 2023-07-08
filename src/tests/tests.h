#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

//здесь надо прописать библиотеки, необходимые для тестов
#include <check.h>
#include <stdlib.h>

#include "../s21_decimal.h"

Suite *s21_add_test();
Suite *s21_sub_test();
Suite *s21_mul_test();
Suite *s21_div_test();
Suite *s21_less_test();
Suite *s21_less_equal_test();
Suite *s21_greater_test();
Suite *s21_greater_equal_test();
Suite *s21_equal_test();
Suite *s21_not_equal_test();
Suite *s21_int_decimal_test();
Suite *s21_float_decimal_test();
Suite *s21_decimal_int_test();
Suite *s21_decimal_float_test();

#endif  // SRC_TESTS_TEST_H_
