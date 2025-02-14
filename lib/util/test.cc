#include "Array.hh"
#include <iostream>

int main() {
  int array[4] = {4, 6, 3, 6};
  std::sort(array, array + 4);

  std::cout << Array::indexBinarySearch(&array[2], &array[4], 6);
}
