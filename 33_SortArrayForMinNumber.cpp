// 把数组排成最小的数
// 题目：输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼
// 接出的所有数字中最小的一个。例如输入数组{3, 32, 321}，则打印出这3个数
// 字能排成的最小数字321323。
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int G_MAX_LENGTH = 10;
char* g_string1 = new char[G_MAX_LENGTH * 2 + 1];
char* g_string2 = new char[G_MAX_LENGTH * 2 + 1];

int compare(const void* str_number1, const void* str_number2) {
	strcpy(g_string1, *(const char**)str_number1);
	strcat(g_string1, *(const char**)str_number2);

	strcpy(g_string2, *(const char**)str_number2);
	strcat(g_string2, *(const char**)str_number1);

	return strcmp(g_string1, g_string2);
}

void PrintMinNumber(const int* numbers, int length) {
	if(numbers == NULL || length < 0)
		return;

	char** str_numbers = (char**)(new int[length]);

	for(int i = 0; i < length; i++) {
		str_numbers[i] = new char[G_MAX_LENGTH + 1];
		sprintf(str_numbers[i], "%d", numbers[i]);
	}

	qsort(str_numbers, length, sizeof(char*), compare);

	for(int i = 0; i < length; i++) {
		cout<< str_numbers[i];
	}
	cout<<endl;

	for(int i = 0; i < length; i++) {
		delete[] str_numbers[i];
	}
	delete[] str_numbers;
}

// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, const char* expectedResult)
{
  if(testName != NULL)
    printf("%s begins:\n", testName);

  if(expectedResult != NULL)
    printf("Expected result is: \t%s\n", expectedResult);

  printf("Actual result is: \t");
  PrintMinNumber(numbers, length);

  printf("\n");
}

void Test1()
{
  int numbers[] = {3, 5, 1, 4, 2};
  Test("Test1", numbers, sizeof(numbers)/sizeof(int), "12345");
}

void Test2()
{
  int numbers[] = {3, 32, 321};
  Test("Test2", numbers, sizeof(numbers)/sizeof(int), "321323");
}

void Test3()
{
  int numbers[] = {3, 323, 32123};
  Test("Test3", numbers, sizeof(numbers)/sizeof(int), "321233233");
}

void Test4()
{
  int numbers[] = {1, 11, 111};
  Test("Test4", numbers, sizeof(numbers)/sizeof(int), "111111");
}

// 数组中只有一个数字
void Test5()
{
  int numbers[] = {321};
  Test("Test5", numbers, sizeof(numbers)/sizeof(int), "321");
}

void Test6()
{
  Test("Test6", NULL, 0, "Don't print anything.");
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