#include <check.h>

#include "../polish_notation.h"

/* GENERAL */
START_TEST(general_1) {
  char test[] = "0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_2) {
  char test[] = "1";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 1);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_3) {
  char test[] = "25";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 25);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_4) {
  char test[] = "-25";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, -25);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_5) {
  char test[] = "-0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_6) {
  char test[] = "0.1";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0.1);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_7) {
  char test[] = "123.456";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 123.456);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_8) {
  char test[] = "-123.456";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, -123.456);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_9) {
  char test[] = "23*34h";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_int_eq(correct, ERROR);
}
END_TEST

START_TEST(general_10) {
  char test[] = "150 / 10 + 5 * 2 / 2";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, (150 / 10 + 5 * 2 / 2));
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_11) {
  char test[] = "log(x)";
  long double result = 0;
  long double x = -1;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_nan(result);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_12) {
  char test[] = "sin(0)*100";
  long double result = 0;
  long double x = -1;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_13) {
  char test[] = "cos(x)*100";
  long double result = 100;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 100);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_14) {
  char test[] =
      "tan(x)*(cos(x)/sin(x))";  // без сокращений получается 0 * inf = nan
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_nan(result);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_15) {
  char test[] = "log(x)-10";
  long double result = 0;
  long double x = 10;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, -9);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_16) {
  char test[] = "sic(x)";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_int_eq(correct, ERROR);
}
END_TEST

START_TEST(general_17) {
  char test[] = "logx";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_int_eq(correct, ERROR);
}
END_TEST

START_TEST(general_18) {
  char test[] = "10mod5";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_19) {
  char test[] = "10mod4";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 2);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_20) {
  char test[] = "ln(1)";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(general_21) {
  char test[] = "2^2^2";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 16);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

/* PLUS */
START_TEST(plus_1) {
  char test[] = "0+0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_2) {
  char test[] = "100+99";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 199);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_3) {
  char test[] = "-10+10";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_4) {
  char test[] = "0+1+2+3";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 6);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_5) {
  char test[] = "1.56+1.44";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 3);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_6) {
  char test[] = "123.456+76.544";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 200);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_7) {
  char test[] = "123.456+(-123.456)";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_8) {
  char test[] = "-0+0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(plus_9) {
  char test[] = "-125+25";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, -100);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

/* MINUS */
START_TEST(minus_1) {
  char test[] = "1-1";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(minus_2) {
  char test[] = "1.5-1";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0.5);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(minus_3) {
  char test[] = "10.5-20";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, -9.5);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(minus_4) {
  char test[] = "10.111-0.111";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 10);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(minus_5) {
  char test[] = "666.666 - 123.456";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 666.666 - 123.456);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(minus_6) {
  char test[] = "-10.111-0.999";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, (-10.111 - 0.999));
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

/* DIV */
START_TEST(div_1) {
  char test[] = "10/20";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 0.5);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(div_2) {
  char test[] = "0/0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_nan(result);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(div_3) {
  char test[] = "-0/0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_nan(result);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(div_4) {
  char test[] = "10/5";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 2);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(div_5) {
  char test[] = "26.25/10.5";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_eq(result, 2.5);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(div_6) {
  char test[] = "1/0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_infinite(result);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

START_TEST(div_7) {
  char test[] = "-1/0";
  long double result = 0;
  long double x = 0;
  int correct = calculate(&result, test, &x);
  ck_assert_ldouble_infinite(result);
  ck_assert_int_eq(correct, SUCSESS);
}
END_TEST

Suite *example_create() {
  Suite *suite = suite_create("TESTS");

  TCase *tcase_general = tcase_create("GENERAL");
  tcase_add_test(tcase_general, general_1);
  tcase_add_test(tcase_general, general_2);
  tcase_add_test(tcase_general, general_3);
  tcase_add_test(tcase_general, general_4);
  tcase_add_test(tcase_general, general_5);
  tcase_add_test(tcase_general, general_6);
  tcase_add_test(tcase_general, general_7);
  tcase_add_test(tcase_general, general_8);
  tcase_add_test(tcase_general, general_9);
  tcase_add_test(tcase_general, general_10);
  tcase_add_test(tcase_general, general_11);
  tcase_add_test(tcase_general, general_12);
  tcase_add_test(tcase_general, general_13);
  tcase_add_test(tcase_general, general_14);
  tcase_add_test(tcase_general, general_15);
  tcase_add_test(tcase_general, general_16);
  tcase_add_test(tcase_general, general_17);
  tcase_add_test(tcase_general, general_18);
  tcase_add_test(tcase_general, general_19);
  tcase_add_test(tcase_general, general_20);
  tcase_add_test(tcase_general, general_21);
  suite_add_tcase(suite, tcase_general);

  TCase *tcase_plus = tcase_create("PLUS");
  tcase_add_test(tcase_plus, plus_1);
  tcase_add_test(tcase_plus, plus_2);
  tcase_add_test(tcase_plus, plus_3);
  tcase_add_test(tcase_plus, plus_4);
  tcase_add_test(tcase_plus, plus_5);
  tcase_add_test(tcase_plus, plus_6);
  tcase_add_test(tcase_plus, plus_7);
  tcase_add_test(tcase_plus, plus_8);
  tcase_add_test(tcase_plus, plus_9);
  suite_add_tcase(suite, tcase_plus);

  TCase *tcase_minus = tcase_create("MINUS");
  tcase_add_test(tcase_minus, minus_1);
  tcase_add_test(tcase_minus, minus_2);
  tcase_add_test(tcase_minus, minus_3);
  tcase_add_test(tcase_minus, minus_4);
  tcase_add_test(tcase_minus, minus_5);
  tcase_add_test(tcase_minus, minus_6);
  suite_add_tcase(suite, tcase_minus);

  TCase *tcase_div = tcase_create("DIV");
  tcase_add_test(tcase_div, div_1);
  tcase_add_test(tcase_div, div_2);
  tcase_add_test(tcase_div, div_3);
  tcase_add_test(tcase_div, div_4);
  tcase_add_test(tcase_div, div_5);
  tcase_add_test(tcase_div, div_6);
  tcase_add_test(tcase_div, div_7);
  suite_add_tcase(suite, tcase_div);
  return suite;
}

int main() {
  int count;
  Suite *s = example_create();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}