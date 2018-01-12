#include <iostream>
bool FindInPartiallySoredMatrix(int* matrix, int row, int column, int dest) {
  bool is_found = false;
  if(matrix != NULL && row > 0 && column > 0){
    int current_row = 0;
    int current_column = column - 1;
    while (current_row < row && current_column > 0) {
      if (matrix[current_row * column + current_column] == dest) {
        is_found = true;
        break;
      } else if (matrix[current_row * column + current_column] > dest) {
        current_column--;
      } else {
        current_row++;
      }
    }
  }
  return is_found;
}

int main(int argc, char const *argv[]) {
  int matrix[4][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  std::cout << FindInPartiallySoredMatrix((int *)matrix,4,4,1) << '\n';
  std::cout << FindInPartiallySoredMatrix((int *)matrix,4,4,15) << '\n';
  std::cout << FindInPartiallySoredMatrix((int *)matrix,4,4,9) << '\n';
  std::cout << FindInPartiallySoredMatrix((int *)matrix,4,4,20) << '\n';
  std::cout << FindInPartiallySoredMatrix(NULL,4,4,1) << '\n';
  return 0;
}
