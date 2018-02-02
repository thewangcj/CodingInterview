// 赋值运算符函数
// 题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数。
#include <iostream>
#include <cstring>
using namespace std;

class CMyString
{
public:
  CMyString(const char* pDate = NULL);
  CMyString(const CMyString& str);
  CMyString& operator=(const CMyString& str);
  ~CMyString(void);
  void print() const;
private:
  char * m_pDate;
};

inline CMyString::CMyString(const char* pDate)
{
  if(pDate) {
    m_pDate = new char[strlen(pDate) + 1];
    strcpy(m_pDate,pDate);
  }
  else {
    m_pDate = new char[1];
    *m_pDate = '\0';
  }
}

inline CMyString::CMyString(const CMyString& str)
{
  m_pDate = new char[strlen(str.m_pDate) + 1];
  strcpy(m_pDate,str.m_pDate);
}

CMyString& CMyString::operator = (const CMyString& str)
{
  if(this == &str){
    return *this;
  }
  else{
    delete[] m_pDate;
    m_pDate = new char[strlen(str.m_pDate) + 1];
    strcpy(m_pDate,str.m_pDate);
    return *this;
  }
}

CMyString::~CMyString()
{
  delete[] m_pDate;
}

void CMyString::print() const
{
  cout<<m_pDate<<endl;
}

int main()
{
  CMyString a("hello");
  CMyString b = a;
  a.print();
  b.print();
  return 0;
}
