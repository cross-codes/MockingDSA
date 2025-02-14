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

namespace _2065B {

auto run() -> void {
  std::string input;
  std::cin >> input;

  usize n = input.size();

  for (usize i = 0; i < n - 1; i++) {
    if (input[i] == input[i + 1]) {
      std::println("{}", 1);
      return;
    }
  }

  std::println("{}", n);
}

} // namespace _2065B

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

  int t;
  std::cin >> t;

  while (t-- > 0)
    _2065B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
