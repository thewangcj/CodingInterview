#include <stdexcept>
#include <iostream>
using namespace std;

int RandomInRange(int min, int max)
{
  int random = rand() % (max - min + 1) + min;
  return random;
}

void Swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int Partition(int data[], int length, int start, int end)
{
  if (data == nullptr || length <= 0 || start < 0 || end >= length)
    throw new invalid_argument("invalid parameters");
  int index = RandomInRange(start, end);
  Swap(&data[index], &data[end]);

  int small = start - 1;
  for (index = start; index < end; ++index)
  {
    if (data[index] < data[end])
    {
      ++small;
      if (small != index)
        Swap(&data[index], &data[small]);
    }
  }
  ++small; 
  Swap(&data[small], &data[end]);
  return small;
}

void QuickSort(int data[], int length, int start, int end)
{
  if (start == end)
    return;
  int index = Partition(data, length, start, end);
  if (index > start)
    QuickSort(data, length, start, index - 1);
  if (index < start)
    QuickSort(data, length, index + 1, end);
}

int main(int argc, char const *argv[])
{
  int test1[] = {5, 8, 1, 10, 3};
  for (int i : test1)
  {
    cout << i << ' ';
  }
  cout << endl;
  QuickSort(test1, 5, 0, 4);
  for (int i : test1)
  {
    cout << i << ' ';
  }
  cout << endl;
  return 0;
}
