#include <gtest/gtest.h>

#include "Model/s21_calculator.h"

/* Calculation test */

TEST(calc_test, test_1) {
  long double result{1.124674733};
  s21::Calculator s;
  s.Calculate("sin(-(-2^(-3)))+log(10^(-4)*10^4*10)");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-9);
}

TEST(calc_test, test_2) {
  long double result = 2.076710069;
  s21::Calculator s;
  s.Calculate("1+2/3^(sin(4-ln(5*6)))");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-9);
}

TEST(calc_test, test_3) {
  long double result = -0.9115691;
  s21::Calculator s;
  s.Calculate("-1+11modsin(5-3)");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test_4) {
  long double result = 5.8252831;
  s21::Calculator s;
  s.Calculate("sqrt(atan(2^10)mod3-7/6)*(-5)+9");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test5) {
  long double result{10.8305775};
  s21::Calculator s;
  s.Calculate("1-2+3*4^tan(10)^cos(30)^2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test6) {
  long double result{256};
  s21::Calculator s;
  s.Calculate("2^(4-2)^3");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test7) {
  long double result{-2.4185717};
  s21::Calculator s;
  s.Calculate("-1+(-sqrt(2+3^(-4)))");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test8) {
  long double result{-46.9567724284};
  s21::Calculator s;
  s.Calculate("-13.2+ln(323.9-3.1)/cos(-7.)*(1.02-5.43)");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-10);
}

TEST(calc_test, test9) {
  long double result{3.16436430321};
  s21::Calculator s;
  s.Calculate("1+2^log(13)");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-11);
}

TEST(calc_test, test10) {
  long double result{-4.8407205193};
  s21::Calculator s;
  s.Calculate("acos(0.5-0.1)-2*3");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-10);
}

TEST(calc_test, test11) {
  long double result{-1.5707963268};
  s21::Calculator s;
  s.Calculate("0-asin(10/10)");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-10);
}

TEST(calc_test, test12) {
  long double result{50};
  s21::Calculator s;
  s.Calculate("2(10/3)sqrt(100-75)1.5");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-10);
}

TEST(calc_test, test13) {
  long double result{1.7018070491};
  s21::Calculator s;
  s.Calculate("sin(24+(30-3*(7-4)))*4/2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-10);
}

TEST(calc_test, test14) {
  long double result{0.5};
  s21::Calculator s;
  s.Calculate("1./2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test15) {
  long double result{24};
  s21::Calculator s;
  s.Calculate("(2+10)2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test16) {
  long double result{28};
  s21::Calculator s;
  s.Calculate("2(3+4)2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test17) {
  long double result{40};
  s21::Calculator s;
  s.Calculate("2((sqrt(9)+2)2)*2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test18) {
  long double result{40};
  s21::Calculator s;
  s.Calculate("2((sqrt(9)+2)2)*2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test19) {
  long double result{-3};
  s21::Calculator s;
  s.Calculate("9/(-(-(-3)))");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test20) {
  long double result{1};
  s21::Calculator s;
  s.Calculate("sin(9)^2+cos(9)^2");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test21) {
  long double result{3};
  s21::Calculator s;
  s.Calculate("9/(-(-3");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test22) {
  long double result{-3};
  s21::Calculator s;
  s.Calculate("9/(-(-(-3))");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test23) {
  long double result{-3};
  s21::Calculator s;
  s.Calculate("-(1+2)");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test24) {
  long double result{-2};
  s21::Calculator s;
  s.Calculate("-(((1+1)/1)+(2+2)*(3+3))/13");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test25) {
  long double result{-0.98803162409};
  s21::Calculator s;
  s.Calculate("sin(30");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-11);
}

TEST(calc_test, test26) {
  long double result{-3.00006};
  s21::Calculator s;
  s.Calculate("(4-7+(-0.00006");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test27) {
  long double result{3.3333333};
  s21::Calculator s;
  s.Calculate("10/3");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test28) {
  long double result{10};
  s21::Calculator s;
  s.Calculate("10/3*3");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test29) {
  long double result{9432.5234};
  s21::Calculator s;
  s.Calculate("9432.5234");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test30) {
  long double result{1e-3};
  s21::Calculator s;
  s.Calculate("1e-3*1");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test31) {
  long double result{1e7};
  s21::Calculator s;
  s.Calculate("1e10/1000");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test32) {
  long double result{0.00099999983};
  s21::Calculator s;
  s.Calculate("sin(1e-3)");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-11);
}

TEST(calc_test, test33) {
  long double result{111111111};
  s21::Calculator s;
  s.Calculate("12345679*9");

  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test34) {
  long double result{1};
  s21::Calculator s;
  s.Calculate("(1/2)/(1/2)");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test35) {
  long double result{0.25};
  s21::Calculator s;
  s.Calculate("(1/2)*(1/2)");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(calc_test, test36) {
  long double result{6};
  s21::Calculator s;
  s.Calculate("+2+(+2)*(+2)");
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

// Test for x

TEST(x_test, test1) {
  long double result{60};
  s21::Calculator s;
  s.Calculate("2xsqrt(9)", 10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test2) {
  long double result{1000000};
  s21::Calculator s;
  s.Calculate("xxx", 100);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test3) {
  long double result{100000};
  s21::Calculator s;
  s.Calculate("xsqrt(x)x", 100);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test4) {
  long double result{70};
  s21::Calculator s;
  s.Calculate("(3-1)x(x+2)", 5);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test5) {
  long double result{111.1};
  s21::Calculator s;
  s.Calculate("x10", 11.11);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test6) {
  long double result{-19};
  s21::Calculator s;
  s.Calculate("2x+1", -10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test7) {
  long double result{-100};
  s21::Calculator s;
  s.Calculate("-x*10", 10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test8) {
  long double result{-1};
  s21::Calculator s;
  s.Calculate("4+(-x/2)", 10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test9) {
  long double result{-110};
  s21::Calculator s;
  s.Calculate("-x+(-x*x)", 10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test10) {
  long double result{-9};
  s21::Calculator s;
  s.Calculate("(-x/(-x))-x", 10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test11) {
  long double result{-9};
  s21::Calculator s;
  s.Calculate("(-x/(-x))-x", 10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test12) {
  long double result{11};
  s21::Calculator s;
  s.Calculate("-x+(-x/(-x))", -10);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test13) {
  long double result{-10};
  s21::Calculator s;
  s.Calculate("-(-x+4)", -6);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test14) {
  long double result{9};
  s21::Calculator s;
  s.Calculate("-x^2", 3);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

TEST(x_test, test15) {
  long double result{1};
  s21::Calculator s;
  s.Calculate("-(x^2)+10", 3);
  EXPECT_TRUE(fabsl(s.GetAnswer() - result) < 1e-7);
}

/* Validation test */

TEST(valid_test, test1) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate(".3-2"); });
}

TEST(valid_test, test2) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("(8-8("); });
}

TEST(valid_test, test3) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("123.321.2/321.32"); });
}

TEST(valid_test, test4) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("2)-4"); });
}

TEST(valid_test, test5) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("200/*2"); });
}

TEST(valid_test, test6) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("123..5+1"); });
}

TEST(valid_test, test7) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("123*/21"); });
}

TEST(valid_test, test8) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("/2"); });
}

TEST(valid_test, test9) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("1/.2"); });
}

TEST(valid_test, test10) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("sin()"); });
}

TEST(valid_test, test11) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("sin(cos("); });
}

TEST(valid_test, test12) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("acos(^2)"); });
}

TEST(valid_test, test13) {
  s21::Calculator s;
  EXPECT_ANY_THROW({ s.Calculate("sqrt(5-3)/"); });
}

/* Tests for INF */

TEST(inf_test, inf1) {
  long double result{-INFINITY};
  s21::Calculator s;
  s.Calculate("ln(3mod2-1)");

  EXPECT_TRUE(s.GetAnswer() == result);
  EXPECT_TRUE(s.GetAnswerString() == "-INF");
}

TEST(inf_test, inf2) {
  long double result{INFINITY};
  s21::Calculator s;
  s.Calculate("123.321/0");

  EXPECT_TRUE(s.GetAnswer() == result);
  EXPECT_TRUE(s.GetAnswerString() == "INF");
}

TEST(inf_test, inf3) {
  s21::Calculator s;
  s.Calculate("sqrt(1/0)");

  EXPECT_TRUE(s.GetAnswer() == INFINITY);
  EXPECT_TRUE(s.GetAnswerString() == "INF");
}

/* Tests for nan */

TEST(nan_test, nan1) {
  s21::Calculator s;
  s.Calculate("sqrt(-9)");

  EXPECT_TRUE(s.GetAnswer() != s.GetAnswer());
  EXPECT_TRUE(s.GetAnswerString() == "nan");
}

TEST(nan_test, nan2) {
  s21::Calculator s;
  s.Calculate("ln(-323.9)");

  EXPECT_TRUE(s.GetAnswer() != s.GetAnswer());
  EXPECT_TRUE(s.GetAnswerString() == "nan");
}

TEST(nan_test, nan3) {
  s21::Calculator s;
  s.Calculate("-1+-sqrt(-2+3^-4)");

  EXPECT_TRUE(s.GetAnswer() != s.GetAnswer());
  EXPECT_TRUE(s.GetAnswerString() == "nan");
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
