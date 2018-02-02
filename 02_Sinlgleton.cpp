// 实现Singleton模式
// 题目：设计一个类，我们只能生成该类的一个实例。
#include <iostream>
#include <cstring>
using namespace std;

class Singleton1
{
public:
  static Singleton1& getInstance(){
    return instance;
  }
private:
  Singleton1(){};
  Singleton1(const Singleton1&);
  static Singleton1 instance;
};
Singleton1 Singleton1::instance;

class Singleton2
{
public:
  //只有当需要这个单例对象的时候才创建
  static Singleton2& getInstance(){
    static Singleton2 instance;
    return instance;
  }
private:
  Singleton2(){};
  Singleton2(const Singleton2&);
};


int main()
{
  Singleton2* singleton1 = &Singleton2::getInstance();
  Singleton2* singleton2 = &Singleton2::getInstance();
  cout << (singleton1==singleton2) << '\n';
  return 0;
}
