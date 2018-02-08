// 最小的k个数
// 题目：输入n个整数，找出其中最小的k个数。例如输入4、5、1、6、2、7、3、8
// 这8个数字，则最小的4个数字是1、2、3、4。
#include <iostream>
#include <set>
#include <Iterator>
#include <cstdlib>
#include <vector>
using namespace std;

typedef multiset<int, std::greater<int>> intSet;
typedef multiset<int, std::greater<int>>::iterator setIterator;

int RandomInRange(int min, int max) {
  int random = rand() % (max - min + 1) + min;
  return random;
}

void Swap(int* num_a, int* num_b) {
  int temp = *num_a;
  *num_a = *num_b;
  *num_b = temp;
}

int Partition(int* numbers, int start, int end, int length) {
  int index = RandomInRange(start, end);
  Swap(&numbers[index], &numbers[end]);
  int small = start - 1;

  for(index = start; index < end; index++) {
    if(numbers[index] < numbers[end]) {
      small++;
      if(small != index) {
        Swap(&numbers[index], &numbers[small]);
      }
    }
  }

  small++;
  Swap(&numbers[small], &numbers[end]);
  return small;
}

void GetLeastNumbers_Solution1(int* numbers, int length, int* results, int k) {
  if(numbers == NULL || length <=0 || results == NULL || k > length || k <= 0) {
    return;
  }
  int start = 0;
  int end = length - 1;
  int index = Partition(numbers, start, end, length);
  while(index != k - 1) {
    if(index < k - 1) 
      index = Partition(numbers, index + 1, end, length);
    else
      index = Partition(numbers, start, index - 1, length);
  }
  for(int i = 0; i < k; i++){
    results[i] = numbers[i];
  }
}


void GetLeastNumbers_Solution2(const vector<int> numbers, intSet& results, int k) {
  results.clear();
  if (k <= 0 || numbers.size() < 0)
    return;
  vector<int>::const_iterator iter = numbers.begin();
  for(; iter != numbers.end(); iter++) {
    if(results.size() < k)
      results.insert(*iter);
    else {
      setIterator set_iter = results.begin();
      if(*iter < *(results.begin())) {
        results.erase(set_iter);
        results.insert(*iter);
      }
    }
  }
}

// ====================测试代码====================
void Test(const char* testName, int* data, int n, int* expectedResult, int k)
{
  if(testName != NULL)
    printf("%s begins: \n", testName);

  vector<int> vectorData;
  for(int i = 0; i < n; ++ i)
    vectorData.push_back(data[i]);

  if(expectedResult == NULL)
    printf("The input is invalid, we don't expect any result.\n");
  else
  {
    printf("Expected result: \n");
    for(int i = 0; i < k; ++ i)
      printf("%d\t", expectedResult[i]);
    printf("\n");
  }

  printf("Result for solution1:\n");
  int* output = new int[k];
  GetLeastNumbers_Solution1(data, n, output, k);
  if(expectedResult != NULL)
  {
    for(int i = 0; i < k; ++ i)
      printf("%d\t", output[i]);
    printf("\n");
  }

  delete[] output;

  printf("Result for solution2:\n");
  intSet leastNumbers;
  GetLeastNumbers_Solution2(vectorData, leastNumbers, k);
  printf("The actual output numbers are:\n");
  for(setIterator iter = leastNumbers.begin(); iter != leastNumbers.end(); ++iter)
    printf("%d\t", *iter);
  printf("\n\n");
}

// k小于数组的长度
void Test1()
{
  int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
  int expected[] = {1, 2, 3, 4};
  Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于数组的长度
void Test2()
{
  int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
  int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
  Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k大于数组的长度
void Test3()
{
  int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
  int* expected = NULL;
  Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k等于1
void Test4()
{
  int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
  int expected[] = {1};
  Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于0
void Test5()
{
  int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
  int* expected = NULL;
  Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// 数组中有相同的数字
void Test6()
{
  int data[] = {4, 5, 1, 6, 2, 7, 2, 8};
  int expected[] = {1, 2};
  Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// 输入空指针
void Test7()
{
  int* expected = NULL;
  Test("Test7", NULL, 0, expected, 0);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();

  return 0;
}