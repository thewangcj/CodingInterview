// 斐波那契数列
// 题目：写一个函数，输入n，求斐波那契（Fibonacci）数列的第n项。
#include <iostream>
using namespace std;

long long Fabonacci(unsigned const int n) {
  int result[2] = {0, 1};
  if(n < 2) {
    return result[n];
  }

  long long fib_one = 0;
  long long fib_two = 1;
  long long fib_n = 0;
  for(unsigned int i = 2; i <= n; i++) {
    fib_n = fib_one + fib_two;
    fib_one = fib_two;
    fib_two = fib_n;
  }
  return fib_n;
}

int main(int argc, char const *argv[]) {
  cout<< Fabonacci(2) << endl;;
  cout<< Fabonacci(48) << endl;
  cout<< Fabonacci(49) << endl;
  cout<< Fabonacci(50) << endl;

  return 0;
}
