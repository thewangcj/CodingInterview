// 字符串的排列
// 题目：输入一个字符串，打印出该字符串中字符的所有排列。例如输入字符串abc，
// 则打印出由字符a、b、c所能排列出来的所有字符串abc、acb、bac、bca、cab和cba。
#include <iostream>

using namespace std;

void Permutation(char* str, char* begin) {
	if(str == NULL)
		return;
	else if(*begin == '\0')
		cout<< str << endl;
	else {
		for(char* ch = begin; *ch != '\0'; ++ch) {
			char temp = *ch;
			*ch = *begin;
			*begin = temp;

			Permutation(str, begin + 1);

			temp = *ch;
			*ch = *begin;
			*begin = temp;
		}
	}
}

// ====================测试代码====================
void Test(char* pStr)
{
  if(pStr == NULL)
    printf("Test for NULL begins:\n");
  else
    printf("Test for %s begins:\n", pStr);

  Permutation(pStr, pStr);

  printf("\n");
}

int main(int argc, char* argv[])
{
  Test(NULL);

  char string1[] = "";
  Test(string1);

  char string2[] = "a";
  Test(string2);

  char string3[] = "ab";
  Test(string3);

  char string4[] = "abc";
  Test(string4);

  return 0;
}