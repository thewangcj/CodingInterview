// 替换空格
// 题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入“We are happy.”，
// 则输出“We%20are%20happy.”。
#include <iostream>
#include <cstring>

void RepalaceBlank(char string[], int length)
{
  if (string == NULL || length <= 0)
  {
    return;
  }
  int original_length = 0;
  int num_of_blank = 0;
  int i = 0;
  while (string[i] != '\0')
  {
    original_length++;
    if (string[i] == ' ')
    {
      num_of_blank++;
    }
    i++;
  }
  int new_length = original_length + num_of_blank * 2;
  if (new_length > length)
  {
    std::cout << "存储空间不足" << '\n';
    return;
  }
  int index_of_original = original_length;
  int index_of_new = new_length;
  while (index_of_original >= 0 && index_of_new > index_of_original)
  {
    if (string[index_of_original] == ' ')
    {
      string[index_of_new--] = '0';
      string[index_of_new--] = '2';
      string[index_of_new--] = '%';
    }
    else
    {
      string[index_of_new--] = string[index_of_original];
    }
    index_of_original--;
  }
}

void TestRepalceBalnk(char test_string[], int length, const char expected[])
{
  RepalaceBlank(test_string, length);
  if (strcmp(test_string, expected) == 0)
  {
    std::cout << "test pass" << '\n';
  }
  else
  {
    std::cout << "test fail" << '\n';
    std::cout << test_string << ',' << expected << '\n';
  }
}

int main()
{
  const int length = 100;
  char test_string1[100] = "hello world";
  TestRepalceBalnk(test_string1, length, "hello%20world");
  char test_string2[100] = " hello world";
  TestRepalceBalnk(test_string2, length, "%20hello%20world");
  char test_string3[100] = "hello  world";
  TestRepalceBalnk(test_string3, length, "hello%20%20world");
  char test_string4[100] = "   ";
  TestRepalceBalnk(test_string4, length, "%20%20%20");
  char test_string5[100] = "";
  TestRepalceBalnk(test_string5, length, "");
  return 0;
}
