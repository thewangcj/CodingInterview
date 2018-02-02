// 调整数组顺序使奇数位于偶数前面
// 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有
// 奇数位于数组的前半部分，所有偶数位于数组的后半部分。
#include <iostream>
using namespace std;

void ReorderArray(int* array, unsigned int size) {
  if( array == NULL || size == 0) {
    return;
  }
  int* p_begin = array;
  int* p_end = array + size - 1;

  while (p_begin < p_end) {
    while (p_begin < p_end && (*p_begin & 0x1) != 0) {
      p_begin++;
    }
    while (p_end > p_begin && (*p_end & 0x1) == 0) {
      p_end--;
    }
    if(p_begin < p_end){
      int tmp = *p_begin;
      *p_begin = *p_end;
      *p_end = tmp;
    }
  }
}

int main(int argc, char const *argv[]) {
  int numbers[] = {1, 2, 3, 4, 5, 6, 7};
  ReorderArray(numbers, 7);
  for (size_t i = 0; i < 7; i++) {
    cout<< numbers[i] << ' ';
  }
  cout<< endl;
  return 0;
}
