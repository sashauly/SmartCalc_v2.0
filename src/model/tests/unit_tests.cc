#include <gtest/gtest.h>

#include "../model.h"

TEST(SmartCalc, TestValidator) {
  s21::Model a;
  std::string str = "(2+3)))--";
  int res = (a.Validator(str));
  EXPECT_EQ(res, 0);
}

TEST(SmartCalc, TestFuncError) {
  s21::Model a;
  std::string str = "fgxh";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_EQ(res, 0);
}

TEST(SmartCalc, TestFuncError1) {
  s21::Model a;
  std::string str = "1/0";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_EQ(res, INFINITY);
}

TEST(SmartCalc, TestBracketsError1) {
  s21::Model a;
  std::string str = "()";
  int res = (a.Validator(str));
  EXPECT_EQ(res, 0);
}

TEST(SmartCalc, TestBracketsError2) {
  s21::Model a;
  std::string str = ")(";
  int res = (a.Validator(str));
  EXPECT_EQ(res, 0);
}

TEST(SmartCalc, TestOperation) {
  s21::Model a;
  std::string str = "-4 + 9 + 7 - 9";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_EQ(res, 3);
}
TEST(SmartCalc, TestOperation1) {
  s21::Model a;
  std::string str = "+4 + 9 / 2 * 67787";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_EQ(res, 305045.5);
}
TEST(SmartCalc, TestFunc) {
  s21::Model a;
  std::string str = "(4^acos(2/4))";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 4.27047);
}
TEST(SmartCalc, TestFunc1) {
  s21::Model a;
  std::string str = "(tan(2*2))";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 1.1578213);
}
TEST(SmartCalc, TestFunc2) {
  s21::Model a;
  std::string str = "(4^acos(2/4)/tan(2*2))";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 3.6883678);
}
TEST(SmartCalc, TestFunc3) {
  s21::Model a;
  std::string str = "(4^acos(2/4)/tan(2*2)/5^acos(2/4))";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 0.68371409);
}
TEST(SmartCalc, TestFunc4) {
  s21::Model a;
  std::string str = "(4^acos(2/4)/tan(2*2)/5^acos(2/4)/tan(tan(tan(2*2))))";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, -0.58934796);
}
TEST(SmartCalc, TestFunc5) {
  s21::Model a;
  std::string str = "3^cos(0.5)/5";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 0.52449733);
}
TEST(SmartCalc, TestFunc6) {
  s21::Model a;
  std::string str = "3^cos(0.5)/sqrt(25)";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 0.52449733);
}
TEST(SmartCalc, TestFunc7) {
  s21::Model a;
  std::string str = "log(10)";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 1);
}
TEST(SmartCalc, TestFunc8) {
  s21::Model a;
  std::string str = "1+2*(3^sin(0.4))^3*2+1";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 16.436413);
}
TEST(SmartCalc, TestFunc9) {
  s21::Model a;
  std::string str = "ln(10)";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 2.3025851);
}
TEST(SmartCalc, TestFunc10) {
  s21::Model a;
  std::string str = "1+2*3^sin(0.4)^3*2+1";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 6.291162);
}
TEST(SmartCalc, TestFunc11) {
  s21::Model a;
  std::string str = "1+2*3^sin(0.4)^56*2+1";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 6);
}
TEST(SmartCalc, TestFunc12) {
  s21::Model a;
  std::string str = "acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 1.5935309);
}
TEST(SmartCalc, TestFunc13) {
  s21::Model a;
  std::string str = "(-5)^(-4)";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 0.0016);
}
TEST(SmartCalc, TestFunc14) {
  s21::Model a;
  std::string str = "-4+5";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 1);
}
TEST(SmartCalc, TestFunc15) {
  s21::Model a;
  std::string str = "4%8";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, 4);
}
TEST(SmartCalc, TestFunc16) {
  s21::Model a;
  std::string str = "4^acos(x/4)/tan(2*x)";
  double res;
  double x = 2.0;
  if (a.Validator(str)) {
    res = a.Calculator(str, x);
  }
  EXPECT_FLOAT_EQ(res, pow(4, acos(x / 4)) / tan(2 * x));
}
TEST(SmartCalc, TestFunc17) {
  s21::Model a;
  std::string str = "(4^acos(x/4))/tan(2*x)";
  double res;
  double x = 2.0;
  if (a.Validator(str)) {
    res = a.Calculator(str, x);
  }
  EXPECT_FLOAT_EQ(res, (pow(4, acos(x / 4)) / tan(2 * x)));
}
TEST(SmartCalc, TestFunc18) {
  s21::Model a;
  std::string str =
      "(4 ^acos( 2/4 )/tan( 2*2 )/( 5 ^acos( 2/4 ))/tan(tan(tan( 2*2))))";
  double res;
  double x = 2.0;
  if (a.Validator(str)) {
    res = a.Calculator(str, x);
  }
  EXPECT_FLOAT_EQ(res, -0.58934793341);
}
TEST(SmartCalc, TestFunc19) {
  s21::Model a;
  std::string str = "2^sin(0.4)^3";
  double res;
  double x = 0.0;
  if (a.Validator(str)) {
    res = a.Calculator(str, x);
  }
  EXPECT_TRUE((fabs(1.041782) - fabs(res)) < 10e-7);
}
TEST(SmartCalc, TestFunc20) {
  s21::Model a;
  std::string str = "sin(-)";
  double res;
  res = (a.Validator(str));
  EXPECT_FLOAT_EQ(res, 0);
}
TEST(SmartCalc, TestFunc21) {
  s21::Model a;
  std::string str =
      "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
  double res;
  double x = 0.0;
  if (a.Validator(str)) {
    res = a.Calculator(str, x);
  }
  EXPECT_FLOAT_EQ(res, 130);
}
TEST(SmartCalc, TestFunc22) {
  s21::Model a;
  std::string str = "sin()";
  double res;
  res = (a.Validator(str));
  EXPECT_FLOAT_EQ(res, 0);
}
TEST(SmartCalc, TestFunc23) {
  s21::Model a;
  std::string str = "2+7.55.5";
  double res;
  res = (a.Validator(str));
  EXPECT_FLOAT_EQ(res, 0);
}
TEST(SmartCalc, TestFunc24) {
  s21::Model a;
  std::string str = "cos(pi)";
  double res;
  if (a.Validator(str)) {
    res = a.Calculator(str, 0.0);
  }
  EXPECT_FLOAT_EQ(res, cos(acos(-1)));
}
TEST(SmartCalc, TestFunc25) {
  s21::Model a;
  std::string str = ".5";
  double res;
  res = (a.Validator(str));
  EXPECT_FLOAT_EQ(res, 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}