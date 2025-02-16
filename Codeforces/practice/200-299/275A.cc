#include <bits/stdc++.h>

#ifdef CROSS
#include "extras/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace _275A {

auto run() -> void {
  std::vector<std::vector<bool>> grid(3, std::vector<bool>(3, true));

  int i;
  for (ssize y = 0; y < 3; y++) {
    for (ssize x = 0; x < 3; x++) {
      std::cin >> i;
      if (i & 1) {
        grid[y][x] = !grid[y][x];
        if (x < 2)
          grid[y][x + 1] = !grid[y][x + 1];
        if (x > 0)
          grid[y][x - 1] = !grid[y][x - 1];
        if (y < 2)
          grid[y + 1][x] = !grid[y + 1][x];
        if (y > 0)
          grid[y - 1][x] = !grid[y - 1][x];
      }
    }
  }

  for (ssize y = 0; y < 3; y++) {
    for (ssize x = 0; x < 3; x++) {
      std::print("{}", grid[y][x] ? 1 : 0);
    }
    std::println();
  }
}

} // namespace _275A

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t = 1;

  while (t-- > 0)
    _275A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
