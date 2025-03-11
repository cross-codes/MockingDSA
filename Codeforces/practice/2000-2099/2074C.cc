#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _C {

auto run() -> void {
  int x;
  std::cin >> x;

  if ((x & (x - 1)) == 0 || ((x + 1) & x) == 0) {
    std::println("-1");
    return;
  }

  if (x & 1) {
    int y = ((~x & ~(~x - 1)) << 1) - 1;
    if (y >= x)
      std::println("{}", -1);
    else
      std::println("{}", y);
  } else {
    int y = (x & ~(x - 1)) + 1;
    if (y >= x)
      std::println("{}", -1);
    else
      std::println("{}", y);
  }
}

}  // namespace _C

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};
  std::cin >> t;

  while (t-- > 0) _C::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
