// 实现Singleton模式
// 题目：设计一个类，我们只能生成该类的一个实例。
#include <iostream>
#include <cstring>
using namespace std;

class Singleton1
{
public:
  static Singleton1& getInstance()
  {
    return instance;
  }

private:
  Singleton1(){
    cout << "Singleton1 构造" << endl;
  };
  ~Singleton1(){
    cout << "Singleton1 析构" << endl;
  }
  Singleton1(const Singleton1 &);
  static Singleton1 instance;
};
Singleton1 Singleton1::instance;

class Singleton2
{
public:
  //只有当需要这个单例对象的时候才创建
  static Singleton2 &getInstance()
  {
    static Singleton2 instance;
    return instance;
  }

private:
  Singleton2(){
    cout << "Singleton2 构造" << endl;
  };
  ~Singleton2(){
    cout << "Singleton2 析构" << endl;
  }
  Singleton2(const Singleton2 &);
};

void test1()
{
  cout << "单例模式 singleton1 访问前" << endl;
  Singleton1 *singleton1 = &Singleton1::getInstance();
  Singleton1 *singleton2 = &Singleton1::getInstance();
  cout << (singleton1 == singleton2) << '\n';
}

void test2()
{
  cout << "单例模式 singleton2 访问前" << endl;
  Singleton2 *singleton1 = &Singleton2::getInstance();
  Singleton2 *singleton2 = &Singleton2::getInstance();
  cout << (singleton1 == singleton2) << '\n';
}

int main()
{
  test1();
  test2();
  return 0;
}
