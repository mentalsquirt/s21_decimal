#include "tests.h"
//в этом файле мы будем писать сами тесты для всех основных функций

//TESTING ARITHMETIC

START_TEST(test_add) {
//ck_assert_.....
}
END_TEST

START_TEST(test_sub) {
    
}
END_TEST

START_TEST(test_mul) {
    
}
END_TEST

START_TEST(test_div) {
    
}
END_TEST

//TESTING COMPARE
START_TEST(test_less) {
    
}
END_TEST

START_TEST(test_less_equal) {
    
}
END_TEST

START_TEST(test_greater) {
    
}
END_TEST

START_TEST(test_greater_equal) {
    
}
END_TEST

START_TEST(test_equal) {
    
}
END_TEST

START_TEST(test_not_equal) {
    
}
END_TEST

//CONVERTERS

START_TEST(test_int_decimal) {
    
}
END_TEST

START_TEST(test_float_decimal) {
    
}
END_TEST

START_TEST(test_decimal_int) {
    
}
END_TEST

START_TEST(test_decimal_float) {
    
}
END_TEST

Suite *s21_add_test() {
  Suite *suite = suite_create("s21_add:");
  TCase *tc_add = tcase_create("s21_add test");
  tcase_add_test(tc_add, test_add);
  suite_add_tcase(suite, tc_add);
  return suite;
}

Suite *s21_sub_test() {
  Suite *suite = suite_create("s21_sub:");
  TCase *tc_sub = tcase_create("s21_sub test");
  tcase_add_test(tc_sub, test_sub);
  suite_add_tcase(suite, tc_sub);
  return suite;
}

Suite *s21_mul_test() {
  Suite *suite = suite_create("s21_mul:");
  TCase *tc_mul = tcase_create("s21_umul test");
  tcase_add_test(tc_mul, test_mul);
  suite_add_tcase(suite, tc_mul);
  return suite;
}

Suite *s21_div_test() {
  Suite *suite = suite_create("s21_div:");
  TCase *tc_div = tcase_create("s21_div test");
  tcase_add_test(tc_div, test_div);
  suite_add_tcase(suite, tc_div);
  return suite;
}

Suite *s21_less_test() {
  Suite *suite = suite_create("s21_is_less:");
  TCase *tc_less = tcase_create("s21_is_less test");
  tcase_add_test(tc_less, test_less);
  suite_add_tcase(suite, tc_less);
  return suite;
}

Suite *s21_less_equal_test() {
  Suite *suite = suite_create("s21_is_less_or_equal:");
  TCase *tc_less_equal = tcase_create("s21_is_less_or_equal test");
  tcase_add_test(tc_less_equal, test_less_equal);
  suite_add_tcase(suite, tc_less_equal);
  return suite;
}

Suite *s21_greater_test() {
  Suite *suite = suite_create("s21_is_greater:");
  TCase *tc_greater = tcase_create("s21_is_greater test");
  tcase_add_test(tc_greater, test_greater);
  suite_add_tcase(suite, tc_greater);
  return suite;
}

Suite *s21_greater_equal_test() {
  Suite *suite = suite_create("s21_is_greater_or_equal:");
  TCase *tc_greater_equal = tcase_create("s21_is_greater_or_equal test");
  tcase_add_test(tc_greater_equal, test_greater_equal);
  suite_add_tcase(suite, tc_greater_equal);
  return suite;
}

Suite *s21_equal_test() {
  Suite *suite = suite_create("s21_is_equal:");
  TCase *tc_equal = tcase_create("s21_is_equal test");
  tcase_add_test(tc_equal, test_equal);
  suite_add_tcase(suite, tc_equal);
  return suite;
}

Suite *s21_not_equal_test() {
  Suite *suite = suite_create("s21_is_not_equal:");
  TCase *tc_not_equal = tcase_create("s21_is_not_equal test");
  tcase_add_test(tc_not_equal, test_not_equal);
  suite_add_tcase(suite, tc_not_equal);
  return suite;
}

Suite *s21_int_decimal_test() {
  Suite *suite = suite_create("s21_from_int_to_decimal:");
  TCase *tc_int_decimal = tcase_create("s21_from_int_to_decimal test");
  tcase_add_test(tc_int_decimal, test_int_decimal);
  suite_add_tcase(suite, tc_int_decimal);
  return suite;
}

Suite *s21_float_decimal_test() {
  Suite *suite = suite_create("s21_from_float_to_decimal:");
  TCase *tc_float_decimal = tcase_create("s21_from_float_to_decimal test");
  tcase_add_test(tc_float_decimal, test_float_decimal);
  suite_add_tcase(suite, tc_float_decimal);
  return suite;
}

Suite *s21_decimal_int_test() {
  Suite *suite = suite_create("s21_from_decimal_to_int:");
  TCase *tc_decimal_int = tcase_create("s21_from_decimal_to_int test");
  tcase_add_test(tc_decimal_int, test_decimal_int);
  suite_add_tcase(suite, tc_decimal_int);
  return suite;
}

Suite *s21_decimal_float_test() {
  Suite *suite = suite_create("s21_from_decimal_to_float:");
  TCase *tc_decimal_float = tcase_create("s21_from_decimal_to_float test");
  tcase_add_test(tc_decimal_float, test_decimal_float);
  suite_add_tcase(suite, tc_decimal_float);
  return suite;
}


