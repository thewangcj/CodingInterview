#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

bool increment(char* number) {
  bool is_overflow = false;
  unsigned int carry = 0;
  unsigned int length = strlen(number);
  for (size_t i = length - 1; i >= 0; i--) {
    int sum = number[i] - '0' + carry;
    if(i == length - 1)
      sum++;
    if(sum >= 10){
      if(i == 0)
        is_overflow = true;
      else {
        sum -= 10;
        carry = 1;
        number[i] = '0' + sum;
      }
    } else {
      number[i] = '0' + sum;
      break;
    }
  }
  return is_overflow;
}

void print_number(const char* number) {
  bool is_beginning0 = true;
  unsigned int length = strlen(number);
  for (size_t i = 0; i < length; i++) {
    if( is_beginning0 && number[i] != '0') {
      is_beginning0 = false;
    }
    if( !is_beginning0) {
      cout<<number[i];
    }
  }
  cout<<'\t';
}

void print_to_max_ndigits1(int n) {
  if(n < 0) return;
  char* number = new char[n + 1];
  memset(number, '0', n);
  number[n] = '\0';
  while ( !increment(number)) {
    print_number(number);
  }

  delete []number;
}

void print_to_max_ndigits_re(char* number, int length, int index) {
  if(index == length - 1) {
    print_number(number);
    return;
  }
  for (size_t i = 0; i < 10; i++) {
    number[index + 1] = '0' + i;
    print_to_max_ndigits_re(number, length, index + 1);
  }

}

void print_to_max_ndigits2(int n) {
  if(n < 0) return;
  char* number = new char[n + 1];
  number[n] = '\0';
  for (size_t i = 0; i < 10; i++) {

    number[0] = '0' + i;
    print_to_max_ndigits_re(number, n, 0);
  }
  delete [] number;
}

int main(int argc, char const *argv[]) {
  print_to_max_ndigits2(3);
  print_to_max_ndigits2(-1);
  print_to_max_ndigits2(0);
  return 0;
}
