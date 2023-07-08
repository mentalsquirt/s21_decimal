#include "tests.h"

int main() {
    int cnt_failed = 0;
    
    Suite *suite = s21_add_test("s21_add:");
    SRunner *tc_add = srunner_create(suite);
    srunner_set_fork_status(tc_add, CK_NOFORK);
    srunner_run_all(tc_add, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_add);
    srunner_free(tc_add);
    
    suite = s21_sub_test("s21_sub:");
    SRunner *tc_sub = srunner_create(suite);
    srunner_set_fork_status(tc_sub, CK_NOFORK);
    srunner_run_all(tc_sub, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_sub);
    srunner_free(tc_sub);

    suite = s21_mul_test("s21_mul:");
    SRunner *tc_mul = srunner_create(suite);
    srunner_set_fork_status(tc_mul, CK_NOFORK);
    srunner_run_all(tc_mul, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_mul);
    srunner_free(tc_mul);
    
    suite = s21_div_test("s21_div:");
    SRunner *tc_div = srunner_create(suite);
    srunner_set_fork_status(tc_div, CK_NOFORK);
    srunner_run_all(tc_div, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_div);
    srunner_free(tc_div);
    
    suite = s21_less_test("s21_is_less:");
    SRunner *tc_less = srunner_create(suite);
    srunner_set_fork_status(tc_less, CK_NOFORK);
    srunner_run_all(tc_less, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_less);
    srunner_free(tc_less);
    
    suite = s21_less_equal_test("s21_is_less_or_equal:");
    SRunner *tc_less_equal = srunner_create(suite);
    srunner_set_fork_status(tc_less_equal, CK_NOFORK);
    srunner_run_all(tc_less_equal, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_less_equal);
    srunner_free(tc_less_equal);

    suite = s21_greater_test("s21_is_greater:");
    SRunner *tc_greater = srunner_create(suite);
    srunner_set_fork_status(tc_greater, CK_NOFORK);
    srunner_run_all(tc_greater, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_greater);
    srunner_free(tc_greater);

    suite = s21_greater_equal_test("s21_is_greater_or_equal:");
    SRunner *tc_greater_equal = srunner_create(suite);
    srunner_set_fork_status(tc_greater_equal, CK_NOFORK);
    srunner_run_all(tc_greater_equal, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_greater_equal);
    srunner_free(tc_greater_equal);
    
    suite = s21_equal_test("s21_is_equal:");
    SRunner *tc_equal = srunner_create(suite);
    srunner_set_fork_status(tc_equal, CK_NOFORK);
    srunner_run_all(tc_equal, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_equal);
    srunner_free(tc_equal);

    suite = s21_not_equal_test("s21_is_not_equal:");
    SRunner *tc_not_equal = srunner_create(suite);
    srunner_set_fork_status(tc_not_equal, CK_NOFORK);
    srunner_run_all(tc_not_equal, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_not_equal);
    srunner_free(tc_not_equal);
   
    suite = s21_int_decimal_test("s21_from_int_to_decimal:");
    SRunner *tc_int_decimal = srunner_create(suite);
    srunner_set_fork_status(tc_int_decimal, CK_NOFORK);
    srunner_run_all(tc_int_decimal, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_int_decimal);
    srunner_free(tc_int_decimal);

    suite = s21_float_decimal_test("s21_from_float_to_decimal:");
    SRunner *tc_float_decimal = srunner_create(suite);
    srunner_set_fork_status(tc_float_decimal, CK_NOFORK);
    srunner_run_all(tc_float_decimal, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_float_decimal);
    srunner_free(tc_float_decimal);
    
    suite = s21_decimal_int_test("s21_from_decimal_to_int:");
    SRunner *tc_decimal_int = srunner_create(suite);
    srunner_set_fork_status(tc_decimal_int, CK_NOFORK);
    srunner_run_all(tc_decimal_int, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_decimal_int);
    srunner_free(tc_decimal_int);

    suite = s21_decimal_float_test("s21_from_decimal_to_float:");
    SRunner *tc_decimal_float = srunner_create(suite);
    srunner_set_fork_status(tc_decimal_float, CK_NOFORK);
    srunner_run_all(tc_decimal_float, CK_NORMAL);
    cnt_failed += srunner_ntests_failed(tc_decimal_float);
    srunner_free(tc_decimal_float);

    return (cnt_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
