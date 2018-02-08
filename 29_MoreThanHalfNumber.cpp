// 数组中出现次数超过一半的数字
// 题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例
// 如输入一个长度为9的数组{1, 2, 3, 2, 2, 2, 5, 4, 2}。由于数字2在数组中
// 出现了5次，超过数组长度的一半，因此输出2。

#include <iostream>
#include <cstdlib>
using namespace std;

bool g_bInputInvalid = false;

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

bool CheckMoreThanHalf(int* numbers, int length, int number) {
	int times = 0;
  for(int i = 0; i < length; ++i)
  {
    if(numbers[i] == number)
      times++;
  }

  bool isMoreThanHalf = true;
  if(times * 2 <= length)
  {
    g_bInputInvalid = true;
    isMoreThanHalf = false;
  }

  return isMoreThanHalf;
}

int MoreThanHalfNum(int* numbers, int length) {
	if(numbers == NULL && length <= 0) {
		g_bInputInvalid = true;
		return 0;
	}

	int middle = length >> 1;
	int start = 0;
	int end = length - 1;
	int index = Partition(numbers, start, end, length);
	while(index != middle) {
		if(index < middle) 
			index = Partition(numbers, index + 1, end, length);
		else
			index = Partition(numbers, start, index - 1, length);
	}

	return CheckMoreThanHalf(numbers, length, numbers[index]) ? numbers[index] : 0;
}

int MoreThanHalfNum_Other(int* numbers, int length) {
	if(numbers == NULL && length <= 0) {
		g_bInputInvalid = true;
		return 0;
	}

	int result = numbers[0];
	int times = 1;
	for(int index = 1; index < length; index++) {
		if(times == 0) {
			result = numbers[index];
			times = 1;
		}
		if(result != numbers[index])
			times--;
		else
			times++;
	}
	return CheckMoreThanHalf(numbers, length, result) ? result : 0;
}


// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, int expectedValue, bool expectedFlag)
{
  if(testName != NULL)
    printf("%s begins: \n", testName);

  int* copy = new int[length];
  for(int i = 0; i < length; ++i)
    copy[i] = numbers[i];

  printf("Test for solution1: ");
  int result = MoreThanHalfNum(numbers, length);
  if(result == expectedValue && g_bInputInvalid == expectedFlag)
    printf("Passed.\n");
  else
    printf("Failed.\n");

  printf("Test for solution2: ");
  result = MoreThanHalfNum_Other(copy, length);
   if(result == expectedValue && g_bInputInvalid == expectedFlag)
    printf("Passed.\n\n");
  else
    printf("Failed.\n\n");

  delete[] copy;
  g_bInputInvalid = false;
}

// 存在出现次数超过数组长度一半的数字
void Test1()
{
  int numbers[] = {1, 2, 3, 2, 2, 2, 5, 4, 2};
  Test("Test1", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 不存在出现次数超过数组长度一半的数字
void Test2()
{
  int numbers[] = {1, 2, 3, 2, 4, 2, 5, 2, 3};
  Test("Test2", numbers, sizeof(numbers) / sizeof(int), 0, true);
}

// 出现次数超过数组长度一半的数字都出现在数组的前半部分
void Test3()
{
  int numbers[] = {2, 2, 2, 2, 2, 1, 3, 4, 5};
  Test("Test3", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 出现次数超过数组长度一半的数字都出现在数组的后半部分
void Test4()
{
  int numbers[] = {1, 3, 4, 5, 2, 2, 2, 2, 2};
  Test("Test4", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 只有一个元素
void Test5()
{
 	int numbers[] = {1};
 	Test("Test5", numbers, 1, 1, false);
}

// 输入空指针
void Test6()
{
  Test("Test6", NULL, 0, 0, true);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();

  return 0;
}