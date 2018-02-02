// 旋转数组的最小数字
// 题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
// 输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组
// {3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1。
#include <iostream>
using namespace std;

int MinInArray(int* numbers, int index1, int index2) {
  int min = numbers[index1];
  for(int i = index1 + 1; i <= index2; i++) {
    if(numbers[i] < min) {
      min = numbers[i];
    }
  }
  return min;
}

int Min(int* numbers, int length) {
  if(numbers == NULL || length < 0){
    cout<< "invalid input " ;
    return -1;
  }

  int index1 = 0;
  int index2 = length - 1;
  int index_mid = index1;

  while (numbers[index1] >= numbers[index2]) {
    if(index2 - index1 == 1){
      index_mid = index2;
      break;
    }

    index_mid = (index1 + index2) / 2;

    if(numbers[index1] == numbers[index2] && numbers[index2] == numbers[index_mid]) {
      return MinInArray(numbers, index1, index2);
    }

    if(numbers[index_mid] >= numbers[index1]) {
      index1 = index_mid;
    } else if(numbers[index_mid] <= numbers[index2]) {
      index2 = index_mid;
    }
  }

  return numbers[index_mid];
}

void Test(int* numbers, int length, int expect) {
  int min = Min(numbers, length);
  if( min == -1) {
    cout<< "test fail" << endl;
    return;
  }
  if(min == expect) {
    cout<< "test pass" << endl;
    return;
  } else {
    cout<< "test fail" << endl;
    return;
  }
}

int main(int argc, char const *argv[]) {
  // 典型输入，单调升序的数组的一个旋转
  int array1[] = { 3, 4, 5, 1, 2 };
  Test(array1, sizeof(array1) / sizeof(int), 1);

  // 有重复数字，并且重复的数字刚好的最小的数字
  int array2[] = { 3, 4, 5, 1, 1, 2 };
  Test(array2, sizeof(array2) / sizeof(int), 1);

  // 有重复数字，但重复的数字不是第一个数字和最后一个数字
  int array3[] = { 3, 4, 5, 1, 2, 2 };
  Test(array3, sizeof(array3) / sizeof(int), 1);

  // 有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
  int array4[] = { 1, 0, 1, 1, 1 };
  Test(array4, sizeof(array4) / sizeof(int), 0);

  // 单调升序数组，旋转0个元素，也就是单调升序数组本身
  int array5[] = { 1, 2, 3, 4, 5 };
  Test(array5, sizeof(array5) / sizeof(int), 1);

  // 数组中只有一个数字
  int array6[] = { 2 };
  Test(array6, sizeof(array6) / sizeof(int), 2);

  // 输入NULL
  Test(NULL, 0, 0);

  return 0;
}
