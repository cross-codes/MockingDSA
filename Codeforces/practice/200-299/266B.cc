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

namespace _266B {

auto run() -> void {
  usize n, t;
  std::cin >> n >> t;

  std::string input;
  std::cin >> input;

  while (t-- > 0) {
    for (usize i = 0; i < n - 1; i++) {
      if (input[i] == 'B' && input[i + 1] == 'G') {
        std::swap(input[i], input[i + 1]);
        i++;
      }
    }
  }

  std::println("{}", input);
}

} // namespace _266B

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
    _266B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
