#include <ext/rope>
#include <iostream>

int main() {
  __gnu_cxx::rope<char> x;
  x.insert('2');

  std::cout << x << "\n";
}
