#include <check.h>

#include "smart_calc.h"

START_TEST(result_calc_1) {
  int res = Ok;
  char *str = "1+2";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq(num, 3.0);
}
END_TEST

START_TEST(result_calc_2) {
  int res = Ok;
  char *str = "1+2+sin(1*3+-(-1))^2";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 3.5727500, 0.0000001);
}
END_TEST

START_TEST(result_calc_3) {
  int res = Ok;
  char *str = "1+2+sin(1*3+-(-1)))()()())(";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 1);
  ck_assert_double_eq(num, 0);
}
END_TEST

START_TEST(result_calc_4) {
  int res = Ok;
  char *str = "+1+2+sin(1*3+-(-1)*-31)-+1+2^2^3";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 257.7290942, 0.0000001);
}
END_TEST

START_TEST(result_calc_5) {
  int res = Ok;
  char *str = "(32mod-12)^cos(+12)+sin(-2)";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 4.8726756, 0.0000001);
}
END_TEST

START_TEST(result_calc_6) {
  int res = Ok;
  char *str = "(32/-12)*tan(10)^atan(-0.125)";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, -2.8142991, 0.0000001);
}
END_TEST

START_TEST(result_calc_7) {
  int res = Ok;
  char *str = "acos(-1)^log(0.01)+asin(-1^sqrt(1))";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, -1.4694751, 0.0000001);
}
END_TEST

START_TEST(result_calc_8) {
  int res = Ok;
  char *str = "sqrt(ln(2)^-ln(3.14))/-12*cos(sin(2^2^1^1^1^2)+3)";
  double num = 0;
  char *x = "0";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 0.0640146, 0.0000001);
}
END_TEST

START_TEST(result_calc_9) {
  int res = Ok;
  char *str = "-1+x^2*-3*-(x)";
  double num = 0;
  char *x = "-123.";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, -5582602.0, 0.0000001);
}
END_TEST

START_TEST(result_calc_10) {
  int res = Ok;
  char *str = "-(+(-(+(-12++7)*-1)))";
  double num = 0;
  char *x = "-123.";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 5.0, 0.0000001);
}
END_TEST

START_TEST(result_calc_11) {
  int res = Ok;
  char *str = "cos(sin(2*x))";
  double num = 0;
  char *x = "-1.";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 0.6143003, 0.0000001);
}
END_TEST

START_TEST(result_calc_12) {
  int res = Ok;
  char *str_1 = "1x+-123";
  char *str_2 = "1(x+-123)";
  char *str_3 = "1*(x+-123)+()";
  char *str_4 = "1*(x+-123)sin(1)";
  char *str_5 = "1*(x+-123)+sin(1)+";
  char *str_6 = "1*(x+-123.1.1)+sin(1)*-.-123";
  char *str_7 = "1*(+-1)-1";
  char *str_8 = "1*(+-1)-1+(+)";
  char *str_9 = "1*(-1)-*1+(+1)";
  char *str_10 = "1*(-1)-(sin)1)";
  char *str_11 = "+-1.1-1*(-1)-cos(1+2)";
  char *str_12 = "-1.1-1*(-)-cos(1+2)";
  char *str_13 = "-1.1-1*(+1)-cos(1+2-)";
  char *str_14 = "*1.1-1*(+1)-cos(1+2-)";
  char *str_15 = "1.1-1*(+1)-cos(1+2-1)-.-";
  char *str_16 = "1.1-1*(+1)-cos(1+2-1))))))";
  char *str_17 = "1.1-1*(+1)-cos(((((((((((((1+2-1))))))";
  double num = 0;
  char *x = "-1.123";
  res = result_calc(str_1, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_2, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_3, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_4, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_5, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_6, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_7, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_8, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_9, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_10, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_11, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_12, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_13, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_14, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_15, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_16, &num, x);
  ck_assert_int_eq(res, 1);
  res = result_calc(str_17, &num, x);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(result_calc_13) {
  int res = Ok;
  char *str =
      "cos(28)*sin(31.--x)*tan(sqrt(25))+acos(-0.123)+asin(sin(1)+.001)+atan(0."
      "1)+1";
  double num = 0;
  char *x = "-23.123";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 7.0488723, 0.0000001);
}
END_TEST

START_TEST(result_calc_14) {
  int res = Ok;
  char *str = "7*(3^asin(0.4))^(3.*.2)++1";
  double num = 0;
  char *x = "-1.";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, 10.1812984, 0.0000001);
}
END_TEST

START_TEST(result_calc_15) {
  int res = Ok;
  char *str =
      "tan(atan(asin(.125)))/(4^(acos(2/4)+-(x-1.5))/sin(2*2)/5^(acos(2/-4)))";
  double num = 0;
  char *x = "-1.";
  res = result_calc(str, &num, x);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(num, -0.0201987, 0.0000001);
}
END_TEST

Suite *result_calc_cases(void) {
  Suite *suite = suite_create("ts_result_calc");
  TCase *test_case = tcase_create("tc_result_calc");
  tcase_add_test(test_case, result_calc_1);
  tcase_add_test(test_case, result_calc_2);
  tcase_add_test(test_case, result_calc_3);
  tcase_add_test(test_case, result_calc_4);
  tcase_add_test(test_case, result_calc_5);
  tcase_add_test(test_case, result_calc_6);
  tcase_add_test(test_case, result_calc_7);
  tcase_add_test(test_case, result_calc_8);
  tcase_add_test(test_case, result_calc_9);
  tcase_add_test(test_case, result_calc_10);
  tcase_add_test(test_case, result_calc_11);
  tcase_add_test(test_case, result_calc_12);
  tcase_add_test(test_case, result_calc_13);
  tcase_add_test(test_case, result_calc_14);
  tcase_add_test(test_case, result_calc_15);
  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *test_suites[] = {result_calc_cases(), NULL};
  int failed = 0;
  for (Suite **s = test_suites; *s != NULL; s++) {
    SRunner *runner = srunner_create(*s);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed;
}
