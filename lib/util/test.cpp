#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include "./Array.hpp"
#include <iostream>

int main() {
  std::vector<int> vec = {1, 3, 4, 9, 11, 12, 12, 14};
  std::cout << Array::ternarySearch(vec, 0, vec.size(), 12) << "\n";
}
