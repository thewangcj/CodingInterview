#include <iostream>
using namespace std;
void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 冒泡排序
void bubble_sort(int data[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - 1 - i; j++)
        {
            if (data[j] > data[j + 1])
                Swap(&data[j], &data[j + 1]);
        }
    }
}

// 插入排序
void insert_sort(int data[], int length)
{
    for (int i = 1; i < length; i++)
    {
        int j = i - 1;
        int temp = data[i];
        while (j >= 0 && temp < data[j])
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = temp;
    }
}

// 选择排序
void select_sort(int data[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < length; j++)
        {
            if (data[j] < data[min])
                min = j;
        }
        int temp = data[i];
        data[i] = data[min];
        data[min] = temp;
    }
}

int main(int argc, char const *argv[])
{
    int test1[] = {5, 8, 1, 10, 3};
    for (int i : test1)
    {
        cout << i << ' ';
    }
    cout << endl;
    select_sort(test1, 5);
    for (int i : test1)
    {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}