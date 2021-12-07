// 二进制中1的个数
// 题目：请实现一个函数，输入一个整数，输出该数二进制表示中1的个数。例如
// 把9表示成二进制是1001，有2位是1。因此如果输入9，该函数输出2。
#include <iostream>
using namespace std;

int NumOfOneSolutionOne(int n) {
  int num = 0;
  unsigned int flag = 1;
  while ( flag ) {
    if(n & flag) {
      num++;
    }
    flag = flag << 1;
  }
  return num;
}

int NumOfOneSolutionTwo(int n) {
  int num = 0;
  while ( n ) {
    n = (n - 1) & n;
    num++;
  }
  return num;
}

void Test(int n, int expect) {
  if(NumOfOneSolutionOne(n) == expect && NumOfOneSolutionTwo(n) == expect) {
    cout<< "test pass" << endl;
    return;
  } else {
    cout<< "solution_one:" << NumOfOneSolutionOne(n)
        << " solution_two:" << NumOfOneSolutionTwo(n)
        << " expect:" << expect <<" test fail" << endl;
    return;
  }
}

int main(int argc, char const *argv[]) {
  // 输入0，期待的输出是0
  Test(0, 0);

  // 输入1，期待的输出是1
  Test(1, 1);

  // 输入10，期待的输出是2
  Test(10, 2);

  // 输入0x7FFFFFFF，期待的输出是31
  Test(0x7FFFFFFF, 31);

  // 输入0xFFFFFFFF（负数），期待的输出是32
  Test(0xFFFFFFFF, 32);

  // 输入0x80000000（负数），期待的输出是1
  Test(0x80000000, 1);
  return 0;
}
