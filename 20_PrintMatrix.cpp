#include <iostream>
using namespace std;

void PrintMatrixCircle(int ** numbers, int rows, int columns, int start_index) {
  int end_x = columns - start_index - 1;
  int end_y = rows - start_index -1;
  int i;
  for(i = start_index; i <= end_x; i++)
    cout<< numbers[start_index][i] << ' ';

  if(end_y > start_index) {
    for(i = start_index + 1; i <= end_y; i++)
      cout<< numbers[i][end_x]<< ' ';
  }

  if(end_x > start_index && end_y > start_index) {
    for(i = end_x - 1; i >= start_index; i--)
      cout<<numbers[end_y][i]<< ' ';
  }

  if(end_x > start_index && (end_y - 1) > start_index) {
    for(i = end_y - 1; i > start_index; i--)
      cout<<numbers[i][start_index]<< ' ';
  }
}

void PrintMatrix(int ** numbers, int rows, int columns) {
  if(numbers == NULL || rows <= 0 || columns <= 0) {
    cout << "invalid input" << endl;
    return;
  }

  int start_index = 0;
  while ((rows > start_index * 2) && (columns > start_index * 2)) {
    PrintMatrixCircle(numbers, rows, columns, start_index);
    start_index++;
  }
}

// ====================测试代码====================
void Test(int columns, int rows)
{
  printf("Test Begin: %d columns, %d rows.\n", columns, rows);

  if(columns < 1 || rows < 1)
    return;

  int** numbers = new int*[rows];
  for(int i = 0; i < rows; ++i)
  {
    numbers[i] = new int[columns];
    for(int j = 0; j < columns; ++j)
    {
      numbers[i][j] = i * columns + j + 1;
    }
  }
  // for(int i = 0; i < rows; ++i)
  // {
  //   for(int j = 0; j < columns; ++j)
  //   {
  //     cout<<numbers[i][j];
  //   }
  //   cout<<endl;
  // }
  // cout<<endl;
  PrintMatrix(numbers, rows, columns);
  printf("\n");

  for(int i = 0; i < rows; ++i)
    delete[] (int*)numbers[i];

  delete[] numbers;
}


int main(int argc, char const *argv[]) {
  /*
  1
  */
  Test(1, 1);

  /*
  1    2
  3    4
  */
  Test(2, 2);

  /*
  1    2    3    4
  5    6    7    8
  9    10   11   12
  13   14   15   16
  */
  Test(4, 4);

  /*
  1    2    3    4    5
  6    7    8    9    10
  11   12   13   14   15
  16   17   18   19   20
  21   22   23   24   25
  */
  Test(5, 5);

  /*
  1
  2
  3
  4
  5
  */
  Test(1, 5);

  /*
  1    2
  3    4
  5    6
  7    8
  9    10
  */
  Test(2, 5);

  /*
  1    2    3
  4    5    6
  7    8    9
  10   11   12
  13   14   15
  */
  Test(3, 5);

  /*
  1    2    3    4
  5    6    7    8
  9    10   11   12
  13   14   15   16
  17   18   19   20
  */
  Test(4, 5);

  /*
  1    2    3    4    5
  */
  Test(5, 1);

  /*
  1    2    3    4    5
  6    7    8    9    10
  */
  Test(5, 2);

  /*
  1    2    3    4    5
  6    7    8    9    10
  11   12   13   14    15
  */
  Test(5, 3);

  /*
  1    2    3    4    5
  6    7    8    9    10
  11   12   13   14   15
  16   17   18   19   20
  */
  Test(5, 4);
  return 0;
}
