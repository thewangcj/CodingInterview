// 赋值运算符函数
// 题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数。
#include <iostream>
#include <cstring>
using namespace std;

class CMyString
{
public:
  CMyString(const char *pDate = NULL);
  CMyString(const CMyString &str);
  CMyString &operator=(const CMyString &str);
  ~CMyString(void);
  void Print() const;

private:
  char *m_pData;
};

inline CMyString::CMyString(const char *pDate)
{
  if (pDate)
  {
    m_pData = new char[strlen(pDate) + 1];
    strcpy(m_pData, pDate);
  }
  else
  {
    m_pData = new char[1];
    *m_pData = '\0';
  }
}

inline CMyString::CMyString(const CMyString &str)
{
  m_pData = new char[strlen(str.m_pData) + 1];
  strcpy(m_pData, str.m_pData);
}

CMyString &CMyString::operator=(const CMyString &str)
{
  if (this == &str)
  {
    return *this;
  }
  else
  {
    // delete[] m_pData;
    // m_pData = new char[strlen(str.m_pData) + 1];
    // strcpy(m_pData, str.m_pData);
    // return *this;
    CMyString strTemp(str);
    char* pTemp = strTemp.m_pData;
    strTemp.m_pData = m_pData;
    m_pData = pTemp;
    return *this;
  }
}

CMyString::~CMyString()
{
  delete[] m_pData;
}

// ====================测试代码====================
void CMyString::Print() const
{
  printf("%s", m_pData);
}

void Test1()
{
  printf("Test1 begins:\n");

  const char* text = "Hello world";

  CMyString str1(text);
  CMyString str2;
  str2 = str1;

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str2.Print();
  printf(".\n");
}

// 赋值给自己
void Test2()
{
  printf("Test2 begins:\n");

  const char* text = "Hello world";

  CMyString str1(text);
  str1 = str1;

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str1.Print();
  printf(".\n");
}

// 连续赋值
void Test3()
{
  printf("Test3 begins:\n");

  const char* text = "Hello world";

  CMyString str1(text);
  CMyString str2, str3;
  str3 = str2 = str1;

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str2.Print();
  printf(".\n");

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str3.Print();
  printf(".\n");
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();

  return 0;
}
