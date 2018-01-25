#include <iostream>
#include <cmath>
using namespace std;
bool g_invalid_input = false;

bool equal(double num1, double num2)
{
  if (abs(num1 - num2) < 0.0000001) {
    return true;
  } else {
    return false;
  }
}

double power_with_unsigned_exponent(double base, unsigned int abs_exponent) {
  if( abs_exponent == 0)  return 1;
  if( abs_exponent == 1)  return base;
  double result  = power_with_unsigned_exponent(base, abs_exponent >> 1);
  result *= result;
  if( (abs_exponent & 0x1) == 1)  result *= base;
  return result;
}

double Power(double base, int exponent)
{
  g_invalid_input = false;
  if(equal(base, 0.0) && exponent < 0) {
    g_invalid_input = true;
    return 0.0;
  }

  double result = power_with_unsigned_exponent(base, abs(exponent));
  if(exponent < 0) {
    return 1.0 / result;
  } else {
    return result;
  }

}

void Test(const char* testName, double base, int exponent, double expected_result, bool expected_flag)
{
    double result = Power(base, exponent);
    if (equal(result, expected_result) && g_invalid_input == expected_flag)
      cout << testName << " passed" << std::endl;
    else
      cout << testName << " FAILED" << std::endl;
}

int main(int argc, char const *argv[]) {
  // 底数、指数都为正数
  Test("Test1", 2, 3, 8, false);

  // 底数为负数、指数为正数
  Test("Test2", -2, 3, -8, false);

  // 指数为负数
  Test("Test3", 2, -3, 0.125, false);

  // 指数为0
  Test("Test4", 2, 0, 1, false);

  // 底数、指数都为0
  Test("Test5", 0, 0, 1, false);

  // 底数为0、指数为正数
  Test("Test6", 0, 4, 0, false);

  // 底数为0、指数为负数
  Test("Test7", 0, -4, 0, true);

  return 0;
}
