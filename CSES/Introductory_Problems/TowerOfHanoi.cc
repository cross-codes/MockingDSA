#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

void move(const int &n, const int &from, const int &to, const int &via);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cout << (1 << n) - 1 << "\n";

  ::move(n, 1, 3, 2);

  return 0;
}

void move(const int &n, const int &from, const int &to, const int &via) {
  if (n == 0)
    return;
  move(n - 1, from, via, to);
  std::cout << from << " " << to << "\n";
  move(n - 1, via, to, from);
}
