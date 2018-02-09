// 从1到n整数中1出现的次数
// 题目：输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。例如
// 输入12，从1到12这些整数中包含1 的数字有1，10，11和12，1一共出现了5次。
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int PowerBase10(unsigned int n) {
	int result = 1;
	for(unsigned int i = 0; i < n; i++) {
		result *= 10;
	}
	return result;
}

int NumberOfOne(const char* str) {
	if(!str || *str < '0' || *str > '9' || *str == '\0')
		return 0;
	int first = *str - '0';
	size_t length = static_cast<unsigned int>(strlen(str));
	if(length == 1 && first == 0)
		return 0;
	if(length == 1 && first > 0)
		return 1;

	int num_frist_digit = 0;
	if(first > 1)
		num_frist_digit = PowerBase10(length - 1);
	else if(first == 1)
		num_frist_digit = atoi(str + 1) + 1;

	int num_other_digit = first * (length - 1) * PowerBase10(length - 2);
	int num_recursive = NumberOfOne(str + 1);

	return num_frist_digit + num_other_digit + num_recursive;
}

int NumberOf1Between1AndN(int n) {
	if(n < 0)
		return 0;
	char str[50];
	sprintf(str, "%d", n);
	return NumberOfOne(str);
}

// ====================测试代码====================
void Test(const char* testName, int n, int expected) {
  if(testName != NULL)
    printf("%s begins: \n", testName);
  
  if(NumberOf1Between1AndN(n) == expected)
    printf("passed.\n");
  else
    printf("failed.\n"); 

  printf("\n");
}

void Test() {
  Test("Test1", 1, 1);
  Test("Test2", 5, 1);
  Test("Test3", 10, 2);
  Test("Test4", 55, 16);
  Test("Test5", 99, 20);
  Test("Test6", 10000, 4001);
  Test("Test7", 21345, 18821);
  Test("Test8", 0, 0);
}

int main(int argc, char const *argv[])
{
	Test();
	return 0;
}