#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _318A {

auto run() -> void {
  i64 n, k;
  std::cin >> n >> k;

  if (n & 1) {
    if (k > ((n + 1) >> 1))
      std::println("{}", (k - ((n + 1) >> 1)) << 1);
    else
      std::println("{}", (k << 1) - 1);
  } else {
    if (k > (n >> 1))
      std::println("{}", (k - (n >> 1)) << 1);
    else
      std::println("{}", (k << 1) - 1);
  }
}

}  // namespace _318A

int main() {
#ifdef ANTUMBRA
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

  while (t-- > 0) _318A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
