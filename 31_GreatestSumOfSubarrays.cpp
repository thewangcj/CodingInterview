// 连续子数组的最大和
// 题目：输入一个整型数组，数组里有正数也有负数。数组中一个或连续的多个整
// 数组成一个子数组。求所有子数组的和的最大值。要求时间复杂度为O(n)。

#include <iostream>
using namespace std;
bool g_InvalidInput = false;

int FindGreatestSumOfSubArray(int* numbers, int length) {
	if(numbers == NULL || length < 0){
		g_InvalidInput = true;
		return 0;
	}

	int current_sum = 0;
	int greatest_sum = numbers[0];
	for(int i = 0; i < length; i++) {
		if(current_sum < 0)
			current_sum = numbers[i];
		else
			current_sum += numbers[i];
		if(current_sum > greatest_sum)
			greatest_sum = current_sum;
	}
	return greatest_sum;
}

void Test(const char* testName, int* numbers, int nLength, int expected, bool expectedFlag)
{
	if(testName != NULL)
    printf("%s begins: \n", testName);

	int result = FindGreatestSumOfSubArray(numbers, nLength);
	if(result == expected && expectedFlag == g_InvalidInput)
    printf("Passed.\n");
	else
    printf("Failed.\n");
  g_InvalidInput = false;
}

// 1, -2, 3, 10, -4, 7, 2, -5
void Test1()
{
	int data[] = {1, -2, 3, 10, -4, 7, 2, -5};
  Test("Test1", data, sizeof(data) / sizeof(int), 18, false);
}

// 所有数字都是负数
// -2, -8, -1, -5, -9
void Test2()
{
  int data[] = {-2, -8, -1, -5, -9};
  Test("Test2", data, sizeof(data) / sizeof(int), -1, false);
}

// 所有数字都是正数
// 2, 8, 1, 5, 9
void Test3()
{
  int data[] = {2, 8, 1, 5, 9};
  Test("Test3", data, sizeof(data) / sizeof(int), 25, false);
}

// 无效输入
void Test4()
{
  Test("Test4", NULL, 0, 0, true);
}

int main(int argc, char const *argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	return 0;
}