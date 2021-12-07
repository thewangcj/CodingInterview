// 用两个栈实现队列
// 题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail
// 和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。
#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class MyQueue
{
public:
  MyQueue(void);
  ~MyQueue(void);
  void appendTail(const T &node);
  T deleteHead();

private:
  stack<T> stack1;
  stack<T> stack2;
};
template <typename T>
MyQueue<T>::MyQueue() {}
template <typename T>
MyQueue<T>::~MyQueue() {}

template <typename T>
void MyQueue<T>::appendTail(const T &node)
{
  stack1.push(node);
}

template <typename T>
T MyQueue<T>::deleteHead()
{
  if (stack2.size() <= 0)
  {
    while (stack1.size() > 0)
    {
      T data = stack1.top();
      stack1.pop();
      stack2.push(data);
    }
  }
  if (stack2.size() == 0)
  {
    std::cout << "queue is empty" << '\n';
    return 0;
  }
  T head = stack2.top();
  stack2.pop();
  return head;
}

int main(int argc, char const *argv[])
{
  MyQueue<int> queue;
  queue.appendTail(1);
  queue.appendTail(2);
  queue.appendTail(3);
  std::cout << queue.deleteHead() << '\n';
  std::cout << queue.deleteHead() << '\n';
  std::cout << queue.deleteHead() << '\n';
  std::cout << queue.deleteHead() << '\n';
  return 0;
}
