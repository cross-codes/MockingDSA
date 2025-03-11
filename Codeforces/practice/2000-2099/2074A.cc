#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _A {

auto run() -> void {
  int l, r, d, u;
  std::cin >> l >> r >> d >> u;

  if (l == r && d == u && l == d)
    std::println("Yes");
  else
    std::println("No");
}

}  // namespace _A

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

  while (t-- > 0) _A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
