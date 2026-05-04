#include <bits/stdc++.h>

#ifdef ANTUMBRA
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

namespace _263A {

auto run() -> void {
  ssize X = -1, Y = -1;
  int i;
  for (ssize y = 1; y <= 5; y++) {
    for (ssize x = 1; x <= 5; x++) {
      std::cin >> i;
      if (i == 1)
        X = x, Y = y;
    }
  }

  std::println("{}", std::abs(X - 3) + std::abs(Y - 3));
}

} // namespace _263A

int main() {
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t;
  t = 1;

  while (t-- > 0)
    _263A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
